#pragma once

#include <DxLib.h>
#include "error.hpp"

#define APP_SYSTEM_ERROR(str) Error::finish(str, _T(__FUNCTION__), __LINE__)
