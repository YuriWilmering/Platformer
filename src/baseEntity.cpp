#include "jimi.h"

Entity::Entity() {}

void Entity::draw() {}

void Entity::update() {}

void Entity::run(int direction) {
    running = true;
    vel.x += ACCELERATION * direction;
}

void Entity::halt() {
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

void Entity::wrapLocation() {
    if (loc.x > WIDTH) {
        loc.x = 0;
    } else if (loc.x < 0) {
        loc.x = WIDTH;
    }
}

void Entity::jump() {
    static float jumpVelocity = JUMP_POWER;
    jumping = true;
    jumpVelocity += GRAVITY;
    loc.y += jumpVelocity;
    
    if (jumpVelocity >= 0) {
        jumping = false;
        jumpVelocity = JUMP_POWER;
   	}
}

void Entity::fall() {
    static float fallVelocity = 0;
    fallVelocity += GRAVITY;
    loc.y += fallVelocity;
 
    if (loc.y >= floorHeight) {
        fallVelocity = 0;
        loc.y = floorHeight;
    }
}

void Entity::setTallestObstacle(bool isWW, int obstacleY, int obstacleHeight) {
    static vector<int> heights = {0};

	if (isWW && loc.y < obstacleY) {
        heights.push_back(obstacleHeight);
    } else if (!isWW) {
        heights.erase(remove(heights.begin(), heights.end(), obstacleHeight), heights.end());
    }

    tallestObstacle = *max_element(begin(heights), end(heights));
}

void Entity::setFloorLevel(int obstacleHeight) {
	if (obstacleHeight == tallestObstacle) {
        floorHeight = HEIGHT - obstacleHeight - RADIUS;
    } else if (tallestObstacle == 0) {
        floorHeight = HEIGHT - RADIUS;
    }
}


