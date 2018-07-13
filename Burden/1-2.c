#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define Nx 4
#define Ny 4
#define h 1./3.
#define E 1e-10

void contorno( double **M )
{	int i, j;
	double x = 1, xmax = 2, y = 0, ymax = 1;

	for( i = 0; i < Nx; i++ )
	{	M[i][0] = 2* log(x);	
		M[i][Ny-1] = log( pow( x, 2) + 1);
		x += h;
	}

	for( i = 0; i < Ny; i++ )
	{	M[0][i] = log( pow( y, 2) + 1);	
		M[Nx-1][i] = log( pow( y, 2) + 4);
		y += h;
	}
}

double f()
{	return 0;
}

double u( double **M, double **Maux )
{	int i, j;
	double eps, a = 0;

	for( i = 1; i < Nx-1; i++ )
	{	for( j = 1; j < Ny; j++ )
		{	if( Maux[i][j] == 0 )
			{	eps = M[i][j];
				M[i][j] = ( M[i-1][j] + M[i+1][j] + M[i][j-1] + M[i][j+1] -pow( h, 2)* f())/ 4.;
				eps = fabs( eps - M[i][j] );
				if( eps > a )
					a = eps;
			}
		}
	}
	return a;	
}

void imprime( double **M, int NL, int NC)
{	int i, j;

	//printf("Matriz calculada\n");	
	for(i = 0; i < NL; i++)
	{
		for( j = 0; j < NC; j++)
			printf("%.4lf\t ",M[i][j]);  
		puts("");
	}	
}

void solucao()
{	int i, j;
	double x = 1, xmax = 2, y, ymax = 2;

	printf("\nMatriz exata\n");
	for(i = 0; i < Nx; i++)
	{	y = 0;
		for( j = 0; j < Ny; j++)
		{	printf("%.4lf\t", log( pow( x, 2) + pow( y, 2)));
			y += h;
		}
		x += h;  
		puts("");
	}
}

void main()
{	double	**M, **Maux, erro;
	int  i, j, cont = 0;
 
	Maux = malloc( Nx* sizeof(double*));
	for( i = 0; i < Ny; i++ )
		Maux[i] = malloc( Ny* sizeof(double));
		
	M = malloc( Nx* sizeof(double*));
	for( i = 0; i < Ny; i++ )
		M[i] = malloc( Ny* sizeof(double));
		
	contorno(M);
	//mascara
	for( i = 0; i < Nx; i++ )
	{	Maux[i][0] = 1;	
		Maux[i][Ny-1] = 1;
	}
	for( i = 0; i < Ny; i++ )
	{	Maux[0][i] = 1;	
		Maux[Nx-1][i] = 1;
	}	
		
	//imprime(M,Nx,Ny);
	do
	{	erro = u(M, Maux);
		cont++;
	}while( erro > E );
	imprime(M,Nx,Ny);
	//solucao();
	//printf("%d\n",cont);
}
			

