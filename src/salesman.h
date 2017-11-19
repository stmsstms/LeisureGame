#pragma once
#include "ofMain.h"
#define weapon_amount 3
class salesman
{
public:
	salesman();
	void setup();
	void updata(ofVec2f _PrevMousePos,ofVec2f _Center,bool _MouseLeftDragging);
	void draw();
	void shop_show();
	
	bool shop_on_off;
	int weapon[weapon_amount];
	ofVec2f buying[weapon_amount];
	bool weapon_on_off[weapon_amount];
	int money;
	bool keyre;
	int weapon2_i;
private:
	ofImage imgsalesman;
	ofImage imgshop;
	ofTrueTypeFont f_ont;
};


