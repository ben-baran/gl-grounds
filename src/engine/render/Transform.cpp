#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 &Transform::getMatrix()
{
	if(changed) base = translateComponent * rotateComponent * scaleComponent;
	changed = false;

	if(!attached) return base;
	computed = parent->getMatrix() * parentOriginalInverse * base;
	return computed;
}

Transform &Transform::setRotation(double theta)
{
	return rotate(theta - this->theta);
}

Transform &Transform::setScale(double scaleX, double scaleY)
{
	return scale(scaleX / this->scaleX, scaleY / this->scaleY);
}

Transform &Transform::setTranslation(double dx, double dy)
{
	return translate(dx - this->dx, dy - this->dy);
}

Transform &Transform::rotate(double theta)
{
	this->theta += theta;
	changed = true;
	rotateComponent = glm::rotate(rotateComponent, (float) theta, glm::vec3(0, 0, 1));
	return *this;
}

Transform &Transform::scale(double scaleX, double scaleY)
{
	this->scaleX *= scaleX;
	this->scaleY *= scaleY;
	changed = true;
	scaleComponent = glm::scale(scaleComponent, glm::vec3(scaleX, scaleY, 1));
	return *this;
}

Transform &Transform::translate(double dx, double dy)
{
	this->dx += dx;
	this->dy += dy;
	changed = true;
	translateComponent = glm::translate(translateComponent, glm::vec3(dx, dy, 0));
	return *this;
}

void Transform::attach(Transform *parent)
{
	attached = false;
	getMatrix();

	attached = true;
	this->parent = parent;

	parentOriginalInverse = glm::inverse(parent->getMatrix());
}

void Transform::unattach()
{
	attached = false;
}
