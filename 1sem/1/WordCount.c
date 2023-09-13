#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    int     word_count = 0, line_count = 0, bite_count = 0;
    char    symbol;
    char    kom[7];
    char    file_name[150];
    if(argc == 3)
    {
        strcpy(kom, argv[1]);
        strcpy(file_name, argv[2]);
    }
    else
    {
        printf("Invalid number of arguments");
        return -1;
    }
    FILE *file;
    file = fopen(file_name, "r");
    if(file_name == NULL)
    {
        printf("File not found");
        return -1;
    }
    if(strcmp(kom, "-l") == 0 || strcmp(kom, "--lines") == 0)
    {
        if(fgetc(file) == EOF)
        {
            printf("%d", 0);
            return 0;
        }
        char pr;
        while((symbol = fgetc(file)) != EOF)
        {
            pr = symbol;
            if(symbol == '\n')
                line_count++;
        }
        if(pr == '\n')
            line_count--;
        printf("%d", line_count + 1);
    }
    if(strcmp(kom, "-w") == 0 || strcmp(kom, "--words") == 0)
    {
        int flag = 0;
        while((symbol = fgetc(file)) != EOF)
        {
            if(symbol == ' ' || symbol == '\n' || symbol == '\t')
                flag = 0;
            else
            {
                if(flag == 0)
                {
                    flag = 1;
                    word_count++;
                }
            }
        }
        printf("%d", word_count);
    }
    if(strcmp(kom, "-c") == 0 || strcmp(kom, "--bytes") == 0)
    {
        while((symbol = fgetc(file)) != EOF)
        {
            if(symbol == '\n')
                bite_count += 2;
            else
                bite_count++;
        }
        printf("%d", bite_count);
    }
    fclose(file_name);
    return 0;
}
