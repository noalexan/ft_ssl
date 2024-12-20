NAME=ft_ssl

LIB_STATIC=libft_ssl.a
LIB_SHARED=libft_ssl.so

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

LIB_OBJ=$(addprefix src/, md5.o sha256.o utils.o)

.PHONY: all
all: $(LIB_SHARED) $(LIB_STATIC) $(NAME)

.PHONY: shared
shared: $(LIB_SHARED)

.PHONY: static
static: $(LIB_STATIC)

.PHONY: install
install:
	install -m644 ./.zsh/site-functions/_ft_ssl /usr/share/zsh/site-functions/_ft_ssl
	install -m644 ./include/md5.h /usr/local/include
	install -m644 ./include/sha256.h /usr/local/include
	install -m755 $(LIB_STATIC) /usr/lib64
	install -m755 $(LIB_SHARED) /usr/lib64
	install -m755 $(NAME) /usr/local/bin

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
