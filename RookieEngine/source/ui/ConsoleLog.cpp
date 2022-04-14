#include "stdafx.h"

#include "ConsoleLog.h"

ConsoleLog::ConsoleLog()
{
    AutoScroll = true;
    clear();
}

ConsoleLog::~ConsoleLog()
{
}

ConsoleLog& ConsoleLog::Instance()
{
    static ConsoleLog instance;
    return instance;
}

void ConsoleLog::clear()
{
    Buf.clear();
    LineOffsets.clear();
    LineOffsets.push_back(0);
}

void ConsoleLog::addLog(const char* fmt, ...)
{
    // int old_size = Buf.size();
    va_list args;
    va_start(args, fmt);
    Buf.appendfv(fmt, args);
    va_end(args);
    //for (int new_size = Buf.size(); old_size < new_size; old_size++)
    //    if (Buf[old_size] == '\n')
    //        LineOffsets.push_back(old_size + 1);
}

void ConsoleLog::draw()
{
    if (!ImGui::Begin("ConsoleLog"))
    {
        ImGui::End();
        return;
    }

    ImGui::Text("console log:");
    ImGui::SameLine();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Separator();
    ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    //const char* buf = Buf.begin();
    //const char* buf_end = Buf.end();

    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    //ImGuiListClipper clipper;
    //clipper.Begin(LineOffsets.Size);
    //while (clipper.Step())
    //{
    //    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
    //    {
    //        const char* line_start = buf + LineOffsets[line_no];
    //        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
    //        ImGui::TextUnformatted(line_start, line_end);
    //    }
    //}
    //clipper.End();
    //ImGui::PopStyleVar();

    //if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    //    ImGui::SetScrollHereY(1.0f);

    ImGui::TextUnformatted(Buf.begin());
    ImGui::EndChild();

    ImGui::End();
}





