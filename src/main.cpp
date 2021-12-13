#include "ofMain.h"
#include "ofApp.h"

//Pong Multiplayer 
// Redes y Bases de Datos GPD0121
// 24-nov-21
//========================================================================
int main( int argc , char** argv )
{
	int resx = 1000;
	int resy = 1000;
	bool fullscreen = false;

	//analizar (parse) el archivo config.ini
	ifstream configfile;
	configfile.open("data/config.ini"); //ruta relativa a donde se encuentra el ejecutable
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofApp *myapp = new ofApp();

	if (configfile.is_open())
	{
		puts("leyendo datos del archivo config.ini");
		char * linea = new char[100];
		char *llave, *valor;

		

		while (!configfile.eof())
		{
			configfile.getline(linea, 100);
			//ignorar lineas que comiencen con caracteres no aceptables
			if (linea[0] != '/' &&
				linea[0] != '[' &&
				linea[0] != '\n' &&  //line feed
				linea[0] != '\r' &&  //carriage return, solo en windows
				linea[0] != '\0')
			{
				llave = strtok(linea, "=");
				valor = strtok(NULL, "=");
				printf("llave: %s, valor:%s\n", llave, valor);
				if (!strcmp(llave, "resx"))
					resx = atoi(valor);
				if (!strcmp(llave, "resy"))
					resy = atoi(valor);
				if (!strcmp(llave, "fullscreen"))
					fullscreen = !strcmp(valor, "true");
				//if (!strcmp(llave, "port"))
					//port = atoi(valor);
			}
		}
	}
	
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
		else if (!strcmp(argv[i], "resx"))
		{
			resx = atoi(argv[i + 1]);
		}
		else if (!strcmp(argv[i], "resy"))
		{
			resy = atoi(argv[i + 1]);
		}
		else if (!strcmp(argv[i], "fullscreen"))
		{
			fullscreen = true;
		}
	}


	//usamos el operador ternario para determinar si es pantalla completa
	//  condicion ? valor_si_true : valor_si_false;
	ofSetupOpenGL(resx, resy, fullscreen ? OF_FULLSCREEN:OF_WINDOW  );			// <-------- setup the GL context


	ofRunApp(myapp);
	
}
