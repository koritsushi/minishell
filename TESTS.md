### block signal when running child process for cmd
    pending -> in progress

### heredoc function
    done -> required further testing 

### Pipex execution migrating to minishell await
    done -> required further testing

### singular cmd
    done -> required further testing

### multiple cmd
    partially working -> required further testing

### singular export function
    done -> tested -> working -> required further testing

### multiple export function with pipe
    pending

### multiple export function with pipe and cmd
    pending

### multiple pipe with no cmd with redirection in and out only
    pending     

### multiple pipe with partial cmd
    pending

### adding block signal to parent process when execute a program 
    pending -> in progress

### centralized free function for all
    pending -> done for t_exec exec, t_env env_var, t_token lst -> required futher check -> done -> no double free or memory leaks


### echo
	echo '-n      bla'
	echo "-n      'bla"
	echo -n "     'bla"


### export
	export 1rt yu op
	export rt_1 ui | var=55

### env
	var=11 export 1rt yu op
	v=1 v=2 v=3
	1v=zzzzz
	var=1 1var=4
	var=1 >out
	var=1 <in >out
	<in var=1 >out

### shell-expansion
	echo $var" hello"


### infile redir
	<infile'<'bla <in2
	<infile'>'bla <in2
	  <    infile cmd -f -g << infile2 -k | >>out
	<in>o
	<in< in2
	<in cmd<in2< in3 cmd2
	cmd<in <in2
	cmd<in cmd2<in2


### outfile redir
	>o< in
	>out <in<in2 cmd1 <in3 cmd2 >out2
	>out cmd1 >o2 cmd2 <in cmd3 >o3
	cmd1 -f -g >> out -k
	cmd1 -f -g > out -k| cmd2 > o2
	cmd1 -f -g > o1 > o2 >> o3 -p
		> 	outfile
	>>    outfile cmd -f -g
	  >    outfile cmd -f -g >> outfile2 -h

### syntax-error
	cmd < in <in2 |     | cmd2<in <in2|cmd3
	<<<in4
	|
	<<
	>>
	<|