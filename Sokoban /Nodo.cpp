#include "Nodo.h"

	Nodo::Nodo(){
	}
	Nodo::~Nodo(){}

	bool Nodo::getEsHoja(){
		return esHoja;
	}
	void Nodo::setEsHoja(bool newValue){
		esHoja = newValue;
	}