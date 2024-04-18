SHELL		= /bin/sh

NAME		:= philosophers


CC			= cc
CFLAGS		:= -Wextra -Wall -Werror -g3 -fsanitize=thread

## LIBS ##
LIBFT		:= ./lib/libft
LIBS		= ${LIBFT}/libft.a -lreadline

## HEADERS ##
HEADER_SRCS	:=	philosophers.h message.h structures.h
HEADER_DIR	:=	inc/
HEADERS		= -I $(HEADER_DIR) -I ${LIBFT}

## SOURCE ##
SRCS		:= main.c \
	input.c \
	simulation_init.c forks_exchange.c\
	philos_threads_routine.c main_threads_routine.c\
	print_message_in_real_time.c utils_simulation.c\

SRC_DIR		:= src/
BUILD_DIR	:= build/
SRCS		:= $(addprefix $(SRC_DIR),$(SRCS))
OBJS		:= $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRCS))

## TARGET ##
all		: libft $(NAME)
	@echo "${BBLU}Build successful!${NC}"

libft	:
	@echo "${YEL}Building ${YEL}libft...${NC}"
	@${MAKE} -C ${LIBFT}
	@echo "${YEL}libft ${YEL}build complete.${NC}"

$(NAME)	: $(OBJS)
	@echo "${BBLU}Creating executable: $(NAME)${NC}"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "${YEL}$(NAME) ${YEL}build complete.${NC}"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HEADER_DIR), $(HEADER_SRCS))
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "${BGRE}Compiling:${NC} $(notdir $<) \
		${YEL}for ${YEL}$(NAME)${NC} "

clean	:
	@echo "$(RED)Cleaning$(NC)"
	rm -f $(OBJS)
	${MAKE} -C ${LIBFT} fclean

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all, clean, fclean, re, libft
.DEFAULT_GOAL := all

## Colors ##
RED		:= \033[0;31m
BRED	:= \033[1;31m
GRE		:= \033[0;32m
BGRE	:= \033[1;32m
YEL		:= \033[0;33m
BYEL	:= \033[1;33m
BLU		:= \033[0;34m
BBLU	:= \033[1;34m
MAG		:= \033[0;35m
BMAG	:= \033[1;35m
CYA		:= \033[0;36m
BCYA	:= \033[1;36m
BWHI	:= \033[1;37m
NC		:= \033[0m
