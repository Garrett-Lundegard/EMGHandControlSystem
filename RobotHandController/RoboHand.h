// Robot Hand
// Control all 5 fingers

#ifndef RoboHand_H
#define RoboHand_H

#include <Arduino.h>
#include "RoboFinger.h"

class RoboHand {
public:
  RoboHand();

  // Finger Servos
  RoboFinger thumb;
  RoboFinger pinky;
  RoboFinger ringFinger;
  RoboFinger middleFinger;
  RoboFinger indexFinger;
  // Finger Servo Output Pins
  const int thumbPin = 8;
  const int pinkyPin = 9;
  const int ringPin = 10;
  const int middlePin = 11;
  const int indexPin = 12;
  // Closed Position
  const int thumbClosed = 160;
  const int pinkyClosed = 150;
  const int ringClosed = 130;
  const int middleClosed = 150;
  const int indexClosed = 140;
  // Open Position
  const int thumbOpen = 45;
  const int pinkyOpen = 50;
  const int ringOpen = 75;
  const int middleOpen = 60;
  const int indexOpen = 60;
  
  void init(
    RoboFinger thumb,
    RoboFinger pinky,
    RoboFinger ringFinger,
    RoboFinger middleFinger,
    RoboFinger indexFinger);
  void open();
  void close();
  // State: 0 - 1 Indicating hand position
  // 0 = closed, 0.5 = neutral, 
  float state; 

};

#endif