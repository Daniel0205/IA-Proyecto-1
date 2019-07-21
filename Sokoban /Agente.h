#ifndef AGENTE_H
#define AGENTE_H
#include <string>
#include <vector>
//#include <stack>
#include <queue>
#include "Nodo.h"

#include <iostream>

using namespace std;

class Agente{
    private:
        vector <string> table;
        queue <Nodo *> nodes;
        //stack <Nodo *> nodesProf;
        int numBoxes;
        int **targets;

    public:
        Agente(int numBoxesIn, int* pos, int ** cajasInit,vector <string> * table);
        ~Agente();
        void identifyTargets();
        bool searchBox(int posF, int posC, Nodo * node);
        bool expand(Nodo * node ,char move);
        int** moveBox(Nodo * node,int * pos,char accion);
        bool checkObstacle(int posF,int posC,Nodo * node);
        bool isSolve();
        void expandNode();

        void iniciarBusqueda();
       

};

#endif