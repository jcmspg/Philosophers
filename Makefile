# build all
all: build bonus


# Colors
# Colors using ANSI escape codes
RED = \e[0;31m
GREEN = \e[0;32m
YELLOW = \e[0;33m
BLUE = \e[0;34m
NOCOLOR = \e[0m
CYAN = \e[0;36m



# Name of the project
NAME = philo 

# Compiler
CC = cc

# Flags -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g -pthread

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
BNS_DIR = ./bonus

# Object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Source and bonus files
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")
BNS_FILES = $(shell find $(BNS_DIR) -type f -name "*.c")

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
BNS_OBJ_FILES = $(patsubst $(BNS_DIR)/%.c,$(OBJ_DIR)/%.o,$(BNS_FILES))

# Total number of files and bar length
TOTAL_FILES := $(words $(SRC_FILES))
BAR_SYMBOL := ▓
BAR_LENGTH := 50
PROGRESS := 0

# BONUS total number of files and bar length
BONUS_FILES := $(words $(BNS_FILES))
BONUS_BAR_SYMBOL := ▓
BONUS_BAR_LENGTH := 50
BONUS_PROGRESS := 0

# Rule to compile .c into .o with progress bar
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

# Rule to compile the project
$(NAME): $(OBJ_FILES)
	@echo ""
	@echo "$(YELLOW)Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@sleep 0.2 # Just to let the loading bar finish smoothly
	@echo -n "\r\033[K" # Erase the loading bar
	@echo "$(GREEN)$(NAME) created successfully.$(NOCOLOR)"

# Rule to compile .c into .o with progress bar for bonus
$(OBJ_DIR)/%.o: $(BNS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval BONUS_PROGRESS := $(shell echo $$(($(BONUS_PROGRESS) + 1))))
	@$(eval BONUS_PERCENT := $(shell echo $$(($(BONUS_PROGRESS) * 100 / $(BONUS_FILES))))
	@$(eval BONUS_BAR := $(shell echo $$(($(BONUS_PROGRESS) * $(BONUS_BAR_LENGTH) / $(BONUS_FILES))))
	@$(eval BONUS_REST := $(shell echo $$(($(BONUS_BAR_LENGTH) - $(BONUS_BAR)))))
	@echo -n "\r\033[K"  # Clear the line
	@echo -n "$(CYAN)["  # Start the bar

	@for i in `seq 1 $(BONUS_BAR)`; do \
		echo -n $(BONUS_BAR_SYMBOL); \
	done

	@echo -n "] $(BONUS_PERCENT)% $(RED)Compiling:$(NOCOLOR) $<"
	@sleep 0.1  # Just to make the bar smooth

# Rule to compile the bonus
$(BONUS): $(OBJ_FILES)
	@echo ""
	@echo "$(YELLOW)Creating $(BONUS)..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(BONUS)
	@sleep 0.2 # Just to let the loading bar finish smoothly
	@echo -n "\r\033[K" # Erase the loading bar
	@echo "$(GREEN)$(BONUS) created successfully.$(NOCOLOR)"


# build the project
build: $(NAME)

# build the bonus
bonus: $(BONUS)

# clean the object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Object files removed.$(NOCOLOR)"
	@echo "$(GREEN)Clean done.$(NOCOLOR)"

# clean the object files and the project
fclean: clean
	@rm -f $(NAME) $(BONUS)
	@echo "$(BLUE)Project removed.$(NOCOLOR)"
	@echo "$(GREEN)Full clean done.$(NOCOLOR)"

# clean and rebuild the project
re: fclean all

# run the project
run: build
	@./$(NAME)

# run the bonus
run_bonus: bonus
	@./$(BONUS)

.PHONY: all clean fclean re run build bonus run_bonus
