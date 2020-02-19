#ifndef MATERIALH


#define MATERIALH


#include "../math/ray.h"
#include "../hittable.h"
#include "../math/random.h"

struct hit_record;

class material
{
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

vec3 reflect(const vec3 &v, const vec3 &n)
{
	vec3 nv = unit_vector(v);

	const double cosi = -dot(n, nv);
	return nv + 2 * cosi * n;

	return v - 2 * dot(v, n)*n;
}


bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted)
{
	vec3 uv = unit_vector(v);


	
	double cosI = -dot(n, uv);
	double sint2 = ni_over_nt * ni_over_nt *(1.0 - cosI * cosI);

	if (sint2 > 1.0) return false; // total internal reflection

	double root = sqrt(1.0 - sint2);

	refracted = ni_over_nt * uv + (ni_over_nt*cosI - root)*n;
	return true;
	




	uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}



double schlick(const vec3 &v, const vec3 &n, double n1, double n2)
{
	vec3 nv = unit_vector(v);
	double r0 = (n1 - n2) / (n1 + n2);
	r0 *= r0;
	double cosx = -dot(n, nv); // cosi

	if (n1 > n2) 
	{
		const double ni_no = n1 / n2;
		const double sint2 = ni_no * ni_no *(1.0 - cosx * cosx);
		if (sint2 > 1.0) 
			return 1.0; // total internal reflection
		cosx = sqrt(1 - sint2); // change to cost
	}
	const double x = 1.0 - cosx;
	return r0 + (1.0 - r0) *x*x*x*x*x;
}




#endif // !MATERIALH
