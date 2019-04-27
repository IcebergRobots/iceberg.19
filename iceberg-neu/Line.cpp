#include "Line.h"

Line::Line() {}

void Line::update()
{
	if (isEnabled())
	{
		if (BOTTOM_SERIAL.available())
		{
			int angle = map(BOTTOM_SERIAL.read(), 0, 255, 0, 359);
			io.lineAngle.set(angle);
			io.onLine.now();
		}
	}
}

bool Line::isEnabled()
{
	return LINE_ENABLED;
}

Line line;