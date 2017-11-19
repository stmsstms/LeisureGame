#include "fruit.h"
#include "salesman.h"
fruit::fruit()
{

}
void fruit::setup()
{
	for (int i = 0; i < fruittype; i++)
	{
		for (int j = 0;j < fruitamount;j++)
		{
			if (i == 0)
			{
				initBall_1(j);
			}
			else if (i == 1)
			{
				initBall_2(j);
			}
			else
			{
				initBall_3(j);
			}
			if (i == 0)
			{
				drop[i][j].load("apple.tiff");
			}
			else if (i == 1)
			{
				drop[i][j].load("durian.tiff");
			}
			else
			{
				drop[i][j].load("money.tiff");
			}
			drop[i][j].resize(drop[i][j].getWidth() / 10 * 1.0, drop[i][j].getHeight() / 10 * 1.0);
		}

	}

}
void fruit::updata(float deltaTime, ofVec2f _Center, float _Radius)
{
	/*for (int i = 0; i < fruittype; i++)
	{
		for (int j = 0;j < fruittype;j++)
		{
			_BallCtr[i][j] += _BallVel[i][j] *deltaTime;
			if (_BallCtr[i][j].y >= ofGetHeight() + 10.0f)
			{
				initBall_i(i, j);
			}
			ofVec2f Ball_i_to_PlayerBall = _BallCtr[i][j] - _Center;
			bool bContact = Ball_i_to_PlayerBall.length() <= _Radius + _BallRadius;
			if (bContact)
			{
				initBall_i(i, j);
				if (i == 1)
				{
					_Radius += 20.0f / _Radius;
				}
				else if (i == 2)
				{
					_Radius -= 20.0f / _Radius;
				} 
				else
				{

				}
			}
		}
	}*/
}
void fruit::draw()
{
	ofEnableAlphaBlending();
	ofSetColor(255);
	for (int i = 0; i < fruittype; i++)
	{
		for (int j = 0;j < fruitamount;j++)
		{
			drop[i][j].draw(_BallCtr[i][j]);
		}
	}
	ofDisableAlphaBlending();
}
void fruit::initBall_1( int j)
{
	_BallCtr[0][j] = ofVec2f(ofRandomWidth(), -10.0f);
	_BallVel[0][j] = ofVec2f(ofRandomf()*100.0f, ofRandom(100.0f, 250.0f));
}
void fruit::initBall_2(int j)
{
	_BallCtr[1][j] = ofVec2f(ofRandomWidth(), -10.0f);
	_BallVel[1][j] = ofVec2f(ofRandomf()*100.0f, ofRandom(100.0f, 250.0f));
}
void fruit::initBall_3(int j)
{
	
		_BallCtr[2][j] = ofVec2f(ofRandomWidth(), -10.0f);
		_BallVel[2][j] = ofVec2f(ofRandomf()*100.0f, ofRandom(100.0f, 250.0f));
	
}