#include "jimi.h"

int JUMP_POWER = -6;

Jimi::Jimi() {
    radius = 10;
    floor = HEIGHT - radius;
    jumping = false;
    onFloor = false;
    loc.set(WIDTH / 2, floor);
    vel.set(0, 0);
    acc.set(0.35, 0);
    gravity = 0.3;
    heights = {0};
    vel.limit(4);
    pressingLeft = false;
    pressingUp = false;
    pressingRight = false;
}

void Jimi::draw() {
  	ofSetColor(255, 255, 100, 175);
    ofDrawCircle(loc.x, loc.y, radius);	
}

void Jimi::keyPressed(int key) {
    if (key == OF_KEY_UP) {
        pressingUp = true;
    }

    if (key == OF_KEY_LEFT) {
        pressingLeft = true;
    }

    if (key == OF_KEY_RIGHT) {
        pressingRight = true;
    }
}

void Jimi::keyReleased(int key) {
    if (key == OF_KEY_UP) {
        pressingUp = false;
    }

    if (key == OF_KEY_LEFT) {
        pressingLeft = false;
    }

    if (key == OF_KEY_RIGHT) {
        pressingRight = false;
    }
}

void Jimi::update() {
    loc.x += vel.x;
    onFloor = loc.y == floor;

    walk();

    if ((onFloor && pressingUp) || jumping) {
        jump();
    }

    if (!onFloor && !jumping) {
        fall();
    }
}

void Jimi::walk() {
    if (pressingLeft) 
        vel.x -= acc.x;
    else if (vel.x < 0) {
        vel.x += acc.x;
        if (vel.x > 0) 
            vel.x = 0;
    } 
    if (pressingRight) 
        vel.x += acc.x;
    else if (vel.x > 0) {
        vel.x -= acc.x;
        if (vel.x < 0) 
            vel.x = 0;
    }
}

void Jimi::jump() {
    static float jumpVelocity = JUMP_POWER;
    jumping = true;
    jumpVelocity += gravity;
    loc.y += jumpVelocity;
    
    if (jumpVelocity >= 0) {
        jumpVelocity = JUMP_POWER;
        jumping = false;
   	}
}

void Jimi::fall() {
    static float fallVelocity = 0;
    fallVelocity += gravity;
    loc.y += fallVelocity;
 
    if (loc.y >= floor) {
        fallVelocity = 0;
        loc.y = floor;
    }
}

void Jimi::setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight) {
	if (isWW && loc.y < obstacleY) 
        heights.push_back(obstacleHeight);
    else if (!isWW) 
        heights.erase(remove(heights.begin(), heights.end(), 
                      obstacleHeight), heights.end());

    tallestObstacle = *max_element(begin(heights), end(heights));
}

void Jimi::setFloor(int obstacleHeight) {
	if (obstacleHeight == tallestObstacle) 
        floor = HEIGHT - obstacleHeight - radius;
    else if (tallestObstacle == 0) 
        floor = HEIGHT - radius;
}


