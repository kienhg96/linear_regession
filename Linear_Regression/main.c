#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "./Lib/determination.h"

#define N 100
int main(void){
	FILE * f;
	double a, b, x_avg = 0, y_avg = 0, xy_avg = 0, x2_avg = 0;
	double x, y, y_, e = 0;
	int i;

	printf("y = a + bx\n");
	printf("Reading data from learning_data.txt ... ");
	f = fopen("learning_data.txt", "r");
	if (!f) {
		printf("Cannot read test_data.txt");
		return -1;
	}
	for (i = 0; i < N; i++){
		fscanf(f, "%lf%lf", &x, &y);
		x_avg += x;
		y_avg += y;
		xy_avg += x * y;
		x2_avg += x * x;
	}
	fclose(f);
	printf("OK\n");

	x_avg /= N;
	y_avg /= N;
	xy_avg /= N;
	x2_avg /= N;

	b = (xy_avg - x_avg * y_avg) / (x2_avg - x_avg * x_avg);
	a = y_avg - b * x_avg;

	printf("a = %.17f\n", a);
	printf("b = %.17f\n", b);

	printf("\nReading data from test_data.txt and testing ... \n");
	f = fopen("test_data.txt", "r");
	if (!f) {
		printf("Cannot read test_data.txt");
		return -1;
	}
	printf("         x           |     y - guess        |     y - from data    |        Delta\n");
	for (i = 0; i < N; i++){
		fscanf(f, "%lf%lf", &x, &y);
		y_ = a + b * x;
		printf("%.18f | %.18f | %.18f | %.18f\n", x, y_, y, fabs(y - y_));
		e += (y - y_) * (y - y_);
	}
	printf("Erms = %.17f", sqrt(e / N));
	return 0;
}