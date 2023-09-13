#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//char arc_name[50];

void list(char arc_name[50])
{
    FILE* arc;
    arc = fopen(arc_name, "rb");
    if (arc == NULL)
    {
        printf("Can't find archive\n");
        return -1;
    }
    char file_name[128];
    int file_size;
    printf("LIST:\n");
    int c = 0;
    int temp_count = 0;
    c = getc(arc);
    while ((c = getc(arc)) != EOF)
    {
        if (c == '\n')
            break;
        printf("%c", c);
        if (c == ' ')
            ++temp_count;
        if (temp_count == 3)
        {
            printf("\n");
            temp_count = 0;
        }
    }
    printf("DONE\n");
    fclose(arc);
}

void create(char arc_name[50], int count, char *files[])
{
    FILE* arc;
    arc = fopen(arc_name, "wb");
    if (arc == NULL)
    {
        printf("Can't find archive\n");
        return -1;
    }
    int size[128];
    fprintf(arc, " ");
    for (int i = 4; i < count; ++i)
    {
        FILE* temp;
        temp = fopen(files[i], "rb");
        fseek(temp, 0, SEEK_END);
        size[i - 4] = ftell(temp);
        fprintf(arc, "%s - %d ", files[i], size[i - 4]);
        fclose(temp);
    }
    fprintf(arc, "\n");
    int c;
    for (int i = 4; i < count; ++i)
    {
        FILE* temp;
        temp = fopen(files[i], "rb");
        while ((c = getc(temp)) != EOF)
            putc(c, arc);
        fprintf(arc, "\n");
        fclose(temp);
    }
    printf("DONE\n");
    fclose(arc);
}

void extract(char arc_name[50])
{
    FILE* arc;
    arc = fopen(arc_name, "rb");
    if (arc == NULL)
    {
        printf("Can't find archive\n");
        return -1;
    }
    int arc_size;
    fseek(arc, 0, SEEK_END);
    arc_size = ftell(arc);
    fseek(arc, 0, SEEK_SET);
    int c;
    int begin = 0;
    while ((c = getc(arc)) != '\n')
        ++begin;
    ++begin;

    fseek(arc, 0, SEEK_SET);
    FILE* temp;
    char file_name[50];
    int file_size;
    int temp_position = 0;
    c = getc(arc);
    arc_size--;
    while (ftell(arc) < arc_size)
    {
        fscanf(arc, "%s - %d", file_name, &file_size);
        if (file_size == 0)
        {
            break;
        }
        temp_position = ftell(arc);
        temp = fopen(file_name, "wb");
        fseek(arc, begin, SEEK_SET);
        begin += file_size;
        while (file_size > 0)
        {
            putc((c = getc(arc)), temp);
            file_size--;
        }
        fseek(arc, temp_position, SEEK_SET);
        begin += 1;
        fclose(temp);
    }
    printf("DONE\n");
}

int main(int argc, char* argv[])
{
    char arc_name[50];
    if (argc >= 4)
    {
        if (strcmp(argv[1], "--file") == 0)
            strcpy(arc_name, argv[2]);
        else
        {
            printf("Incorrect\n");
            return -1;
        }
        if (strcmp(argv[3], "--list") == 0)
        {
            list(arc_name);
            return 0;
        }
        if (strcmp(argv[3], "--extract") == 0)
        {
            extract(arc_name);
            return 0;
        }
        if (strcmp(argv[3], "--create") == 0 && argc >= 5)
        {
           create(arc_name, argc, argv);
           return 0;
        }
    }
}
