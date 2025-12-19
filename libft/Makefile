# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 12:21:48 by juyoukim          #+#    #+#              #
#    Updated: 2025/04/21 11:36:39 by juyoukim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c

BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c \
            ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
            ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

ifdef WITH_BONUS
    OBJ_FILES = $(OBJS) $(BONUS_OBJS)
else
    OBJ_FILES = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(AR) $(NAME) $(OBJ_FILES)

bonus:
	make WITH_BONUS=1 all

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
