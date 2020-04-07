#ifndef HITTABLEH
#define HITTABLEH

#include "math/ray.h"

#include "objects/aabb.h"

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
	float u, v;
	bool front_face;

	inline void set_face_normal(const ray &r, const vec3 & outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : outward_normal * -1;
	}
};

class hittable
{
public:
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
	virtual bool bounding_box(float t0, float t1, aabb &box) const = 0;
};



// hittable that contains anotther hittable but flips the normals
class flip_normals :public hittable
{
public:
	flip_normals(hittable *h) : ptr(h)
	{

	}

	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const
	{
		if (ptr->hit(r, t_min, t_max, rec))
		{
			rec.normal *= -1;
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual bool bounding_box(float t0, float t1, aabb &box) const
	{
		return ptr->bounding_box(t0, t1, box);
	}

	hittable *ptr;
};

#endif // !HITTABLEH

