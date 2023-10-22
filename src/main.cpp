#include "M5Dial.h"

long oldPosition = -999;
long origin_x;
long origin_y;
long rad_offset = -90; // デフォルトは3時の位置

void setup()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, false);

  M5Dial.Display.setTextColor(WHITE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextFont(&fonts::Orbitron_Light_32);
  M5Dial.Display.setTextSize(0.5);

  // 角度の初期値
  M5Dial.Encoder.write(45);

  origin_x = M5.Display.width() / 2;
  origin_y = M5.Display.height() / 2;
}

void loop()
{
  M5Dial.update();
  long newPosition = M5Dial.Encoder.read();
  if (newPosition != oldPosition)
  {
    if (newPosition > 360)
    {
      newPosition = newPosition - 360;
      M5Dial.Encoder.write(newPosition);
    }
    if (newPosition < 0)
    {
      newPosition = newPosition + 360;
      M5Dial.Encoder.write(newPosition);
    }

    M5Dial.Speaker.tone(8000, 20);
    oldPosition = newPosition;
    Serial.println(newPosition);
    long tx = cos((newPosition / 2 + rad_offset) * DEG_TO_RAD) * 40 + origin_x;
    long ty = sin((newPosition / 2 + rad_offset) * DEG_TO_RAD) * 40 + origin_y;
    long x = cos((newPosition + rad_offset) * DEG_TO_RAD) * 120 + origin_x;
    long y = sin((newPosition + rad_offset) * DEG_TO_RAD) * 120 + origin_y;

    M5Dial.Display.clear();
    // 半円の塗りつぶし
    M5Dial.Display.fillArc(origin_x, origin_y, 0, 120, rad_offset, (newPosition + rad_offset), M5.Display.color888(50, 50, 128));
    // 角度の表示
    M5Dial.Display.drawString(String(newPosition), tx, ty);
    // 0度を表す直線
    M5Dial.Display.drawLine(origin_x, origin_y, origin_x, 0, WHITE);
    // 角度を表す直線
    M5Dial.Display.drawLine(origin_x, origin_y, x, y, WHITE);
    // 角度を表す円弧
    M5Dial.Display.drawArc(origin_x, origin_y, 20, 20, rad_offset, (newPosition + rad_offset), YELLOW);
    // 中心
    M5Dial.Display.fillCircle(origin_x, origin_y, 2, RED);
  }
}