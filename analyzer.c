#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{
    int row_num_v = 8;
    int colmn_num_v = 16;
    int load_offset_v = 0;
    char *cart_addr_c = NULL;

    if(argc > 2){
        char *option = argv[2];

        if(strcmp(option, "-o") == 0)
        {
            row_num_v = (int) strtol(argv[3], NULL, 0);
            colmn_num_v = (int) strtol(argv[4], NULL, 0);

            if(argc < 5)
            {
                printf("Too few arguments!\n");
                exit(EXIT_FAILURE);
            }
            else if(argc == 6)
            {
                load_offset_v = (int) strtol(argv[5], NULL, 0);
            }
        }
        else if(strcmp(option, "-p") == 0)
        {
            cart_addr_c = argv[3];
            load_offset_v = (int) strtol(cart_addr_c, NULL, 0);
        }
        else if(strcmp(option, "-r") == 0)
        {
            int limit_addr = (int) strtol(argv[4], NULL, 0);
            load_offset_v = (int) strtol(argv[3], NULL, 0);
            colmn_num_v = (limit_addr - load_offset_v)/row_num_v+1;
        }
        else
        {
            printf("Unknown option!\n");
            exit(EXIT_FAILURE);
        }
    }

    const int row_num = row_num_v;
    const int colmn_num = colmn_num_v;
    const int load_offset = load_offset_v;

    uint8_t *cart_data;
    cart_data = malloc(row_num*colmn_num+load_offset);

    FILE *fp;
    if((fp = fopen(argv[1], "rb")) == NULL)
    {
        printf("File does not exist!\n");
        exit(EXIT_FAILURE);
    }
    fread(cart_data, 1, row_num*colmn_num+load_offset, fp);


    if(cart_addr_c != NULL)
    {
        printf("0x%Xh\t0x%X\n", load_offset, cart_data[load_offset]);
    }
    else
    {
        for(int j=0; j<colmn_num; j++)
        {
            printf("0x%Xh\t", j*row_num+load_offset);

            for(int i=0; i<row_num; i++)
            {
                uint8_t data = cart_data[(i+j*row_num)+load_offset];
                if(data <= 0xF)
                {
                    printf("0x0%X ", data);
                }else
                {
                    printf("0x%X ", data);
                }
            }
            printf("\n");
        }
    }


    free(cart_data);
    fclose(fp);
    return 0;
}
