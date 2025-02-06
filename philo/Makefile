# build all
all: build

# Colors
RED = \e[0;31m
GREEN = \e[0;32m
YELLOW = \e[0;33m
BLUE = \e[0;34m
NOCOLOR = \e[0m
CYAN = \e[0;36m

# Names of the executables
NAME = philo

# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror -g -pthread

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj

# Object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Source and bonus files
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Total number of files and progress bar details
TOTAL_FILES := $(words $(SRC_FILES))
BAR_SYMBOL := ▓
BAR_LENGTH := 50
PROGRESS := 0
BONUS_PROGRESS := 0

# Rule to compile .c into .o for mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval PROGRESS := $(shell echo $$(($(PROGRESS) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(PROGRESS) * 100 / $(TOTAL_FILES)))))
	@$(eval BAR := $(shell echo $$(($(PROGRESS) * $(BAR_LENGTH) / $(TOTAL_FILES)))))
	@$(eval REST := $(shell echo $$(($(BAR_LENGTH) - $(BAR)))))
	@echo -n "\r\033[K"  # Clear the line
	@echo -n "$(CYAN)["  # Start the bar
	@for i in `seq 1 $(BAR)`; do \
		echo -n $(BAR_SYMBOL); \
	done
	@echo -n "] $(PERCENT)% $(RED)Compiling:$(NOCOLOR) $<"
	@sleep 0.1  # Just to make the bar smooth


# Rule to create the philo executable for mandatory
$(NAME): $(OBJ_FILES)
	@echo ""
	@echo "$(YELLOW)Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@sleep 0.2 # Just to let the loading bar finish smoothly
	@echo -n "\r\033[K" # Erase the loading bar
	@echo "$(GREEN)$(NAME) created successfully.$(NOCOLOR)"


# build the mandatory project
build: $(NAME)

# clean the object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"
	@echo "$(GREEN)Clean done.$(NOCOLOR)"

# clean the object files and the project executables
fclean: clean
	@rm -f $(NAME) 
	@echo "$(BLUE)Project removed.$(NOCOLOR)"
	@echo "$(GREEN)Full clean done.$(NOCOLOR)"

# clean and rebuild the project
re: fclean all


.PHONY: all clean fclean re
