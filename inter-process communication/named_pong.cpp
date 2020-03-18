// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h>  
#include <iostream>

int main() 
{ 
    int fd1; 
 
    char * myfifo = "/tmp/myfifo"; 
  
    mkfifo(myfifo, 0666); 
  
    char pong[] = "pong!"; 
    char buffer[10];
    int i = 5;

    while (i) 
    { 
        // First open in read only and read 
        fd1 = open(myfifo,O_RDONLY); 
        read(fd1, buffer, strlen(pong)+1); 
  
        // Print the read string and close 
        std::cout << buffer << std::endl;
        memset(buffer, 0 , strlen(pong)+1);
        close(fd1); 
        sleep(1);
        // Now open in write mode and write 
        fd1 = open(myfifo,O_WRONLY); 
        write(fd1, pong, strlen(pong)+1); 
        close(fd1); 
        --i;
    } 
    return 0; 
} 