#include "ofApp.h"
#include "whirlpool.h"
#include "fruit.h"
#include "salesman.h"
//--------------------------------------------------------------

whirlpool whirl_pool;
fruit fr_uit;
salesman sales_man;
void ofApp::setup(){
	_MouseLeftDragging = false;

	_Center = ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
	_Radius = 30.0f;	
	_DecreaseSpd = 1.0f;
	_Dragged = false;
	backgroundcolor = ofGetBackgroundColor();
	_Font.load("vag.ttf", 24);

	_PlayTime = 0.0f;
	_PlayTime1 = 0.0f;
	_PlayTime2 = 0.0f;
	barrier.load("barrier.tiff");
	barrier.resize(barrier.getWidth()/barrier_size , barrier.getHeight() / barrier_size);
	weapon1.load("weapon1.tiff");
	weapon2.load("weapon2.tiff");
	weapon3.load("weapon3.tiff");
	money.load("money.tiff");
	weapon1.resize(weapon1.getWidth() / weapon_size,weapon1.getHeight()/ weapon_size);
	weapon2.resize(weapon2.getWidth() / weapon_size, weapon2.getHeight() / weapon_size);
	weapon3.resize(weapon3.getWidth() / weapon_size, weapon3.getHeight() / weapon_size);
	money.resize(money.getWidth() / money_size, money.getHeight() / money_size);
	whirl_pool.setup();
	fr_uit.setup();
	sales_man.setup();
	animal.load("animal.tiff");
	animal.resize(animal.getWidth() / animal_size, animal.getHeight() / animal_size);
	imgbackground.load("background.tiff");
	imgbackground.resize(ofGetWidth(), ofGetHeight());
	sound_lightning.load("lightning.wav");
	sound_background.load("sound_background.mp3");
	sound_background.play();
	sound_whirlpool.load("whirlpool.mp3");
	time_lock1 = true;
	time_lock2=true;
	time_length = 0;
	_PlayTime1 = 0;
	_PlayTime2 = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	float deltaTime = ofGetLastFrameTime();
	if (sales_man.shop_on_off)
	{
		sales_man.updata(_PrevMousePos,_Center, _MouseLeftDragging);
		if (time_lock1)
		{
			_PlayTime1 = ofGetElapsedTimef();
			time_lock1 = false;
		}
		time_lock2 = true;
	}
	else
	{
		//
		time_lock1 = true;
		if (time_lock2)
		{
			_PlayTime2 = ofGetElapsedTimef();
			time_lock2 = false;
			time_length = -_PlayTime2 + _PlayTime1+time_length;
		}
		
		_PlayTime = ofGetElapsedTimef() + time_length;
		//
		if (sales_man.weapon_on_off[1])
		{
			sound_lightning.play();
		}
		//whirlpool
		whirl_pool.update();
		for (int i = 0;i < 6;i++)
		{
			if (whirl_pool.whirlpool_on_off[i])
			{
				if (whirl_pool.on_now_time[i] > 3.0)
				{
					whirl_pool.whirlpool_on_off[i] = false;
					whirl_pool.on_now_time[i] = 0;
				}
				else
				{
					whirl_pool.on_now_time[i] += 0.01;
					ofVec2f a=whirl_pool.vec[i]-_Radius, b=whirl_pool.vec[i]+100+_Radius;
					if (_Center.x > a.x && _Center.x < b.x && _Center.y>a.y && _Center.y < b.y)
					{
						_Radius -= 1;
					}
				}
			}
			else
			{
				whirl_pool.whirlpool_on_off[i] = (ofRandom(-1, 1) >= 0.999);
				if (whirl_pool.whirlpool_on_off[i])
				{
					whirl_pool.vec[i] = { ofRandomWidth(),ofRandomHeight() };
					sound_whirlpool.play();
				}
			}
			
		}
		//
		for (int i = 0; i < fruittype; i++)
		{
			for (int j = 0;j < fruittype;j++)
			{
				fr_uit._BallCtr[i][j] +=fr_uit._BallVel[i][j] * deltaTime;
				if (fr_uit._BallCtr[i][j].y >= ofGetHeight() + 10.0f)
				{
					if (i == 0)
					{
						fr_uit.initBall_1(j);
					}
					else if(i==1)
					{
						fr_uit.initBall_2(j);
					}
					else
					{
						fr_uit.initBall_3(j);
					}
				}
				ofVec2f Ball_i_to_PlayerBall = fr_uit._BallCtr[i][j] - _Center;
				bool bContact = Ball_i_to_PlayerBall.length() <= _Radius + fr_uit._BallRadius;
				if (bContact)
				{
					if (i == 0)
					{
						fr_uit.initBall_1(j);
					}
					else if (i == 1)
					{
						fr_uit.initBall_2(j);
					}
					else
					{
						fr_uit.initBall_3(j);
					}
					if (i == 0)
					{
						_Radius += 20.0f / _Radius;
					}
					else if (i == 1)
					{
						_Radius -= 20.0f / _Radius;
					}
					else 
					{
						sales_man.money +=1;
					}
				}
			}
		}
		//
		if (_Radius >= 0.0f)
		{
			float deltaRadius = deltaTime * _DecreaseSpd;
			_Radius -= deltaRadius;
		}
		//
		if (_Dragged)
		{
			ofVec2f Offset = _PrevMousePos - _Center;
			_Center += Offset * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
			if ((_Center.x - _Radius) > 0 && (_Center.x + _Radius) < ofGetWidth() && (_Center.y - _Radius) > 0 && (_Center.y + _Radius) < ofGetHeight())
			{
				if (_Center.x < 190 && _Center.y>220 && _Center.y < 340)
				{
					_Center -= Offset * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					_Center.x += Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					if (_Center.x < 190 && _Center.y>220 && _Center.y < 340)
					{
						_Center.x -= Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
						_Center.y += Offset.y * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					}
				}
				if (_Center.x > ofGetWidth() - 190 && _Center.y > 220 && _Center.y < 340)
				{
					_Center -= Offset * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					_Center.x += Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					if (_Center.x > ofGetWidth() - 190 && _Center.y > 220 && _Center.y < 340)
					{
						_Center.x -= Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
						_Center.y += Offset.y * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					}
				}
				if (_Center.x > 200 && _Center.x < 400 && _Center.y>470 && _Center.y < 590)
				{
					_Center -= Offset * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					_Center.x += Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					if (_Center.x > 200 && _Center.x < 400 && _Center.y>470 && _Center.y < 590)
					{
						_Center.x -= Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
						_Center.y += Offset.y * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					}
				}
			}
			else
			{
				_Center.x -= Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
				if ((_Center.x - _Radius) > 0 && (_Center.x + _Radius) < ofGetWidth() && (_Center.y - _Radius) > 0 && (_Center.y + _Radius) < ofGetHeight())
				{

				}
				else
				{
					_Center.x += Offset.x * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
					_Center.y -= Offset.y * exp(-_Radius / 50.0f) *_dragSpd *deltaTime;
				}
			}
			if (_Center.x<100 && _Center.y < ofGetHeight() && _Center.x>0 && _Center.y>ofGetHeight() - 130)
			{
				sales_man.shop_on_off = true;
			}
		}
		//
		

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAlphaBlending();
	ofSetColor(255, 255);
	drawscene();
	ofDisableAlphaBlending();
		if (_Radius >= 0.0f)
		{
			
			ofEnableAlphaBlending();
			ofSetColor(255);
			animal1 = animal;
			animal1.resize(_Radius * 2, _Radius * 2);
			animal1.draw(_Center.x - _Radius, _Center.y - _Radius);
			ofDisableAlphaBlending();
			
			if (_Dragged)
			{
				ofPushStyle();
				ofNoFill();
				ofSetLineWidth(1.0f);
				ofSetColor(ofColor::green);
				ofDrawCircle(_Center, _Radius + 5.0f);
				ofPopStyle();
			}

		}
		else
		{
			drawGameOver();
		}
		

		ofPushStyle();
		ofSetColor(ofColor::black);
		_Font.drawString(ofToString(_PlayTime), 10.0f, 30.0f);
		_Font.drawString(ofToString(sales_man.weapon[0]), ofGetWidth()-35,ofGetHeight()-120);
		_Font.drawString(ofToString(sales_man.weapon[1]), ofGetWidth() - 35, ofGetHeight() - 70);
		_Font.drawString(ofToString(sales_man.weapon[2]), ofGetWidth() - 35, ofGetHeight() - 20);
		_Font.drawString(ofToString(sales_man.money), ofGetWidth() - 30, 60);
		ofPopStyle();

		whirl_pool.draw();
		fr_uit.draw();
		sales_man.draw();
		sales_man.shop_show();
		if (sales_man.weapon_on_off[0])
		{

		}
		if (sales_man.weapon_on_off[1])
		{
			
				_Center = { float(ofGetMouseX()),float(ofGetMouseY()) };
				sales_man.weapon_on_off[1] = false;
				sales_man.weapon[1] -= 1;
		}
		if (sales_man.weapon_on_off[2])
		{
			_Radius += 1;
			sales_man.weapon2_i += 1;
			if (sales_man.weapon2_i > 30)
			{
				sales_man.weapon_on_off[2] = false;
				sales_man.weapon2_i = 0;
				sales_man.weapon[2] -= 1;
			}
		}
}


void ofApp::drawGameOver()
{
	ofPushStyle();
	ofSetColor(ofColor::black);
	string GameOverString = "Game Over";
	float txtWidth = _Font.stringWidth(GameOverString);
	_Font.drawString(GameOverString, ofGetWidth() / 2.0f - txtWidth / 2.0f, ofGetHeight() / 2.0f);
	ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	
	case 'w':
		if (sales_man.weapon[1] > 0)
		{
			sales_man.weapon_on_off[1] = true;
		}
		break;
	case 'e':
		if (sales_man.weapon[2] > 0)
		{
			sales_man.weapon_on_off[2] = true;
		}
		break;
	case 'q':
		sales_man.shop_on_off = false;
		_Center = { float(ofGetWidth() / 2),float(ofGetHeight() / 2) };
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
	_PrevMousePos = ofVec2f(x, y);
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	_MouseLeftDragging = (button == 0);
	
	_PrevMousePos = ofVec2f(x, y);

	ofVec2f Offset = _PrevMousePos - _Center;
	bool mouseInsideBall = (Offset.length() <= _Radius);
	_Dragged = _MouseLeftDragging && mouseInsideBall;	

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
		_MouseLeftDragging = false;
		_Dragged = false;
		sales_man.keyre = true;
		
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	_PrevMousePos = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::drawscene()
{
	imgbackground.draw(0, 0);
	barrier.draw(220, 450);
	barrier.draw(0, 200);
	barrier.draw(ofGetWidth()-170, 200);
	weapon1.draw(ofGetWidth()-100, ofGetHeight()-160);
	weapon2.draw(ofGetWidth() - 100, ofGetHeight()-110);
	weapon3.draw(ofGetWidth() - 100, ofGetHeight() - 60);
	money.draw(ofGetWidth() - 100, 20);
	
}