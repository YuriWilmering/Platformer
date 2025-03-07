#include "obstacle.h"

Obstacle::Obstacle(int x, int y, int width, int height): 
	x(x), y(y), width(width), height(height), color(255) {}

void Obstacle::draw() {
	ofSetColor(255, 255, color, 100);
	ofFill();
	ofDrawRectRounded(x, y, width, height, 3);
}

void Obstacle::setWithinWidth(float objectX) {
    isWithinWidth = objectX < width + x && objectX > x;
}

void Obstacle::lightUp() {
	if (isWithinWidth) {
		color = 100;	
	} else {    
		color = 255;
	}
}


