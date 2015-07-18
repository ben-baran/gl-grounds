#include "Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

glm::mat4 &Transform::getMatrix()
{
	if(animList.size() != 0)
	{
		Animation *curAnim = animList.front();
		double time = glfwGetTime();
		while(animList.size() > 0 && time > curAnim->initialTime + curAnim->duration)
		{
			curAnim->yield(curAnim->duration, *this);
			animList.erase(animList.begin());
			curAnim = animList.front();
		}
		if(time > curAnim->initialTime)
		{
			curAnim->yield(time - curAnim->initialTime, *this);
		}
	}
	if(changed) base = translateComponent * rotateComponent * scaleComponent;
	changed = false;

	if(!attached) return base;
	computed = parent->getMatrix() * parentOriginalInverse * base;
	return computed;
}

double Transform::getTheta()
{
	return theta;
}

double Transform::getScaleX()
{
	return scaleX;
}

double Transform::getScaleY()
{
	return scaleY;
}

double Transform::getDX()
{
	return dx;
}

double Transform::getDY()
{
	return dy;
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
	return *this;
}

Transform &Transform::rotate(double theta)
{
	this->theta += theta;
	changed = true;
	rotateComponent = glm::rotate(rotateComponent, (float) theta, glm::vec3(0, 0, 1));
	return *this;
}

Transform &Transform::scaleInX(double scaleX)
{
	return scale(scaleX, 1);
}

Transform &Transform::scaleInY(double scaleY)
{
	return scale(1, scaleY);
}

Transform &Transform::scale(double scaleX, double scaleY)
{
	this->scaleX *= scaleX;
	this->scaleY *= scaleY;
	changed = true;
	scaleComponent = glm::scale(scaleComponent, glm::vec3(scaleX, scaleY, 1));
	return *this;
}

Transform &Transform::translateX(double dx)
{
	return translate(dx, 0);
}

Transform &Transform::translateY(double dy)
{
	return translate(0, dy);
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

Transform::Animation &Transform::queueAnimation(double duration, double (*animFunc)(double))
{
	double curTime;
	if(animList.size() != 0) curTime = animList.back()->initialTime + animList.back()->duration;
	else curTime = glfwGetTime();
	
	Animation *anim = new Animation(curTime, duration, animFunc);
	animList.push_back(anim);
	return *anim;
}

Transform::Animation::Animation(double initialTime, double duration, double (*animFunc)(double))
{
	this->initialTime = initialTime;
	lastValue = 0;
	this->duration = duration;
	this->animFunc = animFunc;
}

Transform::Animation &Transform::Animation::addComponent(double target, Transform &(Transform::* component)(double))
{
	components.push_back(std::make_pair(target, component));
	return *this;
}

void Transform::Animation::yield(double time, Transform &transform)
{
	time /= duration;
	double value = animFunc(time), difference = value - lastValue;

	for(auto &component : components) (transform.*(component.second))(component.first * difference);
	lastValue = value;
}
