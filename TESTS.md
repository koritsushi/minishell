# Signals
## block signal when running child process for cmd
pending -> in progress - done

	ctrl-c
	ctrl-\
ctrl-c will return an exit status code

ctrl-d is EOF, not signal so handle by checking text return by readlin() == null then exit and free minishell program 

## adding block signal to parent process when execute child process
this is when executing a child process from any parent program
fork()

    status: pending -> in progress -> done and tested

# heredoc
## test case
	<< h1 
	<< h1 cat
	<< h1 << h2 << h3 cat
	<< h1 << h2 << h3 cat | << h1 << h2 > out
	<< h1 << h2 << h3 cat | << h1 << h2 > out | << h4 cat

# Command 
## No Shell Builtin cmd such as zsh, bash etc unless state path
## singular cmd 
	ls
	cat
	wc
## singular cmd with option

	ls -l
	ls -la
	cat -e
	wc -w
	and etc..

	This can work
	awk 'BEGIN { print "Square of", 1, "is", 1*1 }'
	
	Not handle for this, due to pdf state dont handle ';'
	awk 'BEGIN { for(i=1; i<=10; i++) print "Square of", i, "is", i*i }' 

# Pipe
## multiple cmd and Pipe
	ls | cat | cat | wc -a
	cat | cat | cat | ls
	ls | wc -a | cat 

## multiple pipe with no cmd with redirection in and out only
    << h1 << h2 << h3 > out | << h1 << h2 > out1 | << h4 

## multiple pipe with partial cmd
	

# Export
## singular arg export function
	-> shows in export
	export env1
	-> shows in export and env builtin call
	export env2=	
    export env=123	

## multiple arg export function with pipe
    export var1 var2 var3
	export var1= var2= var3=
	export var1=123 var2=123 var3=123

# Unset
## singular arg unset function
	unset env1
	-> does not work as unset takes the envp name only
	unset env2=
	unset env1=123

##  multiple arg unset function
	unset var1 var2 var3

## multiple export function with pipe and cmd
only happen in child process but handling is up to project requirement and user own defined action
	
	export var=123 | var=123 | cat

# memory leaks
### centralized free function for all

    pending -> 
	done for t_exec exec, t_env env_var, t_token lst -> 
	required futher check -> 
	done 
no double free or memory leaks

# Builtins Test Case
## echo
	echo '-n      bla'
	echo "-n      'bla"
	echo -n "     'bla"
	var=123 echo '90 90'

## export
	export 1rt yu op
	export rt_1 ui | var=55
	export 'y='zzz 1var2 var3

## env
	var=11 export 1rt yu op
	v=1 v=2 v=3
    echo bla| var=123
	var=123 | echo $var
	1v=zzzzz
	var=1 1var=4
	var=1 >out
	var=1 <in >out
	var=1<>out
	<in var=1 >out
	< infile var=123 > outfile
	< infile	< infile2   |var=123

# Parsing && Expansion
## shell-expansion
	echo $var" hello"
	echo $var'$var'$var "$var'$var yu'
	echo '$r'$var

## quote-removal
	'a'b"c'dd'”
	'rr$r'$var$r


## infile redir
	<infile'<'bla <in2
	<infile'>'bla <in2
	  <    infile cmd -f -g << infile2 -k | >>out
	<in>o
	<in< in2
	<in cmd<in2< in3 cmd2
	cmd<in <in2
	cmd<in cmd2<in2


## outfile redir
	>o< in
	>out <in<in2 cmd1 <in3 cmd2 >out2
	>out cmd1 >o2 cmd2 <in cmd3 >o3
	cmd1 -f -g >> out -k
	cmd1 -f -g > out -k| cmd2 > o2
	cmd1 -f -g > o1 > o2 >> o3 -p
		> 	outfile
	>>    outfile cmd -f -g
	  >    outfile cmd -f -g >> outfile2 -h

## syntax-error
	cmd < in <in2 |     | cmd2<in <in2|cmd3
	<<<in4
	|
	<<
	>>
	<|