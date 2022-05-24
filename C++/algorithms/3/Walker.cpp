#include "Walker.h"
void Walker::setup() {

	pos = vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	stuck = false;
	point_size = 5;
}

void Walker::setup(vec2 _pos) {

	pos = _pos;
	stuck = false;
}

void Walker::walk() {
	if (stuck == false) {
		vec2 vel = vec2(ofRandom(-5, 5), ofRandom(-5, 5));
		pos += vel;
	}

	ofClamp(pos.x, 0, ofGetWidth());
	ofClamp(pos.y, 0, ofGetHeight());
}

void Walker::check_stuck(vector<Walker> _tree) {
	for (int i = 0; i < _tree.size(); i++) {
		float dist = distance(pos, _tree[i].pos);
		if (dist < point_size * 2) {
			stuck = true;
		}
	}
}

void Walker::draw() {
}