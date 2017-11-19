#pragma once

#include "ofMain.h"
#define barrier_size 1.5
#define weapon_size 5
#define money_size 5
#define animal_size 5
class whirlpool;
class fruit;
class salesman;
class ofApp : public ofBaseApp
{
private:
	// interaction state
	ofVec2f _PrevMousePos;
	bool _MouseLeftDragging;
	
	// ball props
	ofVec2f _Center;
	float _Radius;
	float _DecreaseSpd;
	bool _Dragged;
	float _dragSpd = 5.0f;
	ofImage barrier, weapon1, weapon2, weapon3, money,animal,animal1,imgbackground;
	ofSoundPlayer sound_lightning,sound_background;
	ofColor backgroundcolor;
	ofSoundPlayer sound_whirlpool;
	


	// text display
	ofTrueTypeFont _Font;

	// player performance
	float _PlayTime, _PlayTime1, _PlayTime2,time_length;
	bool time_lock1, time_lock2;
	// resources
	
	public:
		void setup();
		

		void update();
		void draw();

		void drawGameOver();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void drawscene();
		
};
