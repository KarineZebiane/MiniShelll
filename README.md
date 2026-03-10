# Minishell

*This project has been created as part of the 42 curriculum by kzebian, abkhoder.*

---

## Description

**Minishell** is a simplified implementation of a Unix shell, inspired by bash. This project aims to deepen understanding of processes, file descriptors, system calls, and the inner workings of command-line interfaces.

The shell is capable of:
- Parsing and executing commands with arguments
- Handling pipes (`|`) for chaining commands
- Managing input/output redirections (`<`, `>`, `>>`, `<<`)
- Expanding environment variables (`$VAR`, `$?`)
- Implementing built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- Handling signals (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Managing quotes (single `'` and double `"`)

This project provides hands-on experience with low-level system programming, memory management, and the design of interactive applications.

---

## Instructions

### Prerequisites

- **Operating System**: Linux or macOS
- **Compiler**: GCC or Clang with support for C99
- **Libraries**: 
  - `readline` (for command-line editing and history)
  - Standard C library

### Compilation

1. Clone the repository:
```bash
   git clone <repository-url>
   cd minishell
```

2. Compile the project:
```bash
   make
```

   This will generate an executable named `minishell`.

3. Optional targets:
   - `make clean` - Remove object files
   - `make fclean` - Remove object files and executable
   - `make re` - Recompile the entire project

### Execution

Run the shell:
```bash
./minishell
```

You will see a prompt:
```
minishell$
```

### Usage Examples

**Simple commands:**
```bash
minishell$ echo Hello World
Hello World
minishell$ pwd
/home/user/minishell
minishell$ ls -la
```

**Pipes:**
```bash
minishell$ ls -l | grep minishell | wc -l
minishell$ cat file.txt | grep pattern | sort
```

**Redirections:**
```bash
minishell$ echo "Hello" > output.txt
minishell$ cat < input.txt
minishell$ ls >> log.txt
minishell$ cat << EOF
> Line 1
> Line 2
> EOF
```

**Environment variables:**
```bash
minishell$ echo $PATH
minishell$ export MY_VAR=value
minishell$ echo $MY_VAR
minishell$ unset MY_VAR
```

**Built-in commands:**
```bash
minishell$ cd /tmp
minishell$ pwd
minishell$ export TEST=42
minishell$ env | grep TEST
minishell$ exit 0
```

**Exit codes:**
```bash
minishell$ ls
minishell$ echo $?
0
minishell$ invalidcommand
minishell$ echo $?
127
```

---

## Features

### Mandatory Features

- ✅ **Prompt display** - Shows `minishell$` and waits for input
- ✅ **Command history** - Use arrow keys (↑/↓) to navigate history
- ✅ **Command execution** - Searches and launches executables based on PATH
- ✅ **Quote handling** - Single (`'`) and double (`"`) quotes
- ✅ **Redirections**:
  - `<` - Input redirection
  - `>` - Output redirection (truncate)
  - `>>` - Output redirection (append)
  - `<<` - Heredoc
- ✅ **Pipes** - Chain multiple commands with `|`
- ✅ **Environment variables** - Expand `$VAR` and `$?` (exit status)
- ✅ **Signal handling**:
  - `Ctrl+C` - Display new prompt
  - `Ctrl+D` - Exit shell
  - `Ctrl+\` - Do nothing
- ✅ **Built-in commands**:
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute path, and `-`)
  - `pwd` (no options)
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options or arguments)
  - `exit` (with numeric argument)

### Technical Choices

**Lexer → Parser → Expander → Executor architecture:**
1. **Lexer**: Tokenizes input into words, operators, and redirections
2. **Parser**: Builds command structures from tokens
3. **Expander**: Handles variable expansion and quote removal
4. **Executor**: Manages process creation, pipes, and redirections

**Data structures:**
- Linked lists for tokens, commands, and environment variables
- Token types for classification (WORD, PIPE, REDIRECT_IN, etc.)
- Command structure containing arguments and redirections

**Memory management:**
- Systematic cleanup after each command
- Valgrind-tested with zero memory leaks
- Proper signal handling without memory corruption

---

## Library: Libft

This project uses **libft**, a custom implementation of standard C library functions, created as part of the 42 curriculum.

### Description

Libft is a collection of commonly used functions in C, reimplemented from scratch. It includes:

**String manipulation:**
- `ft_strlen`, `ft_strdup`, `ft_strchr`, `ft_strjoin`, `ft_substr`, `ft_split`, `ft_strtrim`

**Memory management:**
- `ft_memset`, `ft_memcpy`, `ft_calloc`, `ft_bzero`

**Character checks:**
- `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`

**Conversions:**
- `ft_atoi`, `ft_itoa`, `ft_toupper`, `ft_tolower`

**Linked lists:**
- `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstlast`, `ft_lstclear`

**Additional functions for minishell:**
- `ft_strjoin_three` - Join three strings
- `ft_free_array` - Free NULL-terminated string arrays
- `ft_atoll` - Convert string to long long

### Integration

The library is compiled separately and linked with the minishell executable:
```bash
cd libft
make
cd ..
make
```

All libft functions are prefixed with `ft_` to avoid naming conflicts.

---

## Resources

### Documentation

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Linux Programming](https://mentorembedded.github.io/advancedlinuxprogramming/)
- Linux man pages:
  - `man fork`
  - `man execve`
  - `man pipe`
  - `man dup2`
  - `man waitpid`
  - `man signal`
  - `man readline`

### Articles & Tutorials

- [Writing Your Own Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [How to Parse Command Line Arguments in C](https://www.gnu.org/software/libc/manual/html_node/Parsing-Program-Arguments.html)
- [Understanding Unix/Linux File Descriptors](https://www.bottomupcs.com/file_descriptors.xhtml)
- [Pipe, Fork and Exec in C](https://tldp.org/LDP/lpg/node11.html)

### AI Usage

AI assistance (Claude) was used for the following tasks:

**Code Review & Debugging:**
- Identifying memory leaks and providing fixes
- Debugging file descriptor issues in redirections
- Resolving signal handling problems
- Fixing Norminette compliance issues

**Documentation:**
- Generating comprehensive code documentation
- Creating test cases and usage examples
- Writing function explanations and algorithm descriptions
- Structuring this README

**Learning & Explanation:**
- Understanding complex system calls (fork, execve, dup2, pipe)
- Clarifying edge cases in bash behavior
- Explaining best practices for process management
- Understanding readline library usage

**Not used for:**
- Initial project architecture design (done by team)
- Core lexer/parser logic implementation (done by team)
- Main execution flow design (done by team)

AI was used as a learning and debugging tool, but all final code was reviewed, understood, and validated by the team members.

---

## Testing

### Manual Testing

Run the shell and test various scenarios:
```bash
./minishell
```

### Memory Leak Testing
```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

Expected output:
```
LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks
```

### Automated Testing

Compare behavior with bash:
```bash
# Test in bash
echo "ls | wc -l" | bash

# Test in minishell
echo "ls | wc -l" | ./minishell
```

---

## Project Structure
```
minishell/
├── Makefile
├── README.md
├── includes/
│   ├── minishell.h
│   ├── ms_lexer.h
│   ├── ms_parser.h
│   ├── ms_exec.h
│   └── ms.builtins.h
├── src/
│   ├── main.c
│   ├── setup/
│   │   ├── ms_init.c
│   │   └── ms_env.c
│   ├── signals/
│   │   └── ms_signals.c
│   ├── lexer/
│   │   ├── lexer.c
│   │   ├── char_utils.c
│   │   ├── extract_utils.c
│   │   ├── quote_utils.c
│   │   └── token_utils.c
│   ├── parser/
│   │   ├── parser.c
│   │   ├── syntax_check.c
│   │   ├── parser_utils.c
│   │   └── build_command.c
│   ├── expander/
│   │   ├── ms_expand_vars.c
│   │   └── ms_remove_quotes.c
│   ├── executor/
│   │   ├── ms_execute.c
│   │   ├── ms_execute_cmd.c
│   │   ├── ms_pipes.c
│   │   └── ms_path.c
│   ├── io_redir/
│   │   ├── ms_redir_setup.c
│   │   └── ms_heredoc.c
│   └── Built-ins/
│       ├── ms_builtin_simple.c
│       ├── ms_builtin_complex.c
│       └── ms_builtin_exit.c
└── libft/
    ├── Makefile
    ├── libft.h
    └── *.c (all libft functions)
```

---

## Authors

- **kzebian** - Lexer, Parser, I/O Redirections, Built-ins (echo, pwd, env)
- **abkhoder** - Expander, Executor, Pipes, Built-ins (cd, export, unset, exit)

---

## Acknowledgments

- 42 Network for the project subject and educational framework
- The creators of bash and other Unix shells for inspiration
- The open-source community for documentation and resources

---

## License

This project is part of the 42 school curriculum and is intended for educational purposes only.