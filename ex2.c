// Chen Larry

#include <stdio.h>
#include <string.h>

#define BYTES_AT_UTF_16 2
#define ONE_BYTE_TO_READ 1
#define MAX_LENGTH_OF_STRING 100

/************************************************************************
*    Declarations                                                       *
*************************************************************************/
void option_one(char *source_file, char *destination_file);

void option_two(char *source_file, char *destination_file, char *flag_from, char *flag_to);

void unix_to_windows(FILE *src, FILE *dst);

void unix_to_mac(FILE *src, FILE *dst);

void mac_to_windows(FILE *src, FILE *dst);

void mac_to_unix(FILE *src, FILE *dst);

void windows_to_unix(FILE *src, FILE *dst);

void windows_to_mac(FILE *src, FILE *dst);

void option_three(char *source_file, char *destination_file, char *flag_from, char *flag_to, char *order);

void swap_bytes_into_file(char *destination_file);

void swap_chars(char *c1, char *c2);

/************************************************************************
 * Function name: main                                                  *
 * he Function operation:                                               *
 * read arguments and operate the correct function.                     *
 * **********************************************************************/
int main(int argc, char *argv[]) {
    switch (argc - 1) {
        // in case got two arguments
        case 2:
            option_one(argv[1], argv[2]);
            break;
        case 4:
            option_two(argv[1], argv[2], argv[3], argv[4]);
            break;
        case 5:
            option_three(argv[1], argv[2], argv[3], argv[4], argv[5]);
            break;
        default:
            break;
    }
    return 0;
}

/************************************************************************
 * Function name: option_one                                            *
 * he Function operation:                                               *
 * copy the source file to destination file by reading 2 bytes every    *
 * time                                                                 *
 * **********************************************************************/
void option_one(char *source_file, char *destination_file) {
    // open files
    FILE *src = fopen(source_file, "rb");
    // if file not open
    if (src == NULL) {
        return;
    }
    FILE *dst = fopen(destination_file, "wb");
    // if file not open
    if (dst == NULL) {
        fclose(src);
        return;
    }
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src))
        fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    // close files
    fclose(src);
    fclose(dst);
}

/************************************************************************
 * Function name: option_two                                            *
 * he Function operation:                                               *
 * convert the source file to other OS into destination file            *
 * **********************************************************************/
void option_two(char *source_file, char *destination_file, char *flag_from, char *flag_to) {
    if (strcmp(flag_from, flag_to) == 0) {
        option_one(source_file, destination_file);
        return;
    }
    // open files
    FILE *src = fopen(source_file, "rb");
    // if file not open
    if (src == NULL)
        return;
    FILE *dst = fopen(destination_file, "wb");
    // if file not open
    if (dst == NULL) {
        fclose(src);
        return;
    }
    // from unix
    if (strstr(flag_from, "unix") != NULL) {
        // to windows
        if (strstr(flag_to, "win") != NULL)
            unix_to_windows(src, dst);
        // to mac
        if (strstr(flag_to, "mac") != NULL)
            unix_to_mac(src, dst);
    }
    // from mac
    if (strstr(flag_from, "mac") != NULL) {
        // to windows
        if (strstr(flag_to, "win") != NULL)
            mac_to_windows(src, dst);
        // to unix
        if (strstr(flag_to, "unix") != NULL)
            mac_to_unix(src, dst);
    }
    // from windows
    if (strstr(flag_from, "win") != NULL) {
        // to mac
        if (strstr(flag_to, "mac") != NULL)
            windows_to_mac(src, dst);
        // to unix
        if (strstr(flag_to, "unix") != NULL)
            windows_to_unix(src, dst);
    }
    // close files
    fclose(src);
    fclose(dst);
}

/************************************************************************
 * Function name: unix_to_windows                                       *
 * he Function operation:                                               *
 * convert unix to windows                                              *
 * **********************************************************************/
