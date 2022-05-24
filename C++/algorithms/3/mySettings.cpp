#include "mySettings.h"

void setupWorld(string _windowName, int _windowWidth, int _windowHeight, int _frameRate, ofColor _background, bool _fullscreen) {
	ofSetWindowTitle(_windowName);
	ofSetWindowShape(_windowWidth, _windowHeight);
	ofSetFullscreen(_fullscreen);
	ofSetFrameRate(_frameRate);
	ofBackground(_background);
}

float x_polar_to_cart(float r, float phi) {
	float x = r * cos(phi);
	return x;
}

float y_polar_to_cart(float r, float phi) {
	float y = r * sin(phi);
	return y;
}

void renderPhoto(int _key) {
	if(_key == 's') {
		ofSaveScreen(ofToString(ofGetFrameNum()) + ".png");
	}
}