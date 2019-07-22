#include "AgenteBFS.h"

AgenteBFS::AgenteBFS(int numBoxesIn, int* pos, int ** cajasInit,vector<string> *tableIn){	
	table=*tableIn;
    numBoxes=numBoxesIn;
	    
    Nodo * node = new Nodo(pos,cajasInit,0);

	nodes.push(node);
}

AgenteBFS::~AgenteBFS(){}

//Esta función identifica las posiciones de los objetivos a los que deben llegar las cajas
void AgenteBFS::identifyTargets(){
	
	int band=0;

	targets = new int*[numBoxes];

	for (int i = 0; i < table.size(); i++){
		for (int j = 0; j < table[i].size(); j++){

			if (table[i][j]=='X'){

				targets[band] = new int[2];

				targets[band][0] = i;
				targets[band][1] = j;
				band++;
			}
			
		}
		
	}
	
}

bool AgenteBFS::searchBox(int posF, int posC, Nodo * node){

	for (int i = 0; i < numBoxes; i++){
		
		if(node->getPosBoxes(i,0)==posF && node->getPosBoxes(i,1)==posC)return true;
	}
	
	return false;
}

bool AgenteBFS::checkObstacle(int posF,int posC,Nodo * node){
	if(posF<0 || posC<0 || posF>=table.size() || posC>=table[0].length())return true;
	else if(table[posF][posC]=='W' || searchBox(posF,posC, node)){
		return true;
	}
	else return false;

}

bool AgenteBFS::expand(Nodo * node ,char move){

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


int** AgenteBFS::moveBox(Nodo * node,int * pos,char accion){
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

bool AgenteBFS::checkExploredBoxes(Nodo * node, int ** boxes){
	for (int  i = 0; i < numBoxes; i++){
		if(node->getPosBoxes(i,0)!=boxes[i][0] || node->getPosBoxes(i,1)!=boxes[i][1]) return false;
	}
	return true;
}


bool AgenteBFS::checkExplored(int* pos, int ** boxes){

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

void AgenteBFS::expandNode(){
	
	Nodo * actualNode=nodes.front();
	
	nodes.pop();

	if(expand(actualNode,'U')){
		//cout << "U" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0)-1;
		pos[1]=actualNode->getPosPlayer(1);

		int** boxes =moveBox(actualNode,pos,'U');
		
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("U"));
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
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("D"));
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
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("L"));
			nodes.push(node);
		}
	}

	
	if(expand(actualNode,'R')){
		//cout << "R" << endl;
		int * pos = new int [2];
		pos[0]=actualNode->getPosPlayer(0);
		pos[1]=actualNode->getPosPlayer(1)+1;
		
		int** boxes =moveBox(actualNode,pos,'R');
		if(checkExplored(pos,boxes)){
			Nodo * node = new Nodo(pos,boxes,actualNode->getProf()+1,actualNode->getPath().append("R"));
			nodes.push(node);
		}
	}	

}

bool AgenteBFS::isSolve(){
	int counting = 0;
	

	for (int i = 0; i < numBoxes; i++){
		
		if(searchBox(targets[i][0],targets[i][1], nodes.front())){
			counting++;
		}
		
	}
		
	if(counting == numBoxes){
		return true;
	}else return false;
	
}


string AgenteBFS::iniciarBusqueda(){

	
	while(!isSolve()){
		if(nodes.front()->getProf()>=64){
			nodes.pop();
		}else{
			explored.push_back(nodes.front());
			expandNode();
		}
	}

	
	return	nodes.front()->getPath(); 
	
}
