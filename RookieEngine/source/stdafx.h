#pragma once

// 预编译头文件，为了加快编译速度

// std
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

// opengl
#include <glad/glad.h>
#include <glfw/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// 操作系统的函数
#include <Windows.h>

// 比较重要的头文件
#include "ui/ConsoleLog.h"

// 自定义宏
#define DEBUG_LOG(fmt,...) ConsoleLog::Instance().addLog(fmt##"\n",__VA_ARGS__)

