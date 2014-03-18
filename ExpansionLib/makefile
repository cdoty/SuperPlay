# Project specific settings

ifeq ($(DEBUG), 1)
NAME	= ../Lib/Linux/libExpansionLib_d.a
else
NAME	= ../Lib/Linux/libExpansionLib.a
endif

CC := g++
AR := ar

INCLUDES = -I../Include -I../Include/Expansion -I../PlatformLib/Include -I../PlatformLib/Linux -I../SuperPlayLib/Include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0
else
CFLAGS += -O2 
endif

SRC	= $(wildcard AudioLoader/*.cpp)
SRC	+= $(wildcard FontLoader/*.cpp)
SRC	+= $(wildcard FontLoader/yspng/*.cpp)
SRC	+= $(wildcard HDMALoader/*.cpp)
SRC	+= $(wildcard MapLoader/*.cpp)
SRC	+= $(wildcard SpriteLoader/*.cpp)

ifeq ($(DEBUG), 1)
OBJDIR := Debug
else
OBJDIR := Release
endif

OBJ	= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

all: $(NAME)
	
$(NAME): $(OBJ)
	mkdir -p ../Lib/Linux/
	$(AR) rcus $(NAME) $(OBJ)
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/AudioLoader
	mkdir -p $(OBJDIR)/FontLoader
	mkdir -p $(OBJDIR)/FontLoader/yspng
	mkdir -p $(OBJDIR)/HDMALoader
	mkdir -p $(OBJDIR)/MapLoader
	mkdir -p $(OBJDIR)/SpriteLoader
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
