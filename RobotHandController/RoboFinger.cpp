#include "RoboFinger.h"
RoboFinger::RoboFinger(){};

void RoboFinger::init(int outputPin, int closedPos, int openPos) {
  // With this particular hand, openPos is min and closed is Max
  // Improve this with a check of polarity or min/max
  this->outputPin = outputPin;
  this->closedPos = closedPos;
  this->openPos = openPos;
  attach(outputPin, openPos, closedPos);  
}

void RoboFinger::open() {
  setPosition(openPos);
}

void RoboFinger::close() {
  setPosition(closedPos);
}

void RoboFinger::move(float velocity){
  
}

void RoboFinger::setPosition(int position){
  write(position);
  this->position = position;
}