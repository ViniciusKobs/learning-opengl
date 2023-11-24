#include "window.h"

Window::Window(U32 width, U32 height, const char* title, bool* success)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    cursorCallbackActive = false;
    GLFWcursorposfun cursorCallbackPtr = nullptr;
    firstMousePos = true;
    lastXPos = static_cast<double>(width) / 2;
    lastYPos = static_cast<double>(height) / 2;

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        *success = false;
    } else {
        glfwMakeContextCurrent(window);
    }
}

Window::~Window()
{
    glfwTerminate();
}

void Window::Update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwSwapBuffers(window);
    glfwPollEvents();
}
void Window::ToggleCursorCallback() {
    if (cursorCallbackActive) {
        cursorCallbackActive = false;
        glfwSetCursorPosCallback(window, nullptr);
        SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        cursorCallbackActive = true;
        glfwSetCursorPosCallback(window, cursorCallbackPtr);
        SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstMousePos = true;
    }
}

void Window::SetInputMode(int mode, int value) {
    glfwSetInputMode(window, mode, value);
};
void Window::SetFramebufferCallback(GLFWframebuffersizefun callback){
    glfwSetFramebufferSizeCallback(window, callback);
}
void Window::SetCursorCallback(GLFWcursorposfun callback){
    cursorCallbackActive = true;
    cursorCallbackPtr = callback;
    glfwSetCursorPosCallback(window, callback);
}
void Window::SetScrollCallback(GLFWscrollfun callback){
    glfwSetScrollCallback(window, callback);
}
void Window::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(window, callback);
}
void Window::SetShouldClose() {
    glfwSetWindowShouldClose(window, true);
}
void Window::SetFirstMouse(bool b) {
    firstMousePos = b;
}
void Window::SetLastX(double x) {
    lastXPos = x;
}
void Window::SetLastY(double y) {
    lastYPos = y;
}

GLFWwindow* Window::GetWindow() {
    return window;
}
int Window::GetShouldClose() {
    return glfwWindowShouldClose(window);
}
int Window::GetKey(int key) {
    return glfwGetKey(window, key);
}
float Window::GetDeltaTime() {
    return deltaTime;
}
bool Window::GetFirstMouse() {
    return firstMousePos;
}
double Window::GetLastX() {
    return lastXPos;
}
double Window::GetLastY() {
    return lastYPos;
}
