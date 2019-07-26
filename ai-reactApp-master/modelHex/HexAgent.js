const Agent = require('ai-agents').Agent;

import Node from "./Node"



class HexAgent extends Agent {
    constructor(value) {
        super(value);
        this.tree=[];
        this.size=0;
        this.board=[];
        this.check=[];
        
    }



    expandNode(type,father){
        
        for (let i = 0; i < this.size; i++) {
            
            for (let j = 0; j < this.size-2; j++) {
                if(this.board[i][j]==0){
                    this.tree.unshift(new Node(father,father.getBoard().slice(),type,father.getDepth()+1));
                    this.tree[0].setPlay(i,j,this.getID());
                }
            }
        }
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


    miniMax(){
        while(this.tree!=0){
            let actualNode=this.tree.shift();
            
            //console.log(actualNode);
            //console.log(this.check);

            if(actualNode.getDepth()==9){
                //console.log(actualNode);
                actualNode.calculateHeuristic();        
                actualNode.informFather();
            }
            else if(this.isExplored(actualNode.getBoard())){
                console.log("expandio");
               /* console.log(actualNode);*/
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
        this.board = this.perception;
        this.size = this.board.length;
        
       // console.log("TABLERO INICAIL")
        console.log( this.perception)

        this.tree.unshift(new Node(null,this.board,"Max",0));
        

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
