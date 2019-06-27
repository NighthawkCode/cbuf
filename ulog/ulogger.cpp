#include "ulogger.h"
#include <mutex>
#include "vlog.h"
#include <unistd.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <memory.h>

// stat() check if directory exists
static  
bool directory_exists( const char* dirpath )
{
  struct stat status;
  if( stat( dirpath, &status ) == 0 && S_ISDIR( status.st_mode ) ) {  
    return true;
  }
  return false;
}


ULogger::ULogger()
{
}

ULogger::~ULogger()
{
}

/// Return the allocated memory to our pool
void ULogger::freeBuffer(void *buffer)
{
  // For now, just a free
  free(buffer);
}

void ULogger::fillFilename()
{
  time_t rawtime;
  struct tm *info;
  time( &rawtime );
  info = localtime( &rawtime );

  char buffer[PATH_MAX];
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "vdnt.%d.%d.%d.%d.%d.%d.ulog",
          info->tm_year + 1900, info->tm_mon, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);

  if( !outputdir.empty() ) {
    filename = outputdir + "/" + buffer;
  }
  else {
    filename = buffer;
  }
}

void ULogger::setOutputDir(const char* outdir)
{
  if( directory_exists( outdir ) ) {
    outputdir = outdir;
  }
}



// Process packet here:
// Check the dictionary if needed for metadata
// Write the packet otherwise
void ULogger::processPacket(PacketQueue& pq)
{
  cbuf_preamble *pre = (cbuf_preamble *)pq.data;
  if (cos.dictionary.count(pre->hash) == 0) {
      cos.serialize_metadata(pq.metadata, pre->hash, pq.type_name);
  }

  write(cos.stream, pq.data, pq.size);

  freeBuffer(pq.data);
}

bool ULogger::initialize()
{
  loggerThread = new std::thread(
        [this]()
  {
    while(logging) {
      PacketQueue pq;
      if (packetQueue.empty()) {
        usleep(1000);
        continue;
      }

      {
        std::lock_guard<std::mutex> guard(mutexQueue);
        pq = packetQueue.front();
        packetQueue.pop();
      }

      processPacket(pq);
    }

    // Continue processing the queue until it is empty
    {
      std::lock_guard<std::mutex> guard(mutexQueue);
      while(!packetQueue.empty()) {
        PacketQueue pq = packetQueue.front();
        processPacket(pq);
        packetQueue.pop();
      }
    }

    cos.close();
  });
  return true;
}

static std::mutex g_ulogger_mutex;
static bool initialized = false;
static ULogger* g_ulogger = nullptr;

bool ULogger::isInitialized()
{
    return initialized;
}

// No public constructors, this is a singleton
ULogger* ULogger::getULogger()
{
  if (!initialized) {
    std::lock_guard<std::mutex> guard(g_ulogger_mutex);

    g_ulogger = new ULogger();

    g_ulogger->fillFilename();

    // Open the serialization file
    bool bret = g_ulogger->cos.open_file(g_ulogger->filename.c_str());
    if (!bret) {
      vlog_fatal(VCAT_GENERAL, "Could not open the ulog file for logging");
      delete g_ulogger;
      return nullptr;
    }

    bret = g_ulogger->initialize();
    if (!bret) {
      vlog_fatal(VCAT_GENERAL, "Could not initialize ulogger singleton");
      delete g_ulogger;
      return nullptr;
    }

    // Do any extra initialization needed here
    initialized = true;
  }
  return g_ulogger;
}

/// function to stop all logging, threads, and terminate the app
void ULogger::endLogging()
{
    logging = false;
    loggerThread->join();
    delete loggerThread;
    loggerThread = nullptr;
    initialized = false;
}

/// Functions to get memory and queue packets for logging
void *ULogger::getBuffer(unsigned int size)
{
  // change me:
  return malloc(size);
}

void ULogger::queuePacket(void *data, unsigned int size, const char *metadata, const char *type_name)
{
  std::lock_guard<std::mutex> guard(mutexQueue);
  packetQueue.emplace( metadata, type_name, data, size );
}
