CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = tst.c get_next_line.c
OBJS = $(SRCS:.c=.o)

# BONUS_SRCS = bonus.c
# BONUS_OBJS = $(BONUS_SRCS:.c=.o)

NAME = cub3D
HEADER = cub3D.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# NAME_BONUS = bonus
# HEADER_BONUS = bonus.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# bonus: $(BONUS_OBJS)
# 	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME_BONUS)

# %_bonus.o: %_bonus.c $(HEADER_BONUS)
# 	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
# 	# rm -f $(OBJS_B)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus