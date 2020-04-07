#ifndef TRANSLATEH


#define TRANSLATEH

#include "../hittable.h"
//#include "../math/ray.h"
//#include "aabb.h"

class translate : public hittable
{
public:
	translate(hittable *ptr, const vec3 &displacement) : ptr(ptr), offset(displacement){}
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const;

	hittable * ptr;
	vec3 offset;
};

bool translate::hit(const ray &r, float t_min, float t_max, hit_record &rec)const
{
	ray moved_ray(r.origin() - offset, r.direction(), r.time());;
	if (!ptr->hit(moved_ray, t_min, t_max, rec))
	{
		return false;
	}
	rec.p += offset;
	rec.set_face_normal(moved_ray, rec.normal);
	return true;
}

bool translate::bounding_box(float t0, float t1, aabb &box) const
{
	if (ptr->bounding_box(t0, t1, box))
	{
		//move box
		box = aabb(box.minp() + offset, box.maxp() + offset);
		return true;
	}
	return false;
}

#endif // !TRANSLATEH

