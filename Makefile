NAME    =   pipex
RM      =   rm -f
CC      =   cc
CFLAGS  =   -Wall -Werror -Wextra

SRCS    =   pipex.c compro.c

OBJS    =   $(SRCS:.c=.o)
LIB     =   ar rcs

all:    $(NAME)

$(NAME):	$(OBJS)
	$(LIB) -r $@ $?

%.o:%.c
	$(CC) -c $(CFLAGS) $?

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean