#include "enemy.h"

Enemy::Enemy(int x) : x(x) {
    brightness = 175;
    green = 0;
    floorHeight = HEIGHT - RADIUS;
    loc.set(x, -50);
    vel.set(0, 0.1);
    srand (time(NULL));
    alive = true;
    hit = false;
    direction = (rand() % 2) * 2 - 1;
}

void Enemy::update() {
    if (alive) {
        vel.limit(2);
        loc.x += vel.x;

        if (loc.y == floorHeight) {
            run(direction);
        }

        if (!(loc.y == floorHeight) && !jumping) {
            fall();
        }
    }
}

void Enemy::draw() {
    ofSetColor(255, green, 0, brightness);
    ofDrawCircle(loc.x, loc.y, RADIUS);	
}

void Enemy::die(int timeOfHit) {
    brightness += 2;
    green = green == 0 ? 255 : 0;
    static int timeOfDeath = timeOfHit + 1000;

    if (timeOfDeath <= ofGetElapsedTimeMillis())  {
        alive = false;
    }
}

