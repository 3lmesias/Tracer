#ifndef RANDOMH

#define RANDOMH

#include<functional>
#include<random>

inline double random_double()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<double()> rand_generator = std::bind(distribution, generator);
	return rand_generator();
}


vec3 random_in_unit_sphere()
{
	vec3 p;
	do {
		p = 2.0*vec3(random_double(), random_double(), random_double()) - vec3(1);
	} while (p.square_length() >= 1.0);
	return p;
}

vec3 random_in_sphere(float r)
{
	vec3 p = random_in_unit_sphere();
	return p * r;
}

vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(random_double(), random_double(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1);
	return p;
}

#endif // !RANDOMH
