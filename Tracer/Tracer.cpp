// Tracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
//#include "Lib/stb_image.h"
#include <iostream>
#include <fstream>
#include "smath.h"
#include "objects/hittable_list.h"
#include "objects/sphere.h"
#include "camera.h"
#include "math/random.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dialetric.h"

vec3 color(const ray &r, hittable *world, int depth) 
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		//return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0);
		}
		//vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		//return 0.5 * color(ray(rec.p,target-rec.p), world);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0); // 0 - 1
		return lerp(t, vec3(1.0), vec3(0.5, 0.7, 1.0));//
	}
}

int main()
{
	std::ofstream imgfile("image.ppm");
	int n=1;
	int nx = 200*n;
	int ny = 100*n;
	int ns = 500;
	/*
		(-2,1,-1)---------------(2,1,-1)
		l								l
		l								l
		l								l
		l								l
		(-2,-1,-1)--------------(2,-1,-1)


		camera at (0,0,0)

	
	*/
	imgfile<< "P3\n" << nx << " " << ny << "\n255\n";
	
	hittable *list[5];
	list[0] = new sphere(vec3(0,0,-1),0.5, new lambertian(vec3(1.0,0.0,0.0)));
	list[1] = new sphere(vec3(0,-100.5,-1),100, new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1,0,-1), 0.5 , new metal(vec3(0.8,0.6,0.2),0.0));
	list[3] = new sphere(vec3(-1,0,-1), 0.5 , new dieletric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dieletric(1.5));
	hittable *world = new hittable_list(list,5);
	
	/*
	hittable *list[2];
	float R = cos(M_PI / 4);
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
	hittable *world = new hittable_list(list, 2);
	*/

	vec3 lookfrom(3, 3, 2);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 0.1;

	//camera cam(lookfrom,lookat,vec3(0,1,0),20, float(nx) / float(ny));
	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny),aperture,dist_to_focus);
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++) 
		{
			vec3 col(0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + random_double()) / float(nx);
				float v = float(j + random_double()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world,0);
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); // gama correct 
			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			//std::cout << ir <<" "<< ig << " " << ib << "\n";
			imgfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	imgfile.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
