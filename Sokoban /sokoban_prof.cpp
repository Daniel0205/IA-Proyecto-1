#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <array>


using namespace std;

vector<string> table;
stack <int*> positions;
stack <int**> boxes;
int numBoxes;
int **targets;


void identifyTargets(){
	
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

	positions.push(pos);

	
	// La ubicación de las cajas a mover se encuentran almacenadas en cajasInit

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
	
	boxes.push(cajasInit);

	//Se guardaraán las posiciones de los objetivos en el arreglo "targets"

	identifyTargets();

}


int main(int argc, char **argv){

	leerArchivo("nivel3.txt");

	cout << "Posición del jugador: " << positions.top()[0] << "-" << positions.top()[1] << endl;

	for (int i = 0; i < numBoxes-1 ; i++){
		
		cout << "Posición de la caja "<< i+1 << ": " << boxes.top()[i][0] << "-" << boxes.top()[i][1] << endl;
		cout << "Posición del objetivo"<< i+1 << ": " << targets[i][0] << "-" << targets[i][1] << endl;
		
	}	

	for (int i = 0; i < table.size(); i++){
		cout << table[i] << endl;
	}
	
}




