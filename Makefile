NAME=ft_ssl

LIB_DIR=./lib
LIBFT_DIR=$(LIB_DIR)/libft

CFLAGS=-I./include -I$(LIBFT_DIR) -Wall -Wextra # -Werror
LDFLAGS=-fPIC
LDLIBS=-L. -L$(LIBFT_DIR) -Wl,-Bstatic -lssl -lft_bonus -Wl,-Bdynamic

OBJ=$(addprefix src/, main.o subcommand.o file.o)

LIB_STATIC=libssl.a
LIB_SHARED=libssl.so

LIB_OBJ=$(addprefix src/, md5.o sha256.o)

.PHONY: all
all: $(LIB_SHARED) $(LIB_STATIC) $(NAME)

.PHONY: shared
shared: $(LIB_SHARED)

.PHONY: static
static: $(LIB_STATIC)

$(NAME): $(LIBFT_DIR)/libft_bonus.a $(LIB_STATIC) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

$(LIB_SHARED): $(LIB_OBJ)
	$(CC) -shared -o $@ $(LIB_OBJ)

$(LIB_STATIC): $(LIB_OBJ)
	$(AR) rcs $@ $(LIB_OBJ)

$(LIBFT_DIR)/libft_bonus.a:
	make -C $(LIBFT_DIR) bonus

.PHONY: clean
clean:
	@$(RM) -v $(OBJ) $(LIB_OBJ)

.PHONY: fclean
fclean: clean
	@$(RM) -v $(LIB_SHARED) $(LIB_STATIC) $(NAME)

.PHONY: re
re: fclean all
