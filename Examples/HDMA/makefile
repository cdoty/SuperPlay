# Project specific settings

NAME	= Environment/HDMADemo

CC := g++
AR := ar
LD := g++

INCLUDES = -I../../Include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0
else
CFLAGS +=  -O2
endif

LDFLAGS += -pthread -L../../Lib/Linux -L../../Lib/Linux/irrKlang -L../../External/irrKlang-1.4.0b/Lib/Linux

SRC	= $(wildcard *.cpp)

ifeq ($(DEBUG), 1)
OBJDIR := Debug
else
OBJDIR := Release
endif

OBJ	= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))
ifeq ($(DEBUG), 1)
LIBS = -lExpansionLib_d -lSuperPlay_d -lPlatform_d -lSound_d -lDisplay_d -lIrrKlang
else
LIBS = -lExpansionLib -lSuperPlay -lPlatform -lSound -lDisplay -lIrrKlang
endif

LIBS	+= -lSDL2 -lX11 -lGLU -lGL -lXext

all: $(NAME)
	
$(NAME): $(OBJ)
	$(LD) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LIBS)
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
