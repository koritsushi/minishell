# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 15:04:47 by mliyuan           #+#    #+#              #
#    Updated: 2024/11/11 15:04:47 by mliyuan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# __________detect os____________
UNAME_S := $(shell uname -s)

# __________all files____________
SRCS 		=	srcs/expansion.c						\
				srcs/expansion_quote.c					\
				srcs/expansion_brace_utils_count.c		\
				srcs/expansion_brace_utils.c			\
				srcs/expansion_brace_utils2.c			\
				srcs/expansion_brace.c					\
				srcs/expansion_shell_exit-status.c		\
				srcs/expansion_shell.c					\
				srcs/token.c							\
				srcs/token_utils.c						\
				srcs/token_utils_filler.c				\
				srcs/token_utils_malloc.c				\
				srcs/token_utils_count.c				\
				srcs/token_utils_extract.c				\
				srcs/token_utils_extract2.c				\
				srcs/token_utils_datatype.c				\
				srcs/token_utils_split.c				\
				srcs/parsing.c							\
				srcs/parsing_utils_check.c				\
				srcs/parsing_utils_vars.c				\
				srcs/parsing_utils_vars_name.c			\
				srcs/parsing_utils_vars_check.c			\
				srcs/parsing_utils_vars_write.c			\
				srcs/utils_skip.c						\
				srcs/utils_free.c						\
				srcs/utils_free2.c						\
				srcs/signals.c							\
				srcs/builtins.c							\
				srcs/builtins_utils.c					\
				srcs/env.c 								\
				srcs/env2.c								\
				srcs/env_print.c						\
				srcs/env_utils.c						\
				srcs/minishell_utils.c					\
				srcs/minishell_utils_execute.c			\
				srcs/minishell_utils_list.c				\
				srcs/minishell_utils_list2.c			\
				srcs/execution.c						\
				srcs/execution_cmd.c					\
				srcs/execution_cmd_utils.c				\
				srcs/execution_process.c				\
				srcs/execution_process2.c				\
				srcs/execution_parent_process_utils.c	\
				srcs/execution_child_process_utils.c	\
				srcs/execution_heredoc.c				\
				srcs/minishell.c 						\
				srcs/_debug.c							\
#				srcs/main-test-token_split.c			\
#				srcs/parsing_utils_replace.c			\
#				srcs/token_utils_operator.c				\
#				srcs/token_utils_truncate.c				\

OBJS		=	$(SRCS:%.c=%.o)

LIBFTDIR	=	./libft/
LIBFT		=	$(LIBFTDIR)libft.a
NAME		=	minishell.a
PROGRAM		=	minishell
COMPILE		=	gcc
CCFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-ggdb3
FSAN		=	-fsanitize=address
READINC		= 	-I/usr/include./
HEADER		=	includes/minishell.h \
				includes/token.h \
				includes/parsing.h \
				includes/expansion.h \
				includes/env.h	\
				includes/builtins.h \
				includes/execution.h \
				includes/signals.h
#READLIB		= 	-L/usr/lib/x86_64-linux-gnu/libreadline.a

# __________readlib paths configs__________
ifeq ($(UNAME_S), Linux)
	READLIB	:= 	-L/usr/lib/x86_64-linux-gnu/libreadline.a
else ifeq ($(UNAME_S), Darwin)
	READLIB	:=
endif

%.o: %.c	$(HEADER)
			$(COMPILE) $(CCFLAGS) $(DEBUG) $(READINC) -I. -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
			@cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT)
			$(COMPILE) $(CCFLAGS) $(NAME) -lreadline $(READLIB) -o $(PROGRAM)
#			$(COMPILE) $(CCFLAGS) $(NAME) -lreadline -o $(PROGRAM)


$(DEBUG):	$(LIBFT) $(OBJS)
			@cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT) 
			$(COMPILE) $(CCFLAGS) $(FSAN) $(NAME) -lreadline $(READLIB) -o $(PROGRAM) 

$(LIBFT):
			@make -C $(LIBFTDIR) all

all: 		$(NAME)

debug:		$(DEBUG)

clean:
			@make clean -C $(LIBFTDIR)
			@rm -rf $(OBJS)

fclean:		clean
			@make fclean -C $(LIBFTDIR)
			@rm -rf $(NAME)
			@rm -rf	$(PROGRAM)

re:			fclean all

.PHONY		= all debug clean fclean re libft fsan