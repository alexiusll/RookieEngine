#pragma once
#include "imgui.h"

// ʹ�õ���ģʽ
// https://github.com/downdemo/Design-Patterns-in-Cpp17/blob/master/src/Singleton.cpp

class ConsoleLog
{
public:
	static ConsoleLog& Instance();

	ConsoleLog(const ConsoleLog&) = delete;
	ConsoleLog& operator=(const ConsoleLog&) = delete;

	void draw();
	void clear();
	void addLog(const char* fmt, ...);

private:
	// ��Ϊ˽��
	ConsoleLog();
	~ConsoleLog();

	ImGuiTextBuffer     Buf;
	bool                AutoScroll;
	ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
};

