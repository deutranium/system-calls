#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int one_mb = 1000000;
char flip[2000000] = {};
char out[250]; 

int min(int a, int b){
    if (a <= b)
        return a;
    return b;
}

void better_write(char *str){
    write(STDOUT_FILENO, str, strlen(str));
}

void print_percentage(double percentage){
    
    char value[5];

    value[4] = (char)(((int)(percentage*((double)100)))%10)+ '0';
    value[3] = (char)(((int)(percentage*((double)10)))%10) + '0';
    value[2] = (char)(((int)(percentage))%10) + '0';
    value[1]= (char)(((int)(percentage/((double)10)))%10) + '0';
    value[0]= (char)(((int)(percentage/((double)99)))%10) + '0';

    
    char okay[10];

    for(int i=1;i<=3;i++){
        okay[i] = value[i-1];
    }
    okay[4] = '.';
    okay[5] = value[3];
    okay[6] = value[4];

    okay[7] = '%';
    okay[0] = '\r';
    okay[8] = '[';
    okay[9] = '\0';
    write(STDOUT_FILENO, okay, strlen(okay));

    for(int i=1;i<=percentage/5;i++){
        write(STDOUT_FILENO, "#", strlen("#"));
    }
    for(int i=(percentage/5)+1;i<=20;i++){
        write(STDOUT_FILENO, " ", strlen(" "));
    } 
    write(STDOUT_FILENO, "]", strlen("]"));
}

int main(int argc, char *argv[]){

    int sizzzz, sizzzz_write;

    int size_waste, total_file_size = 0;

    if(argc != 2){
        better_write("Please enter exactly 2 arguments\n");
        return 0;
    }

    mkdir("Assignment", S_IRWXU | S_IRWXO);
    
    char * in_file = argv[1];
    char out_file[10000];

    strcat(out_file, "Assignment/");
    strcat(out_file, in_file);

    char waste[2000000];
    char BUFFER[2000000];




    int file_read = open(in_file, O_RDONLY);
    int file_write = open(out_file, O_RDWR | O_CREAT | O_TRUNC, 0644);

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


    while(1){
        size_waste = read(file_read, waste, one_mb);

        total_file_size += size_waste;

        if(size_waste < one_mb)
            break;
    }


    int chunk = total_file_size;

    while(chunk ){
        int val = min(one_mb, chunk);


        chunk -= val;

        sizzzz = pread(file_read, BUFFER, val, chunk);

        for (int i = 2 * one_mb; i > 0; i--)
            flip[i] = '\0';

        for (int i = 0; i < val; i++)
            flip[i] = BUFFER[val - i - 1];

        sizzzz_write = write(file_write, flip, val);

        BUFFER[sizzzz_write] = '\0';

        float percentage_finished = (((float)total_file_size - (float)chunk) / (float)total_file_size)*100;

        print_percentage(percentage_finished);
    }

    better_write("100% Loaded!");

    close(file_read);
    close(file_write);


    return 0;
}