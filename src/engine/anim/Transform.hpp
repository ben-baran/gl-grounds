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
		double lastTime;
	public:

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
	Transform &scale(double scaleX, double scaleY);
	Transform &translate(double dx, double dy);
	void attach(Transform *parent); //always follows another transform
	void unattach();
};
