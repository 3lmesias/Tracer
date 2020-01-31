#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:
	vec3();
	vec3(float e0, float e1, float e2);
	float x();
	float y();
	float z();
	float r();
	float g();
	float b();

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3 &v2);
	vec3& operator-=(const vec3 &v2);
	vec3& operator*=(const vec3 &v2);
	vec3& operator/=(const vec3 &v2);
	vec3& operator*=(const float t);
	vec3& operator/=(const float t);

	float length() const;
	float square_length() const;
	void make_unit_vector();




	float e[3];

};