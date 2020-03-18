/* "PING PONG" BETWEEN 2 PROCCESS, USING PIPE() */
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>//cout
#include <string.h>//memset
const int BALLPASSES = 5;

int main()
{ 
   /* pipefds[0] - read pipe file descriptor
      pipefds[1] - write pipe file descriptor */
    int ping_pipe[2];
    int pong_pipe[2];

    char message[2][6] = {"Ping!", "Pong!"};
    char read_buffer[10];

    if (-1 == pipe(ping_pipe) ||(-1 == pipe(pong_pipe)) )
    {
        printf("Error creating pipes\n");
        exit(-1);
    }

    pid_t child_pid = fork();

    if (child_pid == 0)
    {   //am child
        int passes = BALLPASSES;

        while(passes)
        {
            read(pong_pipe[0], read_buffer, 6);
            std::cout << read_buffer << std::endl;

            write(ping_pipe[1], message[0], 6);
            memset(read_buffer, 0, 6);
            --passes;
        }

    }
    else
    {   //am parent
        int passes = BALLPASSES;
        
        while(passes)
        {
            write(pong_pipe[1], message[1], 6);
            
            read(ping_pipe[0], read_buffer, 6);
            std::cout << read_buffer << std::endl;
            memset(read_buffer, 0, 6);
            --passes;
        }           
    }

    return 0;
}
