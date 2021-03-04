#include"rasterizer.h"
bool isInTriangle(vec2 point, vec2 A, vec2 B, vec2 C)
{
	//重心坐标法
	//vec3 v0 = (C - A).toVec3();这种写法得到的三位向量 ，每一维数字都错误，是非常小的一个值，不知道为啥
	vec2 ac = C - A;
	vec2 ab = B - A;
	vec2 ap = point - A;
	vec3 v0 = ac.toVec3();
	vec3 v1 = ab.toVec3();
	vec3 v2 = ap.toVec3();
	float u = (v1.dot(v1) * v2.dot(v0) - v1.dot(v0) * v2.dot(v1))
		/ ((v0.dot(v0) * v1.dot(v1)) - v0.dot(v1) * v1.dot(v0));
	float v = (v0.dot(v0) * v2.dot(v1) - v0.dot(v1) * v2.dot(v0))
		/ ((v0.dot(v0) * v1.dot(v1)) - v0.dot(v1) * v1.dot(v0));
	if (u >= 0 && v >= 0 && (u + v) <= 1)return true;
	else return false;
}
void rasterizerTriangle(vec2 v0, vec2 v1, vec2 v2, TGAImage& image, TGAColor color)
{
	float xMin, xMax, yMin, yMax;
	xMin = fminf((fminf(v0.x, v1.x)), v2.x);
	xMax = fmaxf((fmaxf(v0.x, v1.x)), v2.x);
	yMin = fminf((fminf(v0.y, v1.y)), v2.y);
	yMax = fmaxf((fmaxf(v0.y, v1.y)), v2.y);
	for (int x = xMin; x <= xMax; x++)
	{
		for (int y = yMin; y <= yMax; y++)
		{
			if (isInTriangle(vec2(x, y), v0, v1, v2))
			{
				image.set(x, y, color);
			}
			else
			{
				continue;
			}
		}
	}
}
void rasterize(vec2 p0, vec2 p1, TGAImage& image, TGAColor color, int ybuffer[])
{
	if (p0.x > p1.x)
	{
		swap(p0, p1);
	}
	for (int x = p0.x; x <= p1.x; x++)
	{
		float t = (x - p0.x) / (float)(x - p1.x);//重心坐标
		int y = (1. - t) * p0.y + t * p1.y;
		if (ybuffer[x] < y)
		{
			ybuffer[x] = y;
			image.set(x, 0, color);
		}
	}
}
vec3 getBarycentric(const vec3 A, const vec3 B, const vec3 C, const vec3 P)
{
	float c = ((A.y - B.y) * P.x + (B.x - A.x) * P.y + A.x * B.y - B.x * A.y) /
		((A.y - B.y) * C.x + (B.x - A.x) * C.y + A.x * B.y - B.x * A.y);
	float b = ((A.y - C.y) * P.x + (C.x - A.x) * P.y + A.x * C.y - C.x * A.y) /
		((A.y - C.y) * B.x + (C.x - A.x) * B.y + A.x * C.y - C.x * A.y);
	float a = 1 - b - c;
	return vec3(a, b, c);
}
void triangle(vec3* pts, vec2* texcoords, float* zBuffer, TGAImage& image, TGAColor color, texture& tex)
{
	float xMin, xMax, yMin, yMax;
	/****注意不能超过【0，height（width）-1】*****/
	xMin = fminf(pts[0].x, fminf(pts[1].x, pts[2].x));
	xMin = fmaxf(0, xMin);
	xMax = fmaxf(pts[0].x, fmaxf(pts[1].x, pts[2].x));
	xMax = fminf(image.get_width() - 1, xMax);
	yMin = fminf(pts[0].y, fminf(pts[1].y, pts[2].y));
	yMin = fmaxf(0, yMin);
	yMax = fmaxf(pts[0].y, fmaxf(pts[1].y, pts[2].y));
	yMax = fminf(image.get_height() - 1, yMax);
	vec3 P;
	for (P.x = xMin; P.x <= xMax; P.x++)
	{
		for (P.y = yMin; P.y <= yMax; P.y++)
		{
			vec3 bc_screen = getBarycentric(pts[0], pts[1], pts[2], P);
			if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0)continue;
			P.z = 0;
			vec2 texUV(0, 0);
			for (int i = 0; i < 3; i++)
			{
				P.z += pts[i].z * bc_screen[i];
				texUV.x += texcoords[i].x * bc_screen[i];
				texUV.y += texcoords[i].y * bc_screen[i];
			}
			TGAColor texcolor = tex.getTexColor(texUV.x, texUV.y);
			int idx = P.y * image.get_width() + P.x;
			if (zBuffer[idx] < P.z)
			{
				zBuffer[idx] = P.z;
				//image.set(P.x, P.y, color);
				image.set(P.x, P.y, texcolor);
			}
		}
	}
}