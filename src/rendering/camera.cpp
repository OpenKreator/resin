#include "../include/resin/rendering/camera.h"

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

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)(width/height), nearPlane, farPlane);

    gl->glUniformMatrix4fv(gl->glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

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

void Camera::MouseInputs(float mouseX, float mouseY)
{
    float rotX = sensitivity * mouseY / height;
    float rotY = sensitivity * mouseX / width;

    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

    // Stop camera from rotating too far up  or down
    if(abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f)){
        Orientation = newOrientation;
    }

    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
}