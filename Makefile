PATH_SRC = srcs
SRC = $(PATH_SRC)/*.c #WILDCARD !

FLAGS= -O3 -lpcap
CC = gcc
EXECUTABLE = listendash

HEADERS = -I includes/

all : $(EXECUTABLE)

$(EXECUTABLE) : $(SRC)
	$(CC) $(SRC) -o $(EXECUTABLE) -I includes/ $(FLAGS)
	@printf "$(EXECUTABLE) created\n"
	

clean : 
	/bin/rm -f $(EXECUTABLE)
	@printf "$(EXECUTABLE) removed\n"

re : clean all

.PHONY : clean all $(EXECUTABLE)
