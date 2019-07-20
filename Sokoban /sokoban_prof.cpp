#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include "Nodo.h"


using namespace std;

string* table;
stack <Nodo *> nodes;

int numBoxes;


void leerArchivo(string fileName){
		
	ifstream tablero(fileName);
	
	vector<string> file;
	int endTable=0;
	string texto;
	
	
	while(!tablero.eof()){
		tablero >> texto;
		if(texto[0]!='W' && texto[0]!='0' && texto[0]!='X' && endTable==0){
			endTable=file.size();
			
		}		
		file.push_back(texto);
	}

	tablero.close();

	//La variable table guarda como tal la el tablero del juego, es almacenado en la pila states
	table = new string [endTable];

	//Se almacena la posición del jugador en las variables de arreglo

	int *pos = new int[2];
	
	vector <string> posicionJu; 
    stringstream check1(file[endTable]);
    string intermediate;

 	getline(check1, intermediate, ',');
    posicionJu.push_back(intermediate); 
	getline(check1, intermediate, ',');
    posicionJu.push_back(intermediate); 
    

	pos[0] = stoi(posicionJu[0]);
	pos[1] = stoi(posicionJu[1]);


	
	// La ubicación de las cajas a mover se encuentran almacenadas en 

	int ** cajasInit=new int*[(file.size() - (endTable+1))];
	int bandera = 0;

	for(int i = (endTable+1) ; i<file.size() ; i++){

		cajasInit[bandera]= new int [2];

		vector <string> posicionCa; 
    	stringstream check(file[i]);
    	string intermediate;

    	while(getline(check, intermediate, ',')) 
    	{ 
        	posicionCa.push_back(intermediate); 
    	} 

		cajasInit[bandera][0] = stoi(posicionCa[0]);
		cajasInit[bandera][1] = stoi(posicionCa[1]);

		bandera++;
	}

	numBoxes=(file.size() - (endTable+1));
	

	Nodo * node = new Nodo(pos,cajasInit,0,NULL,NULL);

	nodes.push(node);

}


int main(int argc, char **argv){

	leerArchivo("nivel1.txt");

	cout << "Posición del jugador: " << nodes.top()->getPosPlayer(0) << "-" << nodes.top()->getPosPlayer(1) << endl;

	for (int i = 0; i < numBoxes-1 ; i++){
		
		cout << "Posición de la caja "<< i+1 << ": " << nodes.top()->getPosBoxes(i,0) << "-" << nodes.top()->getPosBoxes(i,1) << endl;
		
		
	}	

	for (int i = 0; i < table->size(); i++){
		cout << table[i] << endl;
	}
	
}




