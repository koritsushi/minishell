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
SRCS 		=	srcs/minishell.c 	\
				srcs/lexical.c		\
				srcs/token.c		\
				srcs/parsing.c		\
				srcs/signals.c		\
				srcs/builtins.c

OBJS		=	$(SRCS:%.c=%.o)

LIBFTDIR	=	./libft/
LIBFT		=	$(LIBFTDIR)libft.a
NAME		=	minishell.a
PROGRAM		=	minishell
COMPILE		=	gcc
CCFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-ggdb3
FSAN		=	-fsanitize=address
READINC		= 	-I/usr/include
READLIB		= 	-L/usr/lib/x86_64-linux-gnu/libreadline.a

%.o: %.c
			$(COMPILE) $(CCFLAGS) $(DEBUG) $(READINC) -I. -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
			@cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT)
			$(COMPILE) $(CCFLAGS) $(NAME) -lreadline $(READLIB) -o $(PROGRAM)

$(DEBUG):	$(LIBFT) $(OBJS)
			@cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT) 
			$(COMPILE) $(CCFLAGS) $(FSAN) $(NAME) -o $(PROGRAM) 

$(LIBFT):
			@make -C $(LIBFTDIR) all

all: 		$(NAME)

debug:		$(DEBUG)

clean:
			@rm -rf $(OBJS)

fclean:		clean
			@make fclean -C $(LIBFTDIR)
			@rm -rf $(NAME)
			@rm -rf	$(PROGRAM)

re:			fclean all

.PHONY		= all debug clean fclean re libft fsan