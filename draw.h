#ifndef __DRAW_H__
#define __DRAW_H__

#include"image.h"
#include"Math.h"
void drawLine(vec2 point1, vec2 point2, TGAImage& image, TGAColor color);
void drawTriangle(vec2 v0,vec2 v1,vec2 v2, TGAImage& image, TGAColor color);
#endif // !__DRAW_H__