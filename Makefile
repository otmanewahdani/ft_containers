CC = c++
CPPFLAGS = -std=c++98 -c -Wall -Wextra -Werror

ifeq ($(shell uname), Darwin)
SHELL = /bin/zsh
else
SHELL = /bin/bash
endif

INCS = -Iiterator -Itype_traits -Ialgorithm -Ivector/incs -Iutility

VECTOR_OBJ = vector/objs/main.o vector/objs/std_main.o 

STACK_OBJ = stack/objs/main.o stack/objs/std_main.o 

MAP_OBJ = map/objs/main.o map/objs/std_main.o 

PAIR_OBJ = map/objs/pairTests.o map/objs/std_pairTests.o

OBJ = $(VECTOR_OBJ) $(STACK_OBJ) $(MAP_OBJ) $(PAIR_OBJ)

NAME = vector/vector stack/stack map/map

VPATH = vector stack map

VPATH := $(VPATH) $(addsuffix /incs, $(VPATH))

TEST = test-vector test-stack test-map

all: $(NAME)

vector: vector/vector

stack: stack/stack

map: map/map

map/objs/main.o: AVL.hpp AVL.tpp List.hpp List.tpp Queue.hpp Queue.tpp map_iterator.hpp map_iterator.tpp

vector/objs/main.o: vec_iterator.hpp

stack/objs/main.o: vector.hpp vector.tpp

%/objs/main.o : %/main.cpp %.hpp %.tpp
	@$(eval CONTAINER=$*)
	@test -d $(CONTAINER)/objs/ || mkdir $(CONTAINER)/objs/
	@sed 's/ft::/std::/g' $< > $(CONTAINER)/std_main.cpp
	@$(CC) $(CPPFLAGS) -I$(CONTAINER)/incs/ $(INCS) $< -o $@
	@$(CC) $(CPPFLAGS) -I$(CONTAINER)/incs/ $(INCS) $(CONTAINER)/std_main.cpp -o $(CONTAINER)/objs/std_main.o
	@rm -f $(CONTAINER)/std_main.cpp

clean:
	@rm -fr $(sort $(dir $(OBJ)))
	@echo -e "\e[1;31m\u26A0 all object files were removed permanently\e[0m"

fclean: clean
	$(eval DIR=$(dir $(NAME)))
	$(eval PROGRAM=$(addprefix std_, $(notdir $(NAME))))
	@rm -f $(NAME)
	@rm -f $(join $(DIR),$(PROGRAM))
	@for dir in $(DIR); do \
		rm -f $${dir}stdOutput $${dir}ftOutput $${dir}diff_results; \
	done
	@echo -e "\e[1;31m\u26A0 all test files were removed permanently\e[0m"
	@echo -e "\e[1;31m\u26A0 full cleaning complete\e[0m"

re: fclean all
	@echo -e "\e[1;32m\u2705 all targets were re-created!\e[0m"

.PHONY: all clean fclean re vector stack map $(TEST)

map/objs/pairTests.o: map/pairTests.cpp incs/pairTests.hpp
	@test -d map/objs/ || mkdir map/objs/
	@sed 's/ft::/std::/g' $< > map/std_pairTests.cpp
	@$(CC) $(CPPFLAGS) $(INCS) -Imap/incs $< -o $@
	@$(CC) $(CPPFLAGS) $(INCS) -Imap/incs map/std_pairTests.cpp \
		-o map/objs/std_pairTests.o
	@rm -f map/std_pairTests.cpp

.SECONDEXPANSION:

map/map: EXTRA_OBJ = map/objs/pairTests.o map/objs/std_pairTests.o

$(NAME): $$(dir $$@)objs/main.o $$(EXTRA_OBJ)
	@$(CC) $< $(firstword $(EXTRA_OBJ)) -o $@
	@$(eval DIR = $(dir $@))
	@$(CC) $(DIR)objs/std_main.o $(lastword $(EXTRA_OBJ)) \
		-o $(DIR)std_$(notdir $@)
	@if [[ $(DIR) == "vector/" ]]; then\
		COLOR="\e[1;35m";\
	elif [[ $(DIR) == "map/" ]]; then\
		COLOR="\e[1;33m";\
	elif [[ $(DIR) == "stack/" ]]; then\
		COLOR="\e[1;34m";\
	fi;\
	echo -e "\e[$$COLOR\u2705 $(notdir $@) was compiled successfully\e[0m"

$(TEST): CONT = $(lastword $(subst -, ,$@))

$(TEST): $$(CONT)/$$(CONT) 
	@rm -f "$(CONT) execution time"
	@./$< > $(CONT)/ftOutput
	@./$(CONT)/std_$(CONT) > $(CONT)/stdOutput
	@cat "$(CONT) execution time"
	@diff $(CONT)/ftOutput $(CONT)/stdOutput > $(CONT)/diff_results; \
	FAIL="\e[1;31m\u26A0";\
	SUCCESS="\e[1;32m\u2705";\
	if [[ ! -s $(CONT)/diff_results ]]; \
	then \
		echo -e "$${SUCCESS} ft::$(CONT) passed the tests!\e[0m";\
	else\
		echo -e "$${FAIL} ft::$(CONT) failed the tests!\e[0m" ; \
	fi
	@rm -f "$(CONT) execution time"
