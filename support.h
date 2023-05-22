//
//  support.hpp
//  Project3
//
//  Created by Cory Chilton on 5/14/21.
//

#ifndef support_hpp
#define support_hpp

#include "provided.h"

const int BIGNUMBER = 1000000;

bool Nhorizontal(int color, int N, const Scaffold& grid); //Returns true if there are N in a horizontal row of the specified color
bool Nvertical(int color, int N, const Scaffold& grid);   //Returns true if there are N in a vertical row of the specified color
bool Ndiagonal(int color, int N, const Scaffold& grid);   //Returns true if there are N in a diagonal row of the specified color
int rate(const Scaffold& s, int N, int color); //1 means color wins, 0 means tie, -1 means other color wins, 2 means game still going

//colBestDepth is a struct holding 2 ints so that we can have multiple things in the return from determineBestComputerMove and HumanMove
//m_col represents the column and m_bestDepth determines the best outcome of the move combined with it's depth
    //bestDepth works like +(BIGNUMBER-depth) for +1 and -(BIGNUMBER-depth) for -1
struct colBestDepth
{
public:
    colBestDepth(int col, int bestDepth): m_col(col), m_bestDepth(bestDepth) {}
    int col() {return m_col;}
    int bestDepth() {return m_bestDepth;}
private:
    int m_col;
    int m_bestDepth;
};

#endif /* support_hpp */
