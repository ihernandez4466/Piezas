#include "Piezas.h"
#include <gtest/gtest.h>
#include <vector>
#include<iostream>
using namespace std;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/

const int ROWS = 3;
const int COLUMNS = 4;

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

Piezas::Piezas()
{
    reset();
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    board.resize(ROWS);
    for(int i = 0;i < (int)board.size(); i++)
    {
        board[i].resize(COLUMNS);
    }

    for(int i = 0;i < (int)board.size(); i++)
    {
        for(int j = 0;j < (int)board[i].size(); j++)
        {
            board[i][j] = Blank;
        }
    }
    turn = X;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{ 
    //out of bounds coordinates
    if(column >= COLUMNS || column < 0){
        //lose a turn
        if(turn == X){
            turn = O;
        }
        else{
            turn = X;
        }
        return Invalid;
    }
    //dont allow piece to be placed in a location where a column is full
    bool full = true;
    for(int i=0; i < ROWS; i++){
        if(board[i][column] == Blank){
            full = false;
        }
    }
    if(full){
        if(turn == X){
            turn = O;
        }
        else{
            turn = X;
        }
        return Blank;
    }
    //drop piece on given column already checked to see if valid
    for(int i = 0; i < COLUMNS; i++){
        if(board[i][column] == Blank){
            board[i][column] = turn;
            if(turn == X){
                turn = O;
            }
            else{
                turn = X;
            }
            return board[i][column];
        }
    }   
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    //out of bounds
    if ((row >= ROWS || row < 0) || (column >= COLUMNS || column < 0))
    {
        return Invalid;
    }
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    //check is board is full 
    bool full = true;
    for(int i=0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            if(board[i][j] == Blank){
                return Invalid;
            }
        }
    }
    //check rows
    int Xmax, Xcur, Omax, Ocur = 0;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS-1; j++){
            if(board[i][j] == X && board[i][j+1] == X){
                Xcur++;
            }
            else if(board[i][j] == O && board[i][j+1] == O){
                Ocur++;
            }
            else if(j == COLUMNS-1){
                if(Xcur > Xmax){
                    Xmax = Xcur;
                }
                if(Ocur > Omax){
                    Omax = Ocur;
                }
            }
        }
    }
    //check columns
    Xcur, Ocur = 0;
    for(int i = 0; i < ROWS-1; i++){
        for(int j = 0; j < COLUMNS; j++){
            if(board[i][j] == X && board[i+1][j] == X){
                Xcur++;
            }
            else if(board[i][j] == O && board[i+1][j] == O){
                Ocur++;
            }
            else if(i == ROWS-1){
                if(Xcur > Xmax){
                    Xmax = Xcur;
                }
                if(Ocur > Omax){
                    Omax = Ocur;
                }
            }
        }
    }
    if(Xmax == Omax){
        return Invalid;
    }
    else if(Xmax > Omax){
        return X;
    }
    else
    {
        return O;
    }
    
}

TEST(PiezasTest, dropPiece){
    Piezas obj;
    Piece actual = obj.dropPiece(0);
    ASSERT_EQ('X', obj.pieceAt(0,0));
}
TEST(PiezasTest, dropPieceInvalid){
    Piezas obj;
    Piece actual = obj.dropPiece(-1);
    ASSERT_EQ(Invalid, actual);
}

TEST(PiezasTest, reset){
    
    Piezas obj;
    Piece actual = obj.dropPiece(0);
    Piece actual1 = obj.dropPiece(2);
    Piece actual2 = obj.dropPiece(1);
    obj.reset();

    ASSERT_EQ(Blank, obj.pieceAt(0,0));
    ASSERT_EQ(Blank, obj.pieceAt(0,1));
    ASSERT_EQ(Blank, obj.pieceAt(0,2));
}

TEST(PiezasTest, FullBoard){
    
    Piezas obj;
    obj.dropPiece(0);
    obj.dropPiece(0);
    obj.dropPiece(0);
    Piece actual = obj.dropPiece(0);

    ASSERT_EQ(Blank, actual);
}
TEST(PiezasTest, FullBoardDifferentColumn){
    
    Piezas obj;
    obj.dropPiece(2);
    obj.dropPiece(2);
    obj.dropPiece(2);
    Piece actual = obj.dropPiece(2);

    ASSERT_EQ(Blank, actual);
}

TEST(PiezasTest, outOfBounds){
    
    Piezas obj;
    Piece actual = obj.pieceAt(-1, 0);
    Piece actual1 = obj.pieceAt(2, 6);
    Piece actual2 = obj.pieceAt(3, 2);

    ASSERT_EQ(Invalid, actual);
    ASSERT_EQ(Invalid, actual1);
    ASSERT_EQ(Invalid, actual2);
}
TEST(PiezasTest, NotoutOfBounds){
    
    Piezas obj;
    Piece actual = obj.dropPiece(1);
    Piece actual1 = obj.dropPiece(2);
    Piece actual2 = obj.dropPiece(3);

    ASSERT_EQ(X, actual);
    ASSERT_EQ(O, actual1);
    ASSERT_EQ(X, actual2);
}
TEST(PiezasTest, GameState){
   Piezas obj;
   obj.dropPiece(0);    //X
   obj.dropPiece(1);    //O
   obj.dropPiece(0);    //X
   obj.dropPiece(0);    //O
   obj.dropPiece(2);    //X
   obj.dropPiece(2);    //O
   obj.dropPiece(1);    //X
   obj.dropPiece(2);    //O
    obj.dropPiece(1);   //X
    obj.dropPiece(2);   //O
    obj.dropPiece(0);   //X
    obj.dropPiece(1);   //0

    Piece result = obj.gameState();

    ASSERT_EQ(O, result);


}