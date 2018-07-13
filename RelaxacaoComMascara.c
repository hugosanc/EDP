#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 200
#define E 1e-3

void contorno( double **M )
{	int i, j;

	for( i = 0; i < N; i++ )
		M[N-1][i] = 100;
		
	
}

double u( double **M, double **Maux )
{	int i, j;
	double eps, a = 0;

	for( i = 1; i < N-1; i++ )
	{	for( j = 1; j < N; j++ )
		{	if( Maux[i][j] == 0 )
			{	eps = M[i][j];
				M[i][j] = ( M[i-1][j] + M[i+1][j] + M[i][j-1] + M[i][j+1] )/ 4.;
				eps = fabs( eps - M[i][j] );
				if( eps > a )
					a = eps;
			}
		}
	}
	for( i = 1; i < N-1; i++ )
	{	M[i][0] = M[i][N-1];
		M[i][N] = M[i][1];
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
{	double	**M, **Maux, erro;
	int  i, cont = 0;
 
	Maux = malloc( N* sizeof(double*));
	for( i = 0; i < N; i++ )
		Maux[i] = malloc( N* sizeof(double));
		
	M = malloc( N* sizeof(double*));
	for( i = 0; i < N; i++ )
		M[i] = malloc( N* sizeof(double));
		
	contorno(M);
	for( i = 0; i < (N-1)/2; i++ )
		Maux[i][N/2] = 1;
		
	//imprime(M,N,N);
	do
	{	erro = u(M, Maux);
		cont++;
	}while( erro > E );
	imprime(M,N,N);
	//printf("%d\n",cont);
}
			

