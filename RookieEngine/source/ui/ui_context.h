#include "window/Iwindow.h"

class UIContext 
{
public:
    bool init(Iwindow* window);
    void pre_render();
    void post_render();
    void end();
protected:
    Iwindow* mWindow;
};