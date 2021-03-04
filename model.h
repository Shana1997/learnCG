#ifndef __MODEL_H__
#define __MODEL_H__

#include"Math.h"
#include<vector>
using namespace std;
struct Faces
{
public:
	int vert[3];
	int tex[3];
	int normal[3];
	/******������ʱ �������������ݻ������֪��Ϊɶ******/ 
	/*
	vector<int> vert;
	vector<int>tex;
	vector<int>normal;	
	*/
};
class Model
{
private:
	vector<vec3>verts;
	vector<vector<int>>faces;
	vector<vec2>texCoords;
	vector<Faces>f;
public:
	Model(const char* FILENAME);
	~Model();
	int vertsNumber;
	int facesNumber;
	vec3 vert(int i);//��ȡ��������
	vector<int> face(int idx);
	Faces fs(int index);
	vec2 getTexcoord(int i);//��ȡ��������
};
vec3& getVertFromStr(const string x, const string y, const string z);
vector<int> getFaceFromStr(const string s1, const string s2, const string s3);
vec2& getUvFromStr(const string ustr, const string vstr);
Faces& getFacesFromstr(const string s1, const string s2, const string s3);
#endif // !__MODEL_H__