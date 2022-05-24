#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	//ofSetBackgroundAuto(false);

	myMesh.clear();

	//starting point
	Walker c_point;
	c_point.setup(vec2(ofGetWidth() / 2, ofGetHeight() / 2));
	tree.push_back(c_point);

	//random walker
	numWalkers = 300;
	for (int i = 0; i < numWalkers; i++) {
		Walker w;
		w.setup();
		walkers.push_back(w);
	}

	

	//setup drawing mesh
	myMesh.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < walkers.size(); i++) {
		walkers[i].walk();
		walkers[i].check_stuck(tree);
	}

	for (int i = 0; i < walkers.size(); i++)
	{
		if (walkers[i].stuck == true)
		{
			tree.push_back(walkers[i]);
			walkers.erase(walkers.begin() + i);
			
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){


	for (int i = 0; i < walkers.size(); i++) {
		ofSetColor(255);
		ofDrawCircle(walkers[i].pos,walkers[i].point_size);
	}

	for (int i = 0; i < tree.size(); i++) {
		ofSetColor(255,0,0);
		ofDrawCircle(tree[i].pos, tree[i].point_size);
	}
	//ofDrawCircle(walker, point_size);
	//myMesh.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	renderPhoto(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
