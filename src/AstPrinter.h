#pragma once

#include "ast.h"
#include "StringBuffer.h"
#include <map>

class AstPrinter
{
    StringBuffer *buffer;
    std::map<void *, int> printed_types;

    void print_elem(ast_element *elem);
    void print_struct(ast_struct *st);
    void print_channel(ast_channel *cn);
    void print_namespace(ast_namespace *sp);

  public:
    AstPrinter();
    ~AstPrinter();

    void print_ast(StringBuffer *buf, ast_global *ast);
    void print_ast(StringBuffer *buf, ast_struct *ast);
    void print_ast(StringBuffer *buf, ast_element *elem);
};
