GLFW_SRC = glfw_src
GLFW = glfw
PROJECT_NAME = GLFW

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"
BOLD = "\e[1m"
LIGHT = "\e[2m"
ITALIC = "\e[3m"
ULINE = "\e[4m"

START = @printf $(GREEN)$(BOLD)"$(PROJECT_NAME)\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)$(BOLD)"--------------------\n"$(NORMAL)

all:
	$(START)
	@make $(GLFW)
	$(END)

$(GLFW):
	@mkdir -p $(GLFW)
	@cd $(GLFW) && cmake ../$(GLFW_SRC)
	@make -C $(GLFW)

clean:
	$(START)
	@printf $(RED)"-x remove $(GLFW)\n"$(NORMAL)
	@rm -rf $(GLFW)
	$(END)

cleanlib:
	$(START)
	@printf $(RED)"-x remove $(GLFW)\n"$(NORMAL)
	@rm -rf $(GLFW)
	$(END)


fclean: clean

re: fclean all

.PHONY: all clean fclean re
