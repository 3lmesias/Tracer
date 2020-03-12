#ifndef  BOXH


#define BOXH
#include "../hittable.h"
#include "xy_rect.h"
#include "hittable_list.h"


class box : public hittable
{
public:
	box(){}
	box(const vec3 &p0, const vec3 &p1, material *ptr);


	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const
	{
		box = aabb(pmin, pmax);
		return true;
	}

	vec3 pmin, pmax;
	hittable *faces;
};


box::box(const vec3 &p0, const vec3 &p1, material *ptr)
{
	pmin = p0;
	pmax = p1;
	hittable **list = new hittable*[6];
	int i = 0;
	list[i++] = new xy_rect(pmin.x(), pmax.x(), pmin.y(), pmax.y(), pmin.z(), ptr);
	list[i++] = new xy_rect(pmin.x(), pmax.x(), pmin.y(), pmax.y(), pmax.z(), ptr);

	list[i++] = new yz_rect(pmin.y(), pmax.y(), pmin.z(), pmax.z(), pmin.x(), ptr);
	list[i++] = new yz_rect(pmin.y(), pmax.y(), pmin.z(), pmax.z(), pmax.x(), ptr);

	list[i++] = new xz_rect(pmin.x(), pmax.x(), pmin.z(), pmax.z(), pmin.y(), ptr);
	list[i++] = new yz_rect(pmin.y(), pmax.y(), pmin.z(), pmax.z(), pmax.x(), ptr);

	faces = new hittable_list(list,i);
}


bool box::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
	return faces->hit(r, t_min, t_max, rec);
}

#endif // ! BOXH

