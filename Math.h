#pragma once
#include<cmath>
#include<iostream>
using namespace std;
class vec3
{
public:
	vec3();
	vec3(float u, float v, float w);
	vec3(float n);
	~vec3() {}
	float x;
	float y;
	float z;
	float dot(const vec3 vec);
	vec3& cross(const vec3 vec);
	vec3& normalized();
	float norm();
	float operator[](const int number);
	vec3& operator+(const vec3 vec);
	vec3& operator-(const vec3 vec);
	vec3& operator*(const vec3 vec);
	vec3& operator*(const float n);
	vec3& operator/(const float n);
};
ostream& operator<<(ostream& cout, const vec3& vec);
class vec2
{
public:
	vec2();
	vec2(const float X, const float Y);
	vec2(const float t);
	~vec2();
	float dot(const vec2& vec);
	vec2& cross(const vec2 vec);
	vec3& toVec3();//vec3类要定义在vec2前，否则报错
	float& operator[](int number);
	vec2& operator*(const vec2 vec);
	vec2& operator+(const vec2 vec);
	vec2& operator-(const vec2 vec);
	vec2& operator=(vec2 vec);
	float x;
	float y;
};
ostream& operator<<(ostream& cout, vec2 vec);
