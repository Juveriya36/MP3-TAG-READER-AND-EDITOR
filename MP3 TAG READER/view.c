#include "types.h"

int do_view(char *filename)
{
    FILE *fptr;
    char header[10];
    char tag[5];
    unsigned char size[4];
    int frame_size;
    unsigned char flags[2];
    

    fptr = fopen(filename, "rb");
    if(fptr == NULL)
    {
        printf("Error: Unable to open file\n");
        return 1;
    }
    printf("File opened successfully\n");

    fread(header, 10, 1, fptr);
    printf("Header read successfully\n");
    if(header[0] == 'I' && header[1] == 'D' && header[2] == '3')
    {
        printf("ID3 tag found\n");
    }
    else
    {
        printf("Error: ID3 tag not found\n");
        fclose(fptr);
        return 1;
    }

    if(header[3] == 3 && header[4] == 0)
    {
        printf("ID3v3 version found\n");
    }
    else
    {
        printf("Error: Unsupported ID3 version\n");
        fclose(fptr);
        return 1;
    }
    
    printf("\n-------- MP3 TAG DETAILS --------\n\n");

    while(fread(tag, 4, 1, fptr) == 1)
    {
    tag[4] = '\0';

    if(strcmp(tag, "APIC") == 0)
    {
        break;
    }
    //printf("Tag : %s\n", tag);

    fread(size, 4, 1, fptr);
    frame_size = convert_size(size);

    if(frame_size <= 0)
    {
        break;
    }
    
    //printf("Frame size : %d\n", frame_size);

    fread(flags, 2, 1, fptr);
    //printf("Flags read successfully\n");

    char data[frame_size + 1];

    fread(data, frame_size, 1, fptr);
    data[frame_size] = '\0';

    //printf("Data : %s\n", data + 1);

    if(strcmp(tag, "TIT2") == 0)
    {
        printf("%-8s : %s\n", "TITLE", data + 1);
    }
    else if(strcmp(tag, "TPE1") == 0)
    {
        printf("%-8s : %s\n", "ARTIST", data + 1);
    }
    else if(strcmp(tag, "TALB") == 0)
    {
        printf("%-8s : %s\n", "ALBUM", data + 1);
    }
    else if(strcmp(tag, "TYER") == 0)
    {
        printf("%-8s : %s\n", "YEAR", data + 1);
    }
    else if(strcmp(tag, "TCON") == 0)
    {
        printf("%-8s : %s\n", "GENRE", data + 1);
    }
    else if(strcmp(tag, "COMM") == 0)
    {
        printf("%-8s : %s\n", "COMMENT", data + 1);
    }
    }

    fclose(fptr);

    return 0;
}