const Agent = require('ai-agents').Agent;

const Graph = require('node-dijkstra');




class HexAgent extends Agent {
    constructor(value) {
        super(value);
        this.tree=[];
        this.size=0;
        this.board=[];
        this.check=[];
        this.raiz;

        this.expandNode=this.expandNode.bind(this)
        this.arraysEqual=this.arraysEqual.bind(this)
        this.isExplored=this.isExplored.bind(this)
        this.miniMax=this.miniMax.bind(this);
    }


    arraysEqual(arr1, arr2) {

        for(var i = arr1.length; i--;) {
            for(var j = arr1.length; j--;) {
                if(arr1[i][j] !== arr2[i][j]) return false;
            }
        }
    
        return true;
    }

    isExplored(board){
        for (let i = 0; i < this.check.length; i++) {
            if(this.arraysEqual(board,this.check[i].getBoard())){

                return false;            

            }
        }
        return true;
    }

    expandNode(type,father){
        var sons = []
        
        
        for (let i = 0; i < this.size; i++) {
            
            for (let j = 0; j < this.size; j++) {
                let aux = father.getBoard().map(function (arr) { return arr.slice(); });
                if(aux[i][j]===0){ //&& (father.getDepth()!==0 || i!== Math.floor(this.size / 2) || j !== Math.floor(this.size / 2))){


                    if(type=="Max")aux[i][j]=this.getID();
                    else if(type=="Min"){
                        if(this.getID()=="1")aux[i][j]="2";
                        else aux[i][j]="1"
                    }
                    
                    
                    if(this.isExplored(father.getBoard())) sons.unshift(new Node(father,aux,type,father.getDepth()+1,i,j));
                   // if(father.getDepth()+1==1)console.log(this.tree[0])
                }
            }
        }
        return sons;
    }

    miniMaxPoda(player,alfa,beta){

        if(player.getDepth()==3){
             player.calculateHeuristic();        
             player.informFather();
             let utility = player.getUtility();
             return utility;
        }
        let hijos=this.expandNode(player.getType(),player);
        if(player.getType()==="Max"){
            for (let i = 0; i < hijos.length; i++) {
                var puntuacion=this.miniMaxPoda(hijos[i],alfa,beta);
                if(puntuacion>alfa){
                    alfa=puntuacion
                }
                if(alfa>=beta){
                    return alfa;
                }
            }
            return alfa;
        }
        else{
            for (let i = 0; i < hijos.length; i++) {
                var puntuacion=this.miniMaxPoda(hijos[i],alfa,beta);
                if(puntuacion<beta){
                    beta=puntuacion
                }
                if(alfa>=beta){
                    return beta;
                }
            }
            return beta;

        }

    }


    miniMax(){
        while(this.tree.length!=0){

            let actualNode=this.tree.shift();
           // console.log(actualNode)

            
            if(actualNode.getDepth()==3){
               // console.log(actualNode)
                actualNode.calculateHeuristic();        
                actualNode.informFather();
            }
            else {
                if(actualNode.getType()=="Max")this.expandNode("Min",actualNode);
                else  this.expandNode("Max",actualNode);

                this.check.push(actualNode);
            }   
        }
        this.check=[];
    }
    



    
    /**
     * return a new move. The move is an array of two integers, representing the
     * row and column number of the hex to play. If the given movement is not valid,
     * the Hex controller will perform a random valid movement for the player
     * Example: [1, 1]
     */
    send() {
        this.board = this.perception.map(function (arr) { return arr.slice(); })
        this.size = this.board.length;

        this.raiz=new Node(null,this.board,"Max",0);


/*        this.tree.unshift();
        
        this.tree.unshift(new Node(null,this.perception.map(function (arr) { return arr.slice(); }),"Max",0,null,null));
          console.log(this.raiz.getPos());
        
        return this.raiz.getPos()
*/
        let num=this.miniMaxPoda(this.raiz,-100,100);

        console.log([this.raiz.getPos(),this.raiz.getUtility(),num])

        return this.raiz.getPos()
    }

}

module.exports = HexAgent;

/**
 * Return an array containing the id of the empty hex in the board
 * id = row * size + col;
 * @param {Matrix} board 
 */
function getEmptyHex(board) {
    let result = [];
    let size = board.length;
    for (let k = 0; k < size; k++) {
        for (let j = 0; j < size; j++) {
            if (board[k][j] === 0) {
                result.push(k * size + j);
            }
        }
    }
    return result;
}


class Node{
    constructor(father,state,type,depth,fila, columna){
        this.father=father;
        this.state=state;
        this.type=type;
        this.depth=depth;
        this.fila=fila;
        this.columna=columna;
        
        if(type=="Min")this.utility=Infinity;
        else this.utility=-Infinity;
        
    }


    getBoard(){
        return this.state;
    }

    getDepth(){
        return this.depth;
    }

    getType(){
        return this.type;
    }

    setUtility(value,row,column){
        
        if(this.type=="Min"){
            this.utility=Math.min(value,this.utility);
        }
        else {
            this.utility=Math.max(value,this.utility)
            
        }
        
        if(this.depth!=0){
            //if(this.father==null)console.log(this.depth);
            this.informFather();
        }
        else if(this.utility==value ){
            //console.log([row,column])
            this.fila=row;
            this.columna=column;
        }

    }

    informFather(){
        //if(this.depth==1)console.log(this);
        this.father.setUtility(this.utility,this.fila,this.columna);
    }

    calculateHeuristic(player){

        /*
        let prueba = [[0,"2","1",0,"1"],[0,0,0,"2","1"],[0,0,0,0,"1"],[0,0,0,"2","1"],[0,0,"1",0,0]]
        let prove = this.shortestPath(this.transpose(prueba,"2"),player).cost - this.shortestPath(prueba,"2").cost;
        //console.log(prove);
        return(prove)
        */

        let oponentPath= this.shortestPath(this.transpose(this.state),player).cost;
        let playerPath = this.shortestPath(this.state,player).cost;

        if(oponentPath <= 7){
            this.utility = -Infinity;
        }else if(oponentPath <= 7){
            this.utility = Infinity;
        }else{
            if (this.type == "Max"){
                this.utility = oponentPath - playerPath;
            } else{
                this.utility=playerPath - oponentPath;
            }
        }
        
    }

    getUtility(){
        return this.utility;
    }

    getPos(){
        return [this.fila,this.columna];
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
                neighborsL[(i * size) + ''] = 2;
            }else if(board[i][0] === player){
                neighborsL[(i * size) + ''] = 1;
            }
            if (board[i][size - 1] === 0) {
                neighborsR[(i * size + size - 1) + ''] = 2;
            }else if(board[i][size - 1] === player){
                neighborsR[(i * size + size - 1) + ''] = 1;
            }
        }
    
        graph.addNode('L', neighborsL);
        graph.addNode('R', neighborsR)
        /*
        console.log(neighborsL);
        console.log(neighborsR);
        */
       //console.log(graph.path('L','R',{cost:true}));
    //   console.log(graph.path('L','R',{cost:true}));
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
