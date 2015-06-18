#include <stdio.h>
#include <stdlib.h>
#include <round.h>

int main(int argc, char *argv[])
{
	float radius = 1.0;

	fprintf(stdout, "radius=%.2f\n"
					"circle=%.2lf\n"
					"area=%.2lf\n"
					"volume=%.2lf\n",
				radius, circle(radius), 
				area(radius),
				volume(radius));
					
	return EXIT_SUCCESS;
}

