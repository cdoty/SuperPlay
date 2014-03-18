# Project specific settings

ifeq ($(DEBUG), 1)
NAME	= ../../Lib/Linux/Hekkus/libSound_d.a
else
NAME	= ../../Lib/Linux/Hekkus/libSound.a
endif

CC := g++
AR := ar

INCLUDES = -I../Include -I../../Include -I../../PlatformLib/Linux -I../../SuperPlayLib/Include -I../../External/Hekkus/include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0
else
CFLAGS +=  -O3
endif

SRC	= $(wildcard *.cpp)

ifeq ($(DEBUG), 1)
OBJDIR := Debug
else
OBJDIR := Release
endif

OBJ	= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

all: $(NAME)
	
$(NAME): $(OBJ)
	mkdir -p ../../Lib/Linux/Hekkus
	$(AR) rcus $(NAME) $(OBJ)
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) -O3 $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
