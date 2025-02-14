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

### Error Handling and Testing

To test `get_next_line`, you need to create a `main.c` file that calls the function and then compile and run it. Below are the test cases you should evaluate to ensure the function works correctly and handles all edge cases.

#### Basic Functionality
| **Test Case**                                          | **Description**                                                                 | **Expected Output**                                                                 |
|--------------------------------------------------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Valid File Descriptor**                              | Reads from a valid file descriptor.                                             | Returns each line from the file, including the newline character.                   |
| **Standard Input (stdin)**                             | Reads from standard input (`stdin`).                                            | Returns each line entered by the user, including the newline character.             |

#### Edge Cases
| **Test Case**                                          | **Description**                                                                 | **Expected Output**                                                                 |
|--------------------------------------------------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Invalid File Descriptor**                            | Attempts to read from an invalid file descriptor (e.g., `-1`).                  | Returns `NULL` and handles the error.                                              |
| **File Without Permissions**                           | Attempts to read from a file without proper permissions.                        | Returns `NULL` and handles the error.                                              |
| **Empty File**                                         | Reads from an empty file.                                                       | Returns `NULL` after the first call.                                               |
| **File Without Newline at End**                        | Reads from a file that doesn’t end with a newline.                              | Returns the last line without a newline character.                                 |
| **File With One Line**                                 | Reads from a file with only one line.                                           | Returns the line, including the newline character.                                 |
| **File With Multiple Lines**                           | Reads from a file with multiple lines.                                          | Returns each line sequentially, including the newline character.                   |

#### Buffer Size Variations
| **Test Case**                                          | **Description**                                                                 | **Expected Output**                                                                 |
|--------------------------------------------------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **BUFFER_SIZE=1**                                      | Reads with a buffer size of 1.                                                  | Returns each line correctly, even with a very small buffer size.                   |
| **BUFFER_SIZE=1000000**                                | Reads with a very large buffer size.                                            | Returns each line correctly, even with a large buffer size.                        |
| **BUFFER_SIZE=42**                                     | Reads with a moderate buffer size.                                              | Returns each line correctly.                                                       |

#### Memory Management
| **Test Case**                                          | **Description**                                                                 | **Expected Output**                                                                 |
|--------------------------------------------------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Check for Memory Leaks**                             | Checks for memory leaks using tools like `valgrind`.                            | No memory leaks should be detected.                                                |
| **Check for Memory Leaks on Error**                    | Checks for memory leaks when handling errors (e.g., invalid file descriptor).    | No memory leaks should be detected.                                                |

#### Bonus Functionality (Multiple File Descriptors)
| **Test Case**                                          | **Description**                                                                 | **Expected Output**                                                                 |
|--------------------------------------------------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Multiple File Descriptors**                          | Alternates reading between multiple file descriptors.                           | Returns lines from each file descriptor in sequence without mixing contexts.        |
| **Check for Memory Leaks with Multiple FDs**           | Checks for memory leaks when handling multiple file descriptors.                | No memory leaks should be detected.                                                |

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
You're absolutely correct! Since `get_next_line` is a function and not a standalone executable, you can't directly run it from the command line like `./get_next_line`. Instead, you need to create a test program (e.g., `main.c`) that calls `get_next_line` and then compile and run that program. Below, I’ve updated the **Error Handling and Testing** section to reflect this, focusing on how to test `get_next_line` in a controlled environment.

---

