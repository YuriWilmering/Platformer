#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "ofApp.h"

#define GRAVITY 0.3
#define ACCELERATION 0.35
#define LEFT -1
#define RIGHT 1
#define RADIUS 10
#define JUMP_POWER -6

class Entity {
	public:
        Entity();
		virtual void draw();
		virtual void update();
		void setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight);
		void setFloorLevel(int obstacleHeight);
		void run(int direction);
		void halt();
		void jump();
		void fall();
		void wrapLocation();

		ofVec2f loc;
		ofVec2f vel;
		int floorHeight;
		bool running, jumping;

	private:
		int tallestObstacle;
};

#endif // _ENTITY_H_