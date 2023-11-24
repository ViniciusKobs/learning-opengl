#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <cmath>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>


class Camera
{
    public:
        Camera();
        ~Camera();

        void Update();
        void IncrementPos(glm::vec3 movement);
        void IncrementPitch(float p);
        void IncrementYaw(float y);

        glm::vec3 GetCamPos();
        glm::vec3 GetCamFront();
        glm::vec3 GetCamUp();
        float GetSpeed();
        float GetSens();

    protected:

    private:
        glm::vec3 camPos;
        glm::vec3 camFront;
        glm::vec3 camUp;
        float pitch;
        float yaw;
        float speed;
        float sens;

};

#endif // CAMERA_H
