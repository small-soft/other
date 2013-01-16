#ifndef __GUI_MOTION_H__
#define __GUI_MOTION_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE
class Motion:public Object
{
public:
	virtual ~Motion(void);
protected:
	Motion(int sourceValue, int destinationValue, int duration);
	Motion(int sourceValue, float initVelocity, float friction);
private:
	static const int LINEAR = 0;
	static const int SPLINE = 1;
	static const int FRICTION = 2;

	int motionType;
	int sourceValue;
	int destinationValue;
	int duration;
	long startTime;
	float initVelocity,  friction;
public :
	static shared_ptr<Motion> createLinearMotion(int sourceValue, int destinationValue, int duration);
	static shared_ptr<Motion> createSplineMotion(int sourceValue, int destinationValue, int duration);
	static shared_ptr<Motion> createFrictionMotion(int sourceValue, float initVelocity, float friction);
	void start();
	bool isFinished();
	int getValue();
	int getSourceValue();
	void setSourceValue(int sourceValue);
private :
	int getSplineValue();
	int getLinear();
	int getFriction();
protected:
	long getStartTime();
};
__GUI_END_NAMESPACE

#endif
