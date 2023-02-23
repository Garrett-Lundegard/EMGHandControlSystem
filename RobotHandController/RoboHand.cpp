#include "RoboHand.h"

RoboHand::RoboHand() {

}

void RoboHand::init(
  RoboFinger thumb,
  RoboFinger pinky,
  RoboFinger ringFinger,
  RoboFinger middleFinger,
  RoboFinger indexFinger){

  this->thumb = thumb;
  this->pinky = pinky;
  this->ringFinger = ringFinger;
  this->middleFinger = middleFinger;
  this->indexFinger = indexFinger;
  /*
  thumb.init(thumbPin, thumbClosed, thumbOpen);
  pinky.init(pinkyPin, pinkyClosed, pinkyOpen);
  ringFinger.init(ringPin, ringClosed, ringOpen);
  middleFinger.init(middlePin, middleClosed, middleOpen);
  indexFinger.init(indexPin, indexClosed, indexOpen);
  
  thumb.init(thumbPin, thumbClosed, thumbOpen);
  pinky.init(pinkyPin, pinkyClosed, pinkyOpen);
  ringFinger.init(ringPin, ringClosed, ringOpen);
  middleFinger.init(middlePin, middleClosed, middleOpen);
  indexFinger.init(indexPin, indexClosed, indexOpen);

  thumb.attach(thumbPin);
  pinky.attach(pinkyPin);
  ringFinger.attach(ringPin);
  middleFinger.attach(middlePin);
  indexFinger.attach(indexPin);

  thumb.init();
  pinky.init();
  ringFinger.init();
  middleFinger.init();
  indexFinger.init();
  */
}

void RoboHand::open() {
  thumb.open();
  pinky.open();
  ringFinger.open();
  middleFinger.open();
  indexFinger.open();
}

void RoboHand::close() {
  thumb.close();
  pinky.close();
  ringFinger.close();
  middleFinger.close();
  indexFinger.close();
}