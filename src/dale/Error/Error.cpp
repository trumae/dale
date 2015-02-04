#include "Error.h"

#include <cstdio>
#include <cstdlib>
#include "../ErrorType/ErrorType.h"

namespace dale
{
Error::Error(int instance,
             Node *node)
{
    init(instance, node);
}

Error::Error(int instance,
             Node *node,
             const char *str1)
{
    init(instance, node);
    arg_strings.push_back(str1);
}

Error::Error(int instance,
             Node *node,
             const char *str1,
             int num1,
             int num2)
{
    init(instance, node);
    arg_strings.push_back(str1);

    char buf[100];
    sprintf(buf, "%d", num1);
    arg_strings.push_back(buf);
    sprintf(buf, "%d", num2);
    arg_strings.push_back(buf);
}

Error::Error(int instance,
             Node *node,
             int num1,
             int num2)
{
    init(instance, node);

    char buf[100];
    sprintf(buf, "%d", num1);
    arg_strings.push_back(buf);
    sprintf(buf, "%d", num2);
    arg_strings.push_back(buf);
}

Error::Error(int instance,
             Node *node,
             const char *str1,
             const char *str2)
{
    init(instance, node);

    arg_strings.push_back(str1);
    arg_strings.push_back(str2);
}

Error::Error(int instance,
             Node *node,
             const char *str1,
             const char *str2,
             const char *str3)
{
    init(instance, node);

    arg_strings.push_back(str1);
    arg_strings.push_back(str2);
    arg_strings.push_back(str3);
}

Error::Error(int instance,
             Node *node,
             const char *str1,
             const char *str2,
             const char *str3,
             const char *str4)
{
    init(instance, node);

    arg_strings.push_back(str1);
    arg_strings.push_back(str2);
    arg_strings.push_back(str3);
    arg_strings.push_back(str4);
}

Error::~Error()
{
}

int Error::getType(void)
{
    return errorInstanceToType(instance);
}

void Error::init(int instance, Node *node)
{
    setFromNode(node);
    this->instance = instance;
}

void Error::setFromNode(Node *node)
{
    filename = node->filename;

    node->getBeginPos()->copyTo(&begin);
    node->getEndPos()->copyTo(&end);

    if (node->macro_begin.getLineNumber()) {
        macro_begin.setLineAndColumn(node->macro_begin.getLineNumber(),
                                     node->macro_begin.getColumnNumber());
        macro_end.setLineAndColumn(node->macro_end.getLineNumber(),
                                   node->macro_end.getColumnNumber());
    } else {
        macro_begin.setLineAndColumn(0,0);
        macro_end.setLineAndColumn(0,0);
    }
}

void Error::addArgString(std::string *str)
{
    arg_strings.push_back(*str);
}

void Error::addArgString(const char *str)
{
    arg_strings.push_back(str);
}

void Error::toString(std::string *to)
{
    char msg_buf[256];
    char final_buf[256];
    char macro_buf[256];

    const char *type_string  = errorTypeToString(getType());
    const char *main_err_str = errorInstanceToString(instance);

    if (arg_strings.size() == 0) {
        sprintf(msg_buf, main_err_str);
    } else if (arg_strings.size() == 1) {
        sprintf(msg_buf, main_err_str, arg_strings[0].c_str());
    } else if (arg_strings.size() == 2) {
        sprintf(msg_buf, main_err_str, arg_strings[0].c_str(),
                                       arg_strings[1].c_str());
    } else if (arg_strings.size() == 3) {
        sprintf(msg_buf, main_err_str, arg_strings[0].c_str(),
                                       arg_strings[1].c_str(),
                                       arg_strings[2].c_str());
    } else if (arg_strings.size() == 4) {
        sprintf(msg_buf, main_err_str, arg_strings[0].c_str(),
                                       arg_strings[1].c_str(),
                                       arg_strings[2].c_str(),
                                       arg_strings[3].c_str());
    } else {
        fprintf(stderr,
                "Internal error: too many argument strings (>4) "
                "in the error.\n");
        abort();
    }

    if (macro_begin.getLineNumber() != 0) {
        sprintf(macro_buf, " (see macro at %d:%d)",
                macro_begin.getLineNumber(),
                macro_begin.getColumnNumber());
    } else {
        macro_buf[0] = '\0';
    }

    sprintf(final_buf,
            "%s:%d:%d: %s: %s%s",
            filename,
            begin.getLineNumber(),
            begin.getColumnNumber(),
            type_string,
            msg_buf,
            macro_buf);

    to->append(final_buf);
}
}
