#include "includes/minishell.h"

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	// char str[] = "< infile cmd1 'some flags' | no | cmd3 > outfile";
	// char str[] = "hello cat's cat meow "; // 2
	// char str[] = "'cat meow  ' yes loop"; // 2
	// char *str = ft_strdup("cat's meow  ' yes loop"); // 2
	// char str[] = "'''"; // 1
	// char str[] = "'' '"; // 2
	// char str[] = "' cat meow";
	// char del[] = " \t\n\v\f\r";

	
	/*-------------------ft_split_shell-------------------*/
	// char **res = ft_split_shell(str , "|");
	// int i = 0;
	// while (res[i])
	// 	printf("%s\n", res[i++]);

	// int x = 0;
	// int y = count_chr(str, del, &x);
	// printf("%d, f=%d\n", y, x);

	// int y = 0;
	// while (str[0])
	// {
	// 	y = count_chr(str, del, &x);
	// 	printf("y=%d f=%d\n", y, x);
	// 	str++;
	// }

	/* ________________________vars_test________________________ */
	// char str[] = "var";
	// char str[] = "var =123";
	// char str[] = "var= 123";
	// char str[] = "var=| 123";
	// char str[] = "var=123";
	char str[] = "var=123 cmd1 | cmd2 var=123 | var=123";
	char str[] = "var=123 ^var=5 var=8";
	char str[] = "var=99 ^var=123 cmd1 v=1 | cmd2 var=123 | var=123";
	char str[] = "cmd1| var=123";
	// char str[] = "var      = 123";
	// char str[] = "echo $var\" hello\"";
	char str[] = "echo '$r'$var";
	char str[] = "'rr$r'$var$r";
	char str[] = "$var\" hello\"";
	// char str[] = "var=123 | echo $var";
	// char str[] = "echo hello | var=cmd2| var=123 | cmd3";
	// char str[] = "echo hello | cmd2| var=123 | cmd3";
	// char str[] = "echo hello | cmd2| var=123 ";
	// char str[] = "var=123<        > outfile";
	// char str[] = "< infile var=123 > outfile";
	// char str[] = "< infile	< infile2   |var=123";
	// char str[] = "< infile	< infile2 	var=123 vars=9090";
	// char str[] = "	  > outfile > 	out2 	> out3	   var=123";
	// char str[] = "	  > outfile >out2>out3	   var=123";
	// char str[] = "       	var=123 < infile";
	// char str[] = "               var=123 < infile";
	// char str[] = "var=123 < infile <infile2 > outfile";
	// char str[] = "var=123 < infile > outfile > outfile2";
	// char str[] = "var=123 < infile <in2";
	// char str[] = "var=\"12'3\" var1='9\"090' > outfile >out2";
	// char str[] = "var=\"12'3\" > outfile >out2";
	// char str[] = "var=123 var1='90> 90'  	> 	 outfile >out2";
	// char str[] = "var=123 var1='90> 	90'  	";
	// char str[] = "var1='90> 90'";
	// char str[] = "echo '90 90'";
	// char str[] = "'90 90'";
	// char str[] = "var=123 var1='90 90'";
	// char str[] = "var=123 cmd1 '90 90'";
	// char str[] = "awk 'BEGIN { x = 1 print x }'";
	// char str[] = "var=\"123 's\"   	var=9020pq     ";
	// char str[] = "var=90/ 90 vars=9020";
	// char str[] = "vars='90\"\"s 90' var='9020'";
	// char str[] = "varp=\"123 's\" 	var='9090\"1'";
	// /******!!!******/char str[] = "var1="123 's" 	var2='9090"1'";
	// char str[] = "var=\"123 's\" 	vars=90901 var='yo\"yo'";
	// char str[] = "var="123 's" 	vars=90901 var='yo"yo'";
	// char str[] = "awk 'BEGIN { x=1 print x }' var=\"12'34\"";
	// char str[] = "awk'BEGIN{x=1printx}' | cmd1 | cmd2";
	// char str[] = "awk 'BEGIN { x=1 '\"print x }' var=12\"34";
	// char str[] = "vars='opop' awk ' BEGIN { x=1 print x }'";
	// char str[] = "awk ' BEGIN { x=1 print x }' vars='opop'";
