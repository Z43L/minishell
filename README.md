# Minishell: Low-Level Systems Interpreter

## 🛠️ Project Essence
A custom Unix-like shell implementation developed in **C**, focusing on the core mechanics of process management, memory allocation, and system call orchestration. This project serves as a rigorous demonstration of low-level systems programming and resource management.

## ⚙️ Technical Implementation

### 1. Process Orchestration
- **Fork & Exec:** Implementation of the process lifecycle, managing the creation of child processes and execution of binary commands.
- **Job Control:** Robust handling of background and foreground processes, including PID tracking and job status management.

### 2. Signal Handling & I/O
- **Signal Management:** Precise implementation of `SIGINT`, `SIGQUIT`, and `SIGCHLD` to ensure graceful termination and prevent zombie processes.
- **I/O Redirections:** Manual management of file descriptors (`dup2`) to implement `<` and `>` redirections, and pipe (`|`) chains for inter-process communication.

### 3. Parsing & Lexing
- **Tokenization:** Custom lexer to parse complex command lines, handling quotes, escape characters, and environment variable expansion.
- **Abstract Syntax Tree (AST):** Logical structuring of commands to ensure correct execution order and redirection priority.

## 🛡️ Memory & Stability
- **Zero Leaks:** Rigorous memory management using `malloc` and `free`, validated with **Valgrind** to ensure 0 byte leaks.
- **Robustness:** Implementation of error handling for all system calls to prevent segmentation faults and ensure shell stability.

## 🚀 Key Skills Demonstrated
- Deep understanding of the **Unix Process Model**.
- Mastery of **Dynamic Memory Allocation**.
- Ability to interact directly with the **Linux Kernel** via system calls.

---
*Developed as part of the 42 Network curriculum, focusing on the "no-library" philosophy to maximize understanding of system internals.*
 ⁠
