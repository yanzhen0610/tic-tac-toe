/*
 * AnimationEquation.h
 *
 *  Created on: Jun 5, 2017
 *      Author: yanzh
 */

#ifndef SRC_ANIMATIONEQUATION_H_
#define SRC_ANIMATIONEQUATION_H_

#include <cmath>

//static inline double abs(double num)
//{
//	if (num & 0x800000000000000)
//	{
//		return -num;
//	}
//	return num;
//}

namespace GUI
{

inline double linearAnimate(double value, double min, double max,
		double outputMin, double outputMax)
{
//	if (min > max || outputMin > outputMax)
//	{
//		return outputMin;
//	}
//	if (value >= max)
//	{
//		return outputMax;
//	}
//	if (value <= min)
//	{
//		return outputMin;
//	}
	if (fabs(max - min) > 0.000001)
	{
		return (value - min) / (max - min) * (outputMax - outputMin) + outputMin;
	}
	return 0;
}

inline double squareRootAnimate(double value, double min, double max,
		double outputMin, double outputMax)
{
//	if (min > max || outputMin > outputMax)
//	{
//		return outputMin;
//	}
//	if (value >= max)
//	{
//		return outputMax;
//	}
//	if (value <= min)
//	{
//		return outputMin;
//	}
	if (fabs(max - min) > 0.000001)
	{
		return sqrt((value - min)) * sqrt((max - min)) / (max - min)
				* (outputMax - outputMin) + outputMin;
	}
	return 0;
}

}

#endif /* SRC_ANIMATIONEQUATION_H_ */
