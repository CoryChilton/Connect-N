//
//  support.cpp
//  Project3
//
//  Created by Cory Chilton on 5/14/21.
//

#include "support.h"



bool Nhorizontal(int color, int N, const Scaffold& grid)                                    //done
{
    for(int i = 1; i <= grid.levels(); i++) //Goes level by level
    {
        int inARow = 0;
        for(int j = 1; j <= grid.cols(); j++)
        {
            if(grid.checkerAt(j, i) == color) //If in the level there are N in a row then we return true
            {
                inARow++;
                if(inARow == N)
                    return true;
            }
            else
                inARow = 0; //If by the end of the level there are not N in a row the inARow counter is reset
        }
    }
    return false;
}

bool Nvertical(int color, int N, const Scaffold& grid)                                       //done
{
    for(int j = 1; j <= grid.cols(); j++) //Goes column by column
    {
        int inARow = 0;
        for(int i = 1; i <= grid.levels(); i++)
        {
            if(grid.checkerAt(j,i) == color) //If in the column there are N in a row we return true
            {
                inARow++;
                if(inARow == N)
                    return true;
            }
            else
                inARow = 0; //If by the end of the column there are not N in a row the inARow counter is reset
        }
    }
    
    return false;
}

bool Ndiagonal(int color, int N, const Scaffold& grid)                                     //done
{
    
    for(int c = grid.cols(); c >= 1; c--)                               //Checks for diags starting from bottom going up to the right
    { //Starts in the bottom right corner
        int inARow = 0;
        for(int x = 0; x <= grid.cols() - c && x < grid.levels(); x++) //x is used to traverse the diagonal
        {
            if(grid.checkerAt(c + x, x + 1) == color)
            {
                inARow++;
                if(inARow == N)
                    return true;
            }
            else
                inARow = 0;
        }
    }
    
    for(int r = grid.levels(); r >= 2; r--)                               //Checks for diags starting from left going up to the right
    {//Starts in the top right corner
        int inARow = 0;
        for(int x = 0; x <= grid.levels() - r && x < grid.cols(); x++) //x is used to traverse the diagonal
        {
            if(grid.checkerAt(x+1,r+x) == color)
            {
                inARow++;
                if(inARow == N)
                    return true;
            }
            else
                inARow = 0;
        }
    }
    
    
    for(int c = 1; c <= grid.cols(); c++)                               //Checks for diags starting from bottom going up to the left
    {//Starts in the bottom left corner
        int inARow = 0;
        for(int x = 0; x < c && x < grid.levels(); x++) //x is used to traverse the diagonal
        {
            if(grid.checkerAt(c - x, x + 1) == color)
            {
                inARow++;
                if(inARow == N)
                    return true;
            }
            else
                inARow = 0;
        }
    }
    
    for(int r = grid.levels(); r >= 2; r--)                               //Checks for diags starting from right going up to the left
    {//Starts at the top right corner
        int inARow = 0;
        for(int x = 0; x <= grid.levels() - r && x < grid.cols(); x++) //x is used to traverse the diagonal
        {
            if(grid.checkerAt(grid.cols() - x,r+x) == color)
            {
                inARow++;
                if(inARow == N)
                    return true;
            }
            else
                inARow = 0;
        }
    }
    
    return false;
}


int rate(const Scaffold& s, int N, int color)
{
    int otherColor = RED;
    if(color == RED)
        otherColor = BLACK;
    
    //Checks all possible outcome for color and otherColor and returns the rating
    if(Nhorizontal(color, N, s))
        return 1;
    else if(Nvertical(color, N, s))
        return 1;
    else if(Ndiagonal(color, N, s))
        return 1;
    else if(Nhorizontal(otherColor, N, s))
        return -1;
    else if(Nvertical(otherColor, N, s))
        return -1;
    else if(Ndiagonal(otherColor, N, s))
        return -1;
    else if(s.numberEmpty() != 0) //The game is still going if this is true so it returns true
        return 2;
    
    return 0; //If none of the other conditions are met it must be a tie so zero is returned
}
