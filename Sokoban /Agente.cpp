#include "Agente.h"

Agente::Agente(int numBoxesIn, int* pos, int ** cajasInit,vector<string> *tableIn){	
	table=*tableIn;
    numBoxes=numBoxesIn;
    
    Nodo * node = new Nodo(pos,cajasInit,0);

	nodes.push(node);
}

Agente::~Agente(){}

void Agente::identifyTargets(){
	
	int band=0;

	targets = new int*[numBoxes];
	for (int i = 0; i < numBoxes; i++){
		targets[i] = new int[2];
	}
	

	for (int i = 0; i < table.size(); i++){
		for (int j = 0; j < table[i].size(); j++){
			if (table[i][j]=='X'){

				targets[band][0] = i;
				targets[band][1] = j;
				band++;
			}
			
		}
		
	}
	
}

bool Agente::searchBox(int posF, int posC, Nodo * node){
	
	for (int i = 0; i < numBoxes; i++){
		if(node->getPosBoxes(i,0)==posF && node->getPosBoxes(i,1)==posC)return true;
	}
	
	return false;
}

bool Agente::expand(Nodo * node ,char move){

	switch (move){
		case 'R':
			if(table[node->getPosPlayer(0)][node->getPosPlayer(1)+1]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)+1, node) && table[node->getPosPlayer(0)][node->getPosPlayer(1)+2]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)+1, node) && searchBox(node->getPosPlayer(0),node->getPosPlayer(1)+2, node))  return false;
			else return true;
		break;
		case 'L':
			if(table[node->getPosPlayer(0)][node->getPosPlayer(1)-1]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)-1, node) && table[node->getPosPlayer(0)][node->getPosPlayer(1)-2]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)-1, node) && searchBox(node->getPosPlayer(0),node->getPosPlayer(1)-2, node))  return false;
			else return true;
		break;
		case 'D':
			if(table[node->getPosPlayer(0)+1][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)+1,node->getPosPlayer(1), node) && table[node->getPosPlayer(0)+2][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)+1,node->getPosPlayer(1), node) && searchBox(node->getPosPlayer(0)+2,node->getPosPlayer(1), node))  return false;
			else return true;
	
		break;
		case 'U':
			if(table[node->getPosPlayer(0)-1][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)-1,node->getPosPlayer(1), node) && table[node->getPosPlayer(0)-2][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)-1,node->getPosPlayer(1), node) && searchBox(node->getPosPlayer(0)-2,node->getPosPlayer(1), node))  return false;
			else return true;
		break;

	}

	return false;
}


int** Agente::moveBox(Nodo * node,int * pos,char accion){
	int ** newBoxes = new int *[numBoxes];
	
	for (int i = 0; i < numBoxes; i++){
		newBoxes[i] = new int [2];
		newBoxes[i][0]=node->getPosBoxes(i,0);
		newBoxes[i][1]=node->getPosBoxes(i,1);

		if(node->getPosBoxes(i,0)==pos[0] && node->getPosBoxes(i,1)==pos[1]){
			switch (accion){
				case 'R':
					newBoxes[i][1]=newBoxes[i][1]+1;
				break;
				case 'L':
					newBoxes[i][1]=newBoxes[i][1]-1;
				break;
				case 'D':
					newBoxes[i][0]=newBoxes[i][0]+1;
				break;
				case 'U':
					newBoxes[i][0]=newBoxes[i][0]-1;
				break;
			}
			return newBoxes;
		}
	}
	return newBoxes;
}



void Agente::expandNode(){
	Nodo * actualNode=nodes.top();

	nodes.pop();

	if(expand(actualNode,'R')){
		cout << "R" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)+1;

		Nodo * node = new Nodo(pos,moveBox(actualNode,pos,'R'),actualNode->getProf()+1,'R',actualNode);
		nodes.push(node);
	}

	if(expand(actualNode,'L')){
		cout << "L" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)-1;

		Nodo * node = new Nodo(pos,moveBox(actualNode,pos,'L'),actualNode->getProf()+1,'L',actualNode);
		nodes.push(node);
	}
	
	

	if(expand(actualNode,'U')){
		cout << "U" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)-1;
		pos[1]=actualNode->getPosPlayer(1);

		Nodo * node = new Nodo(pos,moveBox(actualNode,pos,'U'),actualNode->getProf()+1,'U',actualNode);
		nodes.push(node);
	}

	if(expand(actualNode,'D')){
		cout << "D" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)+1;
		pos[1]=actualNode->getPosPlayer(1);

		Nodo * node = new Nodo(pos,moveBox(actualNode,pos,'D'),actualNode->getProf()+1,'D',actualNode);
		nodes.push(node);
	}

}

bool Agente::isSolve(){
	int counting = 0;
	
	for (int i = 0; i < numBoxes; i++){
		if(searchBox(targets[i][0],targets[i][1], nodes.top())){
			counting++;
		}
	}
	
	if(counting == numBoxes){
		return true;
	}else return false;
	
}


void Agente::iniciarBusqueda(){
    	cout << "Posición del jugador: " << nodes.top()->getPosPlayer(0) << "-" << nodes.top()->getPosPlayer(1) << endl;

	for (int i = 0; i < numBoxes; i++){
		
		cout << "Posición de la caja "<< i+1 << ": " << nodes.top()->getPosBoxes(i,0) << "-" << nodes.top()->getPosBoxes(i,1) << endl;
		cout << "Posición del objetivo"<< i+1 << ": " << targets[i][0] << "-" << targets[i][1] << endl;
		
	}

	for (int i = 0; i < table.size(); i++){
		cout << table[i] << endl;
	}
	

	bool x = isSolve();

	if(x){
		cout << "Listo" << endl;
	}else{
		cout << "O no funciona o no hay cajas ubicadas correctamente" << endl;
	}

	expandNode();

	
	
	for (int i = 0; i < nodes.size(); i++){
		cout << "Posición de la caja "<< i+1 << ": " << nodes.top()->getPosBoxes(i,0) << "-" << nodes.top()->getPosBoxes(i,1) << endl;
		nodes.pop();
		i--;
		
	}	

}