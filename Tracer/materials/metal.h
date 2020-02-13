#ifndef METALH

#define METALH


#include "material.h"
#include "../math/ray.h"
#include "../math/random.h"


class metal : public material
{

public:
	metal(const vec3 &a, float f) : albedo(a)
	{
		f < 1 ? fuzz = f : fuzz = 1;
	}

	 virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		reflected += random_in_sphere(fuzz);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

	vec3 albedo;
	float fuzz;

};


#endif // !METALH

