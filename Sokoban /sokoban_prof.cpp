#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>


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
	string* table = new string [endTable];

	for (int i = 0; i <endTable; i++){
		table[i]=file[i];			
		//cout << table[i] << endl;
	}

	states.push(table);
	

}


int main(int argc, char **argv){

	leerArchivo("nivel1.txt");

	for (int i = 0; i <states.top()->length(); i++){
		cout << states.top()[i] << endl;
	}	

	
	
	
}




