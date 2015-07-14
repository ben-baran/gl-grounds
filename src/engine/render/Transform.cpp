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
	changed = true;
	this->theta = theta;
	rotateComponent = glm::rotate(glm::mat4(), (float) theta, glm::vec3(0, 0, 1));
	return *this;
}

Transform &Transform::setScale(double scaleX, double scaleY)
{
	changed = true;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	scaleComponent = glm::scale(glm::mat4(), glm::vec3(scaleX, scaleY, 1));
	return *this;
}

Transform &Transform::setTranslation(double dx, double dy)
{
	changed = true;
	this->dx = dx;
	this->dy = dy;
	translateComponent = glm::translate(glm::mat4(), glm::vec3(dx, dy, 0));
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
