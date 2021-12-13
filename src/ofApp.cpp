#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//cambiar la tasa de refreso, por default es 60;
	//ofSetFrameRate(15);

	playerSize = new ofVec2f(10, 70);
	//inicializar la pos del Player 1
	posPlayer1 = new ofVec2f(30, 100);
	//inicializar la pos del Player 2
	posPlayer2 = new ofVec2f( ofGetWidth()-30-playerSize->x , 100);
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

	//imprimir el rango de escucha
	int port;
	udpManager.GetListenAddr(serverIP, port);
	printf("ip local : %s ", serverIP.c_str());

	//EJEMPLO DE API WEB, QUITAR LUEGO
	string uid = ofSystemTextBoxDialog("id del usuario", "11111");
	string score = ofSystemTextBoxDialog("score a agregar", "0");
	string url = "http://monsterballgo.com/pong/score.php?u=" + uid + "&s=" + score;
	//enviar peticion web
	ofHttpResponse res = ofLoadURL(url);
	std::cout << res.data << std::endl;
}

void ofApp::setupClient()
{
	puts("Creando cliente");
	udpManager.Create();
	//string ip = ofSystemTextBoxDialog("IP del servidor", "127.0.0.1");
	//udpManager.Connect( ip.c_str(), PORT);
	udpManager.Connect("127.0.0.1", PORT);
	udpManager.SetNonBlocking(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (appState == EAppState::server)
	{
		updateServer();
	}
	else if (appState == EAppState::client)
	{
		updateClient();
	}
	else
	{
	}
}

void ofApp::updateServer()
{
	//calculo de input del Player 1 - Servidor - a la izquierda
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

	//enviar y recibir info por el socket
	memset(buffer, 0, BUFFER_SIZE);
	//serializar datos a enviar: posPaleta y posPlayer1
	sprintf(buffer, "%f,%f,%f", posPelota->x, posPelota->y, posPlayer1->y);
	//printf(buffer);
	udpManager.SendAll(buffer, BUFFER_SIZE);

	//recibir datos del cliente
	memset(buffer, 0, BUFFER_SIZE);
	if (udpManager.Receive(buffer, BUFFER_SIZE) > 0)
	{
		printf(buffer);
	}
}

void ofApp::updateClient()
{
	//calculo de input del Player 2 - cliente - a la derecha
	if (w)
	{
		posPlayer2->y -= 200 * ofGetLastFrameTime();
	}
	if (s)
	{
		posPlayer2->y += 200 * ofGetLastFrameTime();
	}

	//enviar datos
	memset(buffer, 0, BUFFER_SIZE);
	sprintf(buffer, "%f,%f\n", posPlayer1->x , posPlayer2->y);
	udpManager.Send(buffer, BUFFER_SIZE);

	//recibir datos
	memset(buffer, 0, BUFFER_SIZE);
	if (udpManager.Receive(buffer, BUFFER_SIZE) > 0)
	{
		//deserializacion: posPelotax,posPelotaY,PosPlayer1Y
		char* val;
		val = strtok(buffer, ",");
		//el primer valor es la posPelotaX
		posPelota->x = atof(val);
		val = strtok(NULL, ",");
		//el segundo valor es posPelotaY
		posPelota->y = atof(val);
		val = strtok(NULL, ",");
		posPlayer1->y = atof(val);
	}
	
}


//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetBackgroundColor(0, 0, 0);

	if (appState == EAppState::server)
	{
		ofDrawBitmapString("PONG SERVER", 20, 20);
	}
	else if (appState == EAppState::client)
	{
		ofDrawBitmapString("PONG CLIENT", 20, 20);
	}
	else
	{

	}

	//dibujar pelota
	ofSetColor(ofColor::cornflowerBlue); 
	ofCircle(posPelota->x, posPelota->y, 20);

	//dibujar jugador 1
	ofSetColor(ofColor::white);
	ofRect(posPlayer1->x, posPlayer1->y, playerSize->x, playerSize->y);
	//dibujar jugador 2
	ofRect(posPlayer2->x, posPlayer2->y, playerSize->x, playerSize->y);
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
