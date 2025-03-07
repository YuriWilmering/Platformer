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
		double gravity;
		vector<int> heights;
		int tallestObstacle;

		Jimi();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void update();
		void walk();
		void jump();
		void fall();
		void setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight);
		void setFloor(int obstacleHeight);

		bool pressingLeft, pressingUp, pressingRight, onFloor, jumping;
};

#endif // _JIMI_H_
