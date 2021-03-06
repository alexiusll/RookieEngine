#pragma once
class Iwindow
{
public:
    virtual void on_scroll(double xoffset, double yoffset) = 0;

    virtual void on_cursor_pos(double xpos, double ypos) = 0;

    // virtual void on_key(int key, int scancode, int action, int mods) = 0;

    virtual void on_resize(int width, int height) = 0;

    virtual void on_close() = 0;

    virtual GLFWwindow* get_native_window() = 0;

    virtual void set_native_window(GLFWwindow* window) = 0;

    int Width;
    int Height;
    std::string Title;
};