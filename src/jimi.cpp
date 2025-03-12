#include "jimi.h"

Jimi::Jimi() {
    floorHeight = HEIGHT - RADIUS;
    loc.set(WIDTH / 2, floorHeight);
    vel.set(0, 0);
    vel.limit(4.);
    jumping = false;
    running = false;
    pressingLeft = false;
    pressingUp = false;
    pressingRight = false;
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


