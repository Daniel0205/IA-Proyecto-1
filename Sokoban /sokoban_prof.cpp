#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>


using namespace std;

stack <string*> states;


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
	string* table = new string [endTable];

	for (int i = 0; i <endTable; i++){
		table[i]=file[i];			
	}

	states.push(table);

	//Se almacena la posición del jugador en las variables de tipo entero posJuX y posJuY

	int posJuX = 0, posJuY = 0;
	
	vector <string> posicionJu; 
    stringstream check1(file[endTable]);
    string intermediate;

    while(getline(check1, intermediate, ',')) 
    { 
        posicionJu.push_back(intermediate); 
    } 

	posJuX = stoi(posicionJu[0]);
	posJuY = stoi(posicionJu[1]);

	cout << "Posición del jugador: " << posJuX << "," << posJuY << endl;

	// La ubicación de las cajas a mover se encuentran almacenadas en 

	int cajasInit[(file.size() - (endTable+1))][2];
	int bandera = 0;

	for(int i = (endTable+1) ; i<file.size() ; i++){

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

	for (int i = 0; i < 2 ; i++){
		cout << "Posición de la caja "<< i+1 << ": " << cajasInit[i][0] << "," << cajasInit[i][1] << endl;
	}	

}


int main(int argc, char **argv){

	leerArchivo("nivel3.txt");

	for (int i = 0; i <states.top()->length(); i++){
		cout << states.top()[i] << endl;
	}	

	
	
	
}




