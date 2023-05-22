// Player.cpp

#include "provided.h"
#include "support.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

colBestDepth determineBestComputerMove(Scaffold& s, int N, int color);
colBestDepth determineBestHumanMove(Scaffold& s, int N, int color);

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)                            //Done
{
    int column = 0;
    bool validColumn = false;
    while(!validColumn) //User enters a column until they have entered a vald one
    {
        cout << "Enter Column Number: ";
        cin >> column;
        if(column >= 1 && column <= s.cols() && s.checkerAt(column, s.levels()) == VACANT) //Checks column validity
            validColumn = true;
    }
    return column;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)                              //Done
{
    //Always picks the leftmost valid column
    for(int i = 1; i <= s.cols(); i++)
        if(s.checkerAt(i, s.levels()) == VACANT) //Checks if the column is open for a move
            return i;
    return 0;
    
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)                            //Done
{
    // AlarmClock ac(9900);
    Scaffold copy = s; //Make a copy of the scaffold because it is passed in as a constant reference
    
    int tempReturn = determineBestComputerMove(copy, N, color).col(); //Takes the column of the best move and returns it
    // if(ac.timedOut())
    //     cerr << "Out of Time!" << endl;
    // else
    //     cerr << "You passed!" << endl;
    return tempReturn;
}

//************************  Non-Member Functions  *****************************

colBestDepth determineBestComputerMove(Scaffold& s, int N, int color) //Returns the bestDepth associated with the input color for the given scaffold for the given N
{
    //Coded similar to algorithm described in the spec
    vector<int> bestDepths(s.cols()); //use a vector to store all the bestDepths
    for(int i = 1; i <= s.cols(); i++) //Runs through all the columns
    {
        if(s.checkerAt(i, s.levels()) == VACANT) //Checks if the move is valid
        {
            s.makeMove(i, color); //Makes the move
            int result = rate(s, N, color); //Rates the move
            if(result == 1 || result == 0) //If the move results in a win or tie it shortcuts and returns this as the best possible move
            {
                s.undoMove();
                return colBestDepth(i, result * BIGNUMBER);
            }
            else //Otherwise we find the best move from the determineBestHumanMove and store it in the bestDepths vector
            {
                int humanBestDepth = determineBestHumanMove(s, N, color).bestDepth();
                //Have the also update the depth of this by +1 or -1
                if(humanBestDepth > 0)
                    bestDepths[i-1] = humanBestDepth - 1;
                else if(humanBestDepth < 0)
                    bestDepths[i-1] = humanBestDepth + 1;
                else
                    bestDepths[i-1] = 0;
            }
            s.undoMove(); //Undo the move
        }
        else //If the move is invalid we just put a big negative number in that bestDepths slot
            bestDepths[i-1] = -2 * BIGNUMBER;
    }
    
    int bestDepth = bestDepths[0];
    int bestCol = 1;
    for(int i = 1; i <= s.cols(); i++)
    {
        if(bestDepths[i-1] > bestDepth) //Finds the max best depth and returns it, because that is the best computer move
        {
            bestDepth = bestDepths[i-1];
            bestCol = i;
        }
    }
    return colBestDepth(bestCol, bestDepth);
}

colBestDepth determineBestHumanMove(Scaffold& s, int N, int color) //Returns the bestDepth associated with the input color for the given scaffold for the given N (this is like the other player when called by determineBestComputerMove)
{
    //Coded similar to algorithm described in the spec
    vector<int> bestDepths(s.cols()); //use a vector to store all the bestDepths
    for(int i = 1; i <= s.cols(); i++) //Runs through all the columns
    {
        if(s.checkerAt(i, s.levels()) == VACANT) //Checks column validity
        {
            if(color == BLACK) //Need to make the move with the opposite color from the input
                s.makeMove(i, RED);
            else
                s.makeMove(i, BLACK);
            int result = rate(s, N, color);
            if(result == -1 || result == 0) //If this results in a win/tie for the "human" then we shortcut and return it as the colBestDepth
            {
                s.undoMove();
                return colBestDepth(i, result * BIGNUMBER);
            }
            else //Otherwise we find what the bestComputerMove is and store it in the bestDepths vector
            {
                int computerBestDepth = determineBestComputerMove(s, N, color).bestDepth();
                //Have the also update the depth of this by +1 or -1
                if(computerBestDepth > 0)
                    bestDepths[i-1] = computerBestDepth - 1;
                else if(computerBestDepth < 0)
                    bestDepths[i-1] = computerBestDepth + 1;
                else
                    bestDepths[i-1] = 0;
            }
            s.undoMove(); //undo the move
        }
        else
            bestDepths[i-1] = 2 * BIGNUMBER; //Otherwise store a large number in that vector slot
    }
    
    
    int bestDepth = bestDepths[0];
    int bestCol = 1;
    for(int i = 1; i <= s.cols(); i++)
    {
        if(bestDepths[i-1] < bestDepth)
        {
            bestDepth = bestDepths[i-1]; //Finds the min best depth and returns it, because that is the best human move
            bestCol = i;
        }
    }
    return colBestDepth(bestCol, bestDepth);
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
