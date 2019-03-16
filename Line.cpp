#include "Line.h"

Line::Line() {}

void Line::update()
{
	if (isEnabled())
	{
		if (DEBUG_LOOP)
			beginSegment(F("line"));
		if (BOTTOM_SERIAL.available())
		{
			int angle = map(BOTTOM_SERIAL.read(), 0, 255, 0, 359);
			io.lineAngle.set(angle);
			io.onLine.now();
			debug(io.lineAngle.get());
		}
		if (DEBUG_LOOP)
			endSegment();
	}
}

bool Line::isEnabled()
{
	return LINE_ENABLED;
}

Line line;