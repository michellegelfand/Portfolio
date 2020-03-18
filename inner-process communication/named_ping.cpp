// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
#include <string.h> 

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
    int i = 5;
    while (i) 
    { 
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
  
        // Write the input  on FIFO 
        // and close it 
        write(fd, ping, strlen(ping)+1); 
        close(fd); 
        sleep(1);
        // Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY); 
  
        // Read from FIFO 
        read(fd, buffer, sizeof(ping)); 
  
        // Print the read message 
        std::cout << buffer << std::endl;
        memset(buffer, 0, sizeof(ping));
        close(fd);
        --i; 
    } 
    return 0; 
} 
