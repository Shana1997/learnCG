#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__
#include"draw.h"
#include"texture.h"
bool isInTriangle(vec2 point, vec2 A, vec2 B, vec2 C);
/*image那里传引用，否则只是局部变量*/
void rasterizerTriangle(vec2 v0, vec2 v1, vec2 v2, TGAImage& image, TGAColor color);
void rasterize(vec2 p0, vec2 p1, TGAImage& image, TGAColor color, int ybuffer[]);
vec3 getBarycentric(const vec3 A, const vec3 B, const vec3 C, const vec3 P);
//void triangle(vec3* pts, float* zBuffer, TGAImage& image, TGAColor color);
void triangle(vec3* pts, vec2* texcoords, float* zbuffer, TGAImage& image, TGAColor color, texture& tex);
#endif // !__RASTERIZER_H__