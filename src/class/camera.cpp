#include "camera.h"

Camera::Camera() {
    camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    pitch = 90.0f;
    yaw = 0.0f;
    speed = 2.0f;
    sens = 0.1f;
}

Camera::~Camera() {
    //dtor
}

void Camera::Update() {
    float pitchRad = glm::radians(pitch);
    float yawRad = glm::radians(yaw);

    camFront = glm::normalize(glm::vec3(std::cos(pitchRad) * std::cos(yawRad), std::sin(yawRad), -std::sin(pitchRad) * std::cos(yawRad)));
}

void Camera::IncrementPos(glm::vec3 movement) {
    camPos = camPos + movement;
}

void Camera::IncrementPitch(float p) {
    if (pitch + p > 360.0f) {
        pitch = (pitch + p) - 360.0f;
    } else {
        pitch += p;
    }
}

void Camera::IncrementYaw(float y) {
    if (yaw + y > 89) {
        yaw = 89;
    } else if (yaw + y < -89) {
        yaw = -89;
    } else {
        yaw += y;
    }
}

glm::vec3 Camera::GetCamPos() {
    return camPos;
}

glm::vec3 Camera::GetCamFront() {
    return camFront;
}

glm::vec3 Camera::GetCamUp() {
    return camUp;
}

float Camera::GetSpeed() {
    return speed;
}

float Camera::GetSens() {
    return sens;
}
