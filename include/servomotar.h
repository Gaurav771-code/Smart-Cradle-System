#pragma once

class CradleServo {
public:
  bool begin(int leftPin, int rightPin);
  void update(unsigned long nowMs, unsigned long periodMs, bool enable);
  void center();
private:
  int leftPin, rightPin;
};
