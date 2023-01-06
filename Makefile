CC = c++
CPPFLAGS = -std=c++98 -c -Wall -Wextra -Werror

SHELL = /bin/bash

INCS = -Iiterator

VECTOR_OBJ = vector/objs/main.o vector/objs/std_main.o 

OBJ = $(VECTOR_OBJ)

NAME = vector/vector

VPATH = vector

all: $(NAME)

vector: vector/vector

vector/vector: $(VECTOR_OBJ)
	$(CC) $< -o $@
	$(CC) $(lastword $^) -o vector/std_vector
	# add compilation successful in colors

%/objs/main.o : main.cpp %.hpp
	@$(eval DIR = $(dir $<))
	@test -d $(DIR)objs/ || mkdir $(DIR)/objs/
	@$(eval INCS += -I$(DIR))
	@$(CC) $(CPPFLAGS) $(INCS) $< -o $@
	@sed 's/ft::/std::/g' $< > $(DIR)std_main.cpp
	@$(CC) $(CPPFLAGS) $(INCS) $(DIR)std_main.cpp -o $(DIR)objs/std_main.o
	@rm -f $(DIR)std_main.cpp

clean:
	rm -fr $(sort $(dir $(OBJ)))

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re vector
