#include <Servo.h>

Servo myservo;        // create servo object to control a servo
int incomingPos = 0;  // for incoming serial data
int pos = 90;         // variable to store the servo position
const byte numChars = 32;
int minPos = 19;
int maxPos = 181;
char receivedChars[numChars];
bool newData;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin (115200);
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
   
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

int char2int (char *array, size_t n){    
    int number = 0;
    int mult = 1;

    n = (int)n < 0 ? -n : n;       /* quick absolute value check  */

    /* for each character in array */
    while (n--)
    {
        /* if not digit or '-', check if number > 0, break or continue */
        if ((array[n] < '0' || array[n] > '9') && array[n] != '-') {
            if (number)
                break;
            else
                continue;
        }

        if (array[n] == '-') {      /* if '-' if number, negate, break */
            if (number) {
                number = -number;
                break;
            }
        }
        else {                      /* convert digit to numeric value   */
            number += (array[n] - '0') * mult;
            mult *= 10;
        }
    }

    return number;
}

void loop() {
  recvWithEndMarker();
  if(newData){
    incomingPos = char2int(receivedChars, 32);
    newData = false;
    if(incomingPos < maxPos && incomingPos > minPos){
      myservo.write(incomingPos);
    }
    Serial.println(incomingPos);        //Diagnostic - serial echo of position
  }
}
