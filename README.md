<p align="center">
  <img src="https://github.com/Ailton-Bezerra/Ailton-Bezerra/blob/main/badges/minishelle.png" alt="minishell 42 project badge"/>
<p align="center">
<p align="center">
  <strong>101/100</strong> ✅
</p>

## Description
`Minishell` is a simplified Unix shell implementation capable of interpreting and executing commands and:
- Handle redirects (>, >> and < ) and here_doc (<<).
- Pipes.
- Signals (ctrl+c, ctrl+d and ctrl+\).
- Return correct exit codes (echo $?).
- Builtins (echo, cd, pwd, export, unset...).
- And more
  
**All functionality complies with standard Bash behavior.**

### 1️⃣ Compile the program:
```sh
make
```
- This will generate the minishell executable.

### 2️⃣ Run Minishell
```sh
./minishell
```
You will see a prompt similar to:
```sh
MINISHELL > 
```
- Now you can start typing commands..

### 3️⃣  Supported Command Examples:
```sh
MINISHELL > ls -l
MINISHELL > echo "Hello, Minishell!"
MINISHELL > pwd
MINISHELL > echo "Hello, File!" > output.txt
MINISHELL > cat < output.txt
MINISHELL > ls -l | grep minishell
MINISHELL > export VAR="Hello"
MINISHELL > echo $VAR
MINISHELL > /bin/ls
MINISHELL > unset PATH
MINISHELL > cat | cat | ls
MINISHELL > cat << a << "b" << 'c' | cat << d
...
```
---
## Contact Information
For any questions or suggestions, feel free to reach out to me via my [GitHub profile](https://github.com/Ailton-Bezerra).
