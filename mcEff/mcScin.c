/***************************************************
 * Monte Carlo calculation of the efficiency of
 * squared scintillators of fixed size for muons
 * coming from cosmic rays.
 * 
 *  - Compiling:   gcc mcScin.c -o mcScin -lm
 *  - Running:     ./mcScin
 ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654

int main(void) {

	int i, N, n = 0;
	double x1, y1, x2, y2, cosine, tangent, phi, d, rho, effGeom;
	
	/***************************************************
	 * Scintillator dimensions
	 ***************************************************/
	double xs = 10, ys = 31;

	/***************************************************
	 * Data input
	 ***************************************************/
	printf("\n PROGRAM THAT CALCULATES THE GEOMETRIC EFFICIENCY");
	printf("\n   FOR A FIXED DISTANCE BETWEEN SCINTILLATORS");
	printf("\n	   (SCINTILLATORS DIMENSIONS: 10x31 cm2)\n");
	printf("\n Distance between scintillators in cm: ");
	scanf("%lf", &d);
	printf(" Number of muons to simulate: ");
	scanf("%d", &N);
	getchar();
	
	for (i=1; i<=N; i++) { 

		/***************************************************
	 	 * Muon coordinates at upper scintillator
		 * The origin is in the lower scintillator
		 ***************************************************/
		x1  = xs * ( (double)rand() / RAND_MAX );
		y1  = ys * ( (double)rand() / RAND_MAX );

		/***************************************************
	 	 * Muon exit direction (theta, phi)
		 * Simulation of the angular distribution ~cos^4
		 ***************************************************/
		cosine  = pow( (double)rand() / RAND_MAX, 1/4.0 );
		tangent = sqrt(1 - cosine*cosine) / cosine;
		phi     = 2 * PI * ( (double)rand() / RAND_MAX );

		/***************************************************
	 	 * Muon coordinates at the lower scintillator
		 * rho is the module of the vector projected in the detector
		 ***************************************************/
		rho = d * tangent;
		x2  = x1 + rho*cos(phi);
		y2  = y1 + rho*sin(phi);
			
		if(x2 < xs && y2 < ys)
			n++;
	}
		
	effGeom = (double)n / N;
	printf("\n Number of coicidences = %d", n);
	printf("\n Geometric Efficiency  = %3.3lf\n\n", effGeom);
	return 0;
}

#undef MAX
#undef PI
