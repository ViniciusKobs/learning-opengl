#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>

#include "types.h"

class Window
{
    public:
        Window(U32 width, U32 height, const char* title, bool* success);
        ~Window();

        void Update();
        void ToggleCursorCallback();

        GLFWwindow* GetWindow();
        int GetKey(int key);
        int GetShouldClose();
        float GetDeltaTime();
        bool GetFirstMouse();
        double GetLastX();
        double GetLastY();

        void SetInputMode(int mode, int value);
        void SetFramebufferCallback(GLFWframebuffersizefun callback);
        void SetCursorCallback(GLFWcursorposfun callback);
        void SetScrollCallback(GLFWscrollfun callback);
        void SetKeyCallback(GLFWkeyfun callback);
        void SetShouldClose();
        void SetFirstMouse(bool b);
        void SetLastX(double x);
        void SetLastY(double y);

    protected:

    private:
        GLFWwindow* window;
        bool cursorCallbackActive;
        GLFWcursorposfun cursorCallbackPtr;
        float deltaTime;
        float lastFrame;
        bool firstMousePos;
        double lastXPos;
        double lastYPos;
};

#endif // WINDOW_H
