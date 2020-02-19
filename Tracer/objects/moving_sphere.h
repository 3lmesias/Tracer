#ifndef MOVING_SPHEREH


#define MOVING_SPHEREH

#include "../hittable.h"
#include "../math/vec3.h"
#include "../math/ray.h"

class moving_sphere : public hittable
{
public:
	moving_sphere(){}
	moving_sphere(vec3 cen0, vec3 cen1, float t0, float t1,float r, 
	material *m): venter
	{}
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec)const;
	virtual bool bounding_box(float t0, float t1, aabb &box )
	vec3 center(float time) const;
	vec3 center0, center1;
	float time0, time1;
	float radius;
	material *mat_ptr;
};


#endif // !MOVING_SPHEREH
