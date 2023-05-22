// Scaffold.cpp

#include "provided.h"
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

class ScaffoldImpl                                                             //done (I think)
{
public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
private:
    int m_cols;
    int m_levels;
    vector<vector<int>> m_grid;
    stack<int> m_moveHistory;  //uses real columns, not user columns; Keeps track of all the moves
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)                           //done
 :m_cols(nColumns), m_levels(nLevels)
{
    //Check valid columns and levels
    if(m_cols < 1 || m_levels < 1)
    {
        cerr << "Error: non-positive columns or levels!" << endl;
        exit(0);
    }
    //Build the grid into the right shape
    //My grid starts at (0,0) in the lower left corner while user interface starts at (1,1) in the lower left corner
    m_grid.resize(m_levels);
    for(int i = 0; i < m_levels; i++)
        m_grid[i].resize(m_cols);
    
    //Fill grid with VACANTS
    for(int i = 0; i < m_levels; i++)
        for(int j = 0; j < m_cols; j++)
            m_grid[i][j] = VACANT;
}

int ScaffoldImpl::cols() const                                                  //done
{
    return m_cols;
}

int ScaffoldImpl::levels() const                                                //done
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const                                           //done
{
    int numEmpty = 0;
    //Loop through all spots, checking if empty
    for(int i = 0; i < m_levels; i++)
        for(int j = 0; j < m_cols; j++)
            if(m_grid[i][j] == VACANT)
                numEmpty++;
    return numEmpty;
}

int ScaffoldImpl::checkerAt(int column, int level) const                        //done
{
    level--; //Decrease level and column by 1 to match my scaffold implementation
    column--;
    if(m_grid[level][column] == RED)
        return RED;
    if(m_grid[level][column] == BLACK)
        return BLACK;
    return VACANT;
}

void ScaffoldImpl::display() const                                              //done
{
    //All of the lines with potential spaces
    for(int i = m_levels; i >= 1; i--)
    {
        cout << '|';
        for(int j = 1; j <= m_cols; j++)
        {
            int code = checkerAt(j,i); //Adds whatever color or blank depending on what's at the location
            if(code == RED)
                cout << 'R' << '|';
            else if(code == BLACK)
                cout << 'B' << '|';
            else
                cout << ' ' << '|';
        }
        cout << endl;
    }
    //Last Line
    cout << '+';
    for(int i = 0; i < m_cols ; i++)
        cout << '-' << '+';
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)                             //done
{
    if(column >= 1 && column <= m_cols && (color == RED || color == BLACK)) //Checks validity of inputs
    {
        //Then check that column from bottom to top to find the first vacancy
        for(int i = 0; i < m_levels; i++)
        {
            if(m_grid[i][column-1] == VACANT)
            {
                m_grid[i][column-1] = color;
                m_moveHistory.push(column-1); //Updates the history stack
                return true;
            }
        }
    }
    return false; //If there were no vacancys the move was invalid
}

int ScaffoldImpl::undoMove()                                                    //done
{
    if(m_moveHistory.empty()) //Checks if there have been any moves
        return 0;
    //Removes the topmost color in the most recent history column
    int column = m_moveHistory.top();
    for(int i = m_levels - 1; i >= 0; i--)
    {
        if(m_grid[i][column] != VACANT)
        {
            m_grid[i][column] = VACANT;
            m_moveHistory.pop(); //Remove the most recent column from the history
            return column + 1;
        }
    }
    return 0;
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code. 

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
