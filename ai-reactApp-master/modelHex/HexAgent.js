const Agent = require('ai-agents').Agent;

import Node from "./Node"



class HexAgent extends Agent {
    constructor(value) {
        super(value);
        this.tree=[];
        this.size=0;
        this.board=[];
        this.check=[];

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
        
        
        for (let i = 0; i < this.size; i++) {
            
            for (let j = 0; j < this.size; j++) {
                let aux = father.getBoard().map(function (arr) { return arr.slice(); });
                if(this.board[i][j]==0){
                    aux[i][j]=this.getID();
                    if(this.isExplored(father.getBoard())) this.tree.unshift(new Node(father,aux,type,father.getDepth()+1,i,j));
                }
            }
        }

    }


    miniMax(){
        while(this.tree.length!=0){

            let actualNode=this.tree.shift();
            
            if(actualNode.getDepth()==3){
                actualNode.calculateHeuristic();        
                actualNode.informFather();
            }
            else {
                if(actualNode.getType()=="Max")this.expandNode("Min",actualNode);
                else  this.expandNode("Max",actualNode);

                this.check.push(actualNode);
            }   
        }
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

        this.tree.unshift(new Node(null,this.board.slice(),"Max",0,null,null));
        
        this.miniMax();

        let available = getEmptyHex(this.board);
        let nTurn = this.size * this.size - available.length;

        if (nTurn == 0) { // First move
            return [Math.floor(this.size / 2), Math.floor(this.size / 2) - 1];
        } else if (nTurn == 1){
            return [Math.floor(this.size / 2), Math.floor(this.size / 2)];
        }

        let move = available[Math.round(Math.random() * ( available.length -1 ))];
        return [Math.floor (move / this.board.length), move % this.board.length];
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
