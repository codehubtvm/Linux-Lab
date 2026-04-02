#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) 
{
    if (argc != 4)
    {
        printf("Usage: %s <VAS_MB> <PageSize_KB> <VirtualAddress>\n", argv[0]);
        return 1;
    }
    double vspace_mb = atof(argv[1]);
    double page_kb = atof(argv[2]);
    unsigned long long virtual_address = strtoull(argv[3], NULL, 10);
    unsigned long long page_size_bytes = (unsigned long long)(page_kb * 1024);
    unsigned long long vspace_bytes = (unsigned long long)(vspace_mb * 1024 * 1024);
    unsigned int total_pages = (unsigned int)(vspace_bytes / page_size_bytes);
    int *page_table = (int *)malloc(total_pages * sizeof(int));
    for (unsigned int i = 0; i < total_pages; i++)
    {
        page_table[i] = -1; 
    }

    int entries_to_fill = (total_pages < 10) ? total_pages : 10;
    printf("--- Initializing Page Table (First %d entries) ---\n", entries_to_fill);
    for (int i = 0; i < entries_to_fill; i++)
    {
        printf("Enter Frame Number for Page %d: ", i);
        scanf("%d", &page_table[i]);
    }
    if (virtual_address >= vspace_bytes)
    {
        printf("\nError: Virtual Address %llu is out of bounds (Max: %llu).\n", virtual_address, vspace_bytes - 1);
        free(page_table);
        return 1;
    }
    unsigned int vpn = (unsigned int)(virtual_address / page_size_bytes);
    unsigned int offset = (unsigned int)(virtual_address % page_size_bytes);
    printf("\n--- Translation Result ---\n");
    if (vpn >= total_pages || page_table[vpn] == -1)
    {
        printf("Result: PAGE TABLE MISS!\n");
    }
   else 
    {
        int pfn = page_table[vpn];
        unsigned long long physical_address = ((unsigned long long)pfn * page_size_bytes) + offset;
        printf("Format:           <%d, %u>\n", pfn, offset);
        printf("Physical Address: %llu\n", physical_address);
        printf("Calculation:      (%d * %llu) + %u = %llu\n", pfn, page_size_bytes, offset, physical_address);
    }
    free(page_table);
    return 0;
}



OUTPUT
----------
SAMPLE RUN 1 (PAGE HIT)
labex:project/ $ gcc program.c -o paging
labex:project/ $ ./paging 4 4 10000  
labex:project/ $ ./paging 4 4 10000     
--- Initializing Page Table (First 10 entries) ---
Enter Frame Number for Page 0: 1
Enter Frame Number for Page 1: 2
Enter Frame Number for Page 2: 3
Enter Frame Number for Page 3: 4
Enter Frame Number for Page 4: 5
Enter Frame Number for Page 5: 6
Enter Frame Number for Page 6: 7
Enter Frame Number for Page 7: 8
Enter Frame Number for Page 8: 9
Enter Frame Number for Page 9: 10

--- Translation Result ---
Format:           <3, 1808>
Physical Address: 14096
Calculation:      (3 * 4096) + 1808 = 14096
🔷 SAMPLE RUN 2 (PAGE MISS)
labex:project/ $ ./paging 4 4 10000
--- Initializing Page Table (First 10 entries) ---
Enter Frame Number for Page 0: 1
Enter Frame Number for Page 1: 2
Enter Frame Number for Page 2: -1
Enter Frame Number for Page 3: 3
Enter Frame Number for Page 4: 4
Enter Frame Number for Page 5: 5
Enter Frame Number for Page 6: 6
Enter Frame Number for Page 7: 7
Enter Frame Number for Page 8: 8
Enter Frame Number for Page 9: 9

--- Translation Result ---
Result: PAGE TABLE MISS!
Explanation: The requested page is not currently in Physical Memory.


