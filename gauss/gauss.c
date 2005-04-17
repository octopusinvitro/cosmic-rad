/***************************************************
 * Solves a system of equations by the method of 
 * Gauss-Jordan.
 * 
 *  - Using:       Numerical Recipes (gaussj.c)
 *  - Application: To obtain the coefficients in
 * the method of least squares.
 *  - Compiling:   gcc gauss.c -o gauss -lm
 *  - Running:     ./gauss
 ***************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "nrutil.c"
#include "gaussj.c"

/***************************************************
 * COUNT THE NUMBER OF LINES IN THE DATA FILE 
 * (Needed for NR vector/matrix declarations)
 ***************************************************/
int numOfLines(char *filename) {
	FILE *fp;
	int n = 0;
	char line[100];
	
	if ( (fp = fopen(filename, "r")) == NULL ) {
		printf("\nError opening file\n");
		exit(1);
	}
	
	do {
		fgets(line, 100, fp);
		if ( strlen(line) > 2 )
			n++;
	} while(!feof(fp));
	
	fclose(fp);
	return n;
}

/***************************************************
 * READ DATA FILE
 * (Format: two columns of data separated by a space)
 ***************************************************/
void readData(int n, double *x, double *y, char *filename) {
	FILE *fp;

	if ( (fp=fopen(filename, "r")) == NULL ) {
		printf("\nError opening file\n");
		exit(1);
	}

	else {
		int i;
		for (i=1; i<=n; i++) {
			fscanf(fp, "%lf %lf", &x[i], &y[i]);
		}
	}
	
	fclose(fp);
}

/***************************************************
 *   MAIN 
 ***************************************************/
