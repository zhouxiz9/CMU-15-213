#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "cachelab.h"

char* hex_to_bin(char* hexdec);
void prepend(char* s, const char* t);

typedef struct {
    int valid;
    int tag;
    int last_used_time;
} line_t;

int main(int argc, char *argv[])
{
    int start_idx = 0;
    int verbose_flag = 0;

    if (argc == 10) {
        start_idx = 1;
        verbose_flag = 1;
    }

    long set_bits = strtol(argv[start_idx + 2], NULL , 10);
    long num_lines = strtol(argv[start_idx + 4], NULL , 10);
    long block_bits = strtol(argv[start_idx + 6], NULL , 10);
    long tag_bits = 64 - set_bits - block_bits;
    char *trace_file = argv[start_idx + 8];

    // printf("%ld %ld %ld %s\n", set_bits, num_lines, block_bits, trace_file);

    long block_size = 2 << block_bits;
    long set_size = 2 << set_bits;

    line_t *cache[set_size][num_lines];

    for (int i = 0; i < set_size; i++) {
        for (int j = 0; j < num_lines; j++) {
            line_t *line = (line_t*) malloc(sizeof(line_t));

            if (line == NULL) {
                printf("Unable to allocate enough space.\n");
                return 1;
            }

            cache[i][j] = line;
        }
    }

    FILE* fp;
    char buffer[255];

    fp = fopen(trace_file, "r");

    long time = 0;
    long hit_count = 0;
    long miss_count = 0;
    long eviction_count = 0;

    while(fgets(buffer, 255, (FILE*) fp)) {
        time++;

        if (buffer[0] == 'I') {
            continue;
        }

        char operation_type = buffer[1];
        char *hex_address = malloc(sizeof(char) * 20);
        char *address = malloc(sizeof(char) * 80);
        long address_num = -1;
        long size = -1;

        char *token = strtok(buffer + 3, ",");
        while (token != NULL) {
            if (address_num == -1) {
                address_num = strtol(token, NULL, 16);
                address = hex_to_bin(token);
                strcpy(hex_address, token);
            } else {
                size = strtol(token, NULL, 10);
            }

            token = strtok(NULL, ",");
        }

        /* tag: [0, tag_bits - 1]
         * set number: [tag_bits, tag_bits + set_bits - 1]
         * block offset: [tag_bits + set_bits, ADDRESS_BITS - 1]
         */

        char tag_part[tag_bits + 1];
        strncpy(tag_part, address, tag_bits);
        tag_part[tag_bits] = '\0';
        long tag = strtol(tag_part, NULL, 2);

        char set_number_part[set_bits + 1];
        strncpy(set_number_part, address + tag_bits, set_bits);
        set_number_part[set_bits] = '\0';
        long set_number = strtol(set_number_part, NULL, 2);

        char block_offset_part[block_bits + 1];
        strncpy(block_offset_part, address + tag_bits + set_bits, block_bits);
        block_offset_part[block_bits] = '\0';
        long block_offset = strtol(block_offset_part, NULL, 2);

        // printf("Parsed result: %ld %ld %ld %ld %s %s\n",
        //     tag, set_number,block_offset, address_num, address, hex_address);

        if (verbose_flag == 1) {
            printf("%c %s,%ld", operation_type, hex_address, size);
        }

        int hit_flag = 0;
        for (int i = 0; i < num_lines; i++) {
            line_t *line = cache[set_number][i];
            if (line->tag == tag && line->valid == 1 && (block_offset < block_size)) {
                line->last_used_time = time;
                hit_count++;
                hit_flag = 1;

                if (verbose_flag == 1) {
                    printf(" hit");
                }

                break;
            }
        }
 
        if (hit_flag) {
            if (operation_type == 'M') {
                hit_count++;

                if (verbose_flag == 1) {
                    printf(" hit\n");
                }

            } else {
                if (verbose_flag == 1) {
                    printf("\n");
                }
            }
            continue;
        }

        /* 
         * handle miss
         */
        miss_count++;
        int add_flag = 0;

        if (verbose_flag == 1) {
            printf(" miss");
        }

        for (int i = 0; i < num_lines; i++) {
            line_t *line = cache[set_number][i];
            if (line->valid == 0) {
                line->valid = 1;
                line->tag = tag;
                line->last_used_time = time;
                add_flag = 1;
                break;
            }

        }

        if (add_flag == 1) {
            if (operation_type == 'M') {
                hit_count++;

                if (verbose_flag == 1) {
                    printf(" hit\n");
                }
            } else {
                if (verbose_flag == 1) {
                    printf(" \n");
                }
            }
            continue;
        }
        
        eviction_count++;

        long least_recent_time = LONG_MAX;
        int least_recent_line_idx = -1;

        for (int i = 0; i < num_lines; i++) {
            line_t *line = cache[set_number][i];
            if (line->last_used_time < least_recent_time) {
                least_recent_time = line->last_used_time;
                least_recent_line_idx = i;
            }
        }

        line_t *line = cache[set_number][least_recent_line_idx];
        line->valid = 1;
        line->tag = tag;
        line->last_used_time = time;

        if (operation_type == 'M') {
            hit_count++;

            if (verbose_flag == 1) {
                printf(" eviction hit\n");
            }
        } else {
            if (verbose_flag == 1) {
                printf(" eviction\n");
            }
        }
    }

    printf("%ld %ld %ld\n", hit_count, miss_count, eviction_count);
    // printSummary(hit_count, miss_count, eviction_count);

    fclose(fp);

    return 0;
}


char *hex_to_bin(char* hexdec) 
{ 
  
    long int i = 0; 
    char *str = malloc(sizeof(char) * 100);
    memset(str, '\0', 80);
  
    while (hexdec[i] != '\0') { 
        switch (hexdec[i]) { 
        case '0': 
            strcat(str, "0000"); 
            break; 
        case '1': 
            strcat(str, "0001"); 
            break; 
        case '2': 
            strcat(str, "0010"); 
            break; 
        case '3': 
            strcat(str, "0011"); 
            break; 
        case '4': 
            strcat(str, "0100"); 
            break; 
        case '5': 
            strcat(str, "0101"); 
            break; 
        case '6': 
            strcat(str, "0110"); 
            break; 
        case '7': 
            strcat(str, "0111"); 
            break; 
        case '8': 
            strcat(str, "1000"); 
            break; 
        case '9': 
            strcat(str, "1001"); 
            break; 
        case 'A': 
        case 'a': 
            strcat(str, "1010"); 
            break; 
        case 'B': 
        case 'b': 
            strcat(str, "1011"); 
            break; 
        case 'C': 
        case 'c': 
            strcat(str, "1100"); 
            break; 
        case 'D': 
        case 'd': 
            strcat(str, "1101"); 
            break; 
        case 'E': 
        case 'e': 
            strcat(str, "1110"); 
            break; 
        case 'F': 
        case 'f': 
            strcat(str, "1111"); 
            break; 
        default: 
            printf("\nInvalid hexadecimal digit %c", 
                   hexdec[i]); 
        } 
        i++; 
    } 

    // printf("%lu %s %s\n", strlen(hexdec), hexdec, str);
    int prepend_zeros = 64 - strlen(hexdec) * 4;
    for (int i = 0; i < prepend_zeros; i++) {
        prepend(str, "0");
    }
    
    return str;
} 

void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}
