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

const byte row[] = { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8 };  //Array that holds the pinout for rows 0-7
const byte col[] = { COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8 };  //Array that holds the pinout for columns 0-7
LinkedList<Coordinate> snakeList; //Declare a linked list of coordinates on the matrix, will serve as the snake
Coordinate currentPoint;          //Declare a Coordinate object that will serve as the current point the user is trying to obtain

int direct; //used for direction w/ keys 1-4 

void setup() {
  // Set all pins used to output for the LED Matrix
  for (int i = 0; i < sizeof(row); i++) {
    pinMode(row[i], OUTPUT);  //Initialize row pinout on the arduino
    pinMode(col[i], OUTPUT);  //Initialize column pinout on the arduino
  }
  Serial.begin(9600);       //Open serial port, sets data rate to 9600 bps
  /* From arduino random() reference:
   * if analog input pin 0 is unconnected, random analog
   * noise will cause the call to randomSeed() to generate
   * different seed numbers each time the sketch runs.
   * randomSeed() will then shuffle the random function.
  */ 
  randomSeed(analogRead(5));  //A5 (analog pin 5 is unconnected in this circuit) therefore will generate random seed each time
  
  snakeList = LinkedList<Coordinate>(); //Instantiate snakeList
  
  snakeList.add(Coordinate(3,6,1));     //Set starting place for snake at position (3,6)
  currentPoint = Coordinate(3,3);       //Set the initial point at (3,3)
}

void loop() {
  //Have the display show for a period of time (300 ms)
  //Current problem, delay get longer as more leds are light up on the board
  for (int i = 0; i < 300; i++) {
    refresh();
  }
  //If the user has inputted a value
  if (Serial.available() != 0) {
    direct = Serial.parseInt(); //User enters direction for which the snake to travel
    serialFlush();  //Flush other serial data in the queue
  }
  makeMove(direct); //Make a move with the given direction entered by the user
  
  //If the snake has collected the current point on board
  if(snakeList.get(0).equals(currentPoint)) {
    addTailPoint();   //Add a unit length onto the end of the snake
    currentPoint = generatePoint(); //Generate a new point to display on the board
  }
}

/*
   refresh goes through each led and quickly lights it up if denoted by a 1, meaning it should light up.
   Calling that funciton in a loop very quiickly has the effect of the lights being statically lighted.
   Params: N/A
   Returns: N/A
*/
void refresh() {
  //For each led that makes up the snake, turn on each led of the snake
  for (int i = 0; i < snakeList.size(); i++) {
    digitalWrite(col[snakeList.get(i).getCol()], HIGH);
    digitalWrite(row[snakeList.get(i).getRow()], LOW);
    delay(1); //Short delay, otherwise LEDs wouldn't be visible
    reset();  //Reset changes to be ready for next LED
  }
  //Same logic for snake shown above
  digitalWrite(col[currentPoint.getCol()], HIGH);
  digitalWrite(row[currentPoint.getRow()], LOW);
  delay(1);
  reset();
}

/*  Reset sets all the rows to high and all the 
 *  columns back to low, which allows for all
 *  LEDs to be individually lighten up
 *  Params: N/A
 *  Returns: N/A
 */
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
   Returns: point, randomly generated cordinate. 
   Precondition: point is not a point on the snake.
*/
Coordinate generatePoint() {
  Coordinate point; //Point to be randomly generated and returned
  int duplicateFlag;  //Flag to determine if random coordinate is already occipied by snake
  while (true) {
    point = Coordinate(random(8), random(8)); //generate random point
    duplicateFlag = 0;
    //check to see if generated coord is occupied by snake coord
    for(int i = 0; i < snakeList.size() -1; i++)
      if(point.equals(snakeList.get(i)))
        duplicateFlag = 1;  //point generated is on the snake, loop again
    if(duplicateFlag == 0)  //Point not occupied by snake
      break;
  }
  return point;
}

/*  makeMove moves the snake by one unit
 *  params: dir, direction for the snake to move
 *  returns: true if valid move, false otherwise
*/
bool makeMove(int dir) {
  Coordinate headCoord = snakeList.get(0);  //Create new coordinate that will take place for head of snake
  switch (dir) {
    case 1: //Move the snake up
      headCoord.shiftUp();
      headCoord.setDir(1);
      break;
    case 2: //Move snake left
      headCoord.shiftLeft();
      headCoord.setDir(2);
      break;
    case 3: //Move snake down
      headCoord.shiftDown();
      headCoord.setDir(3);
      break;
    case 4: //Move snake right
      headCoord.shiftRight();
      headCoord.setDir(4);
      break;
  }
  snakeList.add(0, headCoord);  //Add coord to front of list 
  snakeList.remove(snakeList.size() -1); //Remove the last element in the snake, has illusion that it's moving
}

/*
 * Appends a point to the end of the snake, gets called when the snake collects a point
 * params: N/A
 * returns: N/A
 */
void addTailPoint() {
  Coordinate endpoint = snakeList.get(snakeList.size() -1); //Get the last element in the list
  Coordinate newPoint = endpoint;
  //Add the tail point in the direction of the last elements, determined by switch statement below:
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
  snakeList.add(newPoint);  //Add tail point to the end of the snake
}

//serialFlush is used to get rid of any junk in the serial queue
void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
