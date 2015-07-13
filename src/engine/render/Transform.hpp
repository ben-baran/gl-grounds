#pragma once

#include <glm/glm.hpp>

class Transform
{
private:
	glm::mat4 base;
	glm::mat4 *parent;

public:
	Transform *rotate(double theta);
	Transform *scale(double scaleX, double scaleY);
	Transform *translate(double dx, double dy);
	Transform *multiply(Transform other); //multiplies internally and returns self
	void attach(Transform parent); //always follows another transform

	static Transform multiply(Transform a, Transform b); //multiplies externally
};
