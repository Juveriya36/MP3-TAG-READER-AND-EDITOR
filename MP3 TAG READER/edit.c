#include "types.h"

int do_edit(char *filename)
{
    FILE *src;
    FILE *dest;

    char ch;
    char new_title[100];
    char new_artist[100];
    char new_album[100];
    char new_year[100];
    char new_genre[100];
    char new_comment[100];

    char header[10];
    char tag[5];
    char current_tag[5];

    char *data;

    unsigned char size[4];
    unsigned char flags[2];

    unsigned char current_size[4];
    unsigned char current_flags[2];

    unsigned char new_size_bytes[4];

    int frame_size;
    int current_frame_size;
    int new_size;
    int choice;

    src = fopen(filename, "rb");

    if(src == NULL)
    {
        printf("Error: Unable to open source file\n");
        return 1;
    }

    dest = fopen("temp.mp3", "wb");

    if(dest == NULL)
    {
        printf("Error: Unable to create duplicate file\n");
        fclose(src);
        return 1;
    }

    printf("Source file opened successfully\n");
    printf("Duplicate file created successfully\n");

    fread(header, 10, 1, src);
    fwrite(header, 10, 1, dest);

    printf("\n1. Title\n");
    printf("2. Artist\n");
    printf("3. Album\n");
    printf("4. Year\n");
    printf("5. Genre\n");
    printf("6. Comment\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter the new title: ");
        scanf(" %[^\n]", new_title);

        new_size = strlen(new_title) + 1;

        printf("New frame size : %d\n", new_size);
    }
    else if(choice == 2)
    {
        printf("Enter the new artist: ");
        scanf(" %[^\n]", new_artist);

        new_size = strlen(new_artist) + 1;

        printf("New frame size : %d\n", new_size);
    }
    else if(choice == 3)
    {
    printf("Enter the new album: ");
    scanf(" %[^\n]", new_album);

    new_size = strlen(new_album) + 1;

    printf("New frame size : %d\n", new_size);
    }
    else if(choice == 4)
    {
    printf("Enter the new year: ");
    scanf(" %[^\n]", new_year);

    new_size = strlen(new_year) + 1;

    printf("New frame size : %d\n", new_size);
    }
    else if(choice == 5)
    {
    printf("Enter the new genre: ");
    scanf(" %[^\n]", new_genre);

    new_size = strlen(new_genre) + 1;

    printf("New frame size : %d\n", new_size);
    }
    else if(choice == 6)
    {
    printf("Enter the new comment: ");
    scanf(" %[^\n]", new_comment);

    new_size = strlen(new_comment) + 1;

    printf("New frame size : %d\n", new_size);
    }
    else
    {
        printf("This option is not implemented yet.\n");

        fclose(src);
        fclose(dest);

        return 0;
    }

    new_size_bytes[0] = (new_size >> 24) & 0xFF;
    new_size_bytes[1] = (new_size >> 16) & 0xFF;
    new_size_bytes[2] = (new_size >> 8) & 0xFF;
    new_size_bytes[3] = new_size & 0xFF;

    fread(tag, 4, 1, src);
    tag[4] = '\0';

    fread(size, 4, 1, src);
    frame_size = convert_size(size);

    fread(flags, 2, 1, src);

    data = malloc(frame_size);

    if(data == NULL)
    {
        printf("Memory allocation failed\n");

        fclose(src);
        fclose(dest);

        return 1;
    }

    fread(data, frame_size, 1, src);

    printf("Current tag: %s\n", tag);
    printf("Current frame size: %d\n", frame_size);

    
    if(choice == 1 && strcmp(tag, "TIT2") == 0)
    {
        printf("Title frame found\n");

        fwrite(tag, 4, 1, dest);
        fwrite(new_size_bytes, 4, 1, dest);
        fwrite(flags, 2, 1, dest);

        fwrite(data, 1, 1, dest);

        fwrite(new_title, strlen(new_title), 1, dest);
    }
    else
    {
        fwrite(tag, 4, 1, dest);
        fwrite(size, 4, 1, dest);
        fwrite(flags, 2, 1, dest);
        fwrite(data, frame_size, 1, dest);
    }

    free(data);

    while(fread(current_tag, 4, 1, src) == 1)
    {
        current_tag[4] = '\0';

        if(current_tag[0] == '\0' &&
           current_tag[1] == '\0' &&
           current_tag[2] == '\0' &&
           current_tag[3] == '\0')
        {
            fwrite(current_tag, 4, 1, dest);

            while(fread(&ch, 1, 1, src) == 1)
            {
                fwrite(&ch, 1, 1, dest);
            }

            break;
        }

        fread(current_size, 4, 1, src);
        current_frame_size = convert_size(current_size);

        fread(current_flags, 2, 1, src);


        data = malloc(current_frame_size);

        if(data == NULL)
        {
            printf("Memory allocation failed\n");

            fclose(src);
            fclose(dest);

            return 1;
        }

        fread(data, current_frame_size, 1, src);

        if(choice == 2 && strcmp(current_tag, "TPE1") == 0)
        {
            printf("Artist frame found\n");

            fwrite(current_tag, 4, 1, dest);
            fwrite(new_size_bytes, 4, 1, dest);
            fwrite(current_flags, 2, 1, dest);

            fwrite(data, 1, 1, dest);

            fwrite(new_artist, strlen(new_artist), 1, dest);
        }
        else if(choice == 3 && strcmp(current_tag, "TALB") == 0)
        {
            printf("Album frame found\n");

            fwrite(current_tag, 4, 1, dest);
            fwrite(new_size_bytes, 4, 1, dest);
            fwrite(current_flags, 2, 1, dest);

            fwrite(data, 1, 1, dest);

            fwrite(new_album, strlen(new_album), 1, dest);
        }
        else if(choice == 4 && strcmp(current_tag, "TYER") == 0)
        {
            printf("Year frame found\n");

            fwrite(current_tag, 4, 1, dest);
            fwrite(new_size_bytes, 4, 1, dest);
            fwrite(current_flags, 2, 1, dest);

            fwrite(data, 1, 1, dest);

            fwrite(new_year, strlen(new_year), 1, dest);
        }
        else if(choice == 5 && strcmp(current_tag, "TCON") == 0)
        {
            printf("Genre frame found\n");

            fwrite(current_tag, 4, 1, dest);
            fwrite(new_size_bytes, 4, 1, dest);
            fwrite(current_flags, 2, 1, dest);

            fwrite(data, 1, 1, dest);

            fwrite(new_genre, strlen(new_genre), 1, dest);
        }
        else if(choice == 6 && strcmp(current_tag, "COMM") == 0)
        {
            printf("Comment frame found\n");

            fwrite(current_tag, 4, 1, dest);
            fwrite(new_size_bytes, 4, 1, dest);
            fwrite(current_flags, 2, 1, dest);

            fwrite(data, 1, 1, dest);

            fwrite(new_comment, strlen(new_comment), 1, dest);
        }
        else
        {
            fwrite(current_tag, 4, 1, dest);
            fwrite(current_size, 4, 1, dest);
            fwrite(current_flags, 2, 1, dest);
            fwrite(data, current_frame_size, 1, dest);
        }

        free(data);
    }

    fclose(src);
    fclose(dest);

    printf("Edit completed successfully\n");

    return 0;
}