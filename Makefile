# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 18:20:34 by yuuko             #+#    #+#              #
#    Updated: 2024/07/21 17:09:34 by tforster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

# **************************************************************************** #
#    Dependencies                                                              #
# **************************************************************************** #

LIBS		:=	\
	lib/libft/libft.a \
	lib/MLX42/build/libmlx42.a \

INCS		:=	\
	lib/libft/include \
	lib/MLX42/include \
	src \

# **************************************************************************** #
#    Sources                                                                   #
# **************************************************************************** #

SRC_DIR		:= src

SRCS		:= \
	main.c \
	color/color.c \
	ctx/ctx.c \
	ctx/image.c \
	ctx/event.c \
	common/error.c \
	graph_lib/angle.c \
	graph_lib/2d_transform.c \
	graph_lib/bresenham.c \
	menu/menu.c \
	game/map.c \
	game/player.c \
	game/draw_player.c \
	game/movement.c \
	ray_casting/ray_casting.c \

SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #

BUILD_DIR	:= build

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= cc
# CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		:= -g3

CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS)))
LDLIBS		:=	-lft -lmlx42 -ldl -lglfw -pthread -lm

# **************************************************************************** #
#    Misc                                                                      #
# **************************************************************************** #

RM			:= rm -f
MAKEFLAGS	+= --no-print-directory

RED			:= $(shell tput setaf 1)
GREEN		:= $(shell tput setaf 2)
YELLOW		:= $(shell tput setaf 3)
BLUE		:= $(shell tput setaf 4)
MAGENTA		:= $(shell tput setaf 5)
CYAN		:= $(shell tput setaf 6)
WHITE		:= $(shell tput setaf 7)
ERROR		:= $(shell tput setab 1)$(WHITE)
SUCCESS		:= $(shell tput setab 2)$(WHITE)
WARNING		:= $(shell tput setab 3)$(WHITE)
INFO		:= $(shell tput setab 4)$(WHITE)
RESET		:= $(shell tput sgr0)
CLEAR		:= $(shell tput cuu1; tput el)
TITLE		:= $(YELLOW)$(basename $(NAME))$(RESET)

# 1: action, 2: target, 3: color
define message
	$(info [$(TITLE)] $(3)$(1)$(RESET) $(2))
endef

ifdef WITH_DEBUG
	TITLE	+= $(MAGENTA)debug$(RESET)
	CFLAGS	+= -g3
else
	CFLAGS	+= -O3
endif

ifdef WITH_SANITIZER
	TITLE	+= $(MAGENTA)sanitizer$(RESET)
	CFLAGS	+= -fsanitize=address
endif

# **************************************************************************** #
#    Targets                                                                   #
# **************************************************************************** #

all: $(NAME) ## Build the program

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(call message,CREATED,$(NAME),$(BLUE))

$(LIBS): lib/MLX42/build
	$(MAKE) -C $(@D) -j4

lib/MLX42/build:
	cmake lib/MLX42 -B lib/MLX42/build

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(call message,CREATED,$(basename $(notdir $@)),$(GREEN))

clean: ## Remove all generated object files
	for lib in $(dir $(LIBS)); do $(MAKE) -C $$lib clean; done
	$(RM) -r $(BUILD_DIR)
	$(call message,DELETED,$(BUILD_DIR),$(RED))

fclean: clean ## Remove all generated files
	for lib in $(dir $(LIBS)); do $(MAKE) -C $$lib fclean; done
	$(RM) $(NAME)
	$(call message,DELETED,$(NAME),$(RED))

re: ## Rebuild the program
	$(MAKE) fclean
	$(MAKE) all

run: ## Run the program
	./$(NAME)

update: ## Update the repository and its submodules
	git stash
	git pull
	git submodule update --init
	git stash pop

info.%: ## Print the target recipe (usage: make info.<target>)
	$(MAKE) --dry-run --always-make $* | grep -v "info"

print.%: ## Print the value of a variable (usage: make print.<variable>)
	$(info '$*'='$($*)')

help: ## Show this message
	echo "Usage: make [<name>=<value>...] [target...]"
	echo
	echo "Targets:"
	grep -E '^[a-zA-Z_.%-]+:.*?## .*$$' Makefile \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "%2s$(CYAN)%-20s$(RESET) %s\n", "", $$1, $$2}'

.PHONY: all clean fclean re help
.SILENT:
.IGNORE: clean fclean run update help
.DELETE_ON_ERROR:

-include $(DEPS)
