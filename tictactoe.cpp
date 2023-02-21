#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <math.h>
#include <climits>
#include <sstream>

using namespace std;

class Board
{//the class tracks the game and the winner
    char positionsSelected[16];
    char winner;
    
public:
    Board()
    {//sets the board to blanks and the winner to 'z'
        cout<<"Creating a 4X4 board\n";
        winner = 'z'; 
        
        for(int i = 0; i < 16; i++)
        {
            positionsSelected[i] = '_';
        }
    }
    
    
    char* getPositions(void)
    {//return all the positions on the board after each input
        return positionsSelected;
    }
    
    
    int setPosition(int gridNumber, char user)
    {//set a given position to x or o
        {
            if(positionsSelected[gridNumber] == '_')
            {
                positionsSelected[gridNumber] = user;
                return 0;
            }
            else
            {
                //That position is taken;
                return -1;
            }
        }
        return 0;
    }
    
    char checkRows()
    {//check the rows for a winner
        int rows = 0;
        int columns = 0;
        int fourInRowX = 0;
        int fourInRowO = 0;
        
        
        for(int rows = 0; rows<16; rows=rows+4)
        {
            for(int i = 0; i < 4; i++)
            {
                if(positionsSelected[i + rows] == 'x')
                    fourInRowX++;
                if(positionsSelected[i + rows] == 'o')
                    fourInRowO++;
            }
            if(fourInRowX == 4)
            {
                //cout<<"ROWS X won\n";
                winner = 'x';
                return 'x';
            }
            if(fourInRowO == 4)
            {
                //cout<<"ROWS O won\n";
                winner = 'o';
                return 'o';
            }
            fourInRowX = 0;
            fourInRowO = 0;
        }
        return 'z';
    }
    
    char checkColumns()
    {//check the columns for a winner
        int rows = 0;
        int columns = 0;
        int fourInRowX = 0;
        int fourInRowO = 0;
        
        
        for(int columns = 0; columns<4; columns++)
        {
            for(int i = 0; i < 16; i= i + 4)
            {
                if(positionsSelected[i + columns] == 'x')
                    fourInRowX++;
                if(positionsSelected[i + columns] == 'o')
                    fourInRowO++;
            }
            if(fourInRowX == 4)
            {
                //COLUMNS X won
                winner = 'x';
                return 'x';
            }
            if(fourInRowO == 4)
            {
                //cout<<"COLUMNs O won"
                winner = 'o';
                return 'o';
            }
            fourInRowX = 0;
            fourInRowO = 0;
        }
        return 'z';
    }
    
    char checkDiagonals()
    {//check the diagonals for a winner
        char winner = 'z';
        int fourInRowX = 0;
        int fourInRowO = 0;
        
        //check left to right diagonal
        for(int i = 0; i < 16; i=i+5)
        {
            if(positionsSelected[i] == 'x')
                fourInRowX++;
            if(positionsSelected[i] == 'o')
                fourInRowO++;
        }
        
        //check right to left diagonal
        if(fourInRowO != 4 and fourInRowX != 4)
        {
            fourInRowX = 0;
            fourInRowO = 0;
            for(int i = 3; i < 15; i= i+3)
            {
                if(positionsSelected[i] == 'x')
                    fourInRowX++;
                if(positionsSelected[i] == 'o')
                    fourInRowO++;
            }
        }

        if(fourInRowX == 4)
        {
            //cout<<"DIAGONALS X won"
            winner = 'x';
            return winner;
        }
        if(fourInRowO == 4)
        {
            //cout<<"DIAGONALS O won"
            winner = 'o';
            return winner;
        }
        fourInRowX = 0;
        fourInRowO = 0;
        return winner;
    }

    char determineWinner()
    {//if 4 in a row, then there is a winner
        char winner = 'z';
        winner =  checkRows();
        if(winner == 'z')
            winner = checkColumns();
        if(winner =='z')
            winner = checkDiagonals();
        return winner;
    }
    
};




void getUserNames(string &, string &);
void printBlankBoard(string);
void printTheBoard(Board, string);
void printUserPrompt(string, char);
void printGameWinner(Board, string, string);
int  getUserResponse();
void checkResponse(Board&, char);
void writeTheBoard(Board);

using namespace std;

