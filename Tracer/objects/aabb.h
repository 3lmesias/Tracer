#ifndef AABB


#define AABB

#include "../math/vec3.h"
#include "../math/ray.h"

class aabb
{
public:
	aabb(){}
	aabb(const vec3 &a, const vec3 &b) { _min = a; _max = b; }

	vec3 min() { return _min; }
	vec3 max() { return _max; }

	bool hit(const ray &r, float tmin, float tmax) const
	{
		// iterate over the 3 axis
		for (int a = 0; a < 3; a++)
		{
			float invD = 1.0f / r.direction()[a]; // avoid +0, -0 problem 
			float t0 = (_min[a] - r.origin()[a]) * invD;
			float t1 = (_max[a] - r.origin()[a]) * invD;
			if (invD < 0.0f)// ray  going back
				std::swap(t0, t1);
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin)
				return false;
		}
		return true;
	}
	vec3 _min;
	vec3 _max;
};


#endif // !AABB

