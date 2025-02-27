#include "includes/token.h"

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

	/*-------------------split_with_pipes-------------------*/
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 'some flags' | no | cmd3 > outfile -a -b |> outfile2 cmd -f -g";
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 | cmd3 > outfile -a -b | > outfile2 cmd -f -g";
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 | cmd3 > outfile -a -b | > outfile2 >outfile3 cmd -f -g";
// /*********/char str[] = "cmd1 -f -g < infile infile2 |cmd2 | cmd3 > outfile -a -b | > outfile2 >outfile3";
	// char str[] = "cmd1 c < infile1 < infile2| cmd2 <infile3 <infile4 | cmd3";
	// char str[] = "cmd1 c |< infile1 < infile2 cmd2| cmd3";
	// char str[] = "cmd1 -c < infile2 | cmd3> outfile1   ";
// char str[] = "cmd1 c |< infile1 < infile2 | cmd3> outfile1   ";
	char str[] = "cmd1 c |< infile1 < infile2 | cmd3 > outfile1 | cmd4 > outfile2";
	// char str[] = "cmd1 c |< infile1 < infile2 | cmd2 > outfile1 >outfile2 -k | cmd3 | cmd4 > outfile3 >outfile4 -f -g >outfile5 -k";
	// char str[] = "cmd1 c |< infile1 | cmd2 c |< infile1 < infile2 | cmd3";
// /*------*/char str[] = "grep cat < infile < infile1 < infile2 infile3 < infile4 infile5";
	// char str[] = "grep cat |<infile1 cmd1";
// /*********/char str[] = "cmd1 < infile infile2 infile3 > out -k -l";// HIGHLIGHT

/* if str[0] !+ '<' */
/* split infiles */

	/* ________________________outfiles_tests________________________ */
// /*********/char str[] = "cmd1 -f -g > out -k";// HIGHLIGHT
			// char str[] = "cmd1 -f -g > outfile -k| cmd2 > outfile2";
	// char str[] = "cmd1 -f -g > outfile1 > outfile2 >out3 -p";
	// char str[] = "> 	outfile";
	// char str[] = ">    outfile cmd -f -g";
	// char str[] = ">    outfile cmd -f -g >outfile2 -h";

	/* ________________________infiles_tests________________________ */
// /*********/char str[] = "< infile cmd1 -f -g > out >out2 -k";// HIGHLIGHT
	// char str[] = "< infile cmd1 -f -g";
			// char str[] = "< infile < infile2 < infile3 | cmd1 |cmd2 |cmd3 ";
	// char str[] = "< infile | < infile2 |< infile3   < infile5 cmd1 -f -g |cmd2 |cmd3 ";
	// char str[] = "|< infile  | cmd1 |cmd2 |cmd3 ";
	// char str[] = "< infile <infile2 <infile3 cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile koko lala";
	// char str[] = "< infile cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile koko lala";
	// char str[] = "< infile cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile > outfile2 koko lala";
	// char str[] = "  < infile cmd1 -f -g infile2 | cmd2 'some flags' | no | cmd3 > outfile koko lala";
// char str[] = "  < infile cmd1 -f -g infile2 | cmd2 'some flags";
	// char str[] = "  < infile";
	// char str[] = "echo $VAR";
	// char str[] = "cat";
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
	
	/*---------------------get_cmd_line-----------------------*/
	t_token	lst;
	get_cmd_line(str, &lst);
	free_all(&lst);

	/*---------------------lst_test-----------------------*/
	// t_list text;
	// text.content = "hello mama";
	// printf("%s\n", (char*)text.content);
}