// /* ******* */char str[] = "awk 'BEGIN { x = 1 print x }'    | 	var=1234 ";
	// char str[] = "var=1234| awk 'BEGIN { x=1 print x }' ";
	// char str[] = "var=1234 0var=tt > outfile";
	// char str[] = "var=1234 0var=tt < infile";
	// char str[] = "awk \"BEGIN { x = 1 print x }\"        ";

	/* ________________________syntax_error_test________________________ */
	// char str[] = "cmd1 c < infile1 < infile2|\t\n\v\f\r| cmd2 <infile3 <infile4 | cmd3";
	// char str[] = "cmd1 c < infile1 < infile2|  			| cmd2 <infile3 <infile4 | cmd3";
	// char str[] = "cmd1 c < infile1 < infile2|cmd2 <infile3 <infile4 ||";
	// char str[] = "<<<infile4";
	// char str[] = "cmd1 c < infile1 << infile2 cmd2 <infile3|>> infile4";
	// char str[] = "cmd1 c < infile1 << infile2 cmd2 < infile3 | < infile4";
	// char str[] = "cmd1 c < infile1 < infile2 cmd2 <infile3 < >infile4";
	// char str[] = "cmd1 c < infile1 < infile2 cmd2 <infile3 |>> infile4";
	// char str[] = "cmd1 c < infile1 < infile2 && cmd2 <infile3 ";
	// char str[] = "|";
	// char str[] = ">>";
	// char str[] = "<<";
	// char str[] = "<<|";
	// char str[] = "<|";

	/* ________________________cmd_combo_tests________________________ */
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 'some flags' | no | cmd3 > outfile -a -b |>> outfile2 cmd -f -g";
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 | cmd3 > outfile -a -b | > outfile2 cmd -f -g";
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 | cmd3 > outfile -a -b | > outfile2 >outfile3 cmd -f -g";
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 | cmd3 > outfile -a -b | >> outfile2 >outfile3";
// 	char str[] = "cmd1 c < infile1 < infile2| cmd2 <infile3 <infile4 | cmd3";
// 	char str[] = "cmd1 c |< infile1 < infile2 cmd2| cmd3";
// 	char str[] = "cmd1 -c < infile2 | cmd3> outfile1   ";
// char str[] = "cmd1 c |< infile1 <<infile2 | cmd3> outfile1   ";
// 	char str[] = "cmd1 c |< infile1 < infile2 | cmd3 > outfile1 | cmd4 > outfile2";
	// char str[] = "cmd1 c |< infile1 < infile2 | cmd2 > outfile1 >outfile2 -k | cmd3 | cmd4 > outfile3 >outfile4 -f -g >outfile5 -k";
// 	char str[] = "cmd1 c |< infile1 | cmd2 c |< infile1 < infile2 | cmd3";
// /*----here--*/char str[] = "grep cat < infile < infile1 < infile2 infile3 << infile4 infile5";
// 	char str[] = "grep cat |<infile1 cmd1";
// /*********/char str[] = "cmd1 << infile infile2 infile3 > out -k -l";// HIGHLIGHT

// 	/* ________________________outfiles_tests________________________ */
// /*********/char str[] = "cmd1 -f -g >> out -k";// HIGHLIGHT
			// char str[] = "cmd1 -f -g > outfile -k| cmd2 > outfile2";
// 	char str[] = "cmd1 -f -g > outfile1 > outfile2 >> out3 -p";
// 	char str[] = "	> 	outfile";
// 	char str[] = ">>    outfile cmd -f -g";
// 	char str[] = "  >    outfile cmd -f -g >> outfile2 -h";
	// char str[] = "  <    infile cmd -f -g << infile2 -k | >>out";

// 	/* ________________________infiles_tests________________________ */
// /*********/char str[] = "< infile cmd1 -f -g > out >>out2 -k";// HIGHLIGHT
// 	char str[] = "<< infile cmd1 -f -g > out";
// 			char str[] = "< infile < infile2     << infile3 | cmd1 |cmd2 |cmd3 ";
	// char str[] = "< infile | < infile2 |   < infile3 cmd1  <infile2 << infile5 cmd2 -f -g |cmd2 |cmd3 ";
// 	char str[] = "|  < infile  | cmd1 |cmd2 |cmd3 ";
	// char str[] = "<infile1 <infile2 | cmd1 | cmd2 | cmd3 > outf1 >out2>>out3";

	// char str[] = "< infile <infile2 <<infile3 cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile koko lala";
