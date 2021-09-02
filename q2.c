#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int one_mb = 1000000;
char flip[2000000] = {};
char out[250]; 

// find minimum of two numbers 
int min(int a, int b){
    if (a <= b)
        return a;
    return b;
}

// for easier printing and logging
void better_write(char *str){
    write(STDOUT_FILENO, str, strlen(str));
}

// print percentage progress
void print_percentage(double percentage){

    char value[5];

    value[4] = (char)(((int)(percentage * ((double)100))) % 10) + '0';
    value[3] = (char)(((int)(percentage * ((double)10))) % 10) + '0';
    value[2] = (char)(((int)(percentage)) % 10) + '0';
    value[1] = (char)(((int)(percentage / ((double)10))) % 10) + '0';
    value[0] = (char)(((int)(percentage / ((double)99))) % 10) + '0';

    char okay[10];

    for (int i = 1; i <= 3; i++){
        okay[i] = value[i - 1];
    }
    okay[4] = '.';
    okay[5] = value[3];
    okay[6] = value[4];

    okay[7] = '%';
    okay[0] = '\r';
    okay[8] = '[';
    okay[9] = '\0';
    better_write(okay);

    for (int i = 1; i <= percentage / 5; i++){
        better_write("#");
    }
    for (int i = (percentage / 5) + 1; i <= 20; i++){
        better_write(" ");
    }
    better_write("]");
}

int main(int argc, char *argv[]){

    int sizzzz, sizzzz_write, size_waste, total_file_size = 0;

    // error handling for number of arguments
    if(argc != 4){
        better_write("Please enter exactly 4 arguments\n");
        return 0;
    }

    // create assignment folder with required perms
    mkdir("Assignment", S_IRWXU | S_IRWXO);
    
    char * in_file_path = argv[1];

    char out_file[10000];

    char in_file[200] = "\0";
    int in_file_len = strlen(in_file_path);

    int slash_ind = 0;  // index of last `/`

    // handling absolute paths + getting input file name
    for(int i = 0; i <= in_file_len; i++){
        char this_char = in_file_path[in_file_len - 1 - i];
        if( this_char == '/'){
            slash_ind = in_file_len - i;
            break;
        } 
    }

    // flag = 1 if relative path is given, 0 for absolute path
    int flag = 1;

    if (slash_ind > 0)
        flag = 0;

    for (int i = slash_ind; i < in_file_len + flag; i++){
        in_file[i - slash_ind] = in_file_path[i];
    }

    // path for output file
    strcat(out_file, "Assignment/");
    strcat(out_file, "2_");
    strcat(out_file, in_file);

    char waste[2000000];
    char BUFFER[2000000];

    int no_of_parts = (int)argv[2][0] - (int)'0', parts_to_be_reversed = (int)argv[3][0] - (int)'0';

    int file_read = open(in_file, O_RDONLY);
    int file_write = open(out_file, O_RDWR | O_CREAT | O_TRUNC, 0644);

    // error handling for file accessing
    if (file_read < 0){
        perror("r1");
        better_write("Error in accessing input file");

        return 1;
    }
    if (file_write < 0){
        perror("r2");
        better_write("Error in accessing output file");

        return 1;
    }

    // compute the file size to determine number of chunks
    while(1){
        size_waste = read(file_read, waste, one_mb);
        total_file_size += size_waste;

        if(size_waste < one_mb)
            break;
    }

    int part_size = total_file_size/no_of_parts;

    int chunk = part_size;

    // loop through one mb of data every time
    while(chunk){

        // check if this is the last chunk to process + update chunk size
        int val = min(one_mb, chunk);
        chunk -= val;

        // read file for the concerned chunk
        sizzzz = pread(file_read, BUFFER, val, (parts_to_be_reversed - 1)*part_size + chunk);

        // initialise everything with a null character for string termination
        for (int i = 2 * one_mb; i > 0; i--)
            flip[i] = '\0';

        // write string in reverse for the concerned chunk
        for (int i = 0; i < val; i++)
            flip[i] = BUFFER[val - i - 1];

        // write file with the reversed chunk string
        sizzzz_write = write(file_write, flip, val);

        BUFFER[sizzzz_write] = '\0';

        // progress persentage
        float percentage_finished = (((float)total_file_size - (float)chunk) / (float)total_file_size)*100;
        print_percentage(percentage_finished);
    }

    better_write("\n100% Loaded!");

    close(file_read);
    close(file_write);

    return 0;
}