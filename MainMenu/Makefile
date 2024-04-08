##
## EPITECH PROJECT, 2024
## strace
## File description:
## Makefile
##

SRC	=	MainMenu.cpp	\
		Score.cpp	\
		../Sources/EventInfo.cpp	\
		../Sources/Pixels/Pixel.cpp	\
		../Sources/Texts/Text.cpp	\
		../Sources/Pixels/APixels.cpp	\
		../Sources/Pixels/Pixels.cpp	\
		../Sources/Texts/ATexts.cpp	\
		../Sources/Texts/Texts.cpp	\
		../Sources/Game/AGameModule.cpp	\
		../Sources/LibraryHandler.cpp

OBJ = $(SRC:.cpp=.o)

NAME	=	main_menu.so

CPPFLAGS	=	-g -std=c++20 -fPIC -I../Includes -fno-gnu-unique -ldl -lssl -lcrypto

all: $(NAME)

$(NAME): $(OBJ)
	g++ -shared $(OBJ) -o $(NAME) $(CPPFLAGS)
	mv $(NAME) ../lib/

%.o:	%.cpp
	g++ -c $< -o $@ $(CPPFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
