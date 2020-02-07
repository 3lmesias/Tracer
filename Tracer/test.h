#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

class test {
public:

	float e[3];

	test() {};
	test(float e0, float e1, float e2);
	inline float x() { return e[0]; }
	inline float y() { return e[1]; }
	inline float z() { return e[2]; }

	inline float r() { return e[0]; }
	inline float g() { return e[1]; }
	inline float b() { return e[2]; }

	inline const test& operator+() const { return *this; }
	inline test operator-() { return test(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	test& operator+=(const test &v2);
	test& operator-=(const test &v2);
	test& operator*=(const test &v2);
	test& operator/=(const test &v2);
	test& operator*=(const float t);
	test& operator/=(const float t);

	inline float length() const
	{
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	inline float square_length() const
	{
		return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline void make_unit_vector();

};

inline void test::make_unit_vector()
{
	float k = 1 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

inline std::istream & operator >> (std::istream &is, test &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream & operator << (std::ostream &os, const test &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline test operator+(const test &v1, const test &v2)
{
	return test(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline test operator-(const test &v1, const test &v2)
{
	return test(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline test operator*(const test &v1, const test &v2)
{
	return test(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline test operator*(float t, const test &v)
{
	return test(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline test operator*(const test &v, float t)
{
	return test(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline test operator/(const test &v1, const test &v2)
{
	return test(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline test operator/(test v, float t)
{
	return test(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const test &v1, const test &v2)
{
	return v1.e[0] * v2.e[0]
		+ v1.e[1] * v2.e[1]
		+ v1.e[2] * v2.e[2];
}

inline test cross(const test &v1, const test &v2)
{
	return test(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline test unit_vector(test v)
{
	return v / v.length();
}

