# Project specific settings

ifeq ($(DEBUG), 1)
NAME	= ../Lib/Linux/libSuperPlay_d.a
else
NAME	= ../Lib/Linux/libSuperPlay.a
endif

CC := g++
AR := ar

INCLUDES = -IInclude -IHardware -ILibraries -I../Include -I../DisplayLib/Include -I../PlatformLib/Include -I../SoundLib/Include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0
else
CFLAGS += -O2
endif

SRC	= $(wildcard Engine/*.cpp)
SRC	+= $(wildcard Hardware/*.cpp)
SRC	+= $(wildcard Libraries/TinyXML2/*.cpp)
SRC	+= $(wildcard Libraries/mtrand/*.cpp)
SRC	+= $(wildcard Libraries/stb_image/*.cpp)

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
	mkdir -p $(OBJDIR)/Engine
	mkdir -p $(OBJDIR)/Hardware
	mkdir -p $(OBJDIR)/Libraries/mtrand
	mkdir -p $(OBJDIR)/Libraries/stb_image
	mkdir -p $(OBJDIR)/Libraries/TinyXML2	
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
