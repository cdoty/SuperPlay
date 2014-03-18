# Project specific settings

ifeq ($(DEBUG), 1)
NAME	= ../../Lib/Linux/libDisplay_d.a
else
NAME	= ../../Lib/Linux/libDisplay.a
endif

CC := g++
AR := ar

INCLUDES = -I../Include -I../../Include -I../../PlatformLib/Linux -I../../SuperPlayLib/Include

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0 -g
else
CFLAGS += -O2 
endif

CFLAGS += -DGLEW_STATIC

SRC	= Display.cpp glew.cpp GLPlatform.cpp IndexBuffer.cpp SpriteBatch.cpp Texture.cpp VertexBuffer.cpp

ifeq ($(DEBUG), 1)
OBJDIR := Debug
else
OBJDIR := Release
endif

OBJ	= $(addprefix $(OBJDIR)/,$(SRC:.cpp=.o))

all: $(NAME)
	
$(NAME): $(OBJ)
	mkdir -p ../../Lib/Linux/
	$(AR) rcus $(NAME) $(OBJ)
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
