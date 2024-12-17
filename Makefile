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
SRCS 		=	

OBJS		=	$(SRCS:%.c=%.o)

LIBFTDIR	=	./libft/
LIBFT		=	$(LIBFTDIR)libft.a
NAME		=	minishell.a
PROGRAM		=	minishell
COMPILE		=	gcc
CCFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-ggdb3
FSAN		=	-fsanitize=address

%.o: %.c
			$(COMPILE) $(CCFLAGS) $(DEBUG) -I. -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
			@cp $(LIBFT) $(NAME)
			ar rcs $(NAME) $(OBJS) $(LIBFT) 
			$(COMPILE) $(CCFLAGS) $(NAME) -o $(PROGRAM)

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