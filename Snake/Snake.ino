#include <Coordinate.h>
#include <LinkedList.h>
#include <Console.h>

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9
#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 A0
#define COL_5 A1
#define COL_6 A2
#define COL_7 A3
#define COL_8 A4

/*
   This program is the game snake, which is played on an 8x8 Led matrix, which is powered by an arduino uno.
   @author: Jack Sipley
   @Date: 12/29/2021
*/

const byte row[] = { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8 };
const byte col[] = { COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8 };
//int matrix[8][8];     //2D array to represents all leds on the board
LinkedList<Coordinate> snakeList; //Declare a linked list of coordinates on the matrix, will serve as the snake

int temp; //used for direction w/ keys 1-4 

void setup() {
  // put your setup code here, to run once:
  // Set all pins used to output for the LED Matrix
  for (int i = 0; i < sizeof(row); i++) {
    pinMode(row[i], OUTPUT);  //Initialize row pinout on the arduino
    pinMode(col[i], OUTPUT);  //Initialize column pinout on the arduino
  }
  Serial.begin(9600);       //Open serial port, sets data rate to 9600 bps
  snakeList = LinkedList<Coordinate>(); //Instantiate snakeList
  
  snakeList.add(Coordinate(0,0));                //Add headCoord to snake
  //modifyLed(headCoord.getCol(), headCoord.getRow(), 1); //Snake starts at coordinate (0,0)
  //refresh();

  /*
  headCol = 3;
  headRow = 3;
  modifyLed(headCol, headRow, 1); //Snake starts at coordinate (0,0)
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 100; i++) {
    refresh();
    delay(5);
  }
  if (Serial.available() != 0) {
    //currDirection = Serial.readString();
    temp = Serial.parseInt();
    serialFlush();
  }
  makeMove(temp);
}

/*
   refresh goes through each led and quickly lights it up if denoted by a 1, meaning it should light up.
   Calling that funciton in a loop very quiickly has the effect of the lights being statically lighted.
   Params: N/A
   Returns: N/A

void refresh() {
  int i = 0;
  for (int c = 0; c < sizeof(col); c++)
    for (int r = 0; r < sizeof(row); r++) {
      //if a certain led is marked by a 1, then should be on
      ///if (matrix[c][r] == 1) {
        if (snakeList.get(i).equals(Coordinate(r, c)) {
        //Led is lighted when col is high and row is low, creating potentail difference
        digitalWrite(col[c], HIGH);
        digitalWrite(row[r], LOW);
        delay(1);
        reset();
        }
        i++;
        }
      }
}
*/

void refresh() {
  for (int i = 0; i < snakeList.size(); i++) {
    digitalWrite(col[snakeList.get(i).getCol()], HIGH);
    digitalWrite(row[snakeList.get(i).getRow()], LOW);
    delay(5);
    reset();
  }
}

void reset() {
  for (int i = 0; i < sizeof(row); i++) {
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], LOW);
  }
}

/*
   modifyLed sets the state of a cell on the led matrix
   Params: col, column in which specified LED is located at
           row, row in which specified LED is located at
           val, 0 for no LED, 1 to present LED, 2 for present LED and if that LED is a point
   Returns: true if successful, false otherwise

bool modifyLed(int col, int row, int val) {
  if (col >= 8 || col < 0 || row >= 8 || row < 0)
    return false;
  matrix[col][row] = val;
  return true;
}
*/

/*
   Generates a new point on the board for the snake to get
   Preconditon: there is empty room on the board for the point to be placed
   Params: N/A
   Returns: N/A

void generatePoint() {
  int randRow;
  int randCol;
  while (true) {
    randRow = random(8);
    randCol = random(8);
    //check to see if generated coord is occupied by snake coord
    if (matrix[randRow][randCol] == 0) {
      matrix[randRow][randCol] = 2;
      break;
    }
  }
}
*/

/*
   Moves the snake head point by 1 in the given direction
*/
bool makeMove(int dir) {
  Coordinate headCoord = snakeList.get(0);
  if (dir == 1) {
    //modifyLed(headCoord.getCol(), headCoord.getRow(), 0);
    headCoord.shiftUp();
   // modifyLed(headCoord.getCol(), headCoord.getRow(), 1);
  }
  if (dir == 2) {
   // modifyLed(headCoord.getCol(), headCoord.getRow(), 0);
    headCoord.shiftLeft();
   // modifyLed(headCoord.getCol(), headCoord.getRow(), 1);
  }
  if (dir == 3) {
   // modifyLed(headCoord.getCol(), headCoord.getRow(), 0);
    headCoord.shiftDown();
   // modifyLed(headCoord.getCol(), headCoord.getRow(), 1);
  }
  if (dir == 4) {
  //  modifyLed(headCoord.getCol(), headCoord.getRow(), 0);
    headCoord.shiftRight();
  //  modifyLed(headCoord.getCol(), headCoord.getRow(), 1);
  }
  snakeList.add(0, headCoord);
  snakeList.remove(snakeList.size() -1);
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
