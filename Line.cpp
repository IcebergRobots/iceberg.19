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
		drive.drive(0, 0);
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
	if (BOTTOM_SERIAL.available())
		debug("available");
	if (BOTTOM_SERIAL.available() >= 3)
	{
		debug("success");
		while (BOTTOM_SERIAL.available() > 3)
			BOTTOM_SERIAL.read();

		BOTTOM_SERIAL.read(); //power wird nicht ausgewertet
		int tempAngle = 0;
		tempAngle = BOTTOM_SERIAL.read();
		tempAngle |= BOTTOM_SERIAL.read() << 8;

		io.lineAngle.set(tempAngle);
		debug(circulate(io.lineAngle.get(), -179, 180));

		io.lineDetected.abort();
		io.lineAvoid.set();
	}
}

void Line::extendAvoid()
{
	if (io.lineDetected.off() && io.lineAvoid.on() && io.lineInterrupt.on())
		io.lineAvoid.set();
}

bool isLineFetchRequest = 0;
Line line;