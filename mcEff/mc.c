/***************************************************
 * Monte Carlo calculation of the efficiency of
 * a detector for photons coming from a circular
 * source of radius r and thickness b.
 * 
 *  - Compiling:   gcc mc.c -o mc -lm
 *  - Running:     ./mc
 ***************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	long int i, N;
	int Nin = 0;
	double r, b, R, d, xSrc, ySrc, zSrc, rSrc, xDet, yDet, rDet;
	double phiSrc, theta, phi, pi = 3.141592654, D, gammaEff;

	/***************************************************
	 * Data input
	 ***************************************************/
	printf("\n Radius of the radiating source in mm: ");
	scanf("%lf", &r);
	printf("\n Thickness of the radiating source in mm: ");
	scanf("%lf", &b);
	printf("\n Detector radius in mm: ");
	scanf("%lf", &R);
	printf("\n Distance between the detector and the source in mm: ");
	scanf("%lf", &d);
	printf("\n Number of photons to simulate: ");
	scanf("%ld", &N);
	
	for(i = 0; i<N; i++) {

		/***************************************************
	 	 * Photon coordinates at source
		 * The origin is in the detector
		 ***************************************************/
        zSrc   = ( (double)rand()/RAND_MAX ) * b + d;
        rSrc   = ( (double)rand()/RAND_MAX ) * r;
        phiSrc = ( (double)rand()/RAND_MAX ) * 360 * pi/180.0;
        xSrc   = rSrc * cos(phiSrc);
		ySrc   = rSrc * sin(phiSrc);

		/***************************************************
	 	 * Photon exit direction (theta, phi)
		 ***************************************************/
		theta = ( (double)rand()/RAND_MAX ) *  90 * pi/180.0;
		phi   = ( (double)rand()/RAND_MAX ) * 360 * pi/180.0;

		/***************************************************
	 	 * Photon coordinates at detector
		 * D is the module of the vector projected in the detector
		 ***************************************************/
		D    = zSrc * tan(theta);
		xDet = xSrc + D * cos(phi);
		yDet = ySrc + D * sin(phi);
		rDet = sqrt( xDet*xDet + yDet*yDet );

		if (rDet < R)
			Nin++;
	}

	gammaEff = (double)Nin / N;
	printf("\n From %ld photons, %d arrived.", N, Nin);
	printf("\n The geometric efficiency is %3.3f\n\n", gammaEff);
	getchar();
	return 0;
}
