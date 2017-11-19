#pragma once
#include "ofMain.h"
#define fruittype 3
#define fruitamount 3
class fruit
{
public:
	fruit();
	float _BallRadius = 10.0f;
	ofImage drop[3][3];
	void setup();
	void updata(float deltaTime, ofVec2f _Center, float _Radius);
	void draw();
	ofVec2f _BallCtr[fruittype][fruitamount];
	ofVec2f	_BallVel[fruittype][fruitamount];
	void initBall_1(int j);
	void initBall_2(int j);
	void initBall_3(int j);
private:
	
	
};



