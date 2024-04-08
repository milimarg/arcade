##
## EPITECH PROJECT, 2024
## strace
## File description:
## Makefile
##

SRC	=	Sources/Core.cpp \
		Sources/LibraryHandler.cpp \
		Sources/Time.cpp \
		Sources/Texts/Text.cpp	\
		Sources/EventInfo.cpp	\
		main.cpp

OBJ = $(SRC:.cpp=.o)

NAME	=	arcade

CPPFLAGS	=	-g -std=c++20 -ldl -fno-gnu-unique -I./Includes -fPIC -lssl -lcrypto

all: $(NAME)

$(NAME): core	games	graphicals

core:	$(OBJ)
	mkdir -p lib
	make -C MainMenu
	g++ $(OBJ) -o $(NAME) $(CPPFLAGS)

%.o:	%.cpp
	g++ -c $< -o $@ $(CPPFLAGS)

games:
	mkdir -p lib
	make -C	Snake
	make -C	SolarFox
	make -C	Pacman
	make -C	Doom
	make -C	Nibbler

graphicals:
	mkdir -p lib
	make -C	SDL2
	make -C	NCurses
	make -C OpenGL
	make -C SFML

clean:
	make clean -C SDL2
	make clean -C Snake
	make clean -C MainMenu
	make clean -C SolarFox
	make clean -C Doom
	make clean -C NCurses
	make clean -C Pacman
	make clean -C OpenGL
	make clean -C SFML
	make clean -C Nibbler
	rm -f $(OBJ)

fclean: clean
	make fclean -C SDL2
	make fclean -C Snake
	make fclean -C MainMenu
	make fclean -C SolarFox
	make fclean -C Doom
	make fclean -C NCurses
	make fclean -C Pacman
	make fclean -C OpenGL
	make fclean -C SFML
	make fclean -C	Nibbler
	rm -f $(NAME)
	rm -rf lib

re: fclean all

.PHONY: all clean fclean re	games	graphicals	core
