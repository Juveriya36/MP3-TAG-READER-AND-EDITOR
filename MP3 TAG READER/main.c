#include "types.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Error: Invalid arguments\n");
        return 1;
    }
    if(strcmp(argv[1], "-v") == 0)
    {
        do_view(argv[2]);
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        do_edit(argv[2]);
    }
    else
    {
        printf("Error: Invalid operation, please enter a valid operation\n");
        return 1;
    }
    return 0;
}