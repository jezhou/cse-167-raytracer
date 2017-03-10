#include "Camera.h"
#include "variables.h"

Camera::Camera(glm::vec3 e, glm::vec3 c, glm::vec3 up, float f) {

  eye = e;
  fov = f;

  w = glm::normalize(e);
  u = glm::cross(up, w);
  u = glm::normalize(u);
  v = glm::cross(w, u);

  glm::mat4 r = glm::mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0,
                          u.z, v.z, w.z, 0, 0, 0, 0, 1);

  glm::mat4 t = glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,
											   c.x - e.x, c.y - e.y, c.z - e.z, 1);

  camera = r * t;

}

void Camera::generateRay(Sample& sample, Ray * ray) {

  float alpha = glm::tan(fov/2) * ((sample.x - (width / 2)) / (width /2));
  float beta = glm::tan(fov/2) * (((height/2) - sample.y) / (height/2));

  glm::vec3 ab_vec = glm::normalize(alpha * u + beta * v - w);

  ray->dir = eye - ab_vec;
  ray->pos = glm::vec3(sample.x, sample.y, 0);

}
