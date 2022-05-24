#pragma once
#include "ofMain.h"

void setupWorld(string _windowName, int _windowWidth, int _windowHeight, int _frameRate, ofColor _background, bool _fullscreen);
float x_polar_to_cart(float r, float phi);
float y_polar_to_cart(float r, float phi);
void renderPhoto(int _key);