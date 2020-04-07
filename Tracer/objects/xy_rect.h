#ifndef XY_RECTH

#define XY_RECTH

#include "../hittable.h"
#include "../materials/material.h"
#include "aabb.h"
#include "../math/ray.h"
#include "../math/vec3.h"

class xy_rect : public hittable
{
public:
	xy_rect(){}
	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mptr) :
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mptr){}
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec)const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const
	{
		box = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
		return true;
	}
	float x0, x1;
	float y0, y1;
	float k;
	material *mp;
};
												
bool xy_rect::hit(const ray &r, float t_min, float t_max, hit_record &rec)const
{
	float invd = 1 / r.direction().z();
	float t = (k - r.origin().z()) * invd;
	if (t < t_min || t > t_max)
		return false;
	float x = r.origin().x() + t * r.direction().x();
	float y = r.origin().y() + t * r.direction().y();
	if (x < x0 || x > x1 || y < y0 || y > y1)
		return false;


	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.p = r.point_at_parameter(t);
	rec.mat_ptr = mp;
	vec3 outward_normal = vec3(0, 0, 1);
	rec.set_face_normal(r, outward_normal);
	rec.t = t;
	return true;

}

class xz_rect :public hittable
{
public:
	xz_rect(){}
	xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mptr) :
		x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mptr) {}
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec)const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const
	{
		box = aabb(vec3(x0, k - 0.0001, z0 ), vec3(x1, k + 0.0001,z1));
		return true;
	}
	float x0, x1;
	float z0, z1;
	float k;
	material *mp;
};

class yz_rect :public hittable
{
public:
	yz_rect(){}
	yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mptr) :
		y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mptr) {}
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec)const;
	virtual bool bounding_box(float t0, float t1, aabb &box) const
	{
		box = aabb(vec3(k - 0.0001,y0, z0), vec3(k + 0.0001,y1, z1));
		return true;
	}
	float y0, y1;
	float z0, z1;
	float k;
	material *mp;
};

bool xz_rect::hit(const ray &r, float t_min, float t_max, hit_record &rec)const
{
	float invd = 1 / r.direction().y();
	float t = (k - r.origin().y()) * invd;
	if (t < t_min || t > t_max)
		return false;
	float x = r.origin().x() + t * r.direction().x();
	float z = r.origin().z() + t * r.direction().z();
	if (x < x0 || x > x1 || z < z0 || z > z1)
		return false;


	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.p = r.point_at_parameter(t);
	rec.mat_ptr = mp;
	//rec.normal = vec3(0, 1, 0);
	vec3 outward_normal = vec3(0, 1, 0);
	rec.set_face_normal(r, outward_normal);
	rec.t = t;
	return true;

}


bool yz_rect::hit(const ray &r, float t_min, float t_max, hit_record &rec)const
{
	float invd = 1 / r.direction().x();
	float t = (k - r.origin().x()) * invd;
	if (t < t_min || t > t_max)
		return false;
	float y = r.origin().y() + t * r.direction().y();
	float z = r.origin().z() + t * r.direction().z();
	if (y < y0 || y > y1 || z < z0 || z > z1)
		return false;


	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.p = r.point_at_parameter(t);
	rec.mat_ptr = mp;
	vec3 outward_normal = vec3(1, 0, 0);
	rec.set_face_normal(r, outward_normal);
	rec.t = t;
	return true;

}

#endif // !XY_RECTH
