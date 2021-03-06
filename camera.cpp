#include <iostream>
#include <GLFW/glfw3.h>
#include "camera.h"

using namespace std;

void Camera::processKeyboardInput(bool keys[], GLfloat deltaTime) {
  GLfloat cameraSpeed = 25.0f * deltaTime;

  if (keys[GLFW_KEY_W]){
    cameraPos += cameraSpeed * cameraFront;
  }
  if (keys[GLFW_KEY_S]) {
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (keys[GLFW_KEY_A]) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
  if (keys[GLFW_KEY_D]) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
}

void Camera::processMousePosition(GLfloat mouseX, GLfloat mouseY) {
  if (firstMouse) {
    lastX = mouseX;
    lastY = mouseY;
    firstMouse = false;
  }

  GLfloat xOffset = mouseX - lastX;
  GLfloat yOffset = lastY - mouseY;
  lastX = mouseX;
  lastY = mouseY;

  GLfloat sensitivity = 0.05f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  yaw += xOffset;
  pitch += yOffset;

  if (pitch > 89.0f) {
    pitch = 89.0f;
  }

  if (pitch < -89.0f) {
    pitch = -89.0f;
  }
}

void Camera::Print(void) {
  cout << "Camera position:" << endl;
  cout << "CameraPos: (" << cameraPos[0] << ", " << cameraPos[1] << ", " << cameraPos[2] << ")" << endl;
  cout << "CameraFront: (" << cameraFront[0] << ", " << cameraFront[1] << ", " << cameraFront[2] << ")" << endl;
  cout << "CameraUp: (" << cameraUp[0] << ", " << cameraUp[1] << ", " << cameraUp[2] << ")" << endl;
  cout << endl;
}

glm::mat4 Camera::getView(void) {
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  cameraFront = glm::normalize(front);

  return glm::lookAt(cameraPos,
                     cameraPos + cameraFront,
                     cameraUp);
}
