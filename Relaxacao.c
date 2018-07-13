#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 200
#define E 1e-2

void contorno( double **M )
{	int i, j;

	for( i = 0; i < N; i++ )
	{	M[i][N-1] = 200;
		M[N-1][i] = 200;
	}
}

double u( double **M )
{	int i, j, mi, mj;
	double eps, a = 0;

	for( i = 1; i < N-1; i++ )
	{	for( j = 1; j < N-1; j++ )
		{	eps = M[i][j];
			M[i][j] = ( M[i-1][j] + M[i+1][j] + M[i][j-1] + M[i][j+1] )/ 4.;
			eps = fabs( eps - M[i][j] );
			if( eps > a )
				a = eps;
		}
	}
	return a;	
}

void imprime( double **M, int NL, int NC)
{
	int i, j;
	for(i = 0; i < NL; i++)
	{
		for( j = 0; j < NC; j++)
			printf("%.4lf\t ",M[i][j]);  
		puts("");
	}	
}

void main()
{	double	**M, erro;
	int  i, cont = 0;
 
	M = malloc( N* sizeof(double*));
	for( i = 0; i < N; i++ )
		M[i] = malloc( N* sizeof(double));
		
	contorno(M);
	do
	{	erro = u(M);
		cont++;
	}while( erro > E );
	imprime(M,N,N);
	//printf("%d\n",cont);
}
			

