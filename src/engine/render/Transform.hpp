#pragma once

#include <glm/glm.hpp>

class Transform
{
private:
	bool attached = false, changed = false;
	glm::mat4 base;
	Transform *parent;
	glm::mat4 preposition, baseOriginalInverse, computed;

public:
	glm::mat4 &getMatrix();

	Transform &rotate(float theta);
	Transform &scale(double scaleX, double scaleY);
	Transform &translate(double dx, double dy);
	void attach(Transform *parent); //always follows another transform
	void unattach();
};
