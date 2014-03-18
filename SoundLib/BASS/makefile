# Project specific settings

ifeq ($(DEBUG), 1)
NAME	= ../../Lib/Linux/BASS/libSound_d.a
else
NAME	= ../../Lib/Linux/BASS/libSound.a
endif

CC := g++
AR := ar

INCLUDES = -I../Include -I../../Include -I../../PlatformLib/Linux -I../../SuperPlayLib/Include -I../../External/BASS/Include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0
else
CFLAGS +=  -O2
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
	mkdir -p ../../Lib/Linux/BASS
	$(AR) rcus $(NAME) $(OBJ)
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
