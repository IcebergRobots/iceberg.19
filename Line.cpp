#include "Line.h"

Line::Line() {}

void Line::update()
{
	if (DEBUG_LOOP)
		beginSegment(F("line"));
	if (isLineFetchRequest)
	{
    isLineFetchRequest = false;
		debug("line");
		drive.brake();
		io.lineDetected.set();
	}
	if (io.lineDetected.on())
		fetch();
	extendAvoid();
	if (DEBUG_LOOP)
		endSegment();
}

void Line::fetch()
{
  debug("fetch");
	if (BOTTOM_SERIAL.available() >= 3)
	{
		while (BOTTOM_SERIAL.available() > 3)
			BOTTOM_SERIAL.read();

		BOTTOM_SERIAL.read(); //power wird nicht ausgewertet
		int tempAngle = 0;
		tempAngle = BOTTOM_SERIAL.read();
		tempAngle |= BOTTOM_SERIAL.read() << 8;

		io.lineAngle.set(tempAngle);

		io.lineDetected.abort();
		io.lineAvoid.set();
	}
}

void Line::extendAvoid()
{
	if (io.lineDetected.off() && io.lineAvoid.on() && io.lineInterrupt.on())
		io.lineAvoid.set();
}

void Line::execute()
{
	drive.drive(io.lineAngle.get() + 180, SPEED_LINE);
}

bool isLineFetchRequest = 0;
Line line;