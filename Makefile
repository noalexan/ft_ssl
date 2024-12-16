NAME=ft_ssl

LIB_STATIC=libssl.a
LIB_SHARED=libssl.so

LIB_DIR=./lib

INCLUDE_LIBFT=$(LIB_DIR)/libft
LIB_LIBFT=$(LIB_DIR)/libft/libft_bonus.a

CFLAGS=-fPIC -I./include $(addprefix -I, $(INCLUDE_LIBFT)) -Wall -Wextra # -Werror

LDFLAGS=# -fsanitize=address
LDLIBS= \
	$(addprefix -L, \
		$(foreach I, $(LIB_STATIC) $(LIB_LIBFT), $(shell dirname $(I))) \
	) \
	-Wl,-Bstatic \
	$(addprefix -l, \
		$(foreach I, $(filter %.a, $(LIB_STATIC) $(LIB_LIBFT)), \
			$(patsubst lib%.a, %, $(shell basename $(I))) \
		) \
	) \
	-Wl,-Bdynamic

OBJ=$(addprefix src/, main.o subcommand.o file.o $(addprefix subcmd_, $(addsuffix .o, md5 sha256)))

LIB_OBJ=$(addprefix src/, md5.o sha256.o)

.PHONY: all
all: $(LIB_SHARED) $(LIB_STATIC) $(NAME)

.PHONY: shared
shared: $(LIB_SHARED)

.PHONY: static
static: $(LIB_STATIC)

$(NAME): $(LIB_LIBFT) $(LIB_STATIC) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

$(LIB_SHARED): $(LIB_OBJ)
	$(CC) -shared -o $@ $(LIB_OBJ)

$(LIB_STATIC): $(LIB_OBJ)
	$(AR) rcs $@ $(LIB_OBJ)

$(LIB_LIBFT):
	make -C $(shell dirname $(LIB_LIBFT)) bonus

.PHONY: clean
clean:
	@$(RM) -v $(OBJ) $(LIB_OBJ)

.PHONY: fclean
fclean: clean
	@$(RM) -v $(LIB_SHARED) $(LIB_STATIC) $(NAME)

.PHONY: re
re: fclean all
