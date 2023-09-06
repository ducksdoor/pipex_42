DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m

NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SOURCE = pipex.c children.c rute.c utils.c


%.o: %.c
				@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(GREEN)$< $(DEF_COLOR)"
				@${CC} ${CFLAGS} -c $< -o $@

OBJS = ${SOURCE:.c=.o}

all: ${NAME}
	
${NAME}: ${OBJS}
				@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(GREEN) libft $(DEF_COLOR)"
				@make bonus -sC ./libft
				@$(CC) $(SOURCE) -o $(NAME) -Llibft -lft
				@echo "\n$(GREEN) Created $(NAME) ✓$(DEF_COLOR)\n"
				@echo "$(YELLOW)    _       _       _"
				@echo " __(.)<  __(.)>  __(.)=    Cuak!"
				@echo " \___)   \___)   \___)$(DEF_COLOR)"

clean:
				@make clean -C ./libft
				@${RM} ${OBJS}
				@echo "\n${GRAY} ◎ $(RED)All objects cleaned successfully ${GRAY}◎$(DEF_COLOR)\n"

fclean:
				@make fclean -C ./libft
				@${RM} ${NAME}
				@${RM} ${OBJS}
				@echo "\n${GRAY} ◎ $(RED)All objects and executable cleaned successfully${GRAY} ◎$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re

