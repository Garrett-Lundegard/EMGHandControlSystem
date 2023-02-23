// Robot Finger
// Control a finger's servo

#ifndef RoboFinger_H
#define RoboFinger_H

#include <Arduino.h>
#include <Servo.h>

class RoboFinger: public Servo {
public:
  RoboFinger();
  // Pin servo is connected to
  int outputPin;
  // Servo Positions (current, closed, open)
  int position; // current
  int closedPos; // fully closed into hand
  int openPos; // fully open and extended
  // Initialize finger servo
  void init(int outputPin, int closedPos, int openPos);
  
  // Move finger to the fully open position
  void open();
  
  // Move finger to the fully closed position
  void close();

  // 
  // Velocity is a number from -1 (closed) to 1 (open)
  // Moves to open or closed with 
  void move(float velocity);

  // Move finger to a given position and save the position
  void setPosition(int position);
};

#endif