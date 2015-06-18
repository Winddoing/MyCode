#include <math.h>

float volume(float r)
{
//	return M_PI * r * r * r * 3.0 / 4.0 ;
	return M_PI * pow(r, 3.0) 
				* 4.0 / 3.0 ;
}

