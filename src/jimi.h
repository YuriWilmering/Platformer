#ifndef _JIMI_H_
#define _JIMI_H_

#include "ofApp.h"

class Jimi {
	public:
		Jimi();
		void draw();
		void setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight);
		void setFloorLevel(int obstacleHeight);
		void keyPressed(int key);
		void keyReleased(int key);
		void update();

		ofVec2f loc;

	private:
		void run(int direction);
		void halt();
		void jump();
		void fall();
		void wrapLocation();

		ofVec2f vel;
		int floorHeight;
		int tallestObstacle;
		bool pressingLeft, pressingUp, pressingRight;
		bool jumping, running;
};

#endif // _JIMI_H_
