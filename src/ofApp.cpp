#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//cambiar la tasa de refreso, por default es 60;
	//ofSetFrameRate(15);
	//inicializar la pos del Player 1
	posPlayer1 = new ofVec2f(30, 100);
	posPelota = new ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::update()
{
	//calculo de input del Player 1
	if (w)
	{
		posPlayer1->y -= 200 * ofGetLastFrameTime();
	}
	if (s)
	{
		posPlayer1->y += 200 * ofGetLastFrameTime();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetBackgroundColor(0, 0, 0);

	//dibujar pelota
	ofSetColor(ofColor::cornflowerBlue); 
	ofCircle(posPelota->x, posPelota->y, 20);

	//dibujar jugador 1
	ofSetColor(ofColor::white);

	ofRect(posPlayer1->x, posPlayer1->y, 10, 70);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'w')
	{
		w = true;
	}
	if (key == 's')
	{
		s = true;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'w')
	{
		w = false;
	}
	if (key == 's')
	{
		s = false;
	}
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
