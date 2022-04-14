#pragma once

// Ԥ����ͷ�ļ���Ϊ�˼ӿ�����ٶ�

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

// ����ϵͳ�ĺ���
#include <Windows.h>

// �Ƚ���Ҫ��ͷ�ļ�
#include "ui/ConsoleLog.h"

// �Զ����
#define DEBUG_LOG(fmt,...) ConsoleLog::Instance().addLog(fmt##"\n",__VA_ARGS__)

