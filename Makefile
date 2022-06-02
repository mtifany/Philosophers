NAME	=	philo

BONUS_NAME	=	philo_bonus

HEADER	=	philo.h

BONUS_HEADER =	philo_bonus.h

SRC_F	=	philo.c utils.c init.c eating.c check-mate.c

BONUS_SRC_F	=	philo_bonus.c utils_bonus.c init_bonus.c eating_bonus.c

SRC_DIR	=	./philos

BONUS_SRC_DIR =	./philos_bonus

SRCS	=	$(addprefix ${SRC_DIR}/,${SRC_F})

BONUS_SRCS	=	$(addprefix ${BONUS_SRC_DIR}/,${BONUS_SRC_F})

OBJS	=	${SRCS:.c=.o}

BONUS_OBJS	=	${BONUS_SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

%.o			:	%.c ${SRC_DIR}/${HEADER}
				${CC} ${CFLAGS} $< -c -o $@

.PHONY		:	all re clean fclean

${NAME}		:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

bonus		:
				make all NAME=${BONUS_NAME} OBJS="${BONUS_OBJS}" \
 										SRC_DIR=${BONUS_SRC_DIR} HEADER=${BONUS_HEADER}

clean		:
				rm -rf ${OBJS} ${BONUS_OBJS}

fclean		:	clean
				rm -rf ${NAME} ${BONUS_NAME}

all			:	${NAME}

re			:	fclean ${NAME}
