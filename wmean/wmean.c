/***************************************************
 * Calculates the weighted mean.
 * 
 *  - Using:	   Numerical Recipes
 *  - Compiling:   gcc gauss.c -o gauss -lm
 *  - Running:	 ./gauss
 ***************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "nrutil.h"
#include "nrutil.c"

/***************************************************
 * COUNT THE NUMBER OF LINES IN THE DATA FILE 
 * (Needed for NR vector/matrix declarations)
 ***************************************************/
int numOfLines(char *filename) {
	FILE *fp;
	int n = 0;
	char line[10];
	
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
	double *x, *y, num = 0, den = 0, sum = 0, average, typDev, stdDev;
	int i, N;
	int numOfLines(char *filename);
	void readData(int n, double *x, double *y, char *filename);	
		
	char name[10];
	FILE *fp;
	if ((fp=fopen("output2.txt", "w")) == NULL) {
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
	getchar();
			  
	/***************************************************
	 * NR vector and matrix declaration
	 ***************************************************/
	x = dvector(1,N);
	y = dvector(1,N);
			 
	/***************************************************
	 * Filling in vectors and matrixes
	 ***************************************************/
	readData(N, x, y, name);
	for(i=1; i<=N; i++) {
		printf(     "\n Data[%d] = %3.3lf	Error[%d] = %3.3lf", i, x[i], i, y[i]);
		fprintf(fp, "\n Data[%d] = %3.3lf	Error[%d] = %3.3lf", i, x[i], i, y[i]);
	}

	/***************************************************
	 * Weighted mean calculation
	 ***************************************************/
	for (i=1; i<=N; i++) {
		num += x[i] / ( y[i]*y[i] );
		den += 1 / ( y[i]*y[i] );
	}
	average = num / den;
	typDev = 1 / sqrt(den);
	
	for (i=1; i<=N; i++)
		sum += pow(x[i] - average, 2);
	stdDev = sqrt(sum) / ( (double)(N-1) );
	
	printf(     "\n\nWeighted Average = %3.3lf", average);
	fprintf(fp, "\n\nWeighted Average = %3.3lf", average);
	printf(     "\nTyp Deviation      = %3.3lf", typDev);
	fprintf(fp, "\nTyp Deviation      = %3.3lf", typDev);
	printf(     "\nStandard Deviation = %3.3lf\n\n", stdDev);
	fprintf(fp, "\nStandard Deviation = %3.3lf\n\n", stdDev);
	
	free_dvector(y,1,N);
	free_dvector(x,1,N);
	return 0;
}
