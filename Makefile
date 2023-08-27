NAME	=	minishell
NAME_FS	=	minishell_fs

#SOURCES AND DIRECTORIES
SOURCES			=	minishell.c exit.c builtin.c free.c free2.c reset.c pwd.c env.c envlvl.c list.c export.c export_next.c parsing.c parsing_arg.c parsing_length.c \
					unset.c unset_next.c echo.c cd.c cd_child.c cd_parse.c util.c env_null.c access.c command.c command2.c error.c redirection.c redirection_util.c \
					dup.c pipe.c heredoc.c wait.c signals.c parsing_buffer.c parsing_space.c check_redirection.c parser_pipe.c parsing_rm_quotes.c expansion.c expansion2.c expansion3.c expansion4.c \
					signal2.c env_null2.c heredoc2.c init.c minishell_cmd.c parsing_arg2.c exec.c cd2.c

SOURCES_BONUS 	=

HEADER			= minishell.h

HEADER_BONUS	=

DIR				= srcs/
DIR_BONUS		= bonus/srcs/
DIR_OBJ			= Object/
DIR_OBJ_SRCS	= Object/srcs/
DIR_OBJ_BONUS	= Object/bonus/
DIR_OBJ_FS		= Object/fs/
LIBFTDIR		= Libft
DIR_INCLUDE		= includes/
DIR_INCLUDE_BONUS	= bonus/includes

#DEPENDENCY
DEPEND	=	${LIBFTDIR}/include/libft.h
DEPEND	+=	$(addprefix ${DIR_INCLUDE}, ${HEADER})
DEPEND_BONUS = ${LIBFTDIR}/include/libft.h
DEPEND_BONUS += $(addprefix bonus/includes/, ${HEADER_BONUS})

#COMPILATOR AND FLAG
CC		= clang
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -Iincludes
RLFLAGS = -lreadline
LIBFLAG	= -L./${LIBFTDIR} -lft
FLAGSSANITIZE	= -g3 -fsanitize=address
MAKEFLAGS	+=	--no-print-directory

#COMMAND
RM		= rm -f

# COLOR
ifneq (,$(findstring xterm,${TERM}))
	BLACK			:= $(shell tput -Txterm setaf 0)
	RED				:= $(shell tput -Txterm setaf 1)
	GREEN			:= $(shell tput -Txterm setaf 2)
	YELLOW			:= $(shell tput -Txterm setaf 3)
	LIGHTPURPLE		:= $(shell tput -Txterm setaf 4)
	PURPLE			:= $(shell tput -Txterm setaf 5)
	BLUE			:= $(shell tput -Txterm setaf 6)
	WHITE			:= $(shell tput -Txterm setaf 7)
	BOLD 			:= $(shell tput bold)
	RESET			:= $(shell tput -Txterm sgr0)
else
	BLACK			:= ""
	RED				:= ""
	GREEN			:= ""
	YELLOW			:= ""
	LIGHTPURPLE		:= ""
	PURPLE			:= ""
	BLUE			:= ""
	WHITE			:= ""
	BOLD			:= ""
	RESET			:= ""
endif

#OBJECTS
OBJS	= $(addprefix $(DIR_OBJ_SRCS),${SOURCES:.c=.o})
${DIR_OBJ_SRCS}%.o: ${DIR}%.c ${DEPEND}
	@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

OBJS_FS	= $(addprefix $(DIR_OBJ_FS),${SOURCES:.c=.o})
${DIR_OBJ_FS}%.o: ${DIR}%.c ${DEPEND}
		@${CC} ${CFLAGS} ${IFLAGS} ${FLAGSSANITIZE} -c $< -o $@

OBJS_BONUS	= $(addprefix $(DIR_OBJ_BONUS),${SOURCES_BONUS:.c=.o})
${DIR_OBJ_BONUS}%.o: ${DIR_BONUS}%.c ${DEPEND_BONUS}
		${CC} ${CFLAGS} -I${DIR_INCLUDE_BONUS} -c $< -o $@

all: libft
	@mkdir -p ${DIR_OBJ_SRCS}
	@echo "${LIGHTPURPLE}${BOLD}Building ${WHITE}${BOLD}${NAME}${RESET}"
	@make $(NAME)

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${CFLAGS} -o ${NAME} ${RLFLAGS} ${LIBFLAG}
	@echo "${LIGHTPURPLE}${BOLD}Compilation done for ${GREEN}${NAME}${RESET}"

fs: libft
	@mkdir -p ${DIR_OBJ_FS}
	@echo "${RED}${BOLD}[DEBUG MODE] ${LIGHTPURPLE}${BOLD}Building ${WHITE}${BOLD}${NAME}${RESET}"
	@make ${NAME_FS}

${NAME_FS}: ${OBJS_FS}
	@${CC} $^ ${CFLAGS} ${FLAGSSANITIZE} -o ${NAME_FS} ${RLFLAGS} ${LIBFLAG}
	@echo "${RED}${BOLD}[DEBUG MODE] ${LIGHTPURPLE}${BOLD}Compilation done for ${GREEN}${NAME}${RESET}"

bonus: fclean libft
	@mkdir -p ${DIR_OBJ_BONUS}
	@echo "${PURPLE}${BOLD}[BONUS] ${LIGHTPURPLE}Building ${WHITE}${NAME}${RESET}"
	@make build_bonus

build_bonus: ${OBJS_BONUS}
	@${CC} ${OBJS_BONUS} ${CFLAGS} -o ${NAME} ${RLFLAGS} ${LIBFLAG}
	@echo "${PURPLE}${BOLD}[BONUS] ${LIGHTPURPLE}Compilation done for ${GREEN}${NAME}${RESET}"

libft:
		@make -C ${LIBFTDIR}

clean:
		@${RM} -rf ${OBJS} ${DIR_OBJ}
		@make -C ${LIBFTDIR} clean
		@echo "${YELLOW}${BOLD}clean ${WHITE}${NAME}${RESET}"

fclean: clean
		@${RM} ${NAME} ${NAME_FS}
		@make -C ${LIBFTDIR} fclean
		@echo "${YELLOW}${BOLD}fclean ${WHITE}${NAME}${RESET}"

cleanlib:
		@make -C ${LIBFTDIR} cleanobjs

re:		fclean all

.PHONY: all clean fclean re fs build_fs libft cleanlib name bonus build_bonus
