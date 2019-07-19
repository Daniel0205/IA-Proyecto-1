#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>


using namespace std;

vector<string> table;
stack <int*> positions;
stack <int**> boxes;
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

	
	// La ubicación de las cajas a mover se encuentran almacenadas en 

	int ** cajasInit=new int*[(file.size() - (endTable))];
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

}

bool finish(){

	for (int i = 0; i < numBoxes; i++){
		cout << "Posición de la caja "<< i+1 << ": " << boxes.top()[i][0] << "-" << boxes.top()[i][1] << endl;
	}

	return true;
	
}

bool searchBox(int posF, int posC, int ** posBoxes){
	
	for (int i = 0; i < numBoxes; i++){
		if(posBoxes[i][0]==posF && posBoxes[i][1]==posC)return true;
	}
	
	return false;
}

bool expand(int * posjugador, int ** posBoxes,char move){

	switch (move){
		case 'R':
			if(table[posjugador[0]][posjugador[1]+1]=='W') return false;
			else if(searchBox(posjugador[0],posjugador[1]+1, posBoxes) && table[posjugador[0]][posjugador[1]+2]=='W') return false;
			else return true;
		break;
		case 'L':
			if(table[posjugador[0]][posjugador[1]-1]=='W') return false;
			else if(searchBox(posjugador[0],posjugador[1]-1, posBoxes) && table[posjugador[0]][posjugador[1]-2]=='W') return false;
			else return true;
		break;
		case 'D':
			if(table[posjugador[0]+1][posjugador[1]]=='W') return false;
			else if(searchBox(posjugador[0]+1,posjugador[1], posBoxes) && table[posjugador[0]+2][posjugador[1]]=='W') return false;
			else return true;

		break;
		case 'U':
			if(table[posjugador[0]-1][posjugador[1]]=='W') return false;
			else if(searchBox(posjugador[0]-1,posjugador[1], posBoxes) && table[posjugador[0]-2][posjugador[1]]=='W') return false;
			else return true;
		break;
	

	}
	


}

void expandNode(){
	int * actualPos=positions.top();
	int ** actualBox=boxes.top();

	positions.pop();
	boxes.pop();


	if(expand(actualPos,actualBox,'R')){
		cout << "R" << endl;
		positions.push(new int[2]);
		positions.top()[0]=actualPos[0];
		positions.top()[1]=actualPos[1]+1;
	}

	if(expand(actualPos,actualBox,'L')){
		cout << "L" << endl;
		positions.push(new int[2]);
		positions.top()[0]=actualPos[0];
		positions.top()[1]=actualPos[1]-1;
	}
	
	if(expand(actualPos,actualBox,'D')){
		cout << "D" << endl;
		positions.push(new int[2]);
		positions.top()[0]=actualPos[0]+1;
		positions.top()[1]=actualPos[1];
	}

	if(expand(actualPos,actualBox,'U')){
		cout << "U" << endl;
		positions.push(new int[2]);
		positions.top()[0]=actualPos[0]-1;
		positions.top()[1]=actualPos[1];
	}

}


int main(int argc, char **argv){

	leerArchivo("nivel3.txt");

	


	for (int i = 0; i < table.size(); i++){
		cout << table[i] << endl;
	}


	expandNode();

	for (int i = 0; i < positions.size(); i++){
		cout << "Posición del jugador: " << positions.top()[0] << "-" << positions.top()[1] << endl;
		positions.pop();
		i--;
	}
		

}