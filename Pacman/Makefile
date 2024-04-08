##
## EPITECH PROJECT, 2024
## B-OOP-400-STG-4-1-arcade-noe.tritsch
## File description:
## Makefile
##

SRC	=	Pacman.cpp	\
		../Sources/EventInfo.cpp	\
		../Sources/Pixels/Pixel.cpp	\
		../Sources/Texts/Text.cpp	\
		../Sources/Pixels/APixels.cpp	\
		../Sources/Pixels/Pixels.cpp	\
		../Sources/Texts/ATexts.cpp	\
		../Sources/Texts/Texts.cpp	\
		../Sources/Game/AGameModule.cpp

OBJ = $(SRC:.cpp=.o)

NAME	=	arcade_pacman.so

CPPFLAGS	=	-g -std=c++20 -fPIC -I../Includes -fno-gnu-unique

all: $(NAME)

$(NAME): $(OBJ)
	g++ -shared $(OBJ) -o $(NAME) $(CPPFLAGS)
	mv $(NAME) ../lib/

%.o:	%.cpp
	g++ -o $@ -c $< -I../Includes $(CPPFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
