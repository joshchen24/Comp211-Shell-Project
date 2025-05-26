# 🐚 Simple Shell

This project is a simple command-line shell implemented in C. It supports basic functionality such as changing directories and executing system commands (e.g., `pwd`, `ls`, etc.). The goal was to deepen my understanding of Unix-like process control, environment variables, and how real shells like Bash operate under the hood.

---

## 🧠 What I Learned

- I worked directly with system calls like `fork`, `exec`, and `wait` to manage child processes and execute programs.
- I used the `getenv` function to read environment variables like `PATH`, allowing the shell to locate executables.
- I gained experience building and running a shell environment that can interpret user input, locate and execute programs, and handle built-in commands.

---

## 🗂️ Project Structure

.
├── data/ # Input and output test cases
├── main.c # Entry point to launch the shell (provided)
├── shell.c # Core implementation of the shell
├── shell.h # Header file with function declarations
├── Makefile # Compilation instructions
└── README.md # Project documentation


---

## ⚙️ Features

- Interactive command-line interface with a custom prompt (`thsh$`)
- Support for built-in commands like `cd` and `exit`
- Execution of system binaries like `ls`, `pwd`, and others via `execvp`
- Dynamic path resolution by searching through directories defined in the `PATH` environment variable

---

## 🛠️ Key Implementation Details

### `create_command`
Allocated memory for a `command*` structure and parsed input arguments accordingly.

### `parse`
Tokenized raw user input into commands and arguments, returning a populated command structure.

### `find_full_path`
Searched through `PATH` directories to find the full path of an executable. If found, the shell executed the program using its full path.

### `execute`
Handled both built-in command logic (`cd`, `exit`) and external commands via `fork`, `execvp`, and `waitpid`. Ensured that child processes were correctly spawned and managed.

---

## 📌 Notes

- The shell initializes with a strong separation of parsing, command creation, path resolution, and execution for clarity and modularity.
- Error messages and edge cases were handled gracefully to mimic real shell behavior.
- Built-in commands were executed directly in the shell process, while external commands were forked into child processes.

---

## ✅ Accomplishments

- Built a working shell from scratch in C
- Gained hands-on experience with Unix process control APIs
- Improved debugging skills and memory management (checked with Valgrind)
- Reinforced understanding of how environment variables and executables work together

---

## 📸 Demo

```bash
$ ./main
thsh$ pwd
/home/user/projects/simple-shell
thsh$ ls
main.c  shell.c  shell.h  Makefile  README.md
thsh$ cd ..
thsh$ pwd
/home/user/projects
thsh$ exit
$
