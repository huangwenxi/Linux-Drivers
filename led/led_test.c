#include<stdio.h>   
#include<stdlib.h>   
#include<string.h>
#include<fcntl.h>   
#include<sys/types.h>   
#include<sys/stat.h>   
struct devfd_t {
	int fdleds;
	int fdled1;
	int fdled2;
	int fdled3;
};
char *devnamearray[4]= {"leds","led1","led2","led3"};
int  devfd[4]={-1,-1,-1,-1};
void printhelp(char**argv)
{
	printf("usage %s leds on|off\n",argv[0]);
	printf("usage %s led1 on|off\n",argv[0]);
	printf("usage %s led2 on|off\n",argv[0]);
	printf("usage %s led3 on|off\n",argv[0]);
}
int main(int argc, char **argv)
{
	int index = 0;
	int from = 1;
	char devname[12];
	if(argc!=3)
	{
		printhelp(argv);
		return 0;
	}
	for(index=0;index<4;index++)
	{
		printf("%d\n",__LINE__);
		if(!strcmp(devnamearray[index],argv[1]))
		{
			printf("%d\n",__LINE__);
			if(!strcmp("on",argv[2]))
			{
				printf("%d\n",__LINE__);
				if(devfd[index] == -1)
				{
					printf("%d\n",__LINE__);
					sprintf(devname,"/dev/%s",devnamearray[index]);
					printf("%d\n",__LINE__);
					devfd[index]= open(devname,O_RDWR);
					printf("%d\n",__LINE__);
				}
				from = 0;
				printf("%d\n",__LINE__);
				write(devfd[index],&from,1);
				printf("%d\n",__LINE__);
			}
			else if(!strcmp("off",argv[2]))
			{
				printf("%d\n",__LINE__);
				if(devfd[index] == -1)
				{
					sprintf(devname,"/dev/%s",devnamearray[index]);
					devfd[index]= open(devname,O_RDWR);
				}
				from = 1;
				printf("%d\n",__LINE__);
				write(devfd[index],&from,1);
			}
			memset(argv[0],0,strlen(argv[0]));
			memset(argv[1],0,strlen(argv[1]));
			memset(argv[2],0,strlen(argv[2]));
			argc = 0;
			break;
		}
	}
	return 0;
		
	
}

