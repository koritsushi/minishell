# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mliyuan <mliyuan@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 15:55:31 by mliyuan           #+#    #+#              #
#    Updated: 2024/11/11 19:15:03 by mliyuan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY	=		ft_atoi.c						\
					ft_bzero.c						\
					ft_calloc.c						\
					ft_isalnum.c					\
					ft_isalpha.c					\
					ft_isascii.c					\
					ft_isdigit.c					\
					ft_isprint.c					\
					ft_itoa.c						\
					ft_memchr.c						\
					ft_memcmp.c						\
					ft_memcpy.c						\
					ft_memmove.c					\
					ft_memset.c						\
					ft_split.c						\
					ft_strchr.c						\
					ft_strdup.c						\
					ft_striteri.c					\
					ft_strjoin.c					\
					ft_strlcat.c					\
					ft_strlcpy.c					\
					ft_strlen.c						\
					ft_strmapi.c					\
					ft_strncmp.c					\
					ft_strnstr.c					\
					ft_strrchr.c					\
					ft_strtrim.c					\
					ft_substr.c						\
					ft_tolower.c					\
					ft_toupper.c					\
					ft_putchar_fd.c					\
					ft_putstr_fd.c					\
					ft_putendl_fd.c					\
					ft_putnbr_fd.c	
					
FT_PRINTF	=		ft_printf.c 					\
					ft_printchar.c 					\
					ft_printstr.c 					\
					ft_printnum.c 					\
					ft_printuint.c 					\
					ft_printhexa.c 					\
					ft_printmemory.c

GNL			=		get_next_line.c					\
					get_next_line_utils.c

BONUS		=		ft_lstnew.c 					\
					ft_lstadd_front.c				\
					ft_lstsize.c					\
					ft_lstlast.c 					\
					ft_lstadd_back.c 				\
					ft_lstdelone.c					\
					ft_lstclear.c 					\
					ft_lstiter.c 					\
					ft_lstmap.c


OBJS		= 		$(MANDATORY:%.c=%.o) 			\
					$(FT_PRINTF:%.c=%.o)			\
					$(GNL:%.c=%.o)

OBJS_BONUS	= 		$(BONUS:%.c=%.o)
NAME		= 		libft.a
CC			= 		gcc -Wall -Wextra -Werror
DEBUG		=		-ggdb3

%.o: %.c
	@$(CC) -I. -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

bonus:		$(OBJS_BONUS)
			@ar rcs $(NAME) $(OBJS_BONUS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY = all clean fclean re bonus
