#ifndef DIELETRICH

#include "material.h"
#include "../math/ray.h"
#include "../math/random.h"

class dieletric : public material
{
public:
	dieletric(float ri) : ref_idx(ri){}
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
	{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;

		if (dot(r_in.direction(), rec.normal) > 0) // va entrando
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx; //ref_idx/1(air)
		}
		else
		{
			outward_normal = rec.normal; // va saliendo 
			ni_over_nt = 1 / ref_idx;
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			scattered = ray(rec.p, refracted);
		}
		else
		{
			scattered = ray(rec.p, refracted);
			return false;
		}
		return true;
	}


	float ref_idx;
};


#endif // !DIELETRICH

