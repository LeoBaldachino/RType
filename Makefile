##
## EPITECH PROJECT, 2023
## B-CPP-500-MLH-5-1-rtype-robin.denni
## File description:
## Makefile
##

SRC	=	main.cpp									\
		Core/Core.cpp								\
		Entity/Player.cpp							\
		Entity/Bydos.cpp							\
		Entity/ShotEntity.cpp						\
		Entity/PiercingShotEntity.cpp				\
		Entity/Tourre.cpp							\
		Systems/PlayerSystem.cpp					\
		Systems/BydosSystem.cpp						\
		Systems/TourreSystem.cpp					\
		Systems/Subsystems/DrawSystem.cpp			\
		Systems/Subsystems/InputSystem.cpp			\
		Systems/Subsystems/PiercingShotSystem.cpp	\
		Systems/Subsystems/ShotSystem.cpp			\
		Systems/Subsystems/MovementSystem.cpp		\
		Systems/Subsystems/AIShoot.cpp				\
		Systems/Subsystems/HitBox.cpp

OBJ	=	$(SRC:.cpp=.o)
CC	=	g++ -g

CFLAGS	+=	 -Wall -Wextra

FLAGS = -lsfml-system -lsfml-graphics -lsfml-window

all:	$(OBJ)
	$(CC) -o a.out $(OBJ) $(FLAGS)

clean:
	rm -f $(BIN)
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:		all clean fclean re
