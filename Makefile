NAME1 = client
NAME2 = server
NAME3 = client_bonus
NAME4 = server_bonus

CC = cc
CFLAGES = -Wall -Wextra -Werror

SRC_C = client.c
SRC_S = server.c
SRC_CB = client_bonus.c
SRC_SB = server_bonus.c

OBJ_CLIENT = $(SRC_C:.o=.c)
OBJ_SERVER = $(SRC_S:.o=.c)
OBJ_CLIENT_BONUS = $(SRC_CB:.o=.c)
OBJ_SERVER_BONUS = $(SRC_SB:.o=.c)

all : $(NAME1) $(NAME2)

$(NAME1) : $(OBJ_CLIENT)
	$(CC) $(CFLAGES) $(OBJ_CLIENT) -o $(NAME1)

$(NAME2) : $(OBJ_SERVER)
	$(CC) $(CFLAGES) $(OBJ_SERVER) -o $(NAME2)

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus : $(NAME3) $(NAME4)

$(NAME3) : $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGES) $(OBJ_CLIENT_BONUS) -o $(NAME3)

$(NAME4) : $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGES) $(OBJ_SERVER_BONUS) -o $(NAME4)

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME1) $(NAME2) $(NAME3) $(NAME4)

re : fclean all

.PHONY : all clean fclean re bonus

.SECONDARY : *.o