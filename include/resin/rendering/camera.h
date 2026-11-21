#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_3_3_Core>
#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>
#include <../include/glm/gtx/rotate_vector.hpp>
#include <../include/glm/gtx/vector_angle.hpp>
#include <QSet>
#include <QKeyEvent>

#include "shaderclass.h"

class Camera
{
public:
    Camera(QOpenGLFunctions_3_3_Core* gl, int width, int height, glm::vec3 position);
    ~Camera();

    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    float speed = 0.1f;
    float sensitivity = 100.0f;

    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Inputs(QSet<int> keys);
    void MouseInputs(float mouseX, float mouseY);

private:
    QOpenGLFunctions_3_3_Core* gl;
};

#endif // CAMERA_H