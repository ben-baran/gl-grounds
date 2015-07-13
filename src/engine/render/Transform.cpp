#include "Transform.hpp"

Transform *Transform::rotate(double theta)
{

	return this;
}

Transform *Transform::scale(double scaleX, double scaleY)
{
	return this;
}

Transform *Transform::translate(double dx, double dy)
{
	return this;
}

Transform *Transform::multiply(Transform other)
{
	return this;
}

void Transform::attach(Transform parent)
{

}

Transform Transform::multiply(Transform a, Transform b)
{
	return Transform();
}
