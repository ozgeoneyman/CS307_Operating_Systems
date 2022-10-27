//
//  OZGE ONEYMAN 24906
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    char file_name[25] = "loremipsum.txt";
    char chr;
    int count=0;
    FILE *fp;
    fp = fopen(file_name, "r");
    
    while ((chr=fgetc(fp)) != EOF)
    {
        if (chr== 'a')
        {
            count++;
        }
    }
    printf("Number of occurence of character 'a' in the file: %d \n ",count);
    
    fclose(fp);
    
    return 0;
}

