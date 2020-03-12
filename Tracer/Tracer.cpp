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
#include "objects/moving_sphere.h"
#include "camera.h"
#include "math/random.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dialetric.h"
#include "materials/constant_texture.h"
#include "materials/checker_texture.h"
#include "materials/diffuse_light.h"
#include "objects/xy_rect.h"
#include "objects/box.h"
vec3 color(const ray &r, hittable *world, int depth) 
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		//return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		ray scattered;
		vec3 attenuation;
		vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return emitted + attenuation * color(scattered, world, depth + 1);
		}
		else {
			return emitted;
		}
	}
	else {

		return vec3(0); // worldd color
	}
}

hittable *cornell_box() {
	hittable **list = new hittable*[5];
	int i = 0;
	material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
	material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
	material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
	material *light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));

	list[i++] = new flip_normals( new yz_rect(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

	list[i++] = new box(vec3(130, 0, 65), vec3(295, 165, 230), white);
	list[i++] = new box(vec3(256,0,295), vec3(430,330,460), white);

	return new hittable_list(list, i);
}

hittable *random_scene() {
	int n = 500;
	hittable **list = new hittable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(new constant_texture (vec3(0.5, 0.5, 0.5))));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = random_double();
			vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new moving_sphere(
						center, 
						center+vec3(0,0.25*random_double(),0),
						0.0,1.0,0.2,
						new lambertian(new constant_texture(vec3(random_double()*random_double(),
							random_double()*random_double(),
							random_double()*random_double()))
						)
					);
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5*(1 + random_double()),
							0.5*(1 + random_double()),
							0.5*(1 + random_double())),
							0.5*random_double()));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dieletric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dieletric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(new constant_texture(vec3(0.4, 0.2, 0.1))));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hittable_list(list, i);
}

hittable *two_spheres() {
	texture *checker = new checker_texture(
		new constant_texture(vec3(0.2, 0.3, 0.1)),
		new constant_texture(vec3(0.9, 0.9, 0.9))
	);
	int n = 2;
	hittable **list = new hittable*[n + 1];
	list[0] = new sphere(vec3(0, -10, 0), 10, new lambertian(checker));
	list[1] = new sphere(vec3(0, 10, 0), 10, new lambertian(checker));
	return new hittable_list(list, 2);
}

hittable *simple_light() {
	texture *pertext = new constant_texture(vec3(0.7,0.05, 0.05));//new noise_texture(4);
	hittable **list = new hittable*[4];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
	list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
	list[2] = new sphere(vec3(0, 7, 0), 2,
		new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	list[3] = new xy_rect(3, 5, 1, 3, -2,
		new diffuse_light(new constant_texture(vec3(1, 1, 4))));
	return new hittable_list(list, 4);
}

int main()
{
	std::ofstream imgfile("image.ppm");
	int n=16*4;
	int nx = 200*2;//16*n;
	int ny = 200*2;//9*n;
	int ns = 500;

	imgfile<< "P3\n" << nx << " " << ny << "\n255\n";
	/*
	hittable *list[5];
	list[0] = new sphere(vec3(0,0,-1),0.5, new lambertian(vec3(1.0,0.0,0.0)));
	list[1] = new sphere(vec3(0,-100.5,-1),100, new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1,0,-1), 0.5 , new metal(vec3(0.8,0.6,0.2),0.0));
	list[3] = new sphere(vec3(-1,0,-1), 0.5 , new dieletric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dieletric(1.5));
	hittable *world = new hittable_list(list,5);
	*/
	hittable *world = cornell_box();//simple_light();//two_spheres();//random_scene();
	
	/*
	hittable *list[2];
	float R = cos(M_PI / 4);
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));
	hittable *world = new hittable_list(list, 2);
	*/

	vec3 lookfrom(278, 278, -800);
	vec3 lookat(278, 278, 0);
	float dist_to_focus = 10;
	float aperture = 0.0;
	float t0 = 0; // time
	float t1 = 1;
	float vfov = 40;

	vec3 dir = lookfrom - lookat;
	dir.make_unit_vector();
	float ss = 6.0;
	dir = dir * ss;

	//lookfrom = lookfrom + dir;

	//camera cam(lookfrom,lookat,vec3(0,1,0),20, float(nx) / float(ny));
	camera cam(lookfrom, lookat, vec3(0, 1, 0), vfov, float(nx) / float(ny),aperture,dist_to_focus,t0,t1);
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
