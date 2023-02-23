#ifndef SerialSimulink_h
#define SerialSimulink_h

#include <Arduino.h>

class SerialSimulink {
public:
  SerialSimulink();
  // Size of read buffer
  const static int bufferSize = 16;
  // flag for new data arriving
  boolean newData = false;

  // Byte array of a float value
  union BtoF {
    byte b[bufferSize];
    float fval;
  } u;

  float value = 0;

  // Initialize and begin serial
  void init(int baudRate);
  // Read data from Simulink
  void readFromSimulink();
  // Send data to Simulink
  void writeToSimulink();
};

#endif
