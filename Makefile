UNAME = $(shell uname -s)
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -g -ggdb3 -Ireadline-dghonyan/include/ #-fsanitize=address
PREFIX = "${shell find ${HOME} -name readline-dghonyan 2>/dev/null}"
LIBFT = -lft -L libft
OBJDIR = obj
SRCS = $(wildcard *.c)
TEMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(TEMP))
READLINE = -lreadline

ifneq ($(UNAME), Linux)
	READLINE += -L readline-dghonyan/lib/
endif

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: mkdir lib $(NAME)

mkdir:
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(READLINE) $(LIBFT) -o $(NAME)

lib:
	cd libft && make 

clean:
	rm -rf $(OBJDIR)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

readline:
	cd readline-master && ./configure --prefix=$(PREFIX)/ && make clean && make && make install

.PHONY: all clean fclean re lib readline mkdir
