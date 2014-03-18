# Project specific settings

ifeq ($(DEBUG), 1)
NAME	= ../../Lib/RaspberryPi/libPlatform_d.a
else
NAME	= ../../Lib/RaspberryPi/libPlatform.a
endif

CC := g++
AR := ar

INCLUDES = -I../Include -I../../Include -I../../DisplayLib/Include -I../../SoundLib/Include -I../../SuperPlayLib/Include -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux

CFLAGS += -mfpu=vfp -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM

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
	mkdir -p ../../Lib
	$(AR) -cvq $(NAME) $(OBJ)
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(NAME)
