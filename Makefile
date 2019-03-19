PATH_SRC = srcs
SRC = $(PATH_SRC)/*.c #WILDCARD !

FLAGS= -O3 -lpcap
CC = gcc
BINARY = dashbutton

HEADERS = -I includes/

all : $(BINARY)

$(BINARY) : $(SRC)
	$(CC) $(SRC) -o $(BINARY) -I includes/ $(FLAGS)
	@printf "$(BINARY) created\n"
	

clean : 
	/bin/rm -f $(BINARY)
	@printf "$(BINARY) removed\n"

re : clean all

.PHONY : clean all $(BINARY)
