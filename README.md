 Simple Shell (Tar Heel SHell - thsh)
Welcome to thsh, a simple custom shell implemented in C as a hands-on project to explore low-level operating system concepts like process creation, environment variables, and command execution.

This shell supports basic built-in commands, like cd and exit, and can execute external system commands like pwd and ls. It is designed to demonstrate how minimal shell interfaces work under the hood.

Features
Built-in command support: cd, exit

Execution of external programs (ls, pwd, etc.)

Uses system calls: fork, exec, and wait

Resolves executables using $PATH via getenv

Command parsing with heap-allocated argv

Basic memory safety and cleanup (Valgrind tested)

📂 Project Structure
bash
Copy
Edit
.
├── data/              # Test input/output files
│   ├── in*.txt
│   └── out*.txt
├── main.c             # Entry point (do not modify)
├── Makefile
├── README.md
├── shell.c            # Implement shell functionality here
├── shell.h            # Function declarations and struct definitions
├── tests.cpp          # GoogleTest unit tests
└── tests.hpp
Concepts Demonstrated
Process Control: Creating, executing, and managing processes via fork(), exec(), and wait().

Environment Interaction: Accessing environment variables with getenv().

Command Resolution: Searching for executables using system $PATH.

Memory Management: Dynamically allocating command arguments and freeing them properly.

Error Handling: Handling invalid input and failures in command execution.

References
System Calls
fork(2) – create a new process

exec(3) – replace process image

wait(2) – wait for child process

getenv(3) – get environment variables

Environment
$PATH and external command resolution

Using which to trace full paths of binaries
