#include <stdio.h>
#include <time.h>
int main()
 {
    time_t now;
    time(&now); 
    printf("Current system time: %s", ctime(&now)); 
    return 0;
}


Compile the program:
gcc -o time_print time_print.c
Run the program:
./time_print
Example output:
------------------
Current system time: Thu Nov 13 15:22:47 2025

























#include<stdio.h>
#include<time.h>
#include<unistd.h>
int main()
{
   time_t now;
   time(&now);
   printf("Current system time:%s",ctime(&now));
   printf("Sleeping for 60 seconds...\n");
   sleep(60);
   return 0;
}


Recompile it again:
gcc -o time_print time_print.c
./time_print &

Output:
---------
Current system time:Thu Mar 19 10:25:30 2026
Sleeping for 60 seconds...

Find the process ID (PID):
ps -ef | grep time_print
user   12345  1024  0 15:23 pts/0  00:00:00 ./time_print

Look inside /proc/[pid]/stat:
cat /proc/12345/stat
12345 (time_print) S 1024 12345 1024 0 -1 4194560 103 0 0 0 0 1 2 0 0 20 0 1 0 123456 123456 0 0 0 0 0 0 0 0 0 0 0 0

Extract and convert values:
awk '{print "utime (user): " $14, " | stime (kernel): " $15}' /proc/12345/stat
Example output:
utime (user): 3 | stime (kernel): 1

awk -v ticks=$(getconf CLK_TCK) '{print "User mode (s):", $14/ticks, " Kernel mode (s):", $15/ticks}' /proc/12345/stat
Example output:
User mode (s): 0.03  Kernel mode (s): 0.01


