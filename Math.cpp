#include"Math.h"
/*vec2*/
ostream& operator<<(ostream& cout, vec2 vec)
{
	cout << vec.x << ", " << vec.y;
	return cout;
}
vec2::vec2() :x(0.0), y(0.0) {}
vec2::vec2(const float X, const float Y) :x(X), y(Y) {}
vec2::vec2(const float t) :x(t), y(t) {}
vec2::~vec2() {}
float vec2::dot(const vec2& vec) { return this->x * vec.x + this->y * vec.y; }
vec2& vec2::cross(const vec2 vec)
{
	vec2 v2 = vec2(this->x * vec.y - this->y * vec.x, 0.0);
	return v2;
}
vec3& vec2::toVec3()
{
	vec3 vec(this->x, this->y, 0.0);
	return vec;
}
float& vec2::operator[](int number) { return (number == 0 ? x : y); }
vec2& vec2::operator*(const vec2 vec)
{
	vec2 v2 = vec2(this->x * vec.x, this->y * vec.y);
	return v2;
}
vec2& vec2::operator+(const vec2 vec)
{
	vec2 v2 = vec2(this->x + vec.x, this->y + vec.y);
	return v2;
}
vec2& vec2::operator-(const vec2 vec)
{
	vec2 v = vec2(this->x - vec.x, this->y - vec.y);
	return v;
}
vec2& vec2::operator=(vec2 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

/*vec3*/
ostream& operator<<(ostream& cout, const vec3& vec)
{
	cout << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
	return cout;
}
vec3::vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
vec3::vec3(float u, float v, float w)
{
	this->x = u;
	this->y = v;
	this->z = w;
}
vec3::vec3(float n)
{
	this->x = n;
	this->y = n;
	this->z = n;
}
float vec3::dot(const vec3 vec)
{
	return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}
vec3& vec3::cross(const vec3 vec)
{
	//(a1,a2,a3)x(b1,b2,b3)=(a2b3-a3b2,a3b1-a1b3,a1b2-a2b1)
	vec3 v = vec3(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
	return v;
}
vec3& vec3::normalized()
{
	float sqr = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x /= sqr;
	this->y /= sqr;
	this->z /= sqr;
	vec3 n(this->x, this->y, this->z);
	return n;
}
float vec3::norm()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}
float vec3::operator[](const int number)
{
	if (number == 0)return this->x;
	if (number == 1)return this->y;
	if (number == 2)return this->z;
	return -1;
}
vec3& vec3::operator+(const vec3 vec)
{
	vec3 v(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	return v;
}
vec3& vec3::operator-(const vec3 vec)
{
	vec3 v(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	return v;
}
vec3& vec3:: operator*(const vec3 vec)
{
	vec3 v(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	return v;
}
vec3& vec3:: operator*(const float n)
{
	this->x *= n;
	this->y *= n;
	this->z *= n;
	return *this;
}
vec3& vec3:: operator/(const float n)
{
	this->x /= n;
	this->y /= n;
	this->z /= n;
	return *this;
}