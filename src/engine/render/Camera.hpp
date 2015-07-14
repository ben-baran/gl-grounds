#pragma once

#include "Transform.hpp"

class Camera
{
private:
	Transform inverseTransform;
	glm::mat4 transformMatrix;
public:
	Camera(double centerX, double centerY, double width, double height);
	Transform &getInverseTransform();
	glm::mat4 &getTransformMatrix();
};