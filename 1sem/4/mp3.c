#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int reverse(unsigned int byte)
{
    return(((byte >> 24) & 0x000000ff) | ((byte >> 8) & 0x0000ff00) | ((byte << 8) & 0x00ff0000)  | ((byte << 24) & 0xff000000));
}

int main(int argc, char* argv[])
{
    char value[100];
    char prop_name[4];
    char file_name[50];
    char command[20];
    if (argc >= 5)
    {
        strcpy(file_name, argv[3]);
        strcpy(command, argv[4]);
        if (argc >= 7)
        {
            strcpy(prop_name, argv[6]);
            if (argc == 10)
            {
                strcpy(value, argv[9]);
            }
        }
    }

    FILE *file;
    file = fopen(file_name, "rb");

    if (file == NULL)
    {
        printf("File not found\n");
        return -1;
    }

    char tag_head[6];
    fread(tag_head, 1, 6, file);

    unsigned int tag_size;
    fread(&tag_size, 1, 4, file);
    tag_size = reverse(tag_size) + 10;

    if (strcmp(command, "--show") == 0)
    {
        while (ftell(file) < tag_size)
        {
            int state = 0;
            char frame_head[4];
            fread(frame_head, 1, 4, file);
            for (int i = 0; i < 4; ++i)
            {
                if (i == 0 && frame_head[i] == 0)
                {
                    state = 1;
                    break;
                }
                printf("%c", frame_head[i]);
            }
            if (state == 1)
                break;
            printf("  - ");

            unsigned int frame_size;
            fread(&frame_size, 1, 4, file);
            frame_size = reverse(frame_size);

            fseek(file, 2, SEEK_CUR);

            char* frame_inf = malloc(sizeof(char) * frame_size);
            fread(frame_inf, 1, frame_size, file);
            for (int i = 0; i < (int)frame_size; ++i)
                printf("%c", frame_inf[i]);
            printf("\n");
            free(frame_inf);
        }
    }
    else if (strcmp(command, "--get") == 0)
    {
        int state;
        while (ftell(file) < tag_size)
        {
            state = 0;
            char frame_head[4];
            fread(frame_head, 1, 4, file);
            for (int i = 0; i < 4; ++i)
            {
                if (i == 0 && frame_head[i] == 0)
                {
                    state = 1;
                    break;
                }
                if (frame_head[i] != prop_name[i])
                {
                    state = 2;
                    break;
                }
            }

            if (state == 1)
            {
                printf("Frame not found\n");
                break;
            }

            if (state == 0)
                printf("%s - ", prop_name);

            unsigned int frame_size;
            fread(&frame_size, 1, 4, file);
            frame_size = reverse(frame_size);

            fseek(file, 2, SEEK_CUR);

            char* frame_inf = malloc(sizeof(char) * frame_size);
            fread(frame_inf, 1, frame_size, file);
            if (state == 0)
            {
                for (int i = 0; i < (int)frame_size; ++i)
                    printf("%c", frame_inf[i]);
                printf("\n");
                free(frame_inf);
                break;
            }
            free(frame_inf);
        }
    }
    else if (strcmp(command, "--set") == 0)
    {
        unsigned int old_position = 0;
        unsigned int old_size = 0;

        int state;
        while (ftell(file) < tag_size)
        {
            state = 0;
            char frame_head[4];
            fread(frame_head, 1, 4, file);
            for (int i = 0; i < 4; ++i)
            {
                if (i == 0 && frame_head[i] == 0)
                {
                    state = 1;
                    break;
                }
                if (frame_head[i] != prop_name[i])
                {
                    state = 2;
                    break;
                }
            }

            if (state == 1)
                break;
        
            if (state == 0)
                old_position = ftell(file);

            unsigned int frame_size;
            fread(&frame_size, 1, 4, file);
            frame_size = reverse(frame_size);
            if (state == 0)
                old_size = frame_size;

            char frame_tag[2];
            fread(frame_tag, 1, 2, file);
            char* frame_inf = malloc(sizeof(char) * frame_size);
            fread(frame_inf, 1, frame_size, file);
            free(frame_inf);
        }

        unsigned int new_size;
        if (old_position == 0)
            old_position = ftell(file) - 4;

        if (old_size == 0)
            new_size = tag_size + 10 + strlen(value);
        else
            new_size = tag_size - old_size + strlen(value);

        fclose(file);
        file = fopen(file_name, "rb");
        FILE *temp_file;
        temp_file = fopen("temp.mp3", "wb");

        fwrite(tag_head, 1, 6, temp_file);
        new_size = reverse(new_size);
        fwrite(&new_size, 1, 4, temp_file);

        char tag_head[6];
        fread(tag_head, 1, 6, file);
        unsigned int tag_size;
        fread(&tag_size, 1, 4, file);

        //printf("%u\n", old_position);

        while (ftell(file) < old_position)
            putc(getc(file), temp_file);

        if (old_size == 0)
            fwrite(prop_name, 1, 4, temp_file);

        unsigned int prop_size = strlen(value);
        prop_size = reverse(prop_size);
        fwrite(&prop_size, 1, 4, temp_file);
        prop_size = reverse(prop_size);

        unsigned int temp;
        fread(&temp, 1, 4, file);

        for (int i = 0; i < 2; ++i)
            putc(getc(file), temp_file);

        fwrite(value, 1, prop_size, temp_file);

        //printf("%u\n", ftell(file));
        //printf("%u\n", old_size);

        char* old_inf = malloc(sizeof(char) * old_size);
        fread(old_inf, 1, old_size, file);

        //printf("%s\n", old_inf);

        free(old_inf);

        unsigned int c;
        while ((c = getc(file)) !=  EOF)
            putc(c, temp_file);

        fclose(file);
        fclose(temp_file);

        file = fopen(file_name, "wb");
        temp_file = fopen("temp.mp3", "rb");
        while ((c = getc(temp_file)) !=  EOF)
            putc(c, file);

        fclose(file);
        fclose(temp_file);
    }
}
