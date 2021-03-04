#include"draw.h"
void drawLine(vec2 point1, vec2 point2, TGAImage& image, TGAColor color)
{
	bool steep = false;
	if (fabs(point1.x - point2.x) < fabs(point1.y - point2.y))
	{
		std::swap(point1.x, point1.y);
		std::swap(point2.x, point2.y);
		steep = true;
	}
	if (point1.x > point2.x)
	{
		std::swap(point1.x, point2.x);
		std::swap(point1.y, point2.y);
	}
	float k = (point2.y - point1.y) / (point2.x - point1.x);
	float b = point1.y - k * point1.x;
	for (float t = point1.x; t <= point2.x; t++)
	{
		float x = t;
		float y = k * x + b;
		if (steep == false)
		{
			image.set(x, y, color);
		}
		else
		{
			image.set(y, x, color);
		}
	}
}
void drawTriangle(vec2 v0, vec2 v1, vec2 v2, TGAImage& image, TGAColor color)
{
	drawLine(v0, v1, image, color);
	drawLine(v1, v2, image, color);
	drawLine(v2, v0, image, color);
}