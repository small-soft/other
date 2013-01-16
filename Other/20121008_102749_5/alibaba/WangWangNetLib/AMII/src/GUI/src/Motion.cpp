#include "AMGui.h"
#include "AMOS.h"

__GUI_BEGIN_NAMESPACE
Motion::Motion( int sourceValue, int destinationValue, int duration )
{
	this->sourceValue = sourceValue;
	this->destinationValue = destinationValue;
	this->duration = duration;
}

Motion::Motion( int sourceValue, float initVelocity, float friction )
{
	this->sourceValue = sourceValue;
	this->initVelocity = initVelocity;
	this->friction = friction;

	duration =abs((int)(initVelocity / friction));
}
Motion::~Motion(void)
{
}

shared_ptr<Motion> Motion::createLinearMotion( int sourceValue, int destinationValue, int duration )
{
	shared_ptr<Motion> l = new Motion(sourceValue, destinationValue, duration);
	l->motionType = LINEAR;
	return l;
}

shared_ptr<Motion> Motion::createSplineMotion( int sourceValue, int destinationValue, int duration )
{
	shared_ptr<Motion> spline = new Motion(sourceValue, destinationValue, duration);
	spline->motionType = SPLINE;
	return spline;
}

shared_ptr<Motion> Motion::createFrictionMotion( int sourceValue, float initVelocity, float friction )
{
	shared_ptr<Motion> frictionMotion = new Motion(sourceValue, initVelocity, friction);
	frictionMotion->motionType = FRICTION;
	return frictionMotion;
}

void Motion::start()
{		
	startTime = System::currentTimeMillis();
}

bool Motion::isFinished()
{
	 return System::currentTimeMillis() > duration + startTime;
}

int Motion::getValue()
{
	if (motionType == SPLINE) {
		return getSplineValue();
	}else if(motionType == FRICTION){
		return getFriction();
	}else{
		return getLinear();
	}
}

int Motion::getSourceValue()
{
	return sourceValue;
}

void Motion::setSourceValue( int sourceValue )
{
	 this->sourceValue = sourceValue;
}

int Motion::getSplineValue()
{
	if(isFinished()){
		return destinationValue;
	}
	float totalTime = (float)duration;
	float currentTime = (float) (System::currentTimeMillis() - startTime);
	currentTime = min(currentTime, totalTime);
	int p = abs(destinationValue - sourceValue);
	float centerTime = totalTime / 2;
	float l = p / (centerTime * centerTime);
	int x;
	if (sourceValue < destinationValue) {
		if (currentTime > centerTime) {
			x = sourceValue + (int) (l * (-centerTime * centerTime + 2 * centerTime * currentTime -
				currentTime * currentTime / 2));
		} else {
			x = sourceValue + (int) (l * currentTime * currentTime / 2);
		}
	} else {
		currentTime = totalTime - currentTime;
		if (currentTime > centerTime) {
			x = destinationValue + (int) (l * (-centerTime * centerTime + 2 * centerTime * currentTime -
				currentTime * currentTime / 2));
		} else {
			x = destinationValue + (int) (l * currentTime * currentTime / 2);
		}
	}
	return x;
}

int Motion::getLinear()
{
	if(isFinished()){
		return destinationValue;
	}
	float totalTime = (float)duration;
	float currentTime = (float) (System::currentTimeMillis() - startTime);
	int dis = destinationValue - sourceValue;
	int val = (int)(sourceValue + (currentTime / totalTime * dis));

	if(destinationValue < sourceValue) {
		return max(destinationValue, val);
	} else {
		return min(destinationValue, val);
	}
}

int Motion::getFriction()
{
	int time = (int) (System::currentTimeMillis() - startTime);
	int retVal = 0;

	retVal =abs ((int)(((initVelocity) * time) - (friction * (((float)time * time) / 2))));
	if (initVelocity < 0) {
		retVal *= -1;
	}
	retVal += (int) sourceValue;
	return retVal;
}

long Motion::getStartTime()
{
	  return startTime;
}
__GUI_END_NAMESPACE
