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
	// char str[] = "cmd1 -f -g < infile |cmd2 'some flags' | no | cmd3 > outfile"; //ok
	// char str[] = "cmd1 c < cmd1"; //pending
	// char str[] = "grep cat < infile infile2 infile3"; //pending
	char str[] = "grep cat <\n"; //pending
	// char str[] = "< infile cmd1 -f -g"; //ok
	// char str[] = "< infile cmd1 -f -g | cmd2 'some flags' | no | cmd3 > outfile"; //nok
	// char str[] = "";
	// char del[] = " \t\n\v\f\r";

	char **res = ft_split_shell(str, "|"); //count
	char **infile = ft_split_shell(res[0], "<"); //if true, +1
	int i = 0;
	while (res && res[i])
		i++;
	char **outfile = ft_split_shell(res[--i], ">"); //if true, +1
	i = 0;
	while (res[i])
		i++;
	if (infile[1])
		i++;
	if (outfile[1])
		i++;
	printf("count=%d+1\n", i);


	// debug_print(res);
	// printf("\n");
	debug_print(infile);
	debug_print(outfile);

	free(res);
	free(infile);
	free(outfile);
	// printf("%d\n", has_pipes("|", res));

	// t_token	lst;
	// get_cmd_line(str, &lst);

	// free_all(&lst);
}
