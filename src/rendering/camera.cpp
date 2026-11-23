#include "../include/resin/rendering/camera.h"
#include <cmath>

Camera::Camera(QOpenGLFunctions_3_3_Core* gl, int width, int height, glm::vec3 position) : gl(gl)
{
    Camera::width = width;
    Camera::height = height;
    Position = position;
}

Camera::~Camera()
{

}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    if (height <= 0)
        return;

    view = glm::lookAt(Position, Pivot, WorldUp);
    projection = glm::perspective(glm::radians(FOVdeg), aspectRatio, nearPlane, farPlane);

    gl->glUniformMatrix4fv(gl->glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Resize(int width, int height)
{
    Camera::width = width;
    Camera::height = height;
}

/*
void Camera::Inputs(QSet<int> keys)
{
    // Handles key inputs
    if (keys.contains(Qt::Key_W))
    {
        Position += speed * Orientation;
    }

    if (keys.contains(Qt::Key_A))
    {
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }

    if (keys.contains(Qt::Key_S))
    {
        Position += speed * -Orientation;
    }

    if (keys.contains(Qt::Key_D))
    {
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }

    if (keys.contains(Qt::Key_E))
    {
        Position += speed * Up;
    }

    if (keys.contains(Qt::Key_Q))
    {
        Position += speed * -Up;
    }

    if (keys.contains(Qt::Key_Shift))
    {
        speed = 0.4f;
    }
    else
    {
        speed = 0.1f;
    }
}
*/

void Camera::MouseInputs(float mouseX, float mouseY)
{
    Yaw -= glm::radians(sensitivity * mouseX / width);
    Pitch += glm::radians(sensitivity * mouseY / height);

    float limit = glm::radians(85.0f);

    Pitch = glm::clamp(Pitch, -limit, limit);

    UpdateOrbit();
}

void Camera::MouseScroll(float scrollY){
    Distance -= scrollY * 0.5f;
    Distance = glm::clamp(Distance, 1.0f, 50.0f);

    UpdateOrbit();
}

void Camera::UpdateOrbit()
{
    glm::vec3 offset;

    glm::vec3 Right = glm::normalize(
        glm::cross(Orientation, WorldUp));

    offset.x = Distance * cos(Pitch) * sin(Yaw);
    offset.y = Distance * sin(Pitch);
    offset.z = Distance * cos(Pitch) * cos(Yaw);

    Position = Pivot + offset;

    Orientation = glm::normalize(glm::cross(Orientation, Up));
}