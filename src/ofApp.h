#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxGui.h"

#define BUFFER_SIZE 100
#define PORT 7777 

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void setupClient();
		void setupServer();

		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVec2f *posPelota;
		ofVec2f *velPelota;
		ofVec2f *posPlayer1; //raqueta o paleta del jugador 1

		//input del jugador 1
		bool w, s;

		//cosas de red
		ofxUDPManager udpManager;
		char buffer[BUFFER_SIZE];
		enum EAppState
		{
			client, server, menu
		};
		EAppState appState;
};
