##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SuperPlay
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/SuperPlayLib"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Charles Doty
Date                   :=01/26/14
CodeLitePath           :="/home/cdoty/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../Lib/Linux/lib$(ProjectName)_d.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="SuperPlay.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)Include $(IncludeSwitch)Libraries $(IncludeSwitch)../Include $(IncludeSwitch)../SoundLib/Include $(IncludeSwitch)../DisplayLib/Include $(IncludeSwitch)../PlatformLib/Include $(IncludeSwitch)../SoundLIb/Include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 $(Preprocessors)
CFLAGS   :=  -g -O0 $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Hardware_BG$(ObjectSuffix) $(IntermediateDirectory)/Hardware_BGManager$(ObjectSuffix) $(IntermediateDirectory)/Hardware_BGVRAM$(ObjectSuffix) $(IntermediateDirectory)/Hardware_CRC32$(ObjectSuffix) $(IntermediateDirectory)/Hardware_DMA$(ObjectSuffix) $(IntermediateDirectory)/Hardware_HDMA$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Hardware$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Joypad$(ObjectSuffix) $(IntermediateDirectory)/Hardware_OAM$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Obj$(ObjectSuffix) \
	$(IntermediateDirectory)/Hardware_ObjVRAM$(ObjectSuffix) $(IntermediateDirectory)/Hardware_SPC$(ObjectSuffix) $(IntermediateDirectory)/Hardware_SRAM$(ObjectSuffix) $(IntermediateDirectory)/Hardware_ShadowOAM$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Text$(ObjectSuffix) $(IntermediateDirectory)/Engine_Image$(ObjectSuffix) $(IntermediateDirectory)/Engine_ResourceManager$(ObjectSuffix) $(IntermediateDirectory)/Engine_System$(ObjectSuffix) $(IntermediateDirectory)/Engine_Utilities$(ObjectSuffix) $(IntermediateDirectory)/TinyXML2_tinyxml2$(ObjectSuffix) \
	$(IntermediateDirectory)/stb_image_stb_image$(ObjectSuffix) $(IntermediateDirectory)/mtrand_mtrand$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/cdoty/SuperPlay/.build-debug"
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-debug/SuperPlay"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Hardware_BG$(ObjectSuffix): Hardware/BG.cpp $(IntermediateDirectory)/Hardware_BG$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/BG.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_BG$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_BG$(DependSuffix): Hardware/BG.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_BG$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_BG$(DependSuffix) -MM "Hardware/BG.cpp"

$(IntermediateDirectory)/Hardware_BG$(PreprocessSuffix): Hardware/BG.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_BG$(PreprocessSuffix) "Hardware/BG.cpp"

$(IntermediateDirectory)/Hardware_BGManager$(ObjectSuffix): Hardware/BGManager.cpp $(IntermediateDirectory)/Hardware_BGManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/BGManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_BGManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_BGManager$(DependSuffix): Hardware/BGManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_BGManager$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_BGManager$(DependSuffix) -MM "Hardware/BGManager.cpp"

$(IntermediateDirectory)/Hardware_BGManager$(PreprocessSuffix): Hardware/BGManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_BGManager$(PreprocessSuffix) "Hardware/BGManager.cpp"

$(IntermediateDirectory)/Hardware_BGVRAM$(ObjectSuffix): Hardware/BGVRAM.cpp $(IntermediateDirectory)/Hardware_BGVRAM$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/BGVRAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_BGVRAM$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_BGVRAM$(DependSuffix): Hardware/BGVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_BGVRAM$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_BGVRAM$(DependSuffix) -MM "Hardware/BGVRAM.cpp"

$(IntermediateDirectory)/Hardware_BGVRAM$(PreprocessSuffix): Hardware/BGVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_BGVRAM$(PreprocessSuffix) "Hardware/BGVRAM.cpp"

$(IntermediateDirectory)/Hardware_CRC32$(ObjectSuffix): Hardware/CRC32.cpp $(IntermediateDirectory)/Hardware_CRC32$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/CRC32.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_CRC32$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_CRC32$(DependSuffix): Hardware/CRC32.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_CRC32$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_CRC32$(DependSuffix) -MM "Hardware/CRC32.cpp"

