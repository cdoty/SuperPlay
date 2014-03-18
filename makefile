DIRS = DisplayLib/SDL PlatformLib/Linux SoundLib/Hekkus SoundLib/irrKlang SoundLib/BASS SuperPlayLib ExpansionLib Examples/Audio Examples/BLT Examples/HDMA Examples/Joypad Examples/Sprites Examples/Tilemap
BUILDDIRS = $(DIRS:%=build-%)
CLEANDIRS = $(DIRS:%=clean-%)

all: $(BUILDDIRS)
$(DIRS): $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)

# the utils need the libraries in dev built first
build-utils: build-dev

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean


.PHONY: subdirs $(DIRS)
.PHONY: subdirs $(BUILDDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all clean
