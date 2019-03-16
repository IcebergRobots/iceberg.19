#include "Light.h"

/*****************************************************
  Constructor
*****************************************************/
Light::Light()
{
  setCooldown(10);
  pui.setCooldown(10);
  line.setCooldown(100);
  inside.setCooldown(100);
}

void Light::init()
{
  beginSegment(F("l"));
  io.indHeartbeat.set(255);
  io.indFront.set(255);
  io.indLeft.set(255);
  // io.indRight.set(255);
  if (pui.onDemand())
  {
    pui.setAllColor(255, 255, 255);
    pui.show();
  }
  if (line.onDemand())
  {
    line.setAllColor(255, 255, 255);
    line.show();
  }
  io.setupLight.now();
  endSegment();
}

void Light::light()
{
  io.indHeartbeat.set(map(abs(int(millis() % 500) - 250), 0, 250, -100, 356));

  if (io.setupLight.off())
  {
    io.indFront.set(io.seeBall.get());
    io.indLeft.set(0);
    // io.indRight.set(0);

    if (inside.onDemand())
    {
      //animatio
      if (io.animationEnabled.get())
      {
        for (int i = 0; i < 8; i++)
        {
          inside.setPixelColor(i, inside.wheelToColor((i * 255 / 8 + millis() / 4) % 255));
        }
        inside.setBrightness(255);
        inside.show();
      }
      //NO animation
      else
      {
        for (int i = 0; i < 8; i++)
        {
          inside.setPixelColor(i, 0, 0, 0);
        }
        inside.setBrightness(255);
        inside.show();
      }
    }

    if (line.onDemand())
    {
      if (io.bottom.off())
      {
        line.setCooldown(10);
        line.setAllColor(0, 0, 0);
      }
      else if (io.animationEnabled.off())
      {
        line.setCooldown(100);
        line.setBrightness(255);

        for (int i = 0; i <= 39; i++)
        {
          if (i >= 32)
            line.setPixelColor(i, 255, 255, 255);
          else
            line.setPixelColor(i, 0, 0, 0);
        }
      }
      else
      {
        line.setCooldown(10);
        line.setBrightness(255);
        int werte = io.animationState.get();

        for (int i = 0; i < 40; i++)
        {
          if (i < 32)
            line.setPixelColor(i, line.wheelToColor(((3 - (i % 4)) * 64 + ((millis() / 3) % 255) % 255)));
          else
            line.setPixelColor(i, line.wheelToColor(((millis() / 3) % 255) % 255));
        }
      }
      if (LINE_ENABLED) line.show();
    }

    if (pui.onDemand())
    {
      //NO Animation
      if (io.animationEnabled.off())
      {
        pui.setPixelState(0);
        pui.setPixelState(1, io.battery.on());
        pui.setPixelState(2, io.seeMate.on());
        pui.setPixelState(3, io.seeGoal.on());

        if (!camera.isEnabled() || !reflexion.isEnabled())
          pui.setPixelState(4, STATE_ERROR);
        else if (io.seeBall.outsidePeriod(60000))
          pui.setPixelState(4, STATE_WARNING);
        else if (io.hasBall.on())
          pui.setPixelState(4, STATE_ACTIVE);
        else if (io.seeBall.on())
          pui.setPixelState(4, STATE_OK);
        else
          pui.setPixelState(4);

        if (io.flat.off())
          pui.setPixelState(5, STATE_WARNING);
        else
          pui.setPixelState(5);

        if (io.turbo.off() || !DEBUG_ENABLED)
          pui.setPixelState(6);
        else if (DEBUG_LOOP || DEBUG_SEGMENT)
          pui.setPixelState(6, STATE_WARNING);
        else
          pui.setPixelState(6, STATE_ACTIVE);

        if (!line.isEnabled() || io.bottom.off())
          pui.setPixelState(7, STATE_ERROR);
        else if (io.onLine.on())
          pui.setPixelState(7, STATE_ACTIVE);
        else if (io.animationEnabled.on())
          pui.setPixelState(7, STATE_WARNING);
        else
          pui.setPixelState(7);

        if (!KICKER_ENABLED || io.kicker.off())
          pui.setPixelState(8, STATE_ERROR);
        else if (io.kickActive.insidePeroid(100))
          pui.setPixelState(8, STATE_ACTIVE);
        else
          pui.setPixelState(8);

        if (io.bluetooth.off())
          pui.setPixelColor(9, STATE_ERROR);
        else
          pui.setPixelState(9);

        if (io.motor.off())
          pui.setPixelState(10, STATE_ERROR);
        else if (io.pause.on())
          pui.setPixelState(10, STATE_WARNING);
        else
          pui.setPixelState(10);

        if (io.headstart.off())
          pui.setPixelState(11, STATE);
        else
          pui.setPixelState(11, STATE_ACTIVE);

        pui.setBrightness(map(io.poti.get(), 0, 1023, 0, 255));
        pui.show();
      }

      //Animation
      else
      {

        for (int i = 0; i < 12; i++)
        {
          pui.setPixelColor(i, pui.wheelToColor((i * 255 / 12 + millis() / 4) % 255));
        }
        pui.setBrightness(255);
        pui.show();
      }
    }
  }
}

bool Light::isEnabled()
{
  return true;
}

Light light;
