#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include "Nodo.h"
#include "AgenteBFS.h"
#include "AgenteDFS.h"
#include "AgenteIDFS.h"

using namespace std;

vector <string> table;
int numBoxes;
int ** cajasInit;
int *pos;
int search=0;

AgenteDFS * agentDFS; 
AgenteBFS * agentBFS; 
AgenteIDFS * agentIDFS; 


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
		if(endTable==0)table.push_back(texto);
	}

	tablero.close();

	//Se almacena la posición del jugador en las variables de arreglo

	pos = new int[2];
	
	vector <string> posicionJu; 
    stringstream check1(file[endTable]);
    string intermediate;

 	getline(check1, intermediate, ',');
    posicionJu.push_back(intermediate); 
	getline(check1, intermediate, ',');
    posicionJu.push_back(intermediate); 
    

	pos[0] = stoi(posicionJu[0]);
	pos[1] = stoi(posicionJu[1]);


	cajasInit=new int*[(file.size() - (endTable))];
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
	

}



int main(int argc, char **argv){

	if(argc!=2) {
		cout << "Digite el nombre del archivo" ;
		return 0;
	}

	leerArchivo(argv[1]);

	cout << "Campo de juego:" << endl;

	for (int i = 0; i < table.size(); i++){
		cout << table[i] << endl;
	}
	cout << "Posicion del jugador [Fila, Columna]: "  << "[" << pos[0] << "," << pos[1] << "]"  << endl;
	
	cout << "Posicion de las cajas [Fila, Columna]: ";
	for (int i = 0; i < numBoxes; i++){
		cout << "[" << cajasInit[i][0] << "," << cajasInit[i][1] << "] " ;
	}

	cout << endl << endl;
	cout << "SELECCIONE EL NUMERO DEL TIPO DE BUSQUEDA:" << endl;
	cout << "1-PREFERENTE POR PROFUNDIDAD" << endl;
	cout << "2-PREFERENTE POR AMPLITUD" << endl;
	cout << "3-PROFUNDIDAD ITERATIVA" << endl  << endl ;

	cin >> search;
	
	cout << "CAMINO:" << endl;
	switch (search){
		case 1:
			agentDFS = new AgenteDFS(numBoxes,pos,cajasInit,&table);
			agentDFS->identifyTargets();
			cout << agentDFS->iniciarBusqueda() << endl;	
			break;
		case 2:
			agentBFS = new AgenteBFS(numBoxes,pos,cajasInit,&table);
			agentBFS->identifyTargets();
			cout << agentBFS->iniciarBusqueda() << endl;	
			break;
		case 3:
			agentIDFS = new AgenteIDFS(numBoxes,pos,cajasInit,&table);	
			agentIDFS->identifyTargets();
			cout << agentIDFS->iniciarBusqueda() << endl;
			break;
		default:
			cout << "Tipo de busqueda invalida." << endl;
			break;

	}
	
	cout << "Fin." << endl;

	
	
	

	

}
