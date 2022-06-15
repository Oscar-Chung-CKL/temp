#pragma once

#include "include.hpp"

bool overlapped(string board[][10], int ypos, int xpos)
{
    if (board[ypos][xpos] == "Laser_Row")
    {
        for ( int i = 0; i < 9; i++)
        {
            if ( board[i][xpos] == "CL2")
            {
                return true;
            }
        }
    }
    else if (board[ypos][xpos] == "Laser_Column")
    {
        for ( int i = 0; i < 9; i++)
        {
            if (board[ypos][i] == "RL2")
            {
                return true;
            }
        }
    }
    return false;
}
