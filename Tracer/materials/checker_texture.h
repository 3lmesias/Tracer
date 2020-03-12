#ifndef CHECKER_TEXTUREH

#define CHECKER_TEXTUREH

#include "texture.h"
#include "../math/vec3.h"

class checker_texture : public texture
{
public:
	checker_texture(){}
	checker_texture(texture *t0, texture *t1) : even(t0), odd(t1) {}

	virtual vec3 value(float u, float v, const vec3 &p) const
	{
		float sines = sin(2 * p.x()) * sin(2 * p.y()) * sin(2 * p.z());
		if (sines < 0)
			return odd->value(u, v, p);
		else
			return even->value(u, v, p);
	}

	float scale;
	texture *odd;
	texture *even;
};



#endif // !CHECKER_TEXTUREH

