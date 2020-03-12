#ifndef SMATHH
#define SMATHH
#include "math/vec3.h"

class smath
{
private:
	smath();
	~smath();
};

vec3 lerp(float t, const vec3 &start_value, const vec3 &end_value);

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

#endif