$(IntermediateDirectory)/Hardware_CRC32$(PreprocessSuffix): Hardware/CRC32.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_CRC32$(PreprocessSuffix) "Hardware/CRC32.cpp"

$(IntermediateDirectory)/Hardware_DMA$(ObjectSuffix): Hardware/DMA.cpp $(IntermediateDirectory)/Hardware_DMA$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/DMA.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_DMA$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_DMA$(DependSuffix): Hardware/DMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_DMA$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_DMA$(DependSuffix) -MM "Hardware/DMA.cpp"

$(IntermediateDirectory)/Hardware_DMA$(PreprocessSuffix): Hardware/DMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_DMA$(PreprocessSuffix) "Hardware/DMA.cpp"

$(IntermediateDirectory)/Hardware_HDMA$(ObjectSuffix): Hardware/HDMA.cpp $(IntermediateDirectory)/Hardware_HDMA$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/HDMA.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_HDMA$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_HDMA$(DependSuffix): Hardware/HDMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_HDMA$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_HDMA$(DependSuffix) -MM "Hardware/HDMA.cpp"

$(IntermediateDirectory)/Hardware_HDMA$(PreprocessSuffix): Hardware/HDMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_HDMA$(PreprocessSuffix) "Hardware/HDMA.cpp"

$(IntermediateDirectory)/Hardware_Hardware$(ObjectSuffix): Hardware/Hardware.cpp $(IntermediateDirectory)/Hardware_Hardware$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Hardware.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Hardware$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Hardware$(DependSuffix): Hardware/Hardware.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Hardware$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Hardware$(DependSuffix) -MM "Hardware/Hardware.cpp"

$(IntermediateDirectory)/Hardware_Hardware$(PreprocessSuffix): Hardware/Hardware.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Hardware$(PreprocessSuffix) "Hardware/Hardware.cpp"

$(IntermediateDirectory)/Hardware_Joypad$(ObjectSuffix): Hardware/Joypad.cpp $(IntermediateDirectory)/Hardware_Joypad$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Joypad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Joypad$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Joypad$(DependSuffix): Hardware/Joypad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Joypad$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Joypad$(DependSuffix) -MM "Hardware/Joypad.cpp"

$(IntermediateDirectory)/Hardware_Joypad$(PreprocessSuffix): Hardware/Joypad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Joypad$(PreprocessSuffix) "Hardware/Joypad.cpp"

$(IntermediateDirectory)/Hardware_OAM$(ObjectSuffix): Hardware/OAM.cpp $(IntermediateDirectory)/Hardware_OAM$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/OAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_OAM$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_OAM$(DependSuffix): Hardware/OAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_OAM$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_OAM$(DependSuffix) -MM "Hardware/OAM.cpp"

$(IntermediateDirectory)/Hardware_OAM$(PreprocessSuffix): Hardware/OAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_OAM$(PreprocessSuffix) "Hardware/OAM.cpp"

$(IntermediateDirectory)/Hardware_Obj$(ObjectSuffix): Hardware/Obj.cpp $(IntermediateDirectory)/Hardware_Obj$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Obj.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Obj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Obj$(DependSuffix): Hardware/Obj.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Obj$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Obj$(DependSuffix) -MM "Hardware/Obj.cpp"

$(IntermediateDirectory)/Hardware_Obj$(PreprocessSuffix): Hardware/Obj.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Obj$(PreprocessSuffix) "Hardware/Obj.cpp"

$(IntermediateDirectory)/Hardware_ObjVRAM$(ObjectSuffix): Hardware/ObjVRAM.cpp $(IntermediateDirectory)/Hardware_ObjVRAM$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/ObjVRAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_ObjVRAM$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_ObjVRAM$(DependSuffix): Hardware/ObjVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_ObjVRAM$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_ObjVRAM$(DependSuffix) -MM "Hardware/ObjVRAM.cpp"

$(IntermediateDirectory)/Hardware_ObjVRAM$(PreprocessSuffix): Hardware/ObjVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_ObjVRAM$(PreprocessSuffix) "Hardware/ObjVRAM.cpp"

$(IntermediateDirectory)/Hardware_SPC$(ObjectSuffix): Hardware/SPC.cpp $(IntermediateDirectory)/Hardware_SPC$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/SPC.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_SPC$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_SPC$(DependSuffix): Hardware/SPC.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_SPC$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_SPC$(DependSuffix) -MM "Hardware/SPC.cpp"

$(IntermediateDirectory)/Hardware_SPC$(PreprocessSuffix): Hardware/SPC.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_SPC$(PreprocessSuffix) "Hardware/SPC.cpp"

$(IntermediateDirectory)/Hardware_SRAM$(ObjectSuffix): Hardware/SRAM.cpp $(IntermediateDirectory)/Hardware_SRAM$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/SRAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_SRAM$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_SRAM$(DependSuffix): Hardware/SRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_SRAM$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_SRAM$(DependSuffix) -MM "Hardware/SRAM.cpp"

$(IntermediateDirectory)/Hardware_SRAM$(PreprocessSuffix): Hardware/SRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_SRAM$(PreprocessSuffix) "Hardware/SRAM.cpp"

$(IntermediateDirectory)/Hardware_ShadowOAM$(ObjectSuffix): Hardware/ShadowOAM.cpp $(IntermediateDirectory)/Hardware_ShadowOAM$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/ShadowOAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_ShadowOAM$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_ShadowOAM$(DependSuffix): Hardware/ShadowOAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_ShadowOAM$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_ShadowOAM$(DependSuffix) -MM "Hardware/ShadowOAM.cpp"

$(IntermediateDirectory)/Hardware_ShadowOAM$(PreprocessSuffix): Hardware/ShadowOAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_ShadowOAM$(PreprocessSuffix) "Hardware/ShadowOAM.cpp"

$(IntermediateDirectory)/Hardware_Text$(ObjectSuffix): Hardware/Text.cpp $(IntermediateDirectory)/Hardware_Text$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Text.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Text$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Text$(DependSuffix): Hardware/Text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Text$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Text$(DependSuffix) -MM "Hardware/Text.cpp"

$(IntermediateDirectory)/Hardware_Text$(PreprocessSuffix): Hardware/Text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Text$(PreprocessSuffix) "Hardware/Text.cpp"

$(IntermediateDirectory)/Engine_Image$(ObjectSuffix): Engine/Image.cpp $(IntermediateDirectory)/Engine_Image$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/Image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_Image$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_Image$(DependSuffix): Engine/Image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_Image$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_Image$(DependSuffix) -MM "Engine/Image.cpp"

$(IntermediateDirectory)/Engine_Image$(PreprocessSuffix): Engine/Image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_Image$(PreprocessSuffix) "Engine/Image.cpp"

$(IntermediateDirectory)/Engine_ResourceManager$(ObjectSuffix): Engine/ResourceManager.cpp $(IntermediateDirectory)/Engine_ResourceManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/ResourceManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_ResourceManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_ResourceManager$(DependSuffix): Engine/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_ResourceManager$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_ResourceManager$(DependSuffix) -MM "Engine/ResourceManager.cpp"

$(IntermediateDirectory)/Engine_ResourceManager$(PreprocessSuffix): Engine/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_ResourceManager$(PreprocessSuffix) "Engine/ResourceManager.cpp"

$(IntermediateDirectory)/Engine_System$(ObjectSuffix): Engine/System.cpp $(IntermediateDirectory)/Engine_System$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/System.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_System$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_System$(DependSuffix): Engine/System.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_System$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_System$(DependSuffix) -MM "Engine/System.cpp"

$(IntermediateDirectory)/Engine_System$(PreprocessSuffix): Engine/System.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_System$(PreprocessSuffix) "Engine/System.cpp"

$(IntermediateDirectory)/Engine_Utilities$(ObjectSuffix): Engine/Utilities.cpp $(IntermediateDirectory)/Engine_Utilities$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/Utilities.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_Utilities$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_Utilities$(DependSuffix): Engine/Utilities.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_Utilities$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_Utilities$(DependSuffix) -MM "Engine/Utilities.cpp"

$(IntermediateDirectory)/Engine_Utilities$(PreprocessSuffix): Engine/Utilities.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_Utilities$(PreprocessSuffix) "Engine/Utilities.cpp"

$(IntermediateDirectory)/TinyXML2_tinyxml2$(ObjectSuffix): Libraries/TinyXML2/tinyxml2.cpp $(IntermediateDirectory)/TinyXML2_tinyxml2$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Libraries/TinyXML2/tinyxml2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TinyXML2_tinyxml2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TinyXML2_tinyxml2$(DependSuffix): Libraries/TinyXML2/tinyxml2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TinyXML2_tinyxml2$(ObjectSuffix) -MF$(IntermediateDirectory)/TinyXML2_tinyxml2$(DependSuffix) -MM "Libraries/TinyXML2/tinyxml2.cpp"

$(IntermediateDirectory)/TinyXML2_tinyxml2$(PreprocessSuffix): Libraries/TinyXML2/tinyxml2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TinyXML2_tinyxml2$(PreprocessSuffix) "Libraries/TinyXML2/tinyxml2.cpp"

$(IntermediateDirectory)/stb_image_stb_image$(ObjectSuffix): Libraries/stb_image/stb_image.cpp $(IntermediateDirectory)/stb_image_stb_image$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Libraries/stb_image/stb_image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/stb_image_stb_image$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stb_image_stb_image$(DependSuffix): Libraries/stb_image/stb_image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/stb_image_stb_image$(ObjectSuffix) -MF$(IntermediateDirectory)/stb_image_stb_image$(DependSuffix) -MM "Libraries/stb_image/stb_image.cpp"

$(IntermediateDirectory)/stb_image_stb_image$(PreprocessSuffix): Libraries/stb_image/stb_image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stb_image_stb_image$(PreprocessSuffix) "Libraries/stb_image/stb_image.cpp"

$(IntermediateDirectory)/mtrand_mtrand$(ObjectSuffix): Libraries/mtrand/mtrand.cpp $(IntermediateDirectory)/mtrand_mtrand$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Libraries/mtrand/mtrand.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mtrand_mtrand$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mtrand_mtrand$(DependSuffix): Libraries/mtrand/mtrand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mtrand_mtrand$(ObjectSuffix) -MF$(IntermediateDirectory)/mtrand_mtrand$(DependSuffix) -MM "Libraries/mtrand/mtrand.cpp"

$(IntermediateDirectory)/mtrand_mtrand$(PreprocessSuffix): Libraries/mtrand/mtrand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mtrand_mtrand$(PreprocessSuffix) "Libraries/mtrand/mtrand.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Hardware_BG$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BG$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BG$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BGManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BGManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BGManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BGVRAM$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BGVRAM$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_BGVRAM$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_CRC32$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_CRC32$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_CRC32$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_DMA$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_DMA$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_DMA$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_HDMA$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_HDMA$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_HDMA$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Hardware$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Hardware$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Hardware$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Joypad$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Joypad$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Joypad$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_OAM$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_OAM$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_OAM$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Obj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Obj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Obj$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_ObjVRAM$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_ObjVRAM$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_ObjVRAM$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_SPC$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_SPC$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_SPC$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_SRAM$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_SRAM$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_SRAM$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_ShadowOAM$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_ShadowOAM$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_ShadowOAM$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Text$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Text$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Hardware_Text$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Engine_Image$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Engine_Image$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Engine_Image$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Engine_ResourceManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Engine_ResourceManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Engine_ResourceManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Engine_System$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Engine_System$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Engine_System$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Engine_Utilities$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Engine_Utilities$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Engine_Utilities$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/TinyXML2_tinyxml2$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/TinyXML2_tinyxml2$(DependSuffix)
	$(RM) $(IntermediateDirectory)/TinyXML2_tinyxml2$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/stb_image_stb_image$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stb_image_stb_image$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stb_image_stb_image$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mtrand_mtrand$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mtrand_mtrand$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mtrand_mtrand$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/SuperPlay"


