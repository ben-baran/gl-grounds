#pragma once

#include <glm/glm.hpp>
#include <queue>

class Transform
{
private:
	double theta, scaleX, scaleY, dx, dy;

	bool attached = false, changed = false;
	glm::mat4 base, scaleComponent, rotateComponent, translateComponent;
	Transform *parent;
	glm::mat4 parentOriginalInverse, computed;

	std::queue<Animation> animQueue;

	struct Animation
	{
	private:
		double duration, lastTime;
		double (* animFunc)(double);
		std::vector<std::pair<double, Transform &(Transform::*)(double)>> components;
	public:
		Animation(double duration, double (* animFunc)(double));
		Animation &addComponent(double target, Transform &(Transform::* component)(double));
	};
public:
	glm::mat4 &getMatrix();

	double getTheta();
	double getScaleX();
	double getScaleY();
	double getDX();
	double getDY();

	Transform &setRotation(double theta);
	Transform &setScale(double scaleX, double scaleY);
	Transform &setTranslation(double dx, double dy);

	Transform &rotate(double theta);
	Transform &scaleInX(double scaleX);
	Transform &scaleInY(double scaleY);
	Transform &scale(double scaleX, double scaleY);
	Transform &translateX(double dx);
	Transform &translateY(double dy);
	Transform &translate(double dx, double dy);
	void attach(Transform *parent); //always follows another transform
	void unattach();

	Animation &queueAnimation(double target, double (* animFunc)(double));
};
