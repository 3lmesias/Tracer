#ifndef ROTATEH

#define _USE_MATH_DEFINES
#define ROTATEH


#include "../hittable.h"
#include "aabb.h"

class rotate_y : public hittable
{
public:
	rotate_y(){}
	rotate_y(hittable *ptr, float angle);
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const ;
	virtual bool bounding_box(float t0, float t1, aabb &box) const
	{
		box = bbox;
		return hasbox;
	}
	~rotate_y();

	hittable *ptr;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	aabb bbox;

private:

};

rotate_y::rotate_y(hittable *ptr,float angle):ptr(ptr)
{
	float radians = (M_PI / 180.0) * angle;
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = ptr->bounding_box(0, 1, bbox);
	
	vec3 _min(FLT_MAX);
	vec3 _max(-FLT_MAX);
	// rotate every corner of the bounding box
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				float x = i * bbox.maxp().x() + (1 - i)*bbox.minp().x();
				float y = j * bbox.maxp().y() + (1 - j)*bbox.minp().y();
				float z = k * bbox.maxp().z() + (1 - k)*bbox.minp().z();
				float newx = cos_theta * x + cos_theta * z;
				float newz = -sin_theta * x + cos_theta * z;
				vec3 tester(newx, y, newz);
				for (int c = 0; c < 3; c++)
				{
					if (tester[c] > _max[c])
						_max[c] = tester[c];

					if (tester[c] < _min[c])
						_min[c] = tester[c];

				}

			}
		}
	}
	bbox = aabb(_min, _max);
}


bool rotate_y::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
	vec3 origin = r.origin();
	vec3 direction = r.direction();
	origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
	origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];
	direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
	direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];
	ray rotated_r(origin, direction, r.time());
	if (ptr->hit(rotated_r, t_min, t_max, rec))
	{
		vec3 p = rec.p;
		vec3 normal = rec.normal;
		p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
		p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];
		normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
		normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];
		rec.p = p;
		rec.set_face_normal(rotated_r, normal);
		
		return true;
	}
	else
	{
		return false;
	}

}

rotate_y::~rotate_y()
{
	delete ptr;
}

#endif // !ROTATEH

