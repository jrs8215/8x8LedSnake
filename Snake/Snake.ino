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
LinkedList<Coordinate> snakeList; //Declare a linked list of coordinates on the matrix, will serve as the snake
Coordinate currentPoint;          //Declare a Coordinate object that will serve as the current point the user is trying to obtain

int direct; //used for direction w/ keys 1-4 

void setup() {
  // put your setup code here, to run once:
  // Set all pins used to output for the LED Matrix
  for (int i = 0; i < sizeof(row); i++) {
    pinMode(row[i], OUTPUT);  //Initialize row pinout on the arduino
    pinMode(col[i], OUTPUT);  //Initialize column pinout on the arduino
  }
  Serial.begin(9600);       //Open serial port, sets data rate to 9600 bps
  snakeList = LinkedList<Coordinate>(); //Instantiate snakeList
  
  snakeList.add(Coordinate(3,3,1));                //Set starting point at position (3,3)
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 500; i++) {
    refresh();
  }
  if (Serial.available() != 0) {
    direct = Serial.parseInt();
    serialFlush();
  }
  makeMove(direct);
}

/*
   refresh goes through each led and quickly lights it up if denoted by a 1, meaning it should light up.
   Calling that funciton in a loop very quiickly has the effect of the lights being statically lighted.
   Params: N/A
   Returns: N/A
*/
void refresh() {
  for (int i = 0; i < snakeList.size(); i++) {
    digitalWrite(col[snakeList.get(i).getCol()], HIGH);
    digitalWrite(row[snakeList.get(i).getRow()], LOW);
    delay(1);
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
   Generates a new point on the board for the snake to get
   Preconditon: there is empty room on the board for the point to be placed
   Params: N/A
   Returns: N/A
*/
Coordinate generatePoint() {
  Coordinate point;
  int duplicateFlag;
  while (true) {
    point = Coordinate(random(8), random(8));
    duplicateFlag = 0;
    //check to see if generated coord is occupied by snake coord
    for(int i = 0; i < snakeList.size() -1; i++)
      if(point.equals(snakeList.get(i)))
        duplicateFlag = 1;
    if(duplicateFlag == 0)
      break;
  }
}

/*
   Moves the snake head point by 1 in the given direction
*/
bool makeMove(int dir) {
  Coordinate headCoord = snakeList.get(0);
  if (dir == 1) {
    headCoord.shiftUp();
    headCoord.setDir(1);
  }
  if (dir == 2) {
    headCoord.shiftLeft();
    headCoord.setDir(2);
  }
  if (dir == 3) {
    headCoord.shiftDown();
    headCoord.setDir(3);
  }
  if (dir == 4) {
    headCoord.shiftRight();
    headCoord.setDir(4);
  }
  snakeList.add(0, headCoord);
  snakeList.remove(snakeList.size() -1); //Remove the last element in the snake, has illusion that it's moving
}
void addTailPoint() {
  Coordinate endpoint = snakeList.get(snakeList.size() -1); //Get the last element in the list
  Coordinate newPoint = endpoint;
  switch (endpoint.getDir()) {
    case 1:
      newPoint.shiftDown();
      break;
    case 2:
      newPoint.shiftLeft();
      break;
    case 3:
      newPoint.shiftUp();
      break;
    case 4:
      newPoint.shiftRight();
      break;
  }
  snakeList.add(newPoint);
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
