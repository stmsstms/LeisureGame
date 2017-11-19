#pragma once
#include "ofMain.h"
class whirlpool
{
public:
	whirlpool();
	void update();
	void draw();
	void setup();
	bool whirlpool_on_off[6], whirlpool_condition[6];
	ofVec2f vec[6];
	float on_now_time[6];
private:
	ofSoundPlayer sound_whirlpool;
	
	ofColor color_background = {0,0,0};
	ofImage img_whirlpool;
};



