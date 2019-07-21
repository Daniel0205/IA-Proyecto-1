#ifndef AGENTEDFS_H
#define AGENTEDFS_H
#include <string>
#include <vector>
#include <stack>
#include "Nodo.h"

#include <iostream>

using namespace std;

class AgenteDFS{
    private:
        vector <string> table;
        vector <Nodo *> explored;
        stack <Nodo *> nodes;
        int numBoxes;
        int **targets;


    public:
        AgenteDFS(int numBoxesIn, int* pos, int ** cajasInit,vector <string> * table);
        ~AgenteDFS();
        void identifyTargets();
        bool searchBox(int posF, int posC, Nodo * node);
        bool expand(Nodo * node ,char move);
        int** moveBox(Nodo * node,int * pos,char accion);
        bool checkObstacle(int posF,int posC,Nodo * node);
        bool isSolve();
        void expandNode();
        bool checkExplored(int* pos, int ** boxes);
        bool checkExploredBoxes(Nodo * node, int ** boxes);

        void iniciarBusqueda();
       

};

#endif