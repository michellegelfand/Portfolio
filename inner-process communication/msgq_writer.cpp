// C Program for Message Queue (Writer Process) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>
// structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100] = "woof woof"; 
} message; 
  
int main() 
{ 
    key_t key; 
    int msgid; 
  
    // ftok to generate unique key 
    key = ftok("progfile", 65); 

    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
    message.mesg_type = 1; 

    msgsnd(msgid, &message, sizeof(message), 0); 
    memcpy(message.mesg_text, "now write dis", 20);
    msgsnd(msgid, &message, sizeof(message), 0); 
    message.mesg_type = 3;
    memcpy(message.mesg_text, "aminadav", 20);
    msgsnd(msgid, &message, sizeof(message), 0); 

    return 0; 
}