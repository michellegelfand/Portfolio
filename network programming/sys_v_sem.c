/**********************************************************************;
* Project           : Data Structures
*
* Program name      : sys_v_sem.c
*
* Author            : Michelle Gelfand	
*************************************************************/
#define _POSIX_C_SOURCE 199309L

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>/*ftok*/
#include <stdio.h>/*perror*/
#include <stdlib.h>/*abort*/
#include <unistd.h> /* fork */
#include <signal.h>/*sigaction*/
#include <wait.h>/*wait*/

#define NUM_PROCS 3
#define FAILED(str) (-1 == str) 
#define FILE_NAME "out.txt"

typedef union sem_un 
{
    int val;
    struct semid_ds *semset;
    unsigned short int *array;
    struct seminfo *__buf;
}sem_un_t;

void Ex1Ex2();
void Ex3();
void Ex4();

void WriteToFile(int sem_set_id);
void Disappear(int sig);

int sem_id = 0;

int main()
{
   /*  Ex1Ex2() ;
    Ex3(); */
    Ex4();


    return 0;
}

void Ex4()
{
    int sem_set_id = 0;
    key_t key = ftok("avl.h", 'M');
    sem_un_t sem_un = {0};
    size_t i = 0;
    pid_t child = {0};

    struct sigaction disappear = {0};

    disappear.sa_handler = &Disappear;
    disappear.sa_flags = 0;

    sigaction(SIGABRT, &disappear, NULL);
    sigaction(SIGTERM, &disappear, NULL);
    sigaction(SIGINT, &disappear, NULL);

    if(-1 == key)
    {
        perror("\nftok failed\n");
        abort();
    }

    /*0600: wr*/
    sem_set_id = semget(key, 1, IPC_CREAT | 0600);
    sem_id = sem_set_id;

    if(FAILED(sem_set_id))
    {
        perror("\nsemget failed\n");
        abort();
    }

    sem_un.val = 1;

    if(FAILED(semctl(sem_set_id, 0, SETVAL, sem_un)))
    {
        perror("\nsemctl failed\n");
        abort();
    }

    for(i = 0; i < NUM_PROCS; i++)
    {
        child = fork();

        if(FAILED(child))
        {
            perror("fork failed");
            abort();
        }               
        else if(!child)
        {
            /*i am the child*/
            WriteToFileUndo(sem_set_id);
            exit(0);
        }
    }

    for(i = 0; i < NUM_PROCS; ++i)
    {
        wait(NULL);
    }

    while(1);

    semctl(sem_set_id, 0, IPC_RMID, sem_un);
}


void Ex3()
{
    int sem_set_id = 0;
    key_t key = ftok("avl.h", 'M');
    sem_un_t sem_un = {0};
    size_t i = 0;
    pid_t child = {0};

    struct sigaction disappear = {0};

    disappear.sa_handler = &Disappear;
    disappear.sa_flags = 0;

    sigaction(SIGABRT, &disappear, NULL);
    sigaction(SIGTERM, &disappear, NULL);
    sigaction(SIGINT, &disappear, NULL);

    if(-1 == key)
    {
        perror("\nftok failed\n");
        abort();
    }

    /*0600: wr*/
    sem_set_id = semget(key, 1, IPC_CREAT | 0600);
    sem_id = sem_set_id;

    if(FAILED(sem_set_id))
    {
        perror("\nsemget failed\n");
        abort();
    }

    sem_un.val = 1;

    if(FAILED(semctl(sem_set_id, 0, SETVAL, sem_un)))
    {
        perror("\nsemctl failed\n");
        abort();
    }

    for(i = 0; i < NUM_PROCS; i++)
    {
        child = fork();

        if(FAILED(child))
        {
            perror("fork failed");
            abort();
        }               
        else if(!child)
        {
            /*i am the child*/
            WriteToFile(sem_set_id);
            exit(0);
        }
    }

    for(i = 0; i < NUM_PROCS; ++i)
    {
        wait(NULL);
    }

    while(1);

    semctl(sem_set_id, 0, IPC_RMID, sem_un);
}


void Ex1Ex2()
{
    int sem_set_id = 0;
    key_t key = ftok("avl.h", 'M');
    sem_un_t sem_un = {0};
    size_t i = 0;
    pid_t child = {0};

    if(-1 == key)
    {
        perror("\nftok failed\n");
        abort();
    }

    /*0600: wr*/
    sem_set_id = semget(key, 1, IPC_CREAT | 0600);

    if(FAILED(sem_set_id))
    {
        perror("\nsemget failed\n");
        abort();
    }

    sem_un.val = 1;

    if(FAILED(semctl(sem_set_id, 0, SETVAL, sem_un)))
    {
        perror("\nsemctl failed\n");
        abort();
    }

    for(i = 0; i < NUM_PROCS; i++)
    {
        child = fork();

        if(FAILED(child))
        {
            perror("fork failed");
            abort();
        }               
        else if(!child)
        {
            /*i am the child*/
            WriteToFile(sem_set_id);
            exit(0);
        }
    }

    for(i = 0; i < NUM_PROCS; ++i)
    {
        wait(NULL);
    } 
}


void WriteToFile(int sem_set_id)
{
    struct sembuf sem_op;
    FILE* file;

    sem_op.sem_num = 0;

    /* -1 : wait*/
    sem_op.sem_op = -1;               
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);   
    
    file = fopen(FILE_NAME, "a");

    fprintf(file,"%d\n", (getpid()));
    fprintf(file,"%d\n\n", (getpid()));

    fclose(file);
    
    sem_op.sem_num = 0;

    /*1 : post*/
    sem_op.sem_op = 1;            
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

void WriteToFileUndo(int sem_set_id)
{
    struct sembuf sem_op;
    FILE* file;

    sem_op.sem_num = 0;

    /* -1 : wait*/
    sem_op.sem_op = -1;               
    sem_op.sem_flg = SEM_UNDO;
    semop(sem_set_id, &sem_op, 1);   
    
    file = fopen(FILE_NAME, "a");

    fprintf(file,"%d\n", (getpid()));
    fprintf(file,"%d\n\n", (getpid()));

    fclose(file);
    
    sem_op.sem_num = 0;

    /*1 : post*/
    sem_op.sem_op = 1;            
    sem_op.sem_flg = SEM_UNDO;
    semop(sem_set_id, &sem_op, 1);
}

void Disappear(int sig)
{
    sem_un_t args; 
    (void)sig;
    /*disappear semaphore!*/

    semctl(sem_id, 0, IPC_RMID, args);
    exit(0);
    /*omg where'd it go? :O */
}