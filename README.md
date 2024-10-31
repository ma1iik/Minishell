
# Minishell

## Description
Minishell is a simplified shell application inspired by Bash, developed as part of the 42 School curriculum. The project focuses on managing processes, handling file descriptors, and implementing a variety of shell functionalities including command parsing, environment handling, and built-in commands.

## Features
- **Prompt Display**: Displays a prompt, waiting for user input.
- **Command Execution**: Searches and launches the correct executable based on `$PATH`, with support for relative and absolute paths.
- **Redirection Support**:
  - `<`: Redirects input.
  - `>`: Redirects output.
  - `<<`: Reads input until a specified delimiter is encountered (here-document).
  - `>>`: Redirects output in append mode.
- **Pipes**: Supports piping, connecting the output of one command to the input of the next.
- **Environment Variables**: Expands `$` followed by variable names to their values.
- **Exit Status**: Expands `$?` to the exit status of the last executed command.
- **Signal Handling**:
  - `Ctrl+C`: Interrupts the current command and displays a new prompt.
  - `Ctrl+D`: Exits the shell.
  - `Ctrl+\`: Does nothing, as in Bash.
- **Built-in Commands**:
  - `echo` with `-n` option
  - `cd` with relative or absolute path
  - `pwd` to print the working directory
  - `export` to set environment variables
  - `unset` to remove environment variables
  - `env` to list environment variables
  - `exit` to close the shell

## Compilation and Usage
To compile the project, run:
```bash
make
```
This will generate the `minishell` executable.

### Running
```bash
./minishell
```

## Project Structure
- **`src/`**: Contains the main source code files for Minishell functionality.
- **`include/`**: Holds the header files.
- **`libft/`**: Includes the 42-libft library.

## Example Commands
```bash
echo "Hello, World!"
cd /home/user
pwd
export MY_VAR=test
echo $MY_VAR
ls | grep minishell
```

## Author
Developed by [Malik ](https://github.com/ma1iik) as part of the 42 School curriculum.
