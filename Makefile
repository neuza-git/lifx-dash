default: app


SRC = \
	app.c \
	lifx.c

INC = \
	-I./ 

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
-include $(DEP)

CFLAGS += $(INC) -std=gnu99 -g -O3 -lpcap

ifeq ($(findstring clang, $(shell gcc --version)), clang)
	CFLAGS += 
else
	CFLAGS += -fno-delete-null-pointer-checks
endif

CPPFLAGS += -MMD -MP

debug: CFLAGS += -DDEBUG
debug: app

app: $(OBJ)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o listendash -lpcap
	
clean:
	rm -f app $(OBJ) $(DEP)

.PHONY: default debug clean
