#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[])
{
        FILE* fd=fopen("f.txt","w");
        int i,numere[11];
        for(i=1;i<=10;i++)
                numere[i]=i*10;
        fwrite(*numere,sizeof(int),10,fd);
        return 0;
}
