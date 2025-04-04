#include <stdio.h>
#include <stdlib.h>

//#define NULL (void*(0)) 

int main(int argc, char** argv)
{
    unsigned int n, m;
    int * * matrice;

    if( argc < 3 )
    {
	printf("Argumente invalide" );
	return 1;
    }

    char * file_path = argv[ 1 ];
    char * file_path2 = argv[ 2 ];
    FILE * fd,*fd2;

    fd = fopen( file_path, "r" );
    fd2 = fopen( file_path2, "w" );


    if( fd == NULL )
    {
        printf( "Failed to open file" );
	return 1;
    }
    if ( fd2 == NULL )
    {
	printf( "Failed to open file");
	return 1;
    } 

    fscanf( fd, "%u", &n );
    fscanf( fd, "%u", &m );

    fprintf(fd2, "n=%u, m=%u", n, m );
   
    matrice = (int * * )malloc( n * sizeof( int * ) );
    for( int i = 0; i < n; i++ )
    {
	matrice[ i ] = malloc( m * sizeof( int ) );
	
	for( int j = 0; j < m; j++ )
	{
	    fscanf( fd, "%d", &matrice[i][j] );
	}
    }
    fprintf(fd, "\n");
    for( int i = 0; i<n; i++ )
    {
	for( int j = 0; j < m; j++ )
	{
	    fprintf( fd2, "%d ", matrice[i][j] );
	}
	fprintf(fd2, "\n" );

	free( matrice[i] );
    }
    free( matrice );

    fclose( fd );
    fclose( fd2 );
    
    return 0;
}
