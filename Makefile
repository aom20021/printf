NAME = libftprintf.a
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -crs
OBJS = $(FILES:.c=.o)
FILES = ft_printf.c ft_unsigned.c ft_hex.c


all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	@$(AR) $(NAME) $(OBJS)
%.o : %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@
clean :
	@make -C libft fclean
	@$(RM) $(OBJS)
fclean : clean
	@make -C libft fclean
	@$(RM) $(NAME)
re : fclean all
.PHONY : all clean fclean re