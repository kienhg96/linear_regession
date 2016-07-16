#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 100
double det(int n, double ** mat);
void process(int M, double ** train, double ** test, int printDebug);
int main(void){
	int i;
	FILE * f;
	double ** train = (double **)malloc(N * sizeof(double *)); 
	double ** test = (double **)malloc(N * sizeof(double *)); // 2
	for (i = 0; i < N; i++){
		train[i] = (double *)malloc(2 * sizeof(double));
		test[i] = (double *)malloc(2 * sizeof(double));
	}

	// == Read data
	f = fopen("learning_data.txt", "r");
	printf("Reading learning_data.txt ... ");
	for (i = 0; i < N; i++){
		fscanf(f, "%lf%lf", &train[i][0], &train[i][1]);
	}
	fclose(f);
	printf("OK\n");
	f = fopen("test_data.txt", "r");
	printf("Reading test_data.txt ... ");
	for (i = 0; i < N; i++){
		fscanf(f, "%lf%lf", &test[i][0], &test[i][1]);
	}
	fclose(f);
	printf("OK\n");

	// Training with linear regression
	process(2, train, test, 1);

	// Training with other model
	printf("\nTraining with other model\n");
	for (i = 3; i < 9; i++){
		printf("Training with M = %d\n", i);
		process(i, train, test, 0);
		printf("=====\n");
	}

	printf("This program can only process M from 2 to 9");

	// == Free
	for (i = 0; i < N; i++){
		free(train[i]);
		free(test[i]);
	}
	free(test);
	free(train);
	getchar();
	return 0;
}

double det(int n, double ** mat)
{
	int c, subi, i, j, subj;
	double ** submat = (double **)malloc(n * sizeof(double));
	double d = 0;
	for (i = 0; i < n; i++){
		submat[i] = (double *)malloc(n * sizeof(double));
	}
	if (n == 2)
	{
		return((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	}
	else
	{
		for (c = 0; c < n; c++)
		{
			subi = 0;
			for (i = 1; i < n; i++)
			{
				subj = 0;
				for (j = 0; j < n; j++)
				{
					if (j == c)
					{
						continue;
					}
					submat[subi][subj] = mat[i][j];
					subj++;
				}
				subi++;
			}
			d = d + (pow(-1, c) * mat[0][c] * det(n - 1, submat));
		}
	}
	for (i = 0; i < n; i++){
		free(submat[i]);
	}
	free(submat);
	return d;
}

void process(int M, double ** train, double ** test, int printDebug){
	double * xy_avg = (double *)malloc(M * sizeof(double));
	double * x_avg = (double *)malloc((2 * M - 1) * sizeof(double));
	double * w = (double *)malloc(M * sizeof(double));
	double Erms = 0;
	int i, j, k;
	double x, y, y_;
	double ** Det = (double **)malloc(M * sizeof(double *)); // M
	double ** Det_ = (double **)malloc(M * sizeof(double *));
	double D;

	for (i = 0; i < M; i++){
		Det[i] = (double *)malloc(M * sizeof(double));
		Det_[i] = (double *)malloc(M * sizeof(double));
	}

	

	for (i = 0; i < M; i++){
		xy_avg[i] = 0;
	}
	for (i = 0; i < 2 * M - 1; i++){
		x_avg[i] = 0;
	}

	for (i = 0; i < N; i++){
		for (j = 0; j < 2 * M - 1; j++){
			x_avg[j] += pow(train[i][0], j);
		}
		for (j = 0; j < M; j++){
			xy_avg[j] += train[i][1] * pow(train[i][0], j);
		}
	}

	for (i = 0; i < M; i++){
		xy_avg[i] /= N;
	}
	for (i = 0; i < 2 * M - 1; i++){
		x_avg[i] /= N;
	}

	for (i = 0; i < M; i++){
		for (j = 0; j < M; j++){
			Det[i][j] = x_avg[i + j];
		}
	}
	D = det(M, Det);
	for (i = 0; i < M; i++){
		//memcpy(Det_, Det, sizeof(Det));
		// Copy Array
		for (j = 0; j < M; j++){
			for (k = 0; k < M; k++){
				Det_[j][k] = Det[j][k];
			}
		}

		for (j = 0; j < M; j++){
			Det_[j][i] = xy_avg[j];
		}
		w[i] = det(M, Det_);
	}

	for (i = 0; i < M; i++){
		w[i] /= D;
	}
	for (i = 0; i < M; i++){
		printf("w%d = %.17f\n", i, w[i]);
	}
	// Test

	if (printDebug){
		printf("         x           |     y - guess        |     y - from data    |        Delta\n");
	}
	for (i = 0; i < N; i++){
		x = test[i][0];
		y = test[i][1];
		y_ = 0;
		for (j = 0; j < M; j++){
			y_ += w[j] * pow(x, j);
		}
		if (printDebug){
			printf("%.18f | %.18f | %.18f | %.18f\n", x, y_, y, fabs(y - y_));
		}
		Erms += (y - y_) * (y - y_);
	}
	printf("Erms = %.17f\n", sqrt(Erms / N));

	free(xy_avg);
	free(x_avg);
	free(w);

	for (i = 0; i < M; i++){
		free(Det[i]);
		free(Det_[i]);
	}
	free(Det);
	free(Det_);
}