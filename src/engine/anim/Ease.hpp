#pragma once

class Ease
{
public:
	static double linear(double time);
	static double quadraticIn(double time);
	static double quadraticOut(double time);
	static double quadraticInOut(double time);
	static double cubicIn(double time);
	static double cubicOut(double time);
	static double cubicInOut(double time);
	static double quarticIn(double time);
	static double quarticOut(double time);
	static double quarticInOut(double time);
	static double quinticIn(double time);
	static double quinticOut(double time);
	static double quinticInOut(double time);
	static double sineIn(double time);
	static double sineOut(double time);
	static double sineInOut(double time);
	static double exponentialIn(double time);
	static double exponentialOut(double time);
	static double exponentialInOut(double time);
	static double sqrtIn(double time);
	static double sqrtOut(double time);
	static double sqrtInOut(double time);
	static double backIn(double time);
	static double backOut(double time);
	static double backInOut(double time);
	static double elasticIn(double time);
	static double elasticOut(double time);
	static double elasticInOut(double time);
	static double bounceIn(double time);
	static double bounceOut(double time);
	static double bounceInOut(double time);
};
