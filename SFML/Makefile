##
## EPITECH PROJECT, 2024
## strace
## File description:
## Makefile
##

SRC	=	SFML.cpp	\
		../Sources/EventInfo.cpp	\
		../Sources/Pixels/Pixel.cpp	\
		../Sources/Texts/Text.cpp	\
		../Sources/Pixels/APixels.cpp	\
		../Sources/Pixels/Pixels.cpp	\
		../Sources/Texts/ATexts.cpp	\
		../Sources/Texts/Texts.cpp \
		../Sources/GraphicalWindow.cpp

OBJ = $(SRC:.cpp=.o)

NAME	=	arcade_sfml.so

CPPFLAGS	=	-g -fno-gnu-unique -fPIC -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -I../Includes

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
