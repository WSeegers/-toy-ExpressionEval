NAME = eval_expr
CC = clang++
CFLAGS = -g -std=c++98 -Werror -Wall -Wextra
INC = -Iinclude
# LIB = -L 

OS := $(shell uname)

SRC := $(shell find ./src -type f -name "*.cpp")
OBJ := $(SRC:%.cpp=%.o)
DEP := $(OBJ:%.o=%.d)

all : $(NAME) author

author :
	@echo "wseegers" > author

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LFLAGS) $(LIB)

%.o : %.cpp
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(OBJ) $(DEP)

fclean : clean
	rm -f $(NAME)

re : fclean all

run : all
	./$(NAME)

.PHONEY : all clean  fclean  re
