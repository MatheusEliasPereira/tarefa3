#include <stdio.h>
#include <stdlib.h>
#include<math.h>

void imprime(double **m, int dim)
{	int i, j;
	
	for(i=0;i<dim;i++)
	{	for(j=0;j<dim+1;j++)
			printf("%.0lf\t",m[i][j]);
	  
		puts("");
	}
	printf("\n------------------\n");
	
}

double **triang_sup(double **M, int dim)
{
 	int i, j, k;
 	double aux;
 	
 	for(k=0;k<dim;k++) // função que faz triangular superior
 	{	for(i=k+1;i<dim;i++)
 		{	aux = (M[i][k]/M[k][k]);
 
 			for(j=k;j<=dim;j++)
 				M[i][j] = M[i][j] - aux*M[k][j];
 		}
 		
 		printf("\nPasso %d\n", k+1);
 		imprime(M,dim);	
 	}
		
	return M;
}

double **ler(char *arquivo, int *tam)
{	double **R, a, l;
	int i, j, dim;
	FILE *p;
	
	fflush(stdin);
	
	if(!(p = fopen(arquivo, "r")))
		return NULL;
	
	i = fscanf(p,"%d",&dim);

	R = malloc(dim*sizeof(double));

	for(i=0;i<dim;i++)
		R[i] = (double *)malloc((dim+1)*sizeof(double*));
	
	for(i=0;i<dim;i++)
	{	for(j=0;j<dim+1;j++)
		{	l = fscanf(p,"%lf",&a);
			R[i][j] = a;
		}
	}	
	*tam = dim;
	
	fclose(p);
	
	return R;
}

void substituicao_r(double **M, double *raizes, int dim)
{	int i, j = dim;
	double b[dim], soma[dim], aux;
	
	for(i=dim-1;i>=0;i--)
	{	soma[i] = 0;
	
		for(j=i;j<=dim;j++)
			soma[i] = soma[i] + M[i][j-1]*raizes[j-1];
		
		aux = M[i][dim];
		b[i] = aux - soma[i];
		raizes[i] = b[i]/M[i][i];
	}
}

int main(int argc, char **argv)
{
	double **M, **T, **Modulo, *raizes;
	int i, j, a, dim;
	FILE *leitura;
    
  	leitura = fopen("matriz.dat", "r");
	i = fscanf(leitura,"%d",&dim);
	
	M = malloc(dim*sizeof(int *));
	raizes = (double*)malloc(dim*sizeof(double));
	
	*raizes = 0;
	
	for(i=0;i<dim;i++)
		M[i] = malloc((dim)*sizeof(int));
	
	fflush(stdin);
	
	M = ler(argv[1],&dim);
	imprime(M,dim);
	M = triang_sup(M,dim);
	printf("\nMatriz escalonada:\n");
	imprime(M,dim);
	substituicao_r(M, raizes, dim);	
	
	for(i=0;i<dim;i++)
		printf("\nX%d = %5.2lf\n", i, raizes[i]);
	
	return 0;
}
