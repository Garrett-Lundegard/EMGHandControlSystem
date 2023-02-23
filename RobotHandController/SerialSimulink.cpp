#include "SerialSimulink.h"

SerialSimulink::SerialSimulink(){};

void SerialSimulink::init(int baudRate){
  Serial.begin(baudRate, SERIAL_8N1);
}

void SerialSimulink::readFromSimulink(){
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        u.b[ndx] = rc;
        ndx++;
        if (ndx >= bufferSize) {
          ndx = bufferSize - 1;
        }
      }

      // End marker received
      else {
          u.b[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = true;
          value = u.fval;
      }
    }

    // Start marker received
    else if (rc == startMarker) {
        recvInProgress = true;
    }
  }
}

// Send recvd data back to Simulink
void SerialSimulink::writeToSimulink(){
  if (newData == true){
    byte *b = (byte *) &value;
    Serial.write(b, 4);
    Serial.write("\r\n");
    newData = false;  
  }
}
