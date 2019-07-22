#ifndef AGENTEIDFS_H
#define AGENTEIDFS_H
#include <string>
#include <vector>
#include <stack>
#include "Nodo.h"

#include <iostream>

using namespace std;

class AgenteIDFS{
    private:
        vector <string> table;
        vector <Nodo *> explored;
        stack <Nodo *> nodes;
        Nodo * raiz;
        int numBoxes;
        int **targets;
        int deepLimit; 


    public:
        AgenteIDFS(int numBoxesIn, int* pos, int ** cajasInit,vector <string> * table);
        ~AgenteIDFS();
        void identifyTargets();
        bool searchBox(int posF, int posC, Nodo * node);
        bool expand(Nodo * node ,char move);
        int** moveBox(Nodo * node,int * pos,char accion);
        bool checkObstacle(int posF,int posC,Nodo * node);
        bool isSolve();
        void expandNode();
        bool checkExplored(int* pos, int ** boxes);
        bool checkExploredBoxes(Nodo * node, int ** boxes);

        string iniciarBusqueda();
       

};

#endif