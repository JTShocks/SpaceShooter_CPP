
#include "utility.h"
#include "glm\glm.hpp"

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (glm::max(x1, x2) < glm::min(x1 + w1, x2 + w2)) && (glm::max(y1, y2) < glm::min(y1 + h1, y2 + h2));
}

void calcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy)
{
	int steps = glm::max(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}
