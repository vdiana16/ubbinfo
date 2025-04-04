    #include <stdio.h>

void elimina_vocala(int p, char *sir, char* vocale)
{
	int j=0;
	char *sir_ret = malloc();
	for(int i=;i<strlen(sir);i++)
	{
		if(sir[i] != vocale[p])
		{
			sir_nou[j]=sir[i];
			j++;
		}
	}
}

int main(int argc, char* argv[])
{
	char sir[] = "abcdefghijoukl";
	char vocal[] = "aeiou";
	int i = 0;
	while(i<strlen(vocale))
	{
		int pid = fork();
		if(pid == -1)
		{
			perror("fork() error; ");
			exit(EXIT_FAILURE);
		}
		if(pid == 0)
		{
			elimina_vocala(vocala[i]);
			exit(EXIT_SUCCES);
		}
		wait(NULL);
		i++;

	}
	return 0;
}

    
