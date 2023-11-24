#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "window.h"
#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "util/types.h"

U32 WINDOW_HEIGHT = 800;
U32 WINDOW_WIDTH = 1000;

const char* VERTEX_SHADER_PATH = "assets/vsh.glsl";
const char* FRAGMENT_SHADER_PATH = "assets/fsh.glsl";

Camera* GLOBAL_CAM;
Window* GLOBAL_WINDOW;
glm::mat4* GLOBAL_PROJECTION;

void handleCameraMovement(Window* window, Camera* camera);
void framebufferCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorCallback(GLFWwindow *window, double xpos, double ypos);

int main() {
    bool success = true;
    Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, "learning opengl", &success); GLOBAL_WINDOW = &window;
    Renderer renderer = Renderer(&success);
    Shader shaderProgram = Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH, &success);
    if (!success) return -1;

    window.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window.SetFramebufferCallback(framebufferCallback);
    window.SetKeyCallback(keyCallback);
    window.SetCursorCallback(cursorCallback);

    std::vector<Mesh> meshes = createMeshes();

    for (U32 i = 0; i < meshes.size(); i++) {
        renderer.CreateObject(meshes[i]);
    }

    Camera camera = Camera(); GLOBAL_CAM = &camera;

    glm::mat4 view;
    glm::mat4 projection;

    //renderer.SetWireframeMode();

    while (!window.GetShouldClose()) {

        handleCameraMovement(&window, &camera);
        camera.Update();

        view = glm::lookAt(camera.GetCamPos(), camera.GetCamPos() + camera.GetCamFront(), camera.GetCamUp());
        renderer.SetViewMat(view);

        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 100.0f);
        renderer.SetProjectionMat(projection);

        renderer.Clear(0.0f, 0.0f, 0.1f, 1.0f);

        shaderProgram.Use();

        renderer.DrawObjects(shaderProgram.GetID());

        window.Update();
    }
}

void handleCameraMovement(Window* window, Camera* camera) {
    glm::vec3 camRight = glm::normalize(glm::cross(camera->GetCamFront(), camera->GetCamUp()));
    glm::vec3 realCamUp = glm::normalize(glm::cross(camRight, camera->GetCamFront()));
    float camSpeed = camera->GetSpeed() * window->GetDeltaTime();

    if (window->GetKey(GLFW_KEY_W) == GLFW_PRESS)
        camera->IncrementPos(camera->GetCamFront() * camSpeed);
    if (window->GetKey(GLFW_KEY_S) == GLFW_PRESS)
        camera->IncrementPos(camera->GetCamFront() * -camSpeed);


    if (window->GetKey(GLFW_KEY_D) == GLFW_PRESS)
        camera->IncrementPos(camRight * camSpeed);
    if (window->GetKey(GLFW_KEY_A) == GLFW_PRESS)
        camera->IncrementPos(camRight * -camSpeed);


    if (window->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->IncrementPos(realCamUp * camSpeed);
    if (window->GetKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->IncrementPos(realCamUp * -camSpeed);
}
void framebufferCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        GLOBAL_WINDOW->ToggleCursorCallback();
    }
}

void cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    if (GLOBAL_WINDOW->GetFirstMouse()) {
        GLOBAL_WINDOW->SetLastX(xpos);
        GLOBAL_WINDOW->SetLastY(ypos);
        GLOBAL_WINDOW->SetFirstMouse(false);
    }

    double lastX = GLOBAL_WINDOW->GetLastX();
    double lastY = GLOBAL_WINDOW->GetLastY();

    double xOffset = lastX - xpos;
    double yOffset = lastY - ypos;

    GLOBAL_CAM->IncrementPitch(static_cast<float>(xOffset) * GLOBAL_CAM->GetSens());
    GLOBAL_CAM->IncrementYaw(static_cast<float>(yOffset) * GLOBAL_CAM->GetSens());

    GLOBAL_WINDOW->SetLastX(xpos);
    GLOBAL_WINDOW->SetLastY(ypos);

}
