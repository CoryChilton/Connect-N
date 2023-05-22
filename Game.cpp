// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
private:
    Scaffold m_scaffold;
    Player* m_red;
    Player* m_black;
    int m_N;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)            //done
 :m_scaffold(nColumns, nLevels), m_red(red), m_black(black), m_N(N)
{
    if(m_N <= 0) //Checks validity of m_N, validity of columns and levels is checked in scaffold
        exit(0);
}

bool GameImpl::completed(int& winner) const                                                 //done
{
    //First tests all the different ways a color could win
    if(Nhorizontal(RED, m_N, m_scaffold))
        winner = RED;
    else if(Nhorizontal(BLACK, m_N, m_scaffold))
        winner = BLACK;
    else if(Nvertical(RED, m_N, m_scaffold))
        winner = RED;
    else if(Nvertical(BLACK, m_N, m_scaffold))
        winner = BLACK;
    else if(Ndiagonal(RED, m_N, m_scaffold))
        winner = RED;
    else if(Ndiagonal(BLACK, m_N, m_scaffold))
        winner = BLACK;
    else if(m_scaffold.numberEmpty() != 0) //Then tests of the game can continue or if its a tie
        return false;
    else
        winner = TIE_GAME;
    return true;
}

bool GameImpl::takeTurn()                                                                   //done
{
    int winner;
    int move;
    if(completed(winner)) //Checks if the game is over
        return false;
    if( ((m_scaffold.numberEmpty() - (m_scaffold.levels() * m_scaffold.cols())) % 2 == 0)) //Figures out if it's red's turn
    {
        //Makes the move for red depending on the player type
        move = m_red->chooseMove(m_scaffold, m_N, RED);
        m_scaffold.makeMove(move, RED);
    }
    else
    {
        //Makes the move for black depending on the player type
        move = m_black->chooseMove(m_scaffold, m_N, BLACK);
        m_scaffold.makeMove(move, BLACK);
    }
    return true;
}

void GameImpl::play()                                                                      //done
{
    m_scaffold.display(); //Shows empty board to begin
    for(;;) //Runs until we break
    {
        if(!takeTurn()) //Only breaks when someone has won or there is a tie
            break;
        if(!m_red->isInteractive() && !m_black->isInteractive()) //If neither are interactive then the user has to press enter to move the game along
        {
            cout << "Press ENTER to see next move" ;
            cin.ignore(10000, '\n');
        }
        m_scaffold.display(); //Shows current state of game
    }
    
    //Find and display the winner
    int winner;
    completed(winner);
    if(winner == RED)
        cout << "RED is the winner!" << endl;
    else if (winner == BLACK)
        cout << "BLACK is the winner!" << endl;
    else
        cout << "The game is a tie!" << endl;
}

int GameImpl::checkerAt(int c, int r) const                                                //done
{
    if(m_scaffold.checkerAt(c, r) == RED)
        return RED;
    if(m_scaffold.checkerAt(c, r) == BLACK)
        return BLACK;
    return VACANT;
}

//******************Non Member Functions*****************************



//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code. 

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
