#include "Nodo.h"



Nodo::Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn){

	posicionJugador = posicionJugadorIn;
	posBoxes = cajasInitIn;
	deep = profundidadIn;
	
}


Nodo::Nodo(int * posicionJugadorIn,int ** cajasInitIn, int profundidadIn,string camino){

	posicionJugador = posicionJugadorIn;
	posBoxes = cajasInitIn;
	deep = profundidadIn;
	path = camino;
}

Nodo::~Nodo(){
	
}

void Nodo::borrar(){
	delete [] posicionJugador;
	
	delete [] posBoxes;

	
}

int  Nodo::getPosPlayer(int i){
	return posicionJugador[i];
}

int Nodo::getPosBoxes(int f, int c){
	return posBoxes[f][c];
}

int Nodo::getProf(){
	return deep;
}

string Nodo::getPath(){
	return path;
}

