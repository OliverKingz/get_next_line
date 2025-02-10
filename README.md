# Get Next Line  
[42 Cursus] This project involves creating a function `get_next_line` that reads a line from a file descriptor. The function is designed to be called repeatedly to read a file line by line until the end. The project emphasizes understanding static variables, memory management, and efficient file reading in C.  

Keywords  
- **File Descriptors** 
- **Static Variables**  
- **Memory Management**  
- **Buffered Reading**  
- **Error Handling**  
- **C Programming**  
- **Algorithm Optimization**  

---

## Index  
1. [Overview](#overview)  
2. [Features](#features)  
3. [Bonus Features](#bonus-features)  
4. [Requirements](#requirements)  
5. [How to Use](#how-to-use)  
6. [Example Usage](#example-usage)  
7. [What I Learned](#what-i-learned)  
8. [Author](#author)  
9. [Acknowledgments](#acknowledgments)  

---

## Overview  
The `get_next_line` project is a fundamental exercise in the 42 Cursus that focuses on reading lines from a file descriptor efficiently. The function must handle different buffer sizes, manage memory properly, and avoid leaks. The project also includes a bonus part where the function is extended to handle multiple file descriptors simultaneously.  

I implemented three versions of `get_next_line`:  
1. **Using Linked Lists**: A version that uses linked lists to manage the buffer.  
2. **Using Strings**: A version that relies on string manipulation without using the `libft` library.  
3. **Using Libft Functions**: A version that integrates with my `libft` library for future use.  

The bonus version includes support for multiple file descriptors and uses a single static variable.  

---

## Features  
- **Line-by-Line Reading**: Reads a file descriptor line by line until the end.  
- **Dynamic Buffer Size**: Works with any buffer size defined by `BUFFER_SIZE`.  
- **Memory Management**: Ensures no memory leaks and proper allocation/deallocation.  
- **Error Handling**: Handles errors such as invalid file descriptors or read failures.  
- **Support for Multiple File Descriptors (Bonus)**: Manages multiple file descriptors simultaneously without losing track of the reading position.  

## Bonus Features  
- **Single Static Variable**: The bonus version uses only one static variable to manage multiple file descriptors.  
- **Multiple FD Support**: Can alternate between different file descriptors without losing the reading context.  

---

## Requirements  
- The function must compile with the `-D BUFFER_SIZE=xx` flag, where `xx` is the buffer size.  
- No memory leaks are allowed.  
- The function must handle reading from standard input (`stdin`) and files.  
- The function must return the correct line, including the newline character (`\n`), except for the last line if it doesn’t end with `\n`. 
- The bonus version must handle multiple file descriptors without mixing their reading contexts.  

---

## How to Use  
### Requirements  
- A C compiler (e.g., `gcc`).  
- A main function to call `get_next_line`.  

1. Clone this repository:  
   ```bash  
   git clone [repository-url]  
   cd get_next_line  
   ```  
2. Compile the project:  
   ```bash  
   gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o get_next_line  
   ```  
3. Run the project:  
   ```bash  
   ./get_next_line  
   ```  

### Example Usage  
To use `get_next_line`, you need to create a `main.c` file that calls the function. Here’s an example of how to use it:  

```c  
#include "get_next_line.h"  
#include <stdio.h>  
#include <fcntl.h>  

int main(void)  
{  
    int fd = open("test.txt", O_RDONLY);  
    char *line;  

    while ((line = get_next_line(fd)) != NULL)  
    {  
        printf("%s", line);  
        free(line);  
    }  
    close(fd);  
    return 0;  
}  
```  

### Bonus Usage  
For the bonus version, you can use the same `main.c` file, but make sure to include the bonus header and source files:  

```c  
#include "get_next_line_bonus.h"  
#include <stdio.h>  
#include <fcntl.h>  

int main(void)  
{  
    int fd1 = open("test1.txt", O_RDONLY);  
    int fd2 = open("test2.txt", O_RDONLY);  
    char *line1;  
    char *line2;  

    line1 = get_next_line(fd1);  
    line2 = get_next_line(fd2);  
    printf("FD1: %s", line1);  
    printf("FD2: %s", line2);  
    free(line1);  
    free(line2);  

    close(fd1);  
    close(fd2);  
    return 0;  
}  
```  
---

## What I Learned  
- **Static Variables**: Gained a deep understanding of how static variables work in C and how they can be used to maintain state between function calls.  
- **Memory Management**: Improved my skills in managing dynamic memory allocation and avoiding memory leaks.  
- **File Descriptors**: Learned how to work with file descriptors and handle different types of input (files, stdin, etc.).  
- **Algorithm Optimization**: Developed efficient algorithms for reading and processing data in chunks.  
- **Error Handling**: Enhanced my ability to handle edge cases and errors gracefully.  

---

## Author  
- **Name**: Oliver King Zamora  
- **GitHub**: [oliverkingz](https://github.com/oliverkingz)  
- **42 Login**: ozamora-  

---

## Acknowledgments  
This project is part of the **42 Cursus**, a rigorous programming curriculum that emphasizes hands-on learning and problem-solving. Special thanks to the 42 team for providing this challenging and rewarding project!  

Also, thanks to my peers and mentors for their feedback and support during the development process.  

---
