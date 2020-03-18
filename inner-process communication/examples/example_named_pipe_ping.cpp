// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
  
int main() 
{ 
    int fd; 
    char buffer[10];
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 
  
    char ping[] = "ping!";

    while (1) 
    { 
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
  
        // Write the input  on FIFO 
        // and close it 
        write(fd, ping, strlen(ping)+1); 
        close(fd); 
  
        // Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY); 
  
        // Read from FIFO 
        read(fd, buffer, sizeof(ping)); 
  
        // Print the read message 
        std::cout << buffer << std::endl;
        close(fd); 
    } 
    return 0; 
} 
