#pragma once
#include"image.h"
#include <iostream>
#include <fstream>
#include"draw.h"
using namespace std;
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const int width = 1000;
const int height = 1000;
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include"Math.h"
#include"model.h"
#include<vector>
#include"rasterizer.h"
vec3 world2screen(vec3 v)
{
	return vec3(int((v.x + 1.) * width / 2.), int((v.y + 1.) * height / 2.), v.z);
}
void lesson3Resualt()
{
	Model faceModel("F:/Myrender/MyRenderer/MyRenderer/obj/african_head.obj");
	texture faceTexture("F:/Myrender/MyRenderer/MyRenderer/texture/african_head_diffuse.tga");
	TGAImage image(width, height, TGAImage::RGB);
	float* zBuffer = new float[width * height];
	for (int i = 0; i < width * height; i++)zBuffer[i] = numeric_limits<float>::max() * (-1);
	for (int i = 0; i < faceModel.facesNumber; i++)
	{
		vec3 a = faceModel.vert(faceModel.fs(i).vert[0] - 1);
		vec3 b = faceModel.vert(faceModel.fs(i).vert[1] - 1);
		vec3 c = faceModel.vert(faceModel.fs(i).vert[2] - 1);
		vec3 pts[3];
		vec2 texcoords[3];
		for (int j = 0; j < 3; j++)
		{
			texcoords[j] = faceModel.getTexcoord(faceModel.fs(i).tex[j] - 1);
			pts[j] = world2screen(faceModel.vert(faceModel.fs(i).vert[j] - 1));
		}
		vec3 ab = b - a;
		vec3 ac = c - a;
		vec3 n = ab.cross(ac);
		n = n.normalized();
		vec3 lightDir(0, 0, 1);
		float intensity = (n.dot(lightDir)) / (n.norm() * lightDir.norm());
		if (intensity > 0)
		{
			//rasterizerTriangle(vec2(pts[0].x, pts[0].y), vec2(pts[1].x, pts[1].y), vec2(pts[2].x, pts[2].y), image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
			triangle(pts, texcoords, zBuffer, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255), faceTexture);
			cout << "face " << i << " done" << endl;
		}
		else
		{
			continue;
		}
	}
	image.flip_vertically();
	image.write_tga_file("F:/Myrender/MyRenderer/pictures/lesson3_texture.tga");
}

void testTEXTURE()
{
	TGAImage image(1024, 1024,TGAImage::RGB);
	texture tex("F:/Myrender/MyRenderer/MyRenderer/texture/african_head_diffuse.tga");
	for (int i = 0; i < 1024; i++)
	{
		for (int j = 0; j < 1024; j++)
		{
			image.set(i, j, tex.getTexColor(i / 1024., j / 1024.));
		}
	}
	image.write_tga_file("F:/Myrender/MyRenderer/pictures/texture.tga");
}