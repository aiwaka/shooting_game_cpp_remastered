#pragma once

#include <Windows.h>
#include <string>

class Error
{
public:
    static void finish(std::string error_message, LPCTSTR lpsz_func_name, int line_num);
};