// 	char str[] = "< infile cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile koko lala";
// 	char str[] = "< infile cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile >> outfile2 koko lala";
// 	char str[] = "  < infile cmd1 -f -g -k | cmd2 'some flags' | no | cmd3 >> outfile koko lala";
// char str[] = "  < infile cmd1 -f -g infile2 | cmd2 'some flags";
// 	char str[] = "  <  infile   ";
	// char str[] = "echo $VAR";
// 	char str[] = "cat";
	// char del[] = " \t\n\v\f\r";

	// char **res = ft_split_shell(str, "|");
	// char **infile = ft_split_shell(res[0], "<"); //if true, +1
	// int i = 0;
	// while (res && res[i])
	// 	i++;
	// char **outfile = ft_split_shell(res[i-1], ">"); //if true, +1

	// /*check: if infile[1] is splittable by space, if infile[1++]: check if splittable by space*/
	// int x = 1;
	// int flag = 1;

	// if (res[0][0] == '<' && !infile[1] && !is_target(res[1], '<') && has_more_str(infile[0]))
	// 	i++;
	// while (infile && infile[x])
	// {
	// 	if (!flag && res[0][0] != '<')
	// 	{
	// 		i++;
	// 		flag = 1;
	// 	}
	// 	i++;
	// 	x++;
	// 	flag = 0;
	// }
	// /*	outfile count	*/
	// if (outfile[1])
	// 	i++;
	// printf("count=%d+1\n", i);
	// printf("------\nres:\n");
	// debug_print(res);

	// printf("------\ninfile:\n");
	// debug_print(infile);
	// printf("------\noutfile:\n");
	// debug_print(outfile);

	// free(res);
	// free(infile);
	// free(outfile);
	// // printf("%d\n", has_pipes("|", res));

	/*---------------------truncate_string_infile-----------------------*/
	// char	*new = truncate_last_infile(str);
	// char	*new = truncate_input(str);
	// printf("ret=%s\n\n", new);

	/*---------------------get_malloc_size-----------------------*/
	// int count = 0;
	// char *new = truncate_last_infile(str);
	// get_malloc_size(&count, new);
	// printf("trunc=%s\ncount=%d+1\n", new, count);
	
	/*---------------------count_chr_debug-----------------------*/
	// int flag = 0;
	// /*debug*/printf("count_chr=%d\n", count_chr(str, " \t\n\v\f\r", &flag));
	
	/*---------------------count_str_debug-----------------------*/
	int	flag = 0;
	/*debug*/printf("str:%s\n", str);
	/*debug*/printf("count_str:%d, chr:%d\n", count_str(str, " \"\t\n\v\f\r"), count_chr(str, " \"\t\n\v\f\r", &flag));
	
	/*---------------------syntax_check-----------------------*/
	// /*debug*/printf("entry:%s\n", str);
	// check_syntax(str);
	
	/*---------------------ft_strncmp_test-----------------------*/
	// char str[] = "vars=9090";
	// /*debug*/printf("%d\n", ft_strncmp(str, "var", ft_strlen(str)));
	// /*debug*/printf("%s\n", ft_strnstr(str, "var", 4));

	/*---------------------get_envs-----------------------*/
	// t_token	lst;
	// lst.vars = NULL;
	
	// if (check_syntax(str))
	// {
	// 	get_variable(&lst.vars, str);
	// }
	// if (lst.vars && lst.vars->content)
	// {
	// 	// /*debug*/printf("yayaya:%s\n", (char *)lst.vars->content);
	// 	debug_print_lst(lst.vars);
	// 	ft_lstclear(&lst.vars, free);
	// }
	// printf("updated_str=\033[92m%s\033[0m.\n", str);

	/*---------------------get_cmd_line-----------------------*/
	// t_token	lst;
	// /*parsing_check*/
	// get_cmd_line(str, &lst);
	// free_all(&lst);

	/*---------------------cmd_expansion-----------------------*/
	// t_token	lst;
	// lst.vars = NULL;
	
	// if (check_syntax(str))
	// {
	// 	get_variable(&lst.vars, str);
	// 	if (get_cmd_line(str, &lst, lst.vars))
	// 		free_all(&lst);
	// }
	// if (lst.vars && lst.vars->content)
	// {
	// 	// /*debug*/printf("yayaya:%s\n", (char *)lst.vars->content);
	// 	debug_print_lst(lst.vars);
	// 	ft_lstclear(&lst.vars, free);
	// }

	/*---------------------lst_test-----------------------*/
	// t_list text;
	// text.content = "hello mama";
	// printf("%s\n", (char*)text.content);
}
