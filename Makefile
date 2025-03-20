# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymoutaou <ymoutaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 15:47:42 by ymoutaou          #+#    #+#              #
#    Updated: 2025/03/05 15:04:37 by ymoutaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler and Flags
CC      := gcc
CFLAGS  := -Wall -Wextra  -fPIC
LDFLAGS := -shared
RM      := rm -f
AR      := ar rcs

# Directories and Files
SRC_DIR := src
OBJ_DIR := obj
INCLUDE := include
TEST_DIR := tests
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Check HOSTTYPE, set it if not defined
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Library Names
NAME := libft_malloc
SO_NAME := $(NAME)_$(HOSTTYPE).so
SYMLINK := $(NAME).so

# Test Files
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_BIN := test_malloc

# Default target
all: $(SO_NAME) symlink

# Create Object Directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

# Create shared library
$(SO_NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Create symbolic link
symlink: $(SO_NAME)
	ln -sf $(SO_NAME) $(SYMLINK)

# Build the test executable
$(TEST_BIN): $(TEST_SRC) $(SO_NAME)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(TEST_SRC) -L. -lft_malloc -Wl,-rpath=. -o $(TEST_BIN)

# Run tests
test: $(TEST_BIN)
	./$(TEST_BIN)

# Clean object files
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)
	$(RM) $(TEST_BIN)

# Clean all generated files
fclean: clean
	$(RM) $(SO_NAME) $(SYMLINK)

# Recompile everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re test symlink
