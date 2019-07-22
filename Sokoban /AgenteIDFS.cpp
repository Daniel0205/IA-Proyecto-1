#include "AgenteIDFS.h"

AgenteIDFS::AgenteIDFS(int numBoxesIn, int* pos, int ** cajasInit,vector<string> *tableIn){	
	table=*tableIn;
    numBoxes=numBoxesIn;
	    
    Nodo * node = new Nodo(pos,cajasInit,0);
	raiz = node;

	nodes.push(node);
}

AgenteIDFS::~AgenteIDFS(){}

void AgenteIDFS::identifyTargets(){
	
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

bool AgenteIDFS::searchBox(int posF, int posC, Nodo * node){

	for (int i = 0; i < numBoxes; i++){
		
		if(node->getPosBoxes(i,0)==posF && node->getPosBoxes(i,1)==posC)return true;
	}
	
	return false;
}

bool AgenteIDFS::checkObstacle(int posF,int posC,Nodo * node){
	if(posF<0 || posC<0 || posF>=table.size() || posC>=table[0].length())return true;
	else if(table[posF][posC]=='W' || searchBox(posF,posC, node)){
		return true;
	}
	else return false;


}

bool AgenteIDFS::expand(Nodo * node ,char move){

	switch (move){
		case 'R':
			if(table[node->getPosPlayer(0)][node->getPosPlayer(1)+1]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)+1, node) && checkObstacle(node->getPosPlayer(0),node->getPosPlayer(1)+2,node)) return false;
			else return true;
		break;
		case 'L':
			if(table[node->getPosPlayer(0)][node->getPosPlayer(1)-1]=='W') return false;
			else if(searchBox(node->getPosPlayer(0),node->getPosPlayer(1)-1, node) && checkObstacle(node->getPosPlayer(0),node->getPosPlayer(1)-2,node)) return false;
			else return true;
		break;
		case 'D':
			if(table[node->getPosPlayer(0)+1][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)+1,node->getPosPlayer(1), node) && checkObstacle(node->getPosPlayer(0)+2,node->getPosPlayer(1),node)) return false;
			else return true;
	
		break;
		case 'U':
			if(table[node->getPosPlayer(0)-1][node->getPosPlayer(1)]=='W') return false;
			else if(searchBox(node->getPosPlayer(0)-1,node->getPosPlayer(1), node) && checkObstacle(node->getPosPlayer(0)-2,node->getPosPlayer(1),node)) return false;
			else return true;
		break;

	}

	return false;
}


int** AgenteIDFS::moveBox(Nodo * node,int * pos,char accion){
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
		}
	}
	

	return newBoxes;
}

bool AgenteIDFS::checkExploredBoxes(Nodo * node, int ** boxes){
	for (int  i = 0; i < numBoxes; i++){
		if(node->getPosBoxes(i,0)!=boxes[i][0] || node->getPosBoxes(i,1)!=boxes[i][1]) return false;
	}
	return true;
}


bool AgenteIDFS::checkExplored(int* pos, int ** boxes){

	for (int i = 0; i < explored.size(); i++){
		if(explored[i]->getPosPlayer(0)==pos[0] &&
		   explored[i]->getPosPlayer(1)==pos[1] &&
		   checkExploredBoxes(explored[i],boxes)
		   ){
			return false;
		}
	}
	return true;

}

void AgenteIDFS::expandNode(){

	explored.push_back(nodes.top());

	
	Nodo * actualNode=nodes.top();
	
	nodes.pop();


	if(expand(actualNode,'R')){
		//cout << "R" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)+1;
		
		int** boxes =moveBox(actualNode,pos,'R');
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("-R"));
			nodes.push(node);
		}
	}	


	if(expand(actualNode,'L')){
		//cout << "L" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)-1;

		int** boxes =moveBox(actualNode,pos,'L');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("-L"));
			nodes.push(node);
		}
	}

	if(expand(actualNode,'D')){
		//cout << "D" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)+1;
		pos[1]=actualNode->getPosPlayer(1);

		int** boxes =moveBox(actualNode,pos,'D');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("-D"));
			nodes.push(node);
		}
	}

	if(expand(actualNode,'U')){
		//cout << "U" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)-1;
		pos[1]=actualNode->getPosPlayer(1);

		int** boxes =moveBox(actualNode,pos,'U');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("-U"));
			nodes.push(node);
		}
	}
		
}

bool AgenteIDFS::isSolve(){
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


void AgenteIDFS::iniciarBusqueda(){

	deepLimit=0;

		
	while(!isSolve()){

		//cout << "Profundidad: " << nodes.top()->getProf() << endl;
		cout << "Profundidad: " << deepLimit << endl;

		if(nodes.top()->getProf()<deepLimit)expandNode();	
		else nodes.pop();
			

		if(nodes.empty()){
			deepLimit++;

			for (int j = 0; j < explored.size(); j++){
				explored.pop_back();
			}

			nodes.push(raiz);	
		}
	}
	

	cout << "CAMINO:" << endl;
	cout <<	nodes.top()->getPath() << endl; 
	
}
