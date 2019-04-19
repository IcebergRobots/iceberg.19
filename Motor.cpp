#include "Motor.h"


Motor::Motor() {}

void Motor::setPins(OwnPin *_current, OwnPin *_forward, OwnPin *_backward, OwnPin *_speed) {
  current = _current;
  forward = _forward;
  backward = _backward;
  speed = _speed;
}

void Motor::temp(int power) {
  forward->temp(power > 0);
  backward->temp(power <= 0);
  speed->temp(abs(power)); 
}

void Motor::set(int power) {
  temp(power);
  set();
}

void Motor::set() {
  forward->set();
  backward->set();
  speed->set(); 
}

int Motor::get() {
  return speed->get();
}

void Motor::brake(bool active) {
  forward->temp(active);
  backward->temp(active);
  speed->temp(255); 
}

int Motor::amperage() {
  return current->get(); 
}