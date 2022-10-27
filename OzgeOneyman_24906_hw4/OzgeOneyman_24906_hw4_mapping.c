//
//  OZGE ONEYMAN 24906
//

#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open ("loremipsum.txt", O_RDONLY);
    int count=0;
    struct stat s;
    size_t size;
    int status = fstat(fd, &s);
    size=s.st_size;
    char *ptr = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    if (ptr== MAP_FAILED) {
        printf("Failed");
        return 1;
        
    }
    for (size_t i=0; i<=size; i++) {
        if (ptr[i] == 'a') {
            count++;        }
    }
    
    printf("Number of occurence of character 'a' in the file: %d \n",count);
    close(fd);
    
    status = munmap(ptr, size);
    return 0;
}
