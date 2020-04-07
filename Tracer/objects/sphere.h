#ifndef  SPHEREH
#define SPHEREH


#include "../hittable.h"


#include "../math/vec3.h"
#include "../math/ray.h"

class sphere : public hittable
{
public:
	sphere(){}
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec)const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const;
	vec3 center;
	float radius;
	material *mat_ptr;

};


bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec)const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(r.direction(), oc);
	float c = dot(oc, oc) - (radius*radius);
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) 
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

bool sphere::bounding_box(float t0, float t1, aabb &box) const //t0 t1 refs to time
{
	box = aabb(center - vec3(radius), center + vec3(radius));
	return true;
}


#endif // ! SPHEREH
