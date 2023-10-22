#include <M5Unified.h>

void setup()
{
  M5.begin();
}

void loop()
{
  M5.Display.print("Hello World!");
  M5.delay(500);
}