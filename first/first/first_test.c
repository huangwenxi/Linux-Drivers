#include<stdio.h>   
#include<stdlib.h>   
#include<fcntl.h>   
#include<sys/types.h>   
#include<sys/stat.h>   
  
int main()  
{  
    int fd;  
    int val = 1;  
    fd = open("/dev/first_drv_dev", O_RDWR);  
    printf("fd = %d\n", fd);  
    write(fd, &val, 4);  
    read(fd, &val, 4);  
    close(fd);  
    return 0;  
}  

