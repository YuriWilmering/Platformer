#ifndef _JIMI_H_
#define _JIMI_H_

#include "ofApp.h"

class Jimi {
	public:
		ofVec2f loc;
		ofVec2f vel;
		ofVec2f acc;
		int radius;
		int floor;
		int groundFloor;
		double maxVelocity;
		double gravity;
		vector<int> heights;
		int tallestObstacle;

		Jimi();
		void draw();
		bool setMove(int k, bool b);
		void move() ;
		void jump();
		void fall();
		void setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight);
		void setFloor(int obstacleHeight);

		bool isLeft;
		bool isRight;
		bool isUp;
		bool isJump; 

	private:
		double jumpVelocity;
};

#endif // _JIMI_H_