void unix_to_windows(FILE *src, FILE *dst) {
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
        if (strcmp(c, "\n") == 0) {
            fwrite("\r", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
            fwrite("\n", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
        } else fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
}

/************************************************************************
 * Function name: unix_to_mac                                           *
 * the Function operation:                                               *
 * convert unix to mac                                                  *
 * **********************************************************************/
void unix_to_mac(FILE *src, FILE *dst) {
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
        if (strcmp(c, "\n") == 0)
            fwrite("\r", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
        else fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
}

/************************************************************************
 * Function name: mac_to_windows                                        *
 * he Function operation:                                               *
 * convert mac to windows                                               *
 * **********************************************************************/
void mac_to_windows(FILE *src, FILE *dst) {
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
        if (strcmp(c, "\r") == 0) {
            fwrite("\r", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
            fwrite("\n", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
        } else fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
}

/************************************************************************
 * Function name: mac_to_unix                                           *
 * he Function operation:                                               *
 * convert mac to unix                                                  *
 * **********************************************************************/
void mac_to_unix(FILE *src, FILE *dst) {
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
        if (strcmp(c, "\r") == 0)
            fwrite("\n", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
        else fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
}

/************************************************************************
 * Function name: window_to_unix                                        *
 * he Function operation:                                               *
 * convert windows to unix                                              *
 * **********************************************************************/
void windows_to_unix(FILE *src, FILE *dst) {
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
        if (strcmp(c, "\r") == 0) {
            char next[MAX_LENGTH_OF_STRING] = "";
            if (fread(next, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
                if (strcmp(next, "\n") == 0) {
                    fwrite("\n", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
                    continue;
                }
                fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
                fwrite(next, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
                continue;
            }
        }
        fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
}

/************************************************************************
 * Function name: windows_to_mac                                        *
 * he Function operation:                                               *
 * convert windows to mac                                               *
 * **********************************************************************/
void windows_to_mac(FILE *src, FILE *dst) {
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
        // found /r
        if (strcmp(c, "\r") == 0) {
            char next[MAX_LENGTH_OF_STRING] = "";
            if (fread(next, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, src)) {
                // found \n
                if (strcmp(next, "\n") == 0) {
                    fwrite("\r", ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
                    continue;
                } else {
                    // not found \n
                    fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
                    fwrite(next, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
                    continue;
                }
            }
        }
        fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
}

/************************************************************************
 * Function name: option_three                                          *
 * he Function operation:                                               *
 * convert the source file to other OS into destination file and        *
 * changes to the requested endianness                                  *
 * **********************************************************************/
void option_three(char *source_file, char *destination_file, char *flag_from, char *flag_to, char *order) {
    if (strstr(order, "keep") != NULL)
        option_two(source_file, destination_file, flag_from, flag_to);
    if (strstr(order, "swap") != NULL) {
        option_two(source_file, destination_file, flag_from, flag_to);
        swap_bytes_into_file(destination_file);
    }
}

/************************************************************************
 * Function name: swap_bytes_into_file                                  *
 * he Function operation:                                               *
 * gets a file and change bytes in it to other endianness               *
 * **********************************************************************/
void swap_bytes_into_file(char *destination_file) {
    //open files
    FILE *help = fopen(destination_file, "rb");
    if (help == NULL)
        return;
    FILE *dst = fopen(destination_file, "rb+");
    if (dst == NULL) {
        fclose(help);
        return;
    }
    // endianness
    char c[MAX_LENGTH_OF_STRING] = "";
    while (fread(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, help)) {
        swap_chars(&c[0], &c[1]);
        fwrite(c, ONE_BYTE_TO_READ, BYTES_AT_UTF_16, dst);
    }
    // close files
    fclose(help);
    fclose(dst);
}

/************************************************************************
 * Function name: swap_chars                                            *
 * he Function operation:                                               *
 * replace between the chars                                            *
 * **********************************************************************/
void swap_chars(char *c1, char *c2) {
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}
