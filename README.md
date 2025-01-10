# minishell
recreate a shell with major function of a shell in linux/unix/macos

1.0 What is a shell?
- a shell is simply a macro processor that executes commands. The term macro processor means functionality where text and symbols are expanded to create larger expressions. 
- Shells offer features geared specifically for interactive use rather than to augment the programming language. These interactive features include job control, command line editing, command history and aliases. Each of these features is described in this manual. 

1.1 allowed function
	readline
	rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
	add_history
	printf
	malloc, free
	write
	access, open, read, close
	fork
	wait, waitpid, wait3, wait4
	signal, sigaction, sigemptyset, sigaddset
	kill
	exit
	getcwd
	chdir
	stat, lstat, fstat
	unlink
	execve, dup, dup2, pipe
	opendir, readdir, closedir
	strerror
	perror, isatty, ttyname, ttyslot, ioctl,
	getenv, 
	tcsetattr, tcgetattr, tgetent, tgetflag,
	tgetnum, tgetstr, tgoto, tputs