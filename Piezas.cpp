#include "Piezas.h"
#include <gtest/gtest.h>
#include <vector>
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

const int rows = 3;
const int columns = 4;
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
    board.resize(rows);
    for(int i = 0;i < (int)board.size(); i++)
    {
        board[i].resize(columns);
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
    //drop piece on given column 
    /*for(int i = 0; i < columns; i++){
        if(board[column][i] == Blank){
            board[column][i] = turn;
            return turn;
        }
    }*/
    /*bool full = true;
    for(int i=0; i< rows; i++){
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
    }*/
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    return Blank;
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
    return Blank;
}

TEST(PiezasTest, setup){
    Practice obj;
    Piece actual = obj.gameState();
    ASSERT_EQ(actual, Blank);
}