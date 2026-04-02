#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
   pid_t pid;
   pid=fork();
   if(pid<0)
   {
      printf("Fork failed!\n");
   }
   else if(pid==0)
   {
      printf("PCCSL407");
   }
   else
   {
      wait(NULL);
      printf("Operating System Lab\n");
   }
   return 0;
}



How to Compile and Run:
-----------------------------
gcc os_fork_wait.c -o os_fork_wait
./os_fork_wait
Expected Output:
--------------------
PCCSL407 Operating Systems Lab


