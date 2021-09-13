# minishell
## This is the development repo for the 42 project : minishell.
### Project description ( As of August 2021 )
***
#### Mandatory :
- Not interpret unclosed quotes or unspecified special characters like \ or ;
- Not use more than one global variable
- Show a prompt when waiting for a new command
- A working history
- Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)
- Builtins:
    - cd with relative or absolute path
    - echo with -n
    - pwd
    - export
    - unset
    - env
    - exit
- Single and double quote support
- Redirections :
    - `<` should redirect input
    - `>` should redirect output
    -  `<<` read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
    - `>>` should redirect output with append mode
- Piping `|`
- Environment variables expansion
- $? should expand to the exit status of the most recently executed foreground pipeline.
- Signals :
    - ctrl-C print a new prompt on a newline
    - ctrl-D exit the shell.
    - ctrl-\ do nothing

#### Bonus (We did not do the bonus) :
- &&, || with parenthesis for priorities.
- the wildcard * should work for the current working directory.
- $USER 

#### Allowed functions :
`
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history, printf,
malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, unlink, execve, dup,
dup2, pipe, opendir, readdir, closedir, strerror,
perror, isatty, ttyname, ttyslot, ioctl, getenv,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum,
tgetstr, tgoto, tputs
`

### Prerequisites
***
Before starting on the project, it is mandatory to have a basic understanding of some concepts. You might or might not have learnt this in your past projects, but its always a good time to revisit them. These concepts include:
- Linked lists
- Signals in UNIX
- Processes , specifically working with `fork()`
- I/O (Input and output streams) for piping and redirections
- File descriptors for piping and redirections
- Basic libft stuff like Makefiles and headers etc.. youll need them.

If you are confident with the topics given above, great! You are in a good fit to start. Else, it would be wise by starting to grasp the concepts first.
**Study all the functions given**. Before one starts to build a house, one must know the tools.
### minishell in a nutshell
***
To put it in very simple words, this project pretty much sums up to 4 steps
- Reading input
- Expanding input
- Parsing input
- Executing whatever that is parsed.

Put them in a loop, and you can have a shell. (Or at least mimic it).

#### Reading input
First things first, we need to somehow get a working **display/prompt** on the screen like this : 
![](https://imgur.com/YpBL0hO.png)
We can achieve the above result using `readline` [man readline](https://man7.org/linux/man-pages/man3/readline.3.html)
Here is an example code snippet to get a very basic working prompt on the screen
```
    char *buff;
    while (1)
    {
        buff = readline("minishell>");
        printf("%s\n", buff);
    }
```
Every time you press enter, The text you entered in the prompt will be stored in `buff`, from here, you can do lots of amazing things.

#### Expanding input
Quite straightforward, if you have any environment variables like `$PATH` with value `/bin`, naturally `echo $PATH` should expand to `echo /bin`. Wont need any hard time to implement if your libft is good

#### Parsing input
The example shown above just simple reads the input and prints them out on a screen. But before we do any actual program executing or further processing, we have to parse that input into things that the other programs can understand called "tokens".

For example, for command
`echo hello world 1234`, `echo` is the command that we want to execute, `hello world 1234` are the arguments that we want to execute the command with.

It is the parsers job to convert these strings and tell the executor what to do. There are many ways to get this done, one of them is using something similar to a linked list.

With a linked list, our visualized parsed result will look something like this:
![](https://i.imgur.com/HCfCSR3.png)

Each linked list node is a token and they will combine into a list of tokens.
With a valid token list, we can now pass it to the executor!

#### Executing the tokens
Once again, there are many ways to do this but they all generally follow the same sequence:
1. Start to loop through the token list
2. If the current token is a command, get all the following arguments and call the helpers to execute command
3. Go to the next token.

And to visualize those steps : 
1. ![im sry if this img expired](https://i.imgur.com/1ll7w1E.png)
2. ![im sry if this img expired](https://i.imgur.com/fsskZkl.png)
3. ![im sry if this img expired](https://i.imgur.com/L7neJ2F.png)
4. ![im sry if this img expired](https://i.imgur.com/5cPiqxw.png)
5. ![im sry if this img expired](https://i.imgur.com/KrUqWEZ.png)

After all the data is extracted, we can so a `ft_strcmp` on the comamnd variable and see what function we should call. And thats pretty much it, the rest is up to you!

### Conclusion
The stuff you saw above was just a **simple example** to get your feet wet if you dont know where to start, I might include other stuff like piping and redirection later if I feel like it, but so far I hope this helped you in understanding the project better. Feel free to look around!

[jng](https://github.com/neosizzle) handles the display, expanding, parsing, heredoc, executing, signals

[dtan](https://github.com/DylonTan) handles task management, builtins, piping, redirection, environment variables, files