void checkResponse(Board &boardIn, char input)
{//checking that, the position selected is not already been taken.
    int position;
    int userInput;
    do
    {
        position = getUserResponse();
        userInput = boardIn.setPosition(position, input);
        if(userInput == -1)
        {
            cout<<"That postition is taken.";
        }
    }while(userInput == -1);
}

void getUserNames(string &userX, string &userY)
{
    cout<< "Name of user to be 'x' :";
    cin >>userX;
    cout<< "Name of user to be 'o' :";
    cin >>userY;
}

void printBlankBoard()
{//print a blank board, with numbered squares
    for(int i = 0; i <16; i++)
    {
        cout<<"|"<<i<<":";
        if(i <= 9)
            cout<<" ";
        if(i%4 == 3)
        {
            cout<<"|\n";
        }
    }
    cout<<"\n\n\n";
}

void printTheBoard(Board boardIn)
{//print the board with player moves 
    printBlankBoard();

    for(int i = 0; i <16; i++)
    {
        cout<<"|"<<boardIn.getPositions()[i];
        if(i%4 == 3)
        {
            cout<<"|\n";
        }
    }
    cout<<"\n\n\n";
}

void writeTheBoard(Board boardIn)
{//print the updated board with player moves
    cout<<"\n\n";
    for(int i = 0; i <16; i++)
    {
        cout<<"|"<<boardIn.getPositions()[i];
        if(i%4 == 3)
        {
            cout<<"|\n";
        }
    }
    cout<<"\n\n\n";
}

void printUserPrompt(string nameIn, char letter)
{//for user input
    cout<<"Where would you like to place an "<<letter<<"?\n";
}

void printGameWinner(Board boardIn, string nameX, string nameO)
{//print the winner statement
    char winner;
    winner = boardIn.determineWinner();
    if(winner == 'x')
    {
        cout<<"Congrats "<<nameX<<" you won!\nHurrey!!!\n\n";
    }
    if(winner == 'o')
    {
        cout<<"Congrats "<<nameO<<" you won!\n\n";
    }
}

int getUserResponse()
{//get the chosen user position, check that it is an integer
    //check that it is between 0 and 15
    int position = -1;
    cout<<"Enter an integer between 0 and 15: ";
    cin>>position;
    
    while(position > 15 or position < 0 or !cin)
    {
        cin.clear();
        cout<<"That is not a valid position\n";
        cout<<"Enter an integer between 0 and 15: ";
        cin.clear();
        cin>>position;
    }
    return position;
}



int main()
{
    Board gameBoard;
    string nameX;
    string nameO;
    
    int tieGame = 0;
    char gameWinner = 'z';
    int numTurns = 0;
    
    //get the names of the players
    getUserNames(nameX, nameO);
    
    //the game is played for 8 turns maximum
    while(numTurns < 8)
    {
        printTheBoard(gameBoard);
        //ask player x where they want to put an 'x'
        printUserPrompt(nameX, 'x');
        //check that the input is a valid position and that
        //it has not already been taken
        checkResponse(gameBoard, 'x');
        //check to see if player 'x' has four in a row somewhere on the board
        gameWinner = gameBoard.determineWinner();
        
        //if player 'x' has won, end the game
        if(gameWinner != 'z')
        {
            printTheBoard(gameBoard);
            writeTheBoard(gameBoard);
            printGameWinner(gameBoard, nameX, nameO);
            break;
        }
        //Now do the same for player 'o'
        printTheBoard(gameBoard);
        writeTheBoard(gameBoard);
        //ask player x where they want to put an 'o'
        printUserPrompt(nameO, 'o');
        //check that the input is a valid position and that
        //it has not already been taken
        checkResponse(gameBoard, 'o');

        printTheBoard(gameBoard);
        writeTheBoard(gameBoard);
        //check to see if player 'o' has four in a row somewhere on the board
        gameWinner = gameBoard.determineWinner();
        //if player 'o' has won, end the game
        if(gameWinner != 'z')
        {
            printTheBoard(gameBoard);
            writeTheBoard(gameBoard);
            printGameWinner(gameBoard, nameX, nameO);
            break;
        }
        numTurns++;
    }
    //if there is no winner at this point, the game is a tie
    if(numTurns >= 8)
        cout<<"Tie game.\n\n";
    return 0;
}

