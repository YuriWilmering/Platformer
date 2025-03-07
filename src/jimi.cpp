#include "jimi.h"

const int JUMP_POWER = -6;
const float GRAVITY = 0.3;
const float ACCELERATION = 0.35;
const int LEFT = -1;
const int RIGHT = 1;
const int STILL = 0;

Jimi::Jimi() {
    radius = 10;
    floorLevel = HEIGHT - radius;
    jumping = false;
    running = false;
    onFloor = false;
    loc.set(WIDTH / 2, floorLevel);
    vel.set(0, 0);
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
    onFloor = loc.y == floorLevel;

    if (onFloor) {
        if (pressingLeft) {
            run(LEFT);
        }
        if (pressingRight) {
            run(RIGHT);
        }
    }

    if (running && !pressingLeft && !pressingRight) {
        halt();
    }

    if ((onFloor && pressingUp) || jumping) {
        jump();
    }

    if (!onFloor && !jumping) {
        fall();
    }

    wrapLocation();
}

void Jimi::run(int direction) {
    running = true;
    vel.x += ACCELERATION * direction;
}

void Jimi::halt() {
    if (vel.x < 0) {
        vel.x += ACCELERATION;

        if (vel.x > 0) {
            vel.x = 0;
            running = false;
        }
    } 

    if (vel.x > 0) {
        vel.x -= ACCELERATION;

        if (vel.x < 0) {
            vel.x = 0;
            running = false;
        }
    } 
}

void Jimi::wrapLocation() {
    if (loc.x > WIDTH) {
        loc.x = 0;
    }

    if (loc.x < 0) {
        loc.x = WIDTH;
    }
}

void Jimi::jump() {
    static float jumpVelocity = JUMP_POWER;
    jumping = true;
    jumpVelocity += GRAVITY;
    loc.y += jumpVelocity;
    
    if (jumpVelocity >= 0) {
        jumping = false;
        jumpVelocity = JUMP_POWER;
   	}
}

void Jimi::fall() {
    static float fallVelocity = 0;
    fallVelocity += GRAVITY;
    loc.y += fallVelocity;
 
    if (loc.y >= floorLevel) {
        fallVelocity = 0;
        loc.y = floorLevel;
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

void Jimi::setFloorLevel(int obstacleHeight) {
	if (obstacleHeight == tallestObstacle) 
        floorLevel = HEIGHT - obstacleHeight - radius;
    else if (tallestObstacle == 0) 
        floorLevel = HEIGHT - radius;
}


