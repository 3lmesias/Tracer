#ifndef DIFFUSE_LIGHTH 


#define DIFFUSE_LIGHTH
#include "material.h"
#include "texture.h"
#include "../math/ray.h"
#include "../hittable.h"
#include "../math/vec3.h"

class diffuse_light : public material
{
public:

	texture *emit;
	diffuse_light(texture *e) : emit(e) 
	{

	}

	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered)const
	{
		return false;
	}

	virtual vec3 emitted(float u, float v, const vec3 &p)const 
	{
		return emit->value(u, v, p);
	}

};

#endif // !DIFFUSE_LIGHTH 

