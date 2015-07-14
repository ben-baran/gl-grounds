#include "Camera.hpp"

Camera::Camera(double centerX, double centerY, double width, double height)
{
	inverseTransform.translate(centerX, centerY);
	inverseTransform.scale(width, -height);
	transformMatrix = glm::inverse(inverseTransform.getMatrix());
}

glm::mat4 Camera::getTransformMatrix()
{
	return transformMatrix;
}
