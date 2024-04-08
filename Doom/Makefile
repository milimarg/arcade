##
## EPITECH PROJECT, 2024
## strace
## File description:
## Makefile
##

SRC	=	Doom.cpp	\
		../Sources/EventInfo.cpp	\
		../Sources/Pixels/Pixel.cpp	\
		../Sources/Texts/Text.cpp	\
		../Sources/Pixels/APixels.cpp	\
		../Sources/Pixels/Pixels.cpp	\
		../Sources/Texts/ATexts.cpp	\
		../Sources/Texts/Texts.cpp	\
		../Sources/Game/AGameModule.cpp \
		idt1/src/library_utils/lib.cpp \
		idt1/src/library_utils/utils.cpp \
		idt1/src/draw/draw.cpp \
		idt1/src/draw/draw_wall.cpp \
		idt1/src/draw/points.cpp \
		idt1/src/move/move_player.cpp \
		idt1/src/move/move_player_body.cpp \
		idt1/src/move/move_player_view.cpp \
		idt1/src/move/move_strafe.cpp \
		idt1/src/parser/convert_dante_to_config.cpp \
		idt1/src/parser/parser.cpp \
		idt1/src/world_handler.cpp \
		idt1/src/reload_world.cpp \
		idt1/src/walls.cpp \
		idt1/src/sectors.cpp

OBJ = $(SRC:.cpp=.o)

NAME	=	arcade_doom.so

CPPFLAGS	=	-g -std=c++20 -fPIC -I../Includes -fno-gnu-unique

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
