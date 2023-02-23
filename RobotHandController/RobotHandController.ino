#include "SerialSimulink.h"
#include "RoboHand.h"

// Serial comm's with Simulink
SerialSimulink serialSim;

// Robot Hand with 5 finger servos
RoboHand hand;
// Finger Servos
RoboFinger thumb;
RoboFinger pinky;
RoboFinger ringFinger;
RoboFinger middleFinger;
RoboFinger indexFinger;

void setup()
{
  // Initialize serial
  Serial.begin(9600);

  // Initialize fingers and hand
  thumb.init(hand.thumbPin, hand.thumbClosed, hand.thumbOpen);
  pinky.init(hand.pinkyPin, hand.pinkyClosed, hand.pinkyOpen);
  ringFinger.init(hand.ringPin, hand.ringClosed, hand.ringOpen);
  middleFinger.init(hand.middlePin, hand.middleClosed, hand.middleOpen);
  indexFinger.init(hand.indexPin, hand.indexClosed, hand.indexOpen);
  hand.init(thumb, pinky, ringFinger, middleFinger, indexFinger);
  delay(1000);

}

void loop()
{
  // Read signal
  serialSim.readFromSimulink();
  
  // If new control signal received
  if(serialSim.newData){
    // Read and respond to control signal
    if(serialSim.value > 0){
      hand.open();
    }
    else if(serialSim.value < 0){
      hand.close();
    }
    else if(serialSim.value == 0){}
  }
  
  // Send back the received signal
  serialSim.writeToSimulink();
}
