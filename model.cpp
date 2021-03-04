#include"model.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
Model::Model(const char* FILENAME)
{
	f.clear();
	verts.clear();
	faces.clear();
	texCoords.clear();
	ifstream read;
	read.open(FILENAME, ios::in);
	if (read.good() == false)
	{
		cout << "read model file failed" << endl;
		read.close();
		return;
	}
	else
	{
		string line;
		string title, s1, s2, s3;
		while (getline(read, line))
		{
			istringstream sin(line.c_str());
			sin >> title >> s1 >> s2 >> s3;
			if (title == "v")
			{
				vertsNumber++;
				vec3 vert = getVertFromStr(s1, s2, s3);
				verts.push_back(vert);
				//verts.push_back(getVertFromStr(s1, s2, s3));//不能这样写，存下来的数据全为固定的一个极小值 but why？
			}
			else if (title == "f")
			{
				facesNumber++;
				vector<int> face = getFaceFromStr(s1, s2, s3);
				Faces oneface = getFacesFromstr(s1, s2, s3);
				f.push_back(oneface);
				faces.push_back(face);
			}
			else if (title == "vt")
			{
				vec2 vt = getUvFromStr(s1, s2);
				texCoords.push_back(vt);
			}
			else continue;
			
		}
		read.close();
	}
}
Model::~Model() {}
vec3 Model::vert(int i)
{
	return verts[i];
}
vector<int> Model::face(int idx)
{
	return faces[idx];
}
Faces Model::fs(int index)
{
	return f[index];
}
vec2 Model::getTexcoord(int i)
{
	return texCoords[i];
}
vec3& getVertFromStr(const string x, const string y, const string z)
{
	istringstream toX(x.c_str());
	istringstream toY(y.c_str());
	istringstream toZ(z.c_str());
	float X, Y, Z;
	toX >> X;
	toY >> Y;
	toZ >> Z;
	vec3 v3(X, Y, Z);
	return v3;
}
vector<int> getFaceFromStr(const string s1, const string s2, const string s3)
{
	vector<int> face;
	face.resize(3);
	istringstream iss1(s1);
	istringstream iss2(s2);
	istringstream iss3(s3);
	iss1 >> face[0];
	iss2 >> face[1];
	iss3 >> face[2];
	return face;
}
vec2& getUvFromStr(const string ustr, const string vstr)
{
	istringstream toU(ustr.c_str());
	istringstream toV(vstr.c_str());
	float u, v;
	toU >> u;
	toV >> v;
	vec2 texcoord(u, v);
	return texcoord;
}
Faces& getFacesFromstr(const string s1, const string s2, const string s3)
{
	Faces fa;
	//fa.vert.resize(3);
	//fa.tex.resize(3);
	//fa.normal.resize(3);
	istringstream vert1(s1);
	istringstream vert2(s2);
	istringstream vert3(s3);
	
	vert1 >> fa.vert[0];
	vert2 >> fa.vert[1];
	vert3 >> fa.vert[2];
	
	istringstream texcoord1(s1.substr(s1.find_first_of('/') + 1));
	istringstream texcoord2(s2.substr(s2.find_first_of('/') + 1));
	istringstream texcoord3(s3.substr(s3.find_first_of('/') + 1));
	
	texcoord1 >> fa.tex[0];
	texcoord2 >> fa.tex[1];
	texcoord3 >> fa.tex[2];
	
	istringstream normal1(s1.substr(s1.find_last_of('/') + 1));
	istringstream normal2(s2.substr(s2.find_last_of('/') + 1));
	istringstream normal3(s3.substr(s3.find_last_of('/') + 1));
	normal1 >> fa.normal[0];
	normal2 >> fa.normal[1];
	normal3 >> fa.normal[2];
	return fa;
}