const Graph = require('node-dijkstra');

export default class Node{
    constructor(father,state,type,depth){
        this.father=father;
        this.state=state;
        this.type=type;
        this.depth=depth;
        this.utility=Infinity;
        
    }

    getDepth(){
        return this.depth;
    }

    getType(){
        return this.type;
    }

    setUtility(value){
        if(this.type=="Min")this.utility=Math.min(value,this.utility);
        else this.utility=Math.max(value,this.utility)
    }

    informFather(){
        this.father.setUtility(this.utility);
    }

    calculateHeuristic(player){

        /*
        let prueba = [[0,"2","1",0,"1"],[0,0,0,"2","1"],[0,0,0,0,"1"],[0,0,0,"2","1"],[0,0,"1",0,0]]
        let prove = this.shortestPath(this.transpose(prueba,"2"),player).cost - this.shortestPath(prueba,"2").cost;
        //console.log(prove);
        return(prove)
        */

        if (this.type == "Max"){
            this.utility = this.shortestPath(this.transpose(this.state),player).cost - this.shortestPath(this.state,player).cost;
        } else{
            this.utility=this.shortestPath(this.state,player).cost - this.shortestPath(this.transpose(this.state,player)).cost;
        }
        
    }

    shortestPath(board,player){
        const graph = new Graph();
        let size = board.length;

        for (let i = 0; i < size; i++) {
            for (let j = 0; j < size; j++) {

                let key = i*size + j;
                let neighbors = this.getNeighborhood(key,board,player);
               
                if (j === 0) { 
                    if (board[i][j]===0) {
                        neighbors['L'] = 2; 
                    }else if(board[i][j]===player){
                        neighbors['L'] = 1; 
                    }
                }
                if (j === size - 1) {
                    if (board[i][j]===0) {
                        neighbors['R'] = 2; 
                    }else if(board[i][j]===player){
                        neighbors['R'] = 1; 
                    }
                }

                graph.addNode(key+'',neighbors); 
                
            }        
        }

        let neighborsL = {};
        let neighborsR = {};
    
        for (let i = 0; i < size; i++) {
            if (board[i][0] === 0) {
                neighborsL[(i * size) + ''] = 1;
            }else if(board[i][0] === 1){
                neighborsL[(i * size) + ''] = 0;
            }
            if (board[i][size - 1] === 0) {
                neighborsR[(i * size + size - 1) + ''] = 1;
            }else if(board[i][size - 1] === 1){
                neighborsR[(i * size + size - 1) + ''] = 0;
            }
        }
    
        graph.addNode('L', neighborsL);
        graph.addNode('R', neighborsR)
        /*
        console.log(neighborsL);
        console.log(neighborsR);
        */
       console.log(graph.path('L','R',{cost:true}));
       return graph.path('L','R',{cost:true});
    
    }


    getNeighborhood(key,board,player) {
        let size = board.length;
        let row = Math.floor(key / size);
        let col = key % size;
        let result = {};
        
        if(this.insertNeighbor(row-1,col)){
            let name = (row-1)*size + col;
            if(board[row-1][col]=== 0){
                result[name+'']=2;
            }else if(board[row-1][col]=== player){
                result[name+''] = 1;
            }
        }

        if(this.insertNeighbor(row-1,col+1)){
            let name = (row-1)*size + (col+1);
            if(board[row-1][col+1]=== 0){
                result[name+'']=2;
            }else if(board[row-1][col+1]=== player){
                result[name+'']= 1;
            }
        }
        
        if(this.insertNeighbor(row,col+1)){
            let name = (row)*size + (col+1);
            if(board[row][col+1]=== 0){
                result[name+'']=2;
            }else if(board[row][col+1]=== player){
                result[name+''] = 1;
            }
        }

        if(this.insertNeighbor(row+1,col)){
            let name = (row+1)*size + col;
            if(board[row+1][col]=== 0){
                result[name+'']=2;
            }else if(board[row+1][col]=== player){
                result[name+''] = 1;
            }
        }

        if(this.insertNeighbor(row+1,col-1)){
            let name = (row+1)*size + (col-1);
            if(board[row+1][col-1]=== 0){
                result[name+'']=2;
            }else if(board[row+1][col-1]=== player){
                result[name+''] = 1;
            }
        }

        if(this.insertNeighbor(row-1,col-1)){
            let name = (row-1)*size + (col-1);
            if(board[row][col-1]=== 0){
                result[name+'']=2;
            }else if(board[row][col-1]=== player){
                result[name+''] = 1;
            }
        }

        
       return result;
    }


    insertNeighbor(row,col){
        if(row >= 0 && row < this.state.length && col >= 0 && col < this.state.length){
            return true;
        }else{
            return false;
        }
    }

    transpose(board) {
        let size = board.length;
        let boardT = new Array(size);
        for (let j = 0; j < size; j++) {
            boardT[j] = new Array(size);
            for (let i = 0; i < size; i++) {
                boardT[j][i] = board[i][j];
                if (boardT[j][i] === '1') {
                    boardT[j][i] = '2';
                } else if (boardT[j][i] === '2') {
                    boardT[j][i] = '1';
                }
            }
        }
        return boardT;
    }


}