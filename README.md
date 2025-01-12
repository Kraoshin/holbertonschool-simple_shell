# Simple Shell Project

## Description 🕵️‍♀️
This is a basic implementation of a Unix shell in C, designed to meet specific project requirements. The shell provides a command-line interface that can execute system commands, handle environment variables, and support both interactive and non-interactive modes.

## Project Requirements ✅
The shell is implemented according to the specifications in `shell.h`, with the following key functions:
- `shell_interactive()`: Manage interactive shell mode
- `shell_no_interactive()`: Handle non-interactive command execution
- `read_line()`: Read input lines
- `parse_line()`: Tokenize input lines
- `exe_args()`: Execute parsed command arguments
- `print_env()`: Display environment variables
- Custom `getenv()` implementation
- Command path resolution with `is_a_command()`

## Supported Delimiters ⌨️
The shell uses the following token delimiters:
- Space ` `
- Tab `\t`
- Carriage return `\r`
- Newline `\n`
- Bell `\a`

## Prerequisites 🖥️💻💾
- GNU Compiler Collection (GCC)
- UNIX-like operating system (Linux, macOS)
- Standard C libraries

## Compilation 📶
To compile the shell, use the following command:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```

## Usage

### Interactive Mode ▶️
Run the shell and interact directly:
```bash
./simple_shell
simple_shell$ ls
simple_shell$ pwd
simple_shell$ exit
```

### Non-Interactive Mode ⏹️
Pipe commands or use input redirection:
```bash
echo "ls" | ./simple_shell
cat commands.txt | ./simple_shell
```

## Built-in Commands 🦺🥽
- `exit`: Terminate the shell
- `env`: Print environment variables

## Key Functionality 🔑🗝️
- Dynamic command line reading
- Tokenization of input
- Path resolution for executable commands
- Process creation and execution
- Environment variable handling

## Limitations 🛂🛃 
- Limited built-in command support
- Basic path resolution
- No advanced shell features like pipes or redirections

## File Structure 🗂️🗃️
- `shell.h`: Header file with function declarations
- `main.c`: Entry point and mode selection
- Implementation files for each core function

## Error Handling 🆘
Handles various error scenarios:
- Unknown commands
- Memory allocation failures
- Process creation errors
- Command execution errors

## Flowchart
![Flowchart](https://github.com/Kraoshin/holbertonschool-simple_shell/blob/main/Flowchart.%20Simple_Shell.drawio.png)

## Authors
- Giovanni Farias 🥷
  - GitHub: [ginftls](https://github.com/ginftls)
- Killian Kerleau 🧙‍♂️ 
  - GitHub: [Kraoshin](https://github.com/Kraoshin)

## License
MIT License

Copyright (c) 2024 Giovanni Farias, Killian Kerleau

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
