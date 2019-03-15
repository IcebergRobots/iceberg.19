#include "Line.h"

Line::Line() {}

void Line::update()
{
	if (DEBUG_LOOP)
		beginSegment(F("line"));
	if (BOTTOM_SERIAL.available()) {
		int angle = map(BOTTOM_SERIAL.read(), 0, 255, 0, 359);
		io.lineAngle.set(angle);
		io.onLine.set();
		debug(io.lineAngle.get());
	}
	if (DEBUG_LOOP)
		endSegment();
}

Line line;