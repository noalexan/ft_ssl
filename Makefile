NAME=ft_ssl

CFLAGS=-I./include -Wall -Wextra # -Werror
LDLIBS=-L. -lssl

OBJ=$(addprefix src/, main.o subcommand.o)

LIB_STATIC=libssl.a
LIB_SHARED=libssl.so

LIB_OBJ=$(addprefix src/, md5.o sha256.o)

.PHONY: all
all: $(NAME)

.PHONY: shared
shared: $(LIB_SHARED)

.PHONY: static
static: $(LIB_STATIC)

$(NAME): $(LIB_STATIC) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

$(LIB_SHARED): $(LIB_OBJ)
	$(CC) -shared -o $@ $(LIB_OBJ)

$(LIB_STATIC): $(LIB_OBJ)
	$(AR) rcs $@ $(LIB_OBJ)

.PHONY: clean
clean:
	@$(RM) -v $(OBJ) $(LIB_OBJ)

.PHONY: fclean
fclean: clean
	@$(RM) -v $(LIB_SHARED) $(LIB_STATIC) $(NAME)

.PHONY: re
re: fclean all
