#include "Camera.hpp"

Camera::Camera(double centerX, double centerY, double width, double height)
{
	inverseTransform.translate(centerX, centerY);
	inverseTransform.scale(width, -height);
	transformMatrix = glm::inverse(inverseTransform.getMatrix());
}

Transform &Camera::getInverseTransform()
{
	return inverseTransform;
}

glm::mat4 &Camera::getTransformMatrix()
{
	transformMatrix = glm::inverse(inverseTransform.getMatrix());
	return transformMatrix;
}
