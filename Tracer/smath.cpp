#include "smath.h"



smath::smath()
{
}


smath::~smath()
{
}



vec3 lerp(float t, const vec3 &start_value, const vec3 &end_value)
{
	vec3 aux = (1 - t) * start_value + t * end_value;
	return aux;
}