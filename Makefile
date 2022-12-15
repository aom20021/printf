NAME = libftprintf.a
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -crs
OBJS = $(FILES:.c=.o)
FILES = ft_printf.c

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	@$(AR) $(NAME) $(OBJS)
clean :
	@make -C libft fclean
	@$(RM) $(OBJS)
fclean : clean
	@make -C libft fclean
	@$(RM) $(NAME)
re : fclean all
.PHONY : all clean fclean re