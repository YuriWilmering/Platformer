#include "ofApp.h"
#include "jimi.h"
#include "obstacle.h"

auto jimi = new Jimi;
vector<unique_ptr<Obstacle>> obstacles;

random_device r;
default_random_engine s(r());

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	killcount = 0;
	nObstacles = 10;

	// generate obstacles with random x, y, width and height
	for (auto i = 0; i < nObstacles; i++) {
		uniform_int_distribution<> x 		(0, WIDTH - 200);
		uniform_int_distribution<> height 	(20, 200);
		uniform_int_distribution<> w 		(50, 200);
		auto h = height(s);
		obstacles.emplace_back(new Obstacle(x(s), HEIGHT - h, w(s), h));
	} 
}

//--------------------------------------------------------------
void ofApp::update() {
	jimi->update();

	for (auto& obstacle : obstacles) {
		obstacle->setWithinWidth(jimi->loc.x);
		obstacle->lightUp();


		jimi->setTallestObstacle( obstacle->isWithinWidth, 
									obstacle->y, obstacle->height );
		jimi->setFloorLevel( obstacle->height );
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	jimi->draw();

	for (auto& obstacle : obstacles) 
		obstacle->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	jimi->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	jimi->keyReleased(key);
} 

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
