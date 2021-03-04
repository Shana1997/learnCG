#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include"image.h"
class texture
{
public:
	texture(const char *FILENAME);
	~texture();
	TGAColor getTexColor(float u, float v);
	int getTexWidth();
	int getTexHeight();
private:
	TGAImage tex;
	int texWidth;
	int texHeight;
};
#endif // !__TEXTURE_H__
