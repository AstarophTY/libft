# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::     #
#    Makefile                                           :+:      :+:    :+:     #
#                                                     +:+ +:+         +:+       #
#    By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+          #
#                                                 +#+#+#+#+#+   +#+             #
#    Created: 2026/05/25 00:00:00 by sgil--de          #+#    #+#              #
#    Updated: 2026/05/25 00:00:00 by sgil--de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := libft.a

SRCS_DIR    := srcs
OBJS_DIR    := .objs
DEPS_DIR    := .deps
INC_DIR     := includes

CTYPE       := ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
               ft_toupper ft_tolower
MEM         := ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr ft_memcmp \
               ft_calloc
STRING      := ft_strlen ft_strlcpy ft_strlcat ft_strchr ft_strrchr ft_strncmp \
               ft_strnstr ft_strdup ft_substr ft_strjoin ft_split ft_strtrim \
               ft_strmapi ft_striteri ft_atoi ft_itoa
PUT         := ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd
LIST        := ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
               ft_lstdelone ft_lstclear ft_lstiter ft_lstmap
GNL         := get_next_line
PRINTF      := ft_printf ft_putchar ft_putstr ft_puthex ft_putaddr ft_putnbr

NAMES       := $(CTYPE) $(MEM) $(STRING) $(PUT) $(LIST) $(GNL) $(PRINTF)
TOTAL       := $(words $(NAMES))

VPATH       := $(SRCS_DIR)/ctype:$(SRCS_DIR)/mem:$(SRCS_DIR)/string:\
$(SRCS_DIR)/put:$(SRCS_DIR)/list:$(SRCS_DIR)/gnl:$(SRCS_DIR)/printf

OBJS        := $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(NAMES)))
DEPS        := $(addprefix $(DEPS_DIR)/, $(addsuffix .d, $(NAMES)))

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I$(INC_DIR)
DEPFLAGS    = -MMD -MP -MF $(DEPS_DIR)/$*.d
AR          := ar rcs
RM          := rm -rf

GREEN       := \033[0;32m
CYAN        := \033[0;36m
YELLOW      := \033[0;33m
BOLD        := \033[1m
DIM         := \033[2m
RESET       := \033[0m
CLEAR       := \033[2K\r

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@printf "$(CLEAR)$(GREEN)$(BOLD) $(NAME) ready$(RESET) "
	@printf "$(DIM)($(TOTAL) objects)$(RESET)\n"

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR) $(DEPS_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@
	@cur=$$(ls -1 $(OBJS_DIR)/*.o 2>/dev/null | wc -l); \
	tot=$(TOTAL); \
	full=$$((cur * 26 / tot)); i=0; \
	printf "$(CLEAR)$(CYAN)$(BOLD)libft$(RESET) ["; \
	printf "$(GREEN)"; while [ $$i -lt $$full ]; do printf "#"; i=$$((i+1)); done; \
	printf "$(DIM)"; while [ $$i -lt 26 ]; do printf "-"; i=$$((i+1)); done; \
	printf "$(RESET)] %3d%%  $(YELLOW)%s$(RESET)" $$((cur * 100 / tot)) "$*"

$(OBJS_DIR) $(DEPS_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJS_DIR) $(DEPS_DIR)
	@printf "$(YELLOW)libft: objects cleaned$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)libft: $(NAME) removed$(RESET)\n"

re: fclean all

norm:
	@norminette $(SRCS_DIR) $(INC_DIR)

-include $(DEPS)

.PHONY: all clean fclean re norm
