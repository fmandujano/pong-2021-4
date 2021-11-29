#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//cambiar la tasa de refreso, por default es 60;
	//ofSetFrameRate(15);
	//inicializar la pos del Player 1
	posPlayer1 = new ofVec2f(30, 100);
	//condiciones iniciales
	posPelota = new ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	velPelota = new ofVec2f(150, 150);

	if (appState == EAppState::server)
	{
		setupServer();
	}
	else if (appState == EAppState::client)
	{
		setupClient();
	}

}

void ofApp::setupServer()
{
	puts("Creando servidor");
	udpManager.Create();
	udpManager.Bind(PORT);
	udpManager.SetNonBlocking(true);
}

void ofApp::setupClient()
{
	puts("Creando cliente");
	udpManager.Create();
	string ip = ofSystemTextBoxDialog("IP del servidor", "127.0.0.1");
	udpManager.Connect( ip.c_str(), PORT);
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

	//calculo del movimiento de la pelota
	posPelota->x += velPelota->x * ofGetLastFrameTime();
	posPelota->y += velPelota->y * ofGetLastFrameTime();

	//rebote de la pelota en las paredes
	if (posPelota->x < 0)
	{
		velPelota->x *= -1;
		posPelota->x = 0;
	}
	if (posPelota->x > ofGetWidth())
	{
		velPelota->x *= -1;
		posPelota->x = ofGetWidth();
	}
	if (posPelota->y < 0)
	{
		velPelota->y *= -1;
		posPelota->y = 0;
	}
	if (posPelota->y > ofGetHeight())
	{
		velPelota->y *= -1;
		posPelota->y = ofGetHeight();
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
