#pragma once 

#include "ofApp.h"

class Obstacle {
	public:
		Obstacle(int x, int y, int width, int height);
		void draw();
		void setWithinWidth(float objectX);
		void lightUp();

		int x, y, width, height, color;
		bool isWithinWidth;
};