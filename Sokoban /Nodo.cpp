#include "Nodo.h"

Nodo::Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn){

	posicionJugador = posicionJugadorIn;
	posBoxes = cajasInitIn;
	deep = profundidadIn;
	
}


Nodo::Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn,char accionIn,Nodo * padreIn){

	posicionJugador = posicionJugadorIn;
	posBoxes = cajasInitIn;
	deep = profundidadIn;
	accion = accionIn;
	padre = padreIn;	
}

Nodo::~Nodo(){}

int  Nodo::getPosPlayer(int i){
	return posicionJugador[i];
}

int Nodo::getPosBoxes(int f, int c){
	return posBoxes[f][c];
}

int Nodo::getProf(){
	return deep;
}
