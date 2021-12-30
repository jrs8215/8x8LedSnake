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
 * This program is the game snake, which is played on an 8x8 Led matrix, which is powered by an arduino uno.
 * @author: Jack Sipley
 * @Date: 12/29/2021
 */

const byte row[] = { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8 };
const byte col[] = { COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8 };
int matrix[8][8];     //2D array to represents all leds on the board

void setup() {
  // put your setup code here, to run once:
  // Set all pins used to output for the LED Matrix
  for(int i = 0; i < sizeof(row); i++) {
    pinMode(row[i], OUTPUT);  //Initialize row pinout on the arduino
    pinMode(col[i], OUTPUT);  //Initialize column pinout on the arduino
  }
  Serial.begin(9600);       //Open serial port, sets data rate to 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
 * refresh goes through each led and quickly lights it up if denoted by a 1, meaning it should light up.
 * Calling that funciton in a loop very quiickly has the effect of the lights being statically lighted.
 * Params: N/A
 * Returns: N/A
 */
void refresh() {
  for(int c = 0; c < sizeof(col); c++)
    for(int r = 0; r < sizeof(row); r++)
      //if a certain led is marked by a 1, then should be on
      if(matrix[c][r] == 1) {
        //Led is lighted when col is high and row is low, creating potentail difference
        digitalWrite(col[c], HIGH);
        digitalWrite(row[r], LOW);
        delay(1);
        reset();
      }
}

void reset() {
  for(int i = 0; i < sizeof(row); i++) {
      digitalWrite(row[i], HIGH);
      digitalWrite(col[i], LOW);
  }
}

/*
 * modifyLed has two purposes, to remove or to add an Led to the board
 * Params: col, column in which specified LED is located at
 *         row, row in which specified LED is located at
 *         val, 0 to remove LED, 1 to add LED
 * Returns: true if successful, false otherwise
 */
bool modifyLed(int col, int row, int val) {
  if(col >= 8 || col < 0|| row >= 8 || row < 0)
    return false;
  matrix[col][row] = val;
  return true;
}
