NAME	= libft.a

#SOURCE AND DIRECTORY
DIR		= srcs/
SOURCES_LIB	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c \
				ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
				ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c \
				ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr.c ft_putchar.c \
				ft_putstr.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
				ft_lstsize.c ft_split_str.c ft_split_str_next.c \


DIR_GNL	= Get-Next-Line/
SOURCES_GNL	=	get_next_line.c get_next_line_utils.c \

DIR_PTF	= Printf/
SOURCES_PRINTF	=	conversion_func.c conversion_func_next.c fillflag.c itoa_base.c postflag.c \
					postflag_next.c printf.c print_result.c print_width.c width_and_preci.c \

SRCS	= ${addprefix ${DIR},${SOURCES_LIB}}
SRCS	+= ${addprefix ${DIR_GNL},${SOURCES_GNL}}
SRCS	+= ${addprefix ${DIR_PTF},${SOURCES_PRINTF}}

DIR_OBJ_SRCS	= Object/srcs/
DIR_OBJ 		= Object/

#COMPILATOR AND FLAG
CC		= gcc
LIBCOMP	= ar rc
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -Iinclude
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

OBJS	= $(addprefix $(DIR_OBJ_SRCS),${SOURCES_LIB:.c=.o})
OBJS	+= $(addprefix $(DIR_OBJ_SRCS),${SOURCES_GNL:.c=.o})
OBJS	+= $(addprefix $(DIR_OBJ_SRCS),${SOURCES_PRINTF:.c=.o})
${DIR_OBJ_SRCS}%.o: ${DIR}%.c
		@${CC} ${CFLAGS} ${IFLAGS} -c $^ -o $@
${DIR_OBJ_SRCS}%.o: ${DIR_GNL}%.c
		@${CC} ${CFLAGS} ${IFLAGS} -c $^ -o $@
${DIR_OBJ_SRCS}%.o: ${DIR_PTF}%.c
		@${CC} ${CFLAGS} ${IFLAGS} -c $^ -o $@

all:
		@make $(NAME)

${NAME}:
	@mkdir -p ${DIR_OBJ_SRCS}
	@echo "${LIGHTPURPLE}${BOLD}Building ${WHITE}${NAME}${RESET}"
	@make name


name: ${OBJS}
		@${LIBCOMP} ${NAME} ${OBJS}
		@echo "${GREEN}${BOLD}${NAME} ${RESET}${BOLD}created${RESET}"


clean:
		@echo "${YELLOW}${BOLD}clean ${WHITE}libft${RESET}"


fclean:
		@${RM} ${NAME}
		@echo "${YELLOW}${BOLD}fclean ${WHITE}libft${RESET}"

cleanobjs:
		@${RM} ${NAME}
		@${RM} -rf ${DIR_OBJ}
		@echo "${YELLOW}${BOLD}full clean object ${WHITE}libft${RESET}"

re:		fclean all

.PHONY: all clean fclean re bonus cleanobjs name
