NAME = lexer
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	src/lexer.c \
		src/crud.c \
		src/free.c \
		src/operators_utils.c \
		src/words_utils.c \
		src/states/handle_dquote_state.c \
		src/states/handle_normal_state.c \
		src/states/handle_squote_state.c \
		src/states/state_machine.c \

OBJS = $(SRCS:.c=.o)
INCLUDES = -I includes -I libft
LIBFT = libft/libft.a

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(NAME)

$(NAME):	$(OBJS)
			@$(MAKE) -C libft > /dev/null
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
			@echo "✅ lexer compilado correctamente."

# --------------------------------------------------------------
# 🛠 Compilar cada archivo fuente
# --------------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo "🔧 Compilado: $<"

# --------------------------------------------------------------
# 🧹 Limpieza
# --------------------------------------------------------------

clean:
	@rm -rf $(OBJS) > /dev/null
	@$(MAKE) -C libft fclean > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME) > /dev/null
	@$(MAKE) -C libft fclean > /dev/null
	@echo "🧼 Todo limpio."

re: fclean all

.PHONY: all clean fclean re libft