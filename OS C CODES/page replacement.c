#include <stdio.h>
#define MAX 100
int fifo(int ref[], int n, int frames)
{
   int frame[MAX];
   int pointer = 0;     
   int faults = 0;
   for(int i=0;i<frames;i++)
       frame[i] = -1;
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               break;
           }
       }
       if(!found)
       {
           frame[pointer] = page;
           pointer = (pointer + 1) % frames;
           faults++;
       }
   }
   return faults;
}


int lru(int ref[], int n, int frames)
{
   int frame[MAX];
   int recent[MAX];   
   int faults = 0;
   for(int i=0;i<frames;i++)
   {
       frame[i] = -1;
       recent[i] = -1;
   }
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               recent[j] = i;  
               break;
           }
       }
       if(!found)
       {
           int lruIndex = 0;
           for(int j=1;j<frames;j++)
           {
               if(recent[j] < recent[lruIndex])
                   lruIndex = j;
           }
           frame[lruIndex] = page;
           recent[lruIndex] = i;
           faults++;
       }
   }
   return faults;
}


int optimal(int ref[], int n, int frames)
{
   int frame[MAX];
   int faults = 0;
   for(int i=0;i<frames;i++)
       frame[i] = -1;
   for(int i=0;i<n;i++)
   {
       int page = ref[i];
       int found = 0;
       for(int j=0;j<frames;j++)
       {
           if(frame[j] == page)
           {
               found = 1;
               break;
           }
       }
       if(!found)
       {
           int replaceIndex = -1;
           int farthest = -1;
           for(int j=0;j<frames;j++)
           {
               int k;
               for(k=i+1;k<n;k++)
               {
                   if(frame[j] == ref[k])
                       break;
               }
               if(k == n)
               {
                   replaceIndex = j;
                   break;
               }
               if(k > farthest)
               {
                   farthest = k;
                   replaceIndex = j;
               }
           }
           frame[replaceIndex] = page;
           faults++;
       }
   }
   return faults;
}


int main()
{
   int ref[MAX];
   int n, frames;
   printf("Enter number of page references: ");
   scanf("%d",&n);
   printf("Enter the page reference string:\n");
   for(int i=0;i<n;i++)
       scanf("%d",&ref[i]);
   printf("Enter number of frames: ");
   scanf("%d",&frames);
   printf("\nPage Reference String: ");
   for(int i=0;i<n;i++)
       printf("%d ",ref[i]);
   printf("\nFrame Size = %d\n",frames);
   printf("\n--- Page Replacement Results ---\n");
   printf("FIFO Page Faults : %d\n", fifo(ref,n,frames));
   printf("LRU  Page Faults : %d\n", lru(ref,n,frames));
   printf("OPT  Page Faults : %d\n", optimal(ref,n,frames));
   return 0;
}


Output 1
----------
Enter number of page references: 20

Enter the page reference string:
1 9 3 6 4 1 9 0 7 3 1 8 6 9 3 4 0 2 8 9

Enter number of frames: 4
Output:
--- Page Replacement Results ---
FIFO Page Faults : 20
LRU  Page Faults : 20
OPT  Page Faults : 12

Output 2
----------
Enter number of page references: 11
Enter the page reference string:
0 1 2 0 1 3 0 3 1 2 1
Enter number of frames: 3

Page Reference String: 0 1 2 0 1 3 0 3 1 2 1 
Frame Size = 3

--- Page Replacement Results ---
FIFO Page Faults : 7
LRU  Page Faults : 5
OPT  Page Faults : 5

