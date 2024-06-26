NAME        =   minishell

CC          =   cc

FLAG        =   -Wall -Wextra -Werror -g3 

LIBFT_PATH  =   .libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILE      =  	expander/expander.c \
				lexer/lexer_utils.c \
				lexer/store_token.c \
				prompt/readline.c	\
				main.c \
				expander/expander_utils.c \
				parser/parser_utils.c \
				
OBJS        =   $(C_FILE:.c=.o)

.c.o:
	@printf "\r\033[K[Mere-MiShell] \033[0;32mBuilding : $<\n\033[0m"
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)
	
$(NAME): $(LIBFT_LIB) $(OBJS)
	@printf "\r\033[K[Mere-MiShell] \033[0;32mLinking...\033[0m"
	@$(CC) $(OBJS) $(LIBFT_LIB) -o $(NAME) -lm -lreadline
	@printf "\r\033[K[Mere-MiShell] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJS)
	@printf "[Mere-MiShell] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean 
	@rm -f $(NAME) $(BONUS)
	@make fclean -C $(LIBFT_PATH)
	@printf "[Mere-MiShell] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re 
