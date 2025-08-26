#include "servomotar.h"
#include "config.h"
#include <ESP32Servo.h>

static Servo leftServo;
static Servo rightServo;

bool CradleServo::begin(int lp, int rp) {
  leftPin = lp; rightPin = rp;
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  leftServo.setPeriodHertz(50);
  rightServo.setPeriodHertz(50);
  leftServo.attach(leftPin);
  rightServo.attach(rightPin);
  center();
  return true;
}

void CradleServo::center() {
  leftServo.write(90);
  rightServo.write(90);
}

void CradleServo::update(unsigned long nowMs, unsigned long periodMs, bool enable) {
  if (!enable) return;
  int angle = map((nowMs % periodMs), 0, periodMs, 60, 120);
  leftServo.write(angle);
  rightServo.write(180 - angle);
}
