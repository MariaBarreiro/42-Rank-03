# **************************************************************************** #
#                                    Config                                    #
# **************************************************************************** #

MAKE = make 
SHELL = bash

# **************************************************************************** #
#                                    Names                                     #
# **************************************************************************** #

NAME = philo 

# **************************************************************************** #
#                                    Paths                                     #
# **************************************************************************** #

INC_PATH						= ./inc/

SRC_PATH						= ./src/

SRC_FILES						= main.c
SRC_FILES						+= parsing.c
SRC_FILES						+= init.c
SRC_FILES						+= utils.c
SRC_FILES						+= start.c
SRC_FILES						+= output.c
SRC_FILES						+= loop.c
SRC_FILES						+= monitoring_loop.c
SRC_FILES						+= error.c
SRC_FILES						+= free.c

SRC									= $(addprefix $(SRC_PATH), $(SRC_FILES))

OBJS_DIR						= obj
OBJS								= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRC))

# **************************************************************************** #
#                                   Compiler                                   #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g -pthread
INC             = -I $(INC_PATH)

# **************************************************************************** #
#                                   Commands                                   #
# **************************************************************************** #

RM              = rm -rf

# **************************************************************************** #
#                                    Rules                                     #
# **************************************************************************** #
 
all: $(NAME)

$(OBJS_DIR):
	@mkdir -p obj
	@echo "Objects directory created!"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)
	@echo "Compilation completed!"

clean:
	@$(RM) $(OBJS)
	@echo "Objects removed successfully!"

fclean: clean
	@$(RM) $(NAME) $(OBJS_DIR)
	@echo "Program removed successfully!"

re: fclean all
		@echo "Re-compile was successfull!"
