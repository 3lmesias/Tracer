#ifndef CAMERAH

#define CAMERAH
#define _USE_MATH_DEFINES

#include "math/ray.h"
#include <math.h>
#include "math/random.h"

class camera
{
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
		float aperture, float focus_dist, float t0, float t1)
	{
		time0 = t0;
		time1 = t1;

		lens_radius = aperture / 2;

		float theta = vfov * M_PI/180;

		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;

		origin = lookfrom;
		w = unit_vector(lookfrom - lookat); //z forward
		u = unit_vector(cross(vup, w)); // x right
		v = cross(w, u); // y up
		


		lower_left_corner = origin - half_height * v * focus_dist- half_width * u
			*focus_dist- (focus_dist*w);//vec3(-half_width, -half_height, -1.0);// todo change to near_lane
		horizontal = 2 * half_width*u*focus_dist;
		vertical = 2 * half_height*v*focus_dist;
	}

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) 
	{
		lens_radius = 0;

		float theta = vfov * M_PI / 180;

		float half_height =  tan(theta / 2);
		float half_width = aspect * half_height;

		origin = lookfrom;
		w = unit_vector(lookfrom - lookat); //z forward
		u = unit_vector(cross(vup, w)); // x right
		v = cross(w, u); // y up



		lower_left_corner = origin - half_height * v  - half_width * u  - (1*w);//vec3(-half_width, -half_height, -1.0);// todo change to near_lane
		horizontal = 2 * half_width*u;
		vertical = 2 * half_height*v;
	}

	ray get_ray(float s, float t) const{

		float time = time0 + random_double()*(time1 - time0);

		if (lens_radius == 0)
		{
			ray aux = ray(origin, lower_left_corner + s * horizontal + t * vertical - origin,time);
			aux.direction().make_unit_vector();
			return aux;
		}
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		ray aux = ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
		aux.direction().make_unit_vector();
		return aux;

	}



	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	float front_plane;
	float lens_radius;
	vec3 u, v, w;
	float time0, time1;
}; 


#endif // !CAMERAH
