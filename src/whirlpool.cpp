#include "whirlpool.h"
whirlpool::whirlpool()
{

}
void whirlpool::setup()
{
	img_whirlpool.load("whirlpool.tif");
	img_whirlpool.resize(img_whirlpool.getWidth() /2* 1.0, img_whirlpool.getHeight() /2* 1.0);
	float on_now_time[6] = { 0,0,0,0,0,0 };
	bool whirlpool_on_off[6] = { false,false,false,false,false,false };
	sound_whirlpool.load("whirlpool.mp3");
}
void whirlpool::update() 
{

}
void whirlpool::draw(){
	for (int i = 0;i < 6;i++)
	{
		if (whirlpool_on_off[i])
		{
			if (on_now_time[i] < 1.0)
			{
				ofEnableAlphaBlending();
				ofSetColor(255, on_now_time[i] * 255*1.0);
				img_whirlpool.draw(vec[i]);
				ofDisableAlphaBlending();
			
			}
			else if (on_now_time[i] < 2.0)
			{
				ofEnableAlphaBlending();
				ofSetColor(255, 255);
				img_whirlpool.draw(vec[i]);
				ofDisableAlphaBlending();
				
			}
			else if(on_now_time[i] < 3.0)
			{
				ofEnableAlphaBlending();
				ofSetColor(255, (3-on_now_time[i]) * 255 * 1.0);
				img_whirlpool.draw(vec[i]);
				ofDisableAlphaBlending();
				
			}
		}
	}
}