#ifndef AABBH


#define AABBH

#include "../math/vec3.h"
#include "../math/ray.h"
#include "../smath.h"

class aabb
{
public:
	aabb(){}
	aabb(const vec3 &a, const vec3 &b) { _min = a; _max = b; }

	vec3 minp() { return _min; }
	vec3 maxp() { return _max; }

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



aabb surronding_box(aabb box0, aabb box1)
{
	vec3 small(ffmin(box0.minp().x(),box1.minp().x()),
		ffmin(box0.minp().y(), box1.minp().y()),
		ffmin(box0.minp().z(), box1.minp().z())
	);
	vec3 big(ffmax(box0.maxp().x(), box1.maxp().x()),
		ffmax(box0.maxp().y(), box1.maxp().y()),
		ffmax(box0.maxp().z(), box1.maxp().z())
	);

	return aabb(small, big);
}



#endif // !AABBH

