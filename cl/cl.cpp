/***************************************************
 * Computation of the confidence level from Chi-squared (chi2)
 * and number of constraints (ncons).
 * 
 * Note :	
 * for even ncons ==> same result as the Cernlib function PROB
 * for odd	ncons ==> confidence level < result of the Cernlib function PROB
 * 
 * --- Original FORTRAN routine copied from Lau Gatignon 1980
 * --- Modified by NvE 29-sep-1980 K.U. Nijmegen
 * --- Modified by NvE 24-apr-1985 NIKHEF-H Amsterdam
 * --- Converted to C++ by Nve 06-nov-1998 UU-SAP Utrecht
 *
 *  - Compiling:   g++ cl.cpp -o cl
 *  - Running:     ./cl
 ***************************************************/

#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

double conlev(double chi2, int ncons) {
	const double a1 = 0.705230784e-1, a2 = 0.422820123e-1,
                 a3 = 0.92705272e-2,  a4 = 0.1520143e-3,
                 a5 = 0.2765672e-3,   a6 = 0.430638e-4;

	// Change to dummy variables
	int n     = ncons;
	double y0 = chi2;

	// Set CL to zero in case ncons <= 0
	if (n <= 0)
		return 0;

	if (y0 <= 0.) {
		if (y0 < 0.) 
			return 0;
		else 
			return 1;
	}

	if (n > 100) {
		double x     = sqrt(2.*y0) - sqrt(double(n + n - 1));
		double t     = fabs(x) / 1.1412135;
		double denom = 1.0 + t*(a1 + t*(a2 + t*(a3 + t*(a4 + t*(a5 + t*a6)))));
		double vfun  = 1.0 / denom;

		// Prevent underflow
		if (fabs(vfun) < 1.3e-5)
			vfun = 0.; 

		vfun     = pow(vfun, 16);
		double v = 0.5*vfun;

		if (x < 0.)
			v = 1.-v;

		if (v < 0.)
			v = 0.;

		return v;
	}

	else {
		double y1 = 0.5*y0;
		int m     = n / 2;

		if (2*m == n) {
		 double sum=1.;

		if (m > 1) {
			double term=1.;
			
			for (int i=2; i<=m; i++) {
				// Prevent overflow
				if (term > 1.e20)
					break;
 
				 double fi = double(i-1);
				 term      = term * y1 / fi;
				 sum      += term;
			}
		}

		double rnick = y1;

		// Prevent underflow
		if (rnick >= 1.75e2)
			rnick  = 1.75e2; 

		double v = sum*exp(-rnick);

		if (v < 0.)
			v = 0.;

			return v;
		}

		else {
			double x     = sqrt(y0);
			double t     = fabs(x) / 1.1412135;
			double denom = 1.0 + t*(a1 + t*(a2 + t*(a3 + t*(a4 + t*(a5 + t*a6)))));
			double vfun  = 1.0 / denom;

			// Prevent underflow
			if (fabs(vfun) < 1.3e-5)
				vfun=0.; 

			vfun     = pow(vfun,16);
			double v = vfun;

			if (n < 1)
				return 0;

			if (n == 1) {
				if (v < 0.)
					v=0.;
				return v;
			}

			double value = v;
			double sum   = 1.; 

			if (n >= 4) {
				double term = 1.;
				int k       = m - 1;

				for (int j=1; j<=k; j++) {
					// Prevent overflow
					if (term > 1.e20)
						break;

					double fj = double(j);
					term      = term * y0 / (fj + fj + 1.);
					sum      += term;
				}
			}

			// Prevent underflow
			if (y1 > 1.75e2)
				y1 = 1.75e2; 

			double vi = sum * 0.797846 * sqrt(y0) * exp(-y1);
			v         = vi + value;

			if (v < 0.)
				v = 0.;
	
			return v;
		}
	}
}


int main() {
	cout << conlev(1,2) << endl;
}
