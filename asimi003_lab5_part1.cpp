/*        Your Name & E-mail: Angelica Simityan   asimi003@ucr.edu

 *         Discussion Section: 021

 *         Assignment: Lab # 5 Exercise # 1

 *         Exercise Description: [optional - include for your own benefit]

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link:

 https://youtube.com/shorts/mmEbU1P0i-c?feature=share

 */

enum States{INIT, S0, S1} SM1_state;
unsigned long lastRan;
const unsigned long period = 500;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 5;
const char light_pattern[light_pattern_size] = {0,1,3,7,15};
const int button = 2;
int count = 0;

const char sound_pattern_size = 9;
const double sound_pattern[sound_pattern_size] = {329.63,311.13,329.63,311.13,329.63,493.88,293.66,261.63,440.00}; // C4, D4


const int buzzer = 3;

const int xAxis_median = 100; // Adjust this if needed

// Reset the Output Buffer. 
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}

int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0:
          if (digitalRead(button) == 0){
            state = S1;
          }
          else{
            state = S0;
          }
         //State Transition
        break;
      case S1:
            if (digitalRead(button) == 0){
                state = S0;
            }
            else{
                state = S1;
            }
             //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
            //State Action
            resetBuffer();
            
            tone(buzzer, sound_pattern[count]);
           writeBuffer(light_pattern[ map(count, 0, 9, 0, 4)]);
            count++;
            if (count > 9){
              count = 0;
            }
           
         //State Action
        break;
      case S1:
            //State Action
          
            noTone(buzzer);
            
         
         //State Action
        break;
    }

    return state;
}


void setup() {
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
           
        }
        pinMode(button, INPUT_PULLUP);
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
    
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
}
