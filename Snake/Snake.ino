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
