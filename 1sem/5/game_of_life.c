#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int to_int(char s[50])
{
    int n = 0;
    for (int i = 0; i < (int)strlen(s); ++i)
    {
        n *= 10;
        n += (int)s[i] - 48;
    }
    return n;
}

void game(int** img, int height, int width)
{
    int temp_bytes[height][width];
    int neighbours = 0;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            temp_bytes[i][j] = img[i][j];

    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            neighbours = img[i][j + 1] + img[i][j - 1] + img[i - 1][j] + img[i + 1][j];
            neighbours += img[i + 1][j - 1] + img[i + 1][j + 1];
            neighbours += img[i - 1][j - 1] + img[i - 1][j + 1];
            if (temp_bytes[i][j] == 1)
            {
                if (neighbours > 3 || neighbours < 2) 
                    temp_bytes[i][j] = 0;
                else
                    temp_bytes[i][j] = img[i][j];
            }
            else
            {
                if (neighbours == 3)
                    temp_bytes[i][j] = 1;
            }
            neighbours = 0;
        }
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
            img[i][j] = temp_bytes[i][j];
    }
}

int main(int argc, char* argv[])
{
    char file_name[50];
    char dir_name[50];
    char iter[50];
    char freq[50];
    int max_iter = 10000;
    int dump_freq = 1;
    if (argc >= 5)
    {
        strcpy(file_name, argv[2]);
        strcpy(dir_name, argv[4]);
        if (argc == 7)
        {
            if (strcmp(argv[5], "--max_iter") == 0)
            {
                strcpy(iter, argv[6]);
                max_iter = to_int(iter);
            }
            else if (strcmp(argv[5], "--dump_freq") == 0)
            {
                strcpy(freq, argv[6]);
                dump_freq = to_int(freq);
            }
        }
        if (argc == 9)
        {
            if (strcmp(argv[5], "--max_iter") == 0)
            {
                strcpy(iter, argv[6]);
                strcpy(freq, argv[8]);
            }
            else if (strcmp(argv[5], "--dump_freq") == 0)
            {
                strcpy(freq, argv[6]);
                strcpy(iter, argv[8]);
            }
            max_iter = to_int(iter);
            dump_freq = to_int(freq);
        }
    }

    FILE* file;
    file = fopen(file_name, "rb");
    if (file == NULL)
    {
        printf("Can't find file\n");
        return -1;
    }
    mkdir(dir_name);
    int size, height, width;
    unsigned char header[54];
    fread(header, 1, 54, file);
    size = header[2] + header[3] * 256 + header[4] * 256 * 256 + header[5] * 256 * 256 * 256;
    width = header[18] + header[19] * 256 + header[20] * 256 * 256 + header[21] * 256 * 256 * 256;
    height = header[22] + header[23] * 256 + header[24] * 256 * 256 + header[25] * 256 * 256 * 256;
    unsigned char bytes[size - 54];
    fread(bytes, 1, size, file);

    int** img = (int**)malloc(height * sizeof(int*));
    for (int i = 0; i < height; ++i)
        img[i] = (int*)malloc(width * sizeof(int));


    int k = (-1) * (width % 4);
    for (int i = height - 1; i >= 0; --i)
    {
        k += (width % 4);
        for (int j = 0; j < width; ++j)
        {
            if (bytes[k] == 255)
                img[i][j] = 0;
            else
                img[i][j] = 1;
            k += 3;
        }
    }

    fclose(file);

    for (int cur_iter = 1; cur_iter <= max_iter; ++cur_iter)
    {
        if (cur_iter % dump_freq == 0)
        {
            char way[50] = "";
            strcpy(way, dir_name);
            strcat(way, "\\");
            char name_pokolenie[9] = "";
            itoa(cur_iter, name_pokolenie, 10);
            strcat(name_pokolenie, ".bmp");
            strcat(way, name_pokolenie);

            FILE* file_pokolenie;
            file_pokolenie = fopen(way, "wb");
            fwrite(header, 1, 54, file_pokolenie);


            int m = 0;
            for (int i = height - 1; i >= 0; --i)
            {
                for (int j = 0; j < width; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        if (img[i][j] == 1)
                            bytes[m] = 0;
                        else
                            bytes[m] = 255;
                        ++m;
                    }
                }
                while (m % 4 != 0)
                {
                    bytes[m] = 0;
                    ++m;
                }
            }
            fwrite(bytes, 1, size - 54, file_pokolenie);
            fclose(file_pokolenie);
        }
        game(img, height, width);
    }
    free(img);
    return 0;
}
