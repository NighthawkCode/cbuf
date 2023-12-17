#include "toolbox/hjson_helper.h"

#include <errno.h>
#include <math.h>
#include <string.h>

#include <cmath>

bool has_member(const Hjson::Value& doc, const std::string& objName) {
  auto v = doc[objName];
  if (!v.defined()) {
    return false;
  }
  return true;
}

bool get_member_int(const Hjson::Value& doc, const std::string& objName, int8_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = int8_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int8_t(o.operator char());
    return true;
  }
  return false;
}

bool get_member_int(const Hjson::Value& doc, const std::string& objName, int16_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = int16_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int16_t(o);
    return true;
  }
  return false;
}

bool get_member_int(const Hjson::Value& doc, const std::string& objName, int32_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = std::atoi(o);
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int32_t(o);
    return true;
  }
  return false;
}

bool get_member_int(const Hjson::Value& doc, const std::string& objName, int64_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = std::atoll(o);
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int64_t(o);
    return true;
  }
  return false;
}

bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint8_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint8_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint8_t(o);
    return true;
  }
  return false;
}

bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint16_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint16_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint16_t(o);
    return true;
  }
  return false;
}

bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint32_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint32_t(std::atoll(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint32_t(o);
    return true;
  }
  return false;
}

bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint64_t& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint64_t(std::atoll(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint64_t(o);
    return true;
  }
  return false;
}

bool get_member_float(const Hjson::Value& doc, const std::string& objName, float& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = float(std::atof(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = float(o);
    return true;
  }
  return false;
}

bool get_member_double(const Hjson::Value& doc, const std::string& objName, double& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = std::atof(o);
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = o;
    return true;
  }
  return false;
}

bool get_member_bool(const Hjson::Value& doc, const std::string& objName, bool& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = o == std::string("true");
    return true;
  } else if (o.type() == Hjson::Type::Bool) {
    val = o.operator bool();
    return true;
  }
  return false;
}

bool get_member_bool_relaxed(const Hjson::Value& doc, const std::string& objName, bool& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = o == std::string("true");
    return true;
  } else if (o.type() == Hjson::Type::Bool) {
    val = o.operator bool();
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = !(std::floor(o.operator double()) == 0);
    return true;
  }
  return false;
}

bool get_member_string(const Hjson::Value& doc, const std::string& objName, std::string& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = o.operator std::string();
    return true;
  }
  return false;
}

bool get_value_int(const Hjson::Value& o, int8_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = int8_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int8_t(o.operator char());
    return true;
  }
  return false;
}

bool get_value_int(const Hjson::Value& o, int16_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = int16_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int16_t(o);
    return true;
  }
  return false;
}

bool get_value_int(const Hjson::Value& o, int32_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = std::atoi(o);
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int32_t(o);
    return true;
  }
  return false;
}

bool get_value_int(const Hjson::Value& o, int64_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = std::atoll(o);
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = int64_t(o);
    return true;
  }
  return false;
}

bool get_value_uint(const Hjson::Value& o, uint8_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint8_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint8_t(o);
    return true;
  }
  return false;
}

bool get_value_uint(const Hjson::Value& o, uint16_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint16_t(std::atoi(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint16_t(o);
    return true;
  }
  return false;
}

bool get_value_uint(const Hjson::Value& o, uint32_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint32_t(std::atoll(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint32_t(o);
    return true;
  }
  return false;
}

bool get_value_uint(const Hjson::Value& o, uint64_t& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = uint64_t(std::atoll(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = uint64_t(o);
    return true;
  }
  return false;
}

bool get_value_float(const Hjson::Value& o, float& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = float(std::atof(o));
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = float(o);
    return true;
  }
  return false;
}

bool get_value_double(const Hjson::Value& o, double& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = std::atof(o);
    return true;
  } else if (o.type() == Hjson::Type::Double) {
    val = o;
    return true;
  }
  return false;
}

bool get_value_bool(const Hjson::Value& o, bool& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = o == std::string("true");
    return true;
  } else if (o.type() == Hjson::Type::Bool) {
    val = o.operator bool();
    return true;
  }
  return false;
}

bool get_value_string(const Hjson::Value& o, std::string& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::String) {
    val = o.operator std::string();
    return true;
  }
  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<int8_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_int(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<int16_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_int(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<int32_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_int(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<int64_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_int(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<uint8_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_uint(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<uint16_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_uint(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<uint32_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_uint(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<uint64_t>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_uint(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<float>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_float(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<double>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_double(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_bool_deque(const Hjson::Value& o, std::deque<bool>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_bool(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_value_vector(const Hjson::Value& o, std::vector<std::string>& val) {
  if (!o.defined()) {
    return false;
  }

  if (o.type() == Hjson::Type::Vector) {
    size_t len = o.size();
    val.resize(len);

    bool is_value_extracted = false;
    for (size_t i = 0; i < len; ++i) {
      is_value_extracted = get_value_string(o[int(i)], val[i]);
      if (!is_value_extracted) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int8_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int16_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int32_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int64_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint8_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint16_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint32_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint64_t>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<float>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<double>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}

bool get_member_bool_deque(const Hjson::Value& doc, const std::string& objName, std::deque<bool>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_bool_deque(o, val);
  return success;
}

bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<std::string>& val) {
  auto o = doc[objName];
  if (!o.defined()) {
    return false;
  }

  bool success = get_value_vector(o, val);
  return success;
}
