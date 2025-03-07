#include "jimi.h"

const int JUMP_POWER = -6;
const float GRAVITY = 0.3;
const float ACCELERATION = 0.35;
const int LEFT = -1;
const int RIGHT = 1;
const int RADIUS = 10;

Jimi::Jimi() {
    floorHeight = HEIGHT - RADIUS;
    loc.set(WIDTH / 2, floorHeight);
    vel.set(0, 0);
    vel.limit(4);
    jumping = false;
    running = false;
    pressingLeft = false;
    pressingUp = false;
    pressingRight = false;
}

void Jimi::draw() {
  	ofSetColor(255, 255, 100, 175);
    ofDrawCircle(loc.x, loc.y, RADIUS);	
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

    if (loc.y == floorHeight) {
        if (pressingLeft) {
            run(LEFT);
        } else if (pressingRight) {
            run(RIGHT);
        }
    }

    if (running && !pressingLeft && !pressingRight) {
        halt();
    }

    if (((loc.y == floorHeight) && pressingUp) || jumping) {
        jump();
    }

    if (!(loc.y == floorHeight) && !jumping) {
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
    } else if (vel.x > 0) {
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
    } else if (loc.x < 0) {
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
 
    if (loc.y >= floorHeight) {
        fallVelocity = 0;
        loc.y = floorHeight;
    }
}

void Jimi::setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight) {
    static vector<int> heights = {0};

	if (isWW && loc.y < obstacleY) {
        heights.push_back(obstacleHeight);
    } else if (!isWW) {
        heights.erase(remove(heights.begin(), heights.end(), obstacleHeight), heights.end());
    }

    tallestObstacle = *max_element(begin(heights), end(heights));
}

void Jimi::setFloorLevel(int obstacleHeight) {
	if (obstacleHeight == tallestObstacle) {
        floorHeight = HEIGHT - obstacleHeight - RADIUS;
    } else if (tallestObstacle == 0) {
        floorHeight = HEIGHT - RADIUS;
    }
}


