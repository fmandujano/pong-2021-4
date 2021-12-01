#include "ofMain.h"
#include "ofApp.h"

//Pong Multiplayer 
// Redes y Bases de Datos GPD0121
// 24-nov-21
//========================================================================
int main( int argc , char** argv )
{
	ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofApp *myapp = new ofApp();
	
	myapp->appState = ofApp::EAppState::client;
	//leer parametros
	for (int i = 0; i < argc; i++)
	{
		printf("Argumento %i : %s \n", i, argv[i]);

		if (!strcmp(argv[i], "server"))
		{
			myapp->appState = ofApp::EAppState::server;
		}
		else if (!strcmp(argv[i], "client"))
		{
			myapp->appState = ofApp::EAppState::client;
		}
	}


	ofRunApp(myapp);
	
}
