#include"texture.h"
texture::texture(const char* FILENAME)
{
	tex.read_tga_file(FILENAME);
	texWidth = tex.get_width();
	texHeight = tex.get_height();
	tex.flip_vertically();
}
texture::~texture()
{
	//delete tex;
}
TGAColor texture::getTexColor(float u, float v)
{
	return tex.get(u * texWidth, v * texHeight);
}
int texture::getTexWidth()
{
	return texWidth;
}
int texture::getTexHeight()
{
	return texHeight;
}