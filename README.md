# System Calls in C

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/does-not-contain-msg.svg)](https://forthebadge.com)

**Course:** Operating Systems and Networks (Monsoon'21)

*View the assignment PDF [here](OS_Assignment_1.pdf)!*

## Task:

Reverse the file provided **using only system calls** in C. The use of _printf_, _scanf_ etc. is not permitted. This should be accompanied by the percentage of file reversed being constantly updating in the same line on the console. \
**Relevant commands:** read, write, lseek, stat, fflush, perror

## Key features:
- Works perfectly files significantly larger than the RAM size - doesn't load the entire file into RAM in one go
- Compatible with both absolute and relative paths

## Instructions
- Clone the repo on your local machine and navigate to this directory
- Ensure that you have clang version >=12.0.5 or gcc version >=11.2 for compilation
- Run `gcc filename` to compile `filename` (`q1.c` or `q2.c`)and generate the required `.out` executable file which can be run with the required arguments

**For Q1**
- If your executable file is known as `a.out`, run the following command:
``` bash
./a.out path/input_file.txt
```
You will find the output file with the name `1_input_file.txt` in `Assignment/1_input_file.txt` which contains the text reversed from the input file

**For Q2**
- If your executable file is known as `a.out`, run the following command:
``` bash
./a.out path/input_file.txt num_partitions nth_partition
```
Here, the output file `2_input_file.txt` will be stored in `Assignment/2_input_file.txt` and contains the reversal of the text from `nth_partition` partition if we divide the input file text into `num_partition` partitions

## Assumptions

#### Question 1:
- Path argument for input file has less than 200 characters

#### Question 2:

- Number of parts and part to be reversed are both single digit numbers
