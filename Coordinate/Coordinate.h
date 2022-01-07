#ifndef Coordinate_h
#define Coordinate_h

/**
 * @file Coordinate.h
 * @author Jack Sipley
 * @brief  Header file for Coordinate.cpp
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Arduino.h"

class Coordinate
{
    public:
        Coordinate();
        Coordinate(int row, int col);
        Coordinate(int row, int col, int dir);
        int getRow();
        int getCol();
        int getDir();
        void setDir(int dir);
        void updateCoordinate(Coordinate a);
        bool shiftUp();
        bool shiftDown();
        bool shiftLeft();
        bool shiftRight();
        bool equals(Coordinate other);
    private:
        int _row;
        int _col;
        int _direction;
};

#endif