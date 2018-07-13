#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define L 200
#define E 1e-3

void contorno( double **M )
{	int i, j;

	for( i = 0; i < L; i++ )
		M[L-1][i] = 100;
		
	
}

double u( double **M, double **Maux )
{	int i, j;
	double eps, a = 0;

	for( i = 0; i < L*L; i += L )
	{	for( j = 1; j < L; j++ )
		{	if( Maux[i+j] == 0 )
			{	eps = M[i+j];
				M[i+j] = ( M[i-L+j] + M[i+L+j] + M[i+j-1] + M[i+j+1] )/ 4.;
				eps = fabs( eps - M[i+j] );
				if( eps > a )
					a = eps;
			}
		}
	}
	for( i = 1; i < L*L; i += L )
	{	M[i] = M[i][L-1];
		M[i][L] = M[i][1];
	} 
	
	return a;	
}

void imprime( double **M)
{
	int i, j;
	for( i = 0; i < L*L; i += L )
	{	for( j = 1; j < L; j++ )
			printf("%.4lf\t ",M[i][j]);  
		puts("");
	}	
}

void main()
{	double	M[L*L], Maux[L*L], erro;
	int  i, cont = 0;
 
	Maux = malloc( L* sizeof(double*));
	
	M = malloc( L* sizeof(double*));
		
	contorno(M);
	for( i = 0; i < (L*L)/2; i += L )
		Maux[i][L/2] = 1;
		
	//imprime(M,N,N);
	do
	{	erro = u(M, Maux);
		cont++;
	}while( erro > E );
	imprime(M,L,L);
	//printf("%d\n",cont);
}
			
