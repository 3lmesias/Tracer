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
		
		
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;

		float reflect_prob;
		double n1, n2;

		if (!rec.front_face) // va saliendo
		{
			ni_over_nt = ref_idx; //ref_idx/1(air)
			n1 = ref_idx;
			n2 = 1;
		}
		else
		{
			ni_over_nt = 1 / ref_idx;
			n1 = 1;
			n2 = ref_idx;
		}

		if (refract(r_in.direction(), rec.normal, ni_over_nt, refracted))
		{
			reflect_prob = schlick(r_in.direction(), rec.normal, n1, n2);
		}
		else
		{
			reflect_prob = 1;
		}

		if (random_double() < reflect_prob)
		{
			vec3 reflected = reflect(r_in.direction(), rec.normal);
			scattered = ray(rec.p, reflected);
		}
		else
		{
			scattered = ray(rec.p, refracted);
		}


		return true;
	}


	float ref_idx;
};


#endif // !DIELETRICH

