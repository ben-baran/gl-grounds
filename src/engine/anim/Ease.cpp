#include <cmath>
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
	return 1 + (--time) * time * time;
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
	return -((--time) * time * time * time - 1);
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
	return (--time) * time * time * time * time + 1;
}

double Ease::quinticInOut(double time)
{
	if((time *= 2) < 1) return 0.5 * time * time * time * time * time;
	return 0.5 * ((time -= 2) * time * time * time * time + 2);
}

double Ease::sineIn(double time)
{
	return 1 - std::cos(time * M_PI_2);
}

double Ease::sineOut(double time)
{
	return std::sin(time * M_PI_2);
}

double Ease::sineInOut(double time)
{
	return -0.5 * (std::cos(time * M_PI) - 1);
}

double Ease::exponentialIn(double time)
{
	return time == 0 ? 0 : std::pow(2, 10 * (time - 1));
}

double Ease::exponentialOut(double time)
{
	return time == 1 ? 1 : 1 - std::pow(2, -10 * time);
}

double Ease::exponentialInOut(double time)
{
	if(time == 0 || time == 1) return time;
	if((time *= 2) < 1) return 0.5 * std::pow(2, 10 * (time - 1));
	return 0.5 * (2 - std::pow(2, -10 * (time - 1)));
}

double Ease::backIn(double time)
{
	double back = 1.70158;
	return time * time * ((back + 1) * time - back);
}

double Ease::backOut(double time)
{
	double back = 1.70158;
	return (--time) * time * ((back + 1) * time + back) + 1;
}

double Ease::backInOut(double time)
{
	double back = 1.70158, norm = 1.525;
	if((time *= 2) < 1) return 0.5 * (time * time * (((back *= norm) + 1) * time - back));
	return 0.5 * ((time -= 2) * time * (((back *= norm) + 1) * time + back) + 2);
}

double Ease::elasticIn(double time)
{
	if(time == 0 || time == 1) return time;
	double invDuration = 0.3, offset = invDuration / 4;
	return -(std::pow(2, 10 * (--time)) * std::sin((time - offset) * 2 * M_PI / invDuration));
}

double Ease::elasticOut(double time)
{
	if(time == 0 || time == 1) return time;
	double invDuration = 0.3, offset = invDuration / 4;
	return (std::pow(2, -10 * time) * std::sin((time - offset) * 2 * M_PI / invDuration)) + 1;
}

double Ease::elasticInOut(double time)
{
	if(time == 0) return 0;
	if((time *= 2) == 2) return 1;
	double invDuration = 0.45, offset = invDuration / 4;
	if(time < 1) return -0.5 * (std::pow(2, 10 * (--time)) * std::sin((time - offset) * 2 * M_PI / invDuration));
	return 0.5 * (std::pow(2, -10 * (--time)) * std::sin((time - offset) * 2 * M_PI / invDuration)) + 1;
}

double Ease::bounceIn(double time)
{
	return 1 - bounceOut(1 - time);
}

double Ease::bounceOut(double time)
{
	double cycle = 2.75;
	if(time < (1 / cycle)) return 7.5625 * time * time;
	if(time < (2 / cycle)) return 7.5625 * (time -= (1.5 / cycle)) * time + .75;
	if(time	< (2.5 / cycle)) return 7.5625 * (time -= (2.25 / cycle)) * time + .9375;
	return 7.5625 * (time -= (2.625 / cycle)) * time + .984375;
}

double Ease::bounceInOut(double time)
{
	if(time < 0.5) return bounceIn(time * 2) * 0.5;
	return bounceOut(time * 2 - 1) * 0.5 + 0.5;
}