int main(void) {
	int i, j, k, N, n;
	double *x, *y, *A, *b, **a, **B, sumi, sumj, sumk;
	int numOfLines(char *filename);
	void readData(int n, double *x, double *y, char *filename);	
	void gaussj(double **a, int n, double **b, int m);
	
	char name[10];
	FILE *fp;
	if ((fp=fopen("output.txt", "w")) == NULL) {
		printf("\nError opening file\n");
		exit(1);
	}
		
	/***************************************************
	 * Data input
	 ***************************************************/
	printf("\nName of data file: ");
	scanf("%s", name);
	N = numOfLines(name);
	printf("N = %d\n", N);
		
	printf(     "\nNumber of parameters of the funcion: ");
	scanf("%d", &n);
	fprintf(fp, "\nNumber of parameters of the funcion: %d\n", n);
	getchar();
			  
	/***************************************************
	 * NR vector and matrix declaration
	 ***************************************************/
	x = dvector(1,N);
	y = dvector(1,N);

	A = dvector(1,n);
	b = dvector(1,n);

	a = dmatrix(1,n,1,n);
	B = dmatrix(1,n,1,n);
		 
	/***************************************************
	 * Filling in vectors and matrices
	 ***************************************************/
	readData(N, x, y, name);
	printf(     "\n\nVectors x and y:\n");
	fprintf(fp, "\n\nVectors x and y:\n");
	for(i=1; i<=N; i++) {
		printf(     "\n x[%d] = %3.3lf    y[%d] = %3.3lf", i, x[i], i, y[i]);
		fprintf(fp, "\n x[%d] = %3.3lf    y[%d] = %3.3lf", i, x[i], i, y[i]);
	}
	getchar();
		
	/***************************************************/
	printf(    "\n\nMatrix a before inversion:\n\n");
	fprintf(fp,"\n\nMatrix a before inversion:\n\n");
	for (i=1; i<=n; i++) {	   
		for (j=1; j<=n; j++) {
			sumk = 0.0;
			for (k=1; k<=N; k++)
				sumk += pow(x[k], i+j-2);			
			a[i][j] = sumk;
			printf(     " %10.3lf", a[i][j]);
			fprintf(fp, " %10.3lf", a[i][j]);
		}
		printf(     "\n");
		fprintf(fp, "\n");
	}
			
	/***************************************************/
	printf(    "\nVector b:\n\n");
	fprintf(fp,"\nVector b:\n\n");
	for (j=1; j<=n; j++) {
		sumj = 0.0;
		for (i=1; i<=N; i++)
			sumj += y[i]*pow(x[i], j-1);
		b[j] = sumj;
		printf(     " %10.3lf", b[j]);
		fprintf(fp, " %10.3lf", b[j]);
	}
	
	/***************************************************/
	gaussj(a,n,B,n);
	printf(     "\n\nMatrix a after inversion:\n\n");
	fprintf(fp, "\n\nMatrix a after inversion:\n\n");
	for (i=1; i<=n; i++) {
		for (j=1; j<=n; j++) {
			printf(     " %10.3lf", a[i][j]);
			fprintf(fp, " %10.3lf", a[i][j]);
		}
		printf(    "\n");
		fprintf(fp,"\n");
	}
	
	/***************************************************/
	printf(     "\nVector solution: A = B*b, (B = a inverted):\n\n");
	fprintf(fp, "\nVector solution: A = B*b, (B = a inverted):\n\n");
	for (i=1; i<=n; i++) {
		for (j=1; j<=n; j++)  
			A[i] += a[i][j]*b[j];
		printf(     " %10.3e", A[i]);
		fprintf(fp, " %10.3e", A[i]);
	}
	getchar();

	/***************************************************
	 * Corrected values
	 ***************************************************/
	double *yc, s, *S, *xj, yj, *Sjy2, Sy2, R2;
	yc   = dvector(1,N);
	S    = dvector(1,n);
	xj   = dvector(1,n);
	Sjy2 = dvector(1,n);
		
	printf(     "\n\nCorrected y values:\n");
	fprintf(fp, "\n\nCorrected y values:\n");
	for (i=1; i<=N; i++) {
		sumj = 0.0;
		for(j=1; j<=n; j++)
			sumj += A[j]*pow(x[i], j-1);
		yc[i] = sumj;
		printf(     "\n X[%d] = %3.3lf    Ycorr[%d] = %3.3lf", i, x[i], i, yc[i]);
		fprintf(fp, "\n X[%d] = %3.3lf    Ycorr[%d] = %3.3lf", i, x[i], i, yc[i]);
	}
	getchar();

	/***************************************************
	 * Standard deviation
	 ***************************************************/
	sumi    = 0.0;
	for (i=1; i<=N; i++) 
		sumi += pow(y[i] - yc[i], 2);
	s = sqrt( sumi / ((double)(N-n)) );
	printf(     "\n\nStandard deviation of the fit: \n s = %3.3e", s);
	fprintf(fp, "\n\nStandard deviation of the fit: \n s = %3.3e", s);
	getchar();
	
	/***************************************************
	 * Error calculation
	 ***************************************************/
	printf(     "\n\nUncertainty:\n\n");
	fprintf(fp, "\n\nUncertainty:\n\n");
	for(i=1; i<=n; i++) {
		S[i] = s*sqrt(a[i][i]);
		printf(     " S[A%d] = %3.3e\n", i, S[i]);
		fprintf(fp, " S[A%d] = %3.3e\n", i, S[i]);
	}
	getchar(); 
	
	/***************************************************
	 * Regression coefficient
	 ***************************************************/
	for (j=1; j<=n; j++) {
		sumi = 0.0;
		for (i=1; i<=N; i++) 
			sumi += pow(x[i], j-1);
		xj[j] = sumi / (double)N;
		printf(     "\n Average of x to the power of %d = %3.3lf", j-1, xj[j]);
		fprintf(fp, "\n Average of x to the power of %d = %3.3lf", j-1, xj[j]);
	}
	
	sumi = 0.0;
	for (i=1; i<=N; i++)
		sumi += y[i];
	yj = sumi / (double)N;
	printf(     "\n\n Average of experimental y = %3.3lf\n", yj);
	fprintf(fp, "\n\n Average of experimental y = %3.3lf\n", yj);
	
	for (j=1; j<=n; j++) {
		sumi = 0.0;
		for (i=1; i<=N; i++)
			sumi += (pow(x[i], j-1) - xj[j])*(y[i] - yj);
		Sjy2[j] = sumi / ( (double)(N-1) );
		printf(     "\n Dispersion of x%dy: S[x,y]2 = %3.3lf", j-1, Sjy2[j]);
		fprintf(fp, "\n Dispersion of x%dy: S[x,y]2 = %3.3lf", j-1, Sjy2[j]);
	}
	
	sumi = 0.0;
	for (i=1; i<=N; i++) 
		sumi += pow(y[i] - yj, 2);
	Sy2 = sumi / ( (double)(N-1) );
	printf(     "\n\n Dispersion of experimental y: S[y]2 = %3.3lf\n", Sy2);
	fprintf(fp, "\n\n Dispersion of experimental y: S[y]2 = %3.3lf\n", Sy2);

	R2 = 0.0;
	for (j=1; j<=n; j++) 
		R2 += A[j]*Sjy2[j] / Sy2;
	printf(     "\n Regression coefficient: R2 = %lf\n", R2);
	fprintf(fp, "\n Regression coefficient: R2 = %lf\n", R2);
	getchar();

	/***************************************************
	 * Free memory
	 ***************************************************/
	free_dvector(Sjy2,1,n);
	free_dvector(xj,1,n);
	free_dvector(S,1,n);
	free_dvector(yc,1,N); 
	free_dmatrix(B,1,n,1,n);
	free_dmatrix(a,1,n,1,n);
	free_dvector(b,1,n);
	free_dvector(A,1,n);
	free_dvector(y,1,N);
	free_dvector(x,1,N);
	
	printf("\n\n***************************************************");
	printf("\n\n               END OF CALCULATIONS");
	printf("\n\n***************************************************\n\n");
	return 0;
}
