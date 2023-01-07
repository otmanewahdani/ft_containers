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

%/objs/main.o : main.cpp %.hpp
	@$(eval CONTAINER=$*)
	@test -d $(CONTAINER)/objs/ || mkdir $(CONTAINER)/objs/
	@$(CC) $(CPPFLAGS) -I$(CONTAINER)/ $(INCS) $< -o $@
	@sed 's/ft::/std::/g' $< > $(CONTAINER)/std_main.cpp
	@$(CC) $(CPPFLAGS) -I$(CONTAINER)/ $(INCS) $(CONTAINER)/std_main.cpp -o $(CONTAINER)/objs/std_main.o
	@rm -f $(CONTAINER)/std_main.cpp

clean:
	@rm -fr $(sort $(dir $(OBJ)))
	@echo -e "\e[1;31m\u26A0 all object files were removed permanently\e[0m"

fclean: clean
	@rm -f $(NAME)
	@echo -e "\e[1;31m\u26A0 full cleaning complete\e[0m"

re: fclean all
	@echo -e "\e[1;32m\u2705 all targets were re-created!\e[0m"

.PHONY: all clean fclean re vector

.SECONDEXPANSION:

$(NAME): $$(dir $$@)objs/main.o
	@$(CC) $< -o $@
	@$(eval DIR = $(dir $@))
	@$(CC) $(DIR)objs/std_main.o -o $(DIR)std_$(notdir $@)
	@if [ $(DIR) == "vector/" ]; then\
		COLOR="\e[1;35m";\
	elif [ $(DIR) == "map/" ]; then\
		COLOR="\e[1;33m";\
	elif [ $(DIR) == "stack/" ]; then\
		COLOR="\e[1;34m";\
	fi;\
	echo -e "\e[$$COLOR\u2705 $(notdir $@) was compiled successfully\e[0m"
