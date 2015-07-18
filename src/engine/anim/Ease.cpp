#include "Ease.hpp"

double Ease::linear(double time)
{
	return time;
}

double Ease::quadraticIn(double time)
{
	return time * time;
}

double Ease::quadraticOut(double time)
{
	return -time * (time - 2);
}

double Ease::quadraticInOut(double time)
{
	if((time *= 2) < 1) return 0.5 * time * time;
	return -0.5 * ((--time) * (time - 2) - 1);
}

double Ease::cubicIn(double time)
{
	return time * time * time;
}

double Ease::cubicOut(double time)
{
	return 1 + (time -= 1) * time * time;
}

double Ease::cubicInOut(double time)
{
	if((time *= 2) < 1) return 0.5 * time * time * time;
	return 0.5 * ((time -= 2) * time * time + 2);
}

double Ease::quarticIn(double time)
{
	return time * time * time * time;
}

double Ease::quarticOut(double time)
{
	return -((time -= 1) * time * time * time - 1);
}

double Ease::quarticInOut(double time)
{
	if((time *= 2) < 1) return 0.5 * time * time * time * time;
	return -0.5 * ((time -= 2) * time * time * time - 2);
}

double Ease::quinticIn(double time)
{
	return time * time * time * time * time;
}

double Ease::quinticOut(double time)
{
	return (--t);
}

double Ease::quinticInOut(double time)
{
	return 0;
}

double Ease::sineIn(double time)
{
	return 0;
}

double Ease::sineOut(double time)
{
	return 0;
}

double Ease::sineInOut(double time)
{
	return 0;
}

double Ease::exponentialIn(double time)
{
	return 0;
}

double Ease::exponentialOut(double time)
{
	return 0;
}

double Ease::exponentialInOut(double time)
{
	return 0;
}

double Ease::sqrtIn(double time)
{
	return 0;
}

double Ease::sqrtOut(double time)
{
	return 0;
}

double Ease::sqrtInOut(double time)
{
	return 0;
}

double Ease::backIn(double time)
{
	return 0;
}

double Ease::backOut(double time)
{
	return 0;
}

double Ease::backInOut(double time)
{
	return 0;
}

double Ease::elasticIn(double time)
{
	return 0;
}

double Ease::elasticOut(double time)
{
	return 0;
}

double Ease::elasticInOut(double time)
{
	return 0;
}

double Ease::bounceIn(double time)
{
	return 0;
}

double Ease::bounceOut(double time)
{
	return 0;
}

double Ease::bounceInOut(double time)
{
	return 0;
}
