#include "jimi.h"

Jimi::Jimi() {
    radius = 10;
    groundFloor = HEIGHT - radius;
    floor = groundFloor;
    loc.set(WIDTH / 2, floor);
    vel.set(0, 0);
    acc.set(0.35, 0); 
    maxVelocity = 4;
    jumpVelocity = -6;
    gravity = 0.3;
    isJump = false;
    heights = {0};
}

void Jimi::draw() {
  	ofSetColor(255, 255, 100, 175);
    ofDrawCircle(loc.x, loc.y, radius);	
}

bool Jimi::setMove(int k, bool b) {
    switch (k) {
        case OF_KEY_UP:
            return isUp = b;
         
        case OF_KEY_LEFT:
            return isLeft = b;
         
        case OF_KEY_RIGHT:
            return isRight = b; 
         
        default:
            return b;
    }
}

void Jimi::move() {
    // move on x axis
    if (isLeft) 
        vel.x -= acc.x;
    else if (!isLeft && vel.x < 0) {
        vel.x += acc.x;
        if (vel.x > 0) 
            vel.x = 0;
    } 
    if (isRight) 
        vel.x += acc.x;
    else if (!isRight && vel.x > 0) {
        vel.x -= acc.x;
        if (vel.x < 0) 
            vel.x = 0;
    }

    vel.limit(maxVelocity);
    loc.x += vel.x;

    // fall down if not on floor && not jumping
    if (loc.y != floor && !isJump) 
        fall();

    // jump only if on floor and key = OF_KEY_UP
    if (loc.y == floor && isUp) 
        isJump = true;
    
    if (isJump) 
        jump(); 
}

void Jimi::jump() {
    jumpVelocity += gravity;
    loc.y += jumpVelocity;
    
    if (jumpVelocity >= 0) {
        fall();
        isJump = false;
   	}
}

void Jimi::fall() {
    gravity += 0.3;
    loc.y += gravity;
 
    if (loc.y >= floor) {
        gravity = 0.3;
        jumpVelocity = -6;
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
        floor = groundFloor;
}


