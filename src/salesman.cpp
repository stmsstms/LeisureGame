#include "salesman.h"
#include "ofApp.h"
salesman::salesman()
{

}
void salesman::setup()
{
	imgsalesman.load("salesman.tiff");
	imgshop.load("shop.tif");
	imgsalesman.resize(imgsalesman.getWidth() / 2, imgsalesman.getHeight() / 2);
	imgshop.resize(imgshop.getWidth()/2,imgshop.getHeight()/2);
	shop_on_off = false;
	weapon[0] = 0;
	weapon[1] = 0;
	weapon[2] = 0;
	money = 0;
	buying[0] = { 205,470 };
	buying[1] = { 280,470 };
	buying[2] = { 355,470 };
	weapon_on_off [0]= false;
weapon_on_off[1] = false;
weapon_on_off[2] = false;
	f_ont.load("vag.ttf", 20);
	keyre = true;
	weapon2_i = 0;
}
void salesman::updata(ofVec2f _PrevMousePos, ofVec2f _Center,bool _MouseLeftDragging)
{
	if (_MouseLeftDragging&&keyre)
	{
		float a = buying[0].distance(_PrevMousePos);
		float b = buying[1].distance(_PrevMousePos);
		float c = buying[2].distance(_PrevMousePos);
		if (a < 50)
		{
			
		}
		if (b < 50)
		{
			if (money - 3 >= 0)
			{
				weapon[1] += 1;
				money -= 3;
			}
		}
		if (c < 50)
		{
			if (money - 1 >= 0)
			{
				weapon[2] += 1;
				money -= 1;
			}
		}
		keyre = false;
	}
}
void salesman::draw()
{
	ofEnableAlphaBlending();
	ofSetColor(255);
	imgsalesman.draw(0, ofGetHeight() - 130);
	ofDisableAlphaBlending();
}
void salesman::shop_show()
{
	if (shop_on_off)
	{
		ofEnableAlphaBlending();
		ofSetColor(255);
		imgshop.draw(0, 130);
		ofDisableAlphaBlending();
		ofPushStyle();
		ofSetColor(ofColor::black);
		f_ont.drawString(ofToString(money), 360, 550);
		ofEllipse(355, 470, 50, 50);
		ofPopStyle();
	}
}

