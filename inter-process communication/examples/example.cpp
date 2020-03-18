
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <iostream>

int main()
{
    int fd1[2];  // Used to store two ends of first pipe (via file descriptors)
    int fd2[2];  // Used to store two ends of second pipe (via file descriptors)
  
    char ping[] = "pipe2"; 
    char pong[] = "pong"; 
    pid_t p; 
    char buffer[80];

    if (pipe(fd1)==-1) //if successful 2 file descriptors stored in fd1
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 

    p = fork();
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 

    // Parent process 
    else if (p > 0) 
    {
        while(1)
        {
            close(fd1[0]); 
            write(fd1[1], ping, 5);
            close(fd1[1]); 
            read(fd2[0], buffer, 5);
            std::cout << buffer << std::endl;
            memset(buffer, 0, 80);    
        }
    }
    else if (p = 0) 
    {//child
        while(1)
        {
            write(fd1[0], pong, 5);
            read(fd2[1], buffer, 5);
            std::cout << buffer << std::endl;
            memset(buffer, 0, 80);    
        }
    }

}  