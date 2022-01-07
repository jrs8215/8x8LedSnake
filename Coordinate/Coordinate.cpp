#include "Arduino.h"
#include "Coordinate.h"

/**
 * @brief Coordinate is a class that creates, and has basic manipulation with the specified corrdinate 
 *  Used as a library for arduino
 * @author Jack Sipley
 * @date 2022-01-07
 */

const int MAX_ROW = 8, MAX_COL = 8;

Coordinate::Coordinate() {
    _row = -1;
    _col = -1;
    _direction = -1;
}
Coordinate::Coordinate(int row, int col) {
    _row = row;
    _col = col;
    _direction = -1;
}
Coordinate::Coordinate(int row, int col, int dir) {
    _row = row;
    _col = col;
    _direction = dir;
}

int Coordinate::getCol() {
    return _col;
}
int Coordinate::getRow() {
    return _row;
}
int Coordinate::getDir() {
    return _direction;
}
void Coordinate::setDir(int dir) {
    _direction = dir;
}
void Coordinate::updateCoordinate(Coordinate coord) {
   _row = coord.getRow();
   _col = coord.getCol(); 
}
bool Coordinate::shiftUp() {
    if(_row > 7)
        return false;
    _row++;
    return true; 
}
bool Coordinate::shiftDown() {
    if(_row < 0)
        return false;
    _row--;
    return true; 
}
bool Coordinate::shiftLeft() {
    if(_col > 7)
        return false;
    _col++;
    return true; 
}
bool Coordinate::shiftRight() {
    if(_col < 0)
        return false;
    _col--;
    return true; 
}
bool Coordinate::equals(Coordinate other) {
    return _row == other.getRow() && _col == other.getCol(); 
}