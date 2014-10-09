##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SuperPlay
ConfigurationName      :=Release
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/SuperPlayLib"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Charles Doty
Date                   :=10/08/14
CodeLitePath           :="/home/cdoty/.codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../Lib/Linux/lib$(ProjectName).a
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 $(Preprocessors)
CFLAGS   :=  -O2 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Hardware_BG.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_BGManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_BGVRAM.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_CRC32.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_DMA.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_HDMA.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Hardware.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Joypad.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_OAM.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Obj.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_SPC.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_SRAM.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(ObjectSuffix) $(IntermediateDirectory)/Hardware_Text.cpp$(ObjectSuffix) $(IntermediateDirectory)/Engine_Image.cpp$(ObjectSuffix) $(IntermediateDirectory)/Engine_ResourceManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Engine_System.cpp$(ObjectSuffix) $(IntermediateDirectory)/Engine_Utilities.cpp$(ObjectSuffix) $(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/stb_image_stb_image.cpp$(ObjectSuffix) $(IntermediateDirectory)/mtrand_mtrand.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "/home/cdoty/SuperPlay/.build-release"
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-release/SuperPlay"

./Release:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Hardware_BG.cpp$(ObjectSuffix): Hardware/BG.cpp $(IntermediateDirectory)/Hardware_BG.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/BG.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_BG.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_BG.cpp$(DependSuffix): Hardware/BG.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_BG.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_BG.cpp$(DependSuffix) -MM "Hardware/BG.cpp"

$(IntermediateDirectory)/Hardware_BG.cpp$(PreprocessSuffix): Hardware/BG.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_BG.cpp$(PreprocessSuffix) "Hardware/BG.cpp"

$(IntermediateDirectory)/Hardware_BGManager.cpp$(ObjectSuffix): Hardware/BGManager.cpp $(IntermediateDirectory)/Hardware_BGManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/BGManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_BGManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_BGManager.cpp$(DependSuffix): Hardware/BGManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_BGManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_BGManager.cpp$(DependSuffix) -MM "Hardware/BGManager.cpp"

$(IntermediateDirectory)/Hardware_BGManager.cpp$(PreprocessSuffix): Hardware/BGManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_BGManager.cpp$(PreprocessSuffix) "Hardware/BGManager.cpp"

$(IntermediateDirectory)/Hardware_BGVRAM.cpp$(ObjectSuffix): Hardware/BGVRAM.cpp $(IntermediateDirectory)/Hardware_BGVRAM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/BGVRAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_BGVRAM.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_BGVRAM.cpp$(DependSuffix): Hardware/BGVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_BGVRAM.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_BGVRAM.cpp$(DependSuffix) -MM "Hardware/BGVRAM.cpp"

$(IntermediateDirectory)/Hardware_BGVRAM.cpp$(PreprocessSuffix): Hardware/BGVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_BGVRAM.cpp$(PreprocessSuffix) "Hardware/BGVRAM.cpp"

$(IntermediateDirectory)/Hardware_CRC32.cpp$(ObjectSuffix): Hardware/CRC32.cpp $(IntermediateDirectory)/Hardware_CRC32.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/CRC32.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_CRC32.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_CRC32.cpp$(DependSuffix): Hardware/CRC32.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_CRC32.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_CRC32.cpp$(DependSuffix) -MM "Hardware/CRC32.cpp"

$(IntermediateDirectory)/Hardware_CRC32.cpp$(PreprocessSuffix): Hardware/CRC32.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_CRC32.cpp$(PreprocessSuffix) "Hardware/CRC32.cpp"

$(IntermediateDirectory)/Hardware_DMA.cpp$(ObjectSuffix): Hardware/DMA.cpp $(IntermediateDirectory)/Hardware_DMA.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/DMA.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_DMA.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_DMA.cpp$(DependSuffix): Hardware/DMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_DMA.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_DMA.cpp$(DependSuffix) -MM "Hardware/DMA.cpp"

$(IntermediateDirectory)/Hardware_DMA.cpp$(PreprocessSuffix): Hardware/DMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_DMA.cpp$(PreprocessSuffix) "Hardware/DMA.cpp"

$(IntermediateDirectory)/Hardware_HDMA.cpp$(ObjectSuffix): Hardware/HDMA.cpp $(IntermediateDirectory)/Hardware_HDMA.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/HDMA.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_HDMA.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_HDMA.cpp$(DependSuffix): Hardware/HDMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_HDMA.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_HDMA.cpp$(DependSuffix) -MM "Hardware/HDMA.cpp"

$(IntermediateDirectory)/Hardware_HDMA.cpp$(PreprocessSuffix): Hardware/HDMA.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_HDMA.cpp$(PreprocessSuffix) "Hardware/HDMA.cpp"

$(IntermediateDirectory)/Hardware_Hardware.cpp$(ObjectSuffix): Hardware/Hardware.cpp $(IntermediateDirectory)/Hardware_Hardware.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Hardware.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Hardware.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Hardware.cpp$(DependSuffix): Hardware/Hardware.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Hardware.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Hardware.cpp$(DependSuffix) -MM "Hardware/Hardware.cpp"

$(IntermediateDirectory)/Hardware_Hardware.cpp$(PreprocessSuffix): Hardware/Hardware.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Hardware.cpp$(PreprocessSuffix) "Hardware/Hardware.cpp"

$(IntermediateDirectory)/Hardware_Joypad.cpp$(ObjectSuffix): Hardware/Joypad.cpp $(IntermediateDirectory)/Hardware_Joypad.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Joypad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Joypad.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Joypad.cpp$(DependSuffix): Hardware/Joypad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Joypad.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Joypad.cpp$(DependSuffix) -MM "Hardware/Joypad.cpp"

$(IntermediateDirectory)/Hardware_Joypad.cpp$(PreprocessSuffix): Hardware/Joypad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Joypad.cpp$(PreprocessSuffix) "Hardware/Joypad.cpp"

$(IntermediateDirectory)/Hardware_OAM.cpp$(ObjectSuffix): Hardware/OAM.cpp $(IntermediateDirectory)/Hardware_OAM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/OAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_OAM.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_OAM.cpp$(DependSuffix): Hardware/OAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_OAM.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_OAM.cpp$(DependSuffix) -MM "Hardware/OAM.cpp"

$(IntermediateDirectory)/Hardware_OAM.cpp$(PreprocessSuffix): Hardware/OAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_OAM.cpp$(PreprocessSuffix) "Hardware/OAM.cpp"

$(IntermediateDirectory)/Hardware_Obj.cpp$(ObjectSuffix): Hardware/Obj.cpp $(IntermediateDirectory)/Hardware_Obj.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Obj.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Obj.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Obj.cpp$(DependSuffix): Hardware/Obj.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Obj.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Obj.cpp$(DependSuffix) -MM "Hardware/Obj.cpp"

$(IntermediateDirectory)/Hardware_Obj.cpp$(PreprocessSuffix): Hardware/Obj.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Obj.cpp$(PreprocessSuffix) "Hardware/Obj.cpp"

$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(ObjectSuffix): Hardware/ObjVRAM.cpp $(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/ObjVRAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(DependSuffix): Hardware/ObjVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(DependSuffix) -MM "Hardware/ObjVRAM.cpp"

$(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(PreprocessSuffix): Hardware/ObjVRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_ObjVRAM.cpp$(PreprocessSuffix) "Hardware/ObjVRAM.cpp"

$(IntermediateDirectory)/Hardware_SPC.cpp$(ObjectSuffix): Hardware/SPC.cpp $(IntermediateDirectory)/Hardware_SPC.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/SPC.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_SPC.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_SPC.cpp$(DependSuffix): Hardware/SPC.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_SPC.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_SPC.cpp$(DependSuffix) -MM "Hardware/SPC.cpp"

$(IntermediateDirectory)/Hardware_SPC.cpp$(PreprocessSuffix): Hardware/SPC.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_SPC.cpp$(PreprocessSuffix) "Hardware/SPC.cpp"

$(IntermediateDirectory)/Hardware_SRAM.cpp$(ObjectSuffix): Hardware/SRAM.cpp $(IntermediateDirectory)/Hardware_SRAM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/SRAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_SRAM.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_SRAM.cpp$(DependSuffix): Hardware/SRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_SRAM.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_SRAM.cpp$(DependSuffix) -MM "Hardware/SRAM.cpp"

$(IntermediateDirectory)/Hardware_SRAM.cpp$(PreprocessSuffix): Hardware/SRAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_SRAM.cpp$(PreprocessSuffix) "Hardware/SRAM.cpp"

$(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(ObjectSuffix): Hardware/ShadowOAM.cpp $(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/ShadowOAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(DependSuffix): Hardware/ShadowOAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(DependSuffix) -MM "Hardware/ShadowOAM.cpp"

$(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(PreprocessSuffix): Hardware/ShadowOAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_ShadowOAM.cpp$(PreprocessSuffix) "Hardware/ShadowOAM.cpp"

$(IntermediateDirectory)/Hardware_Text.cpp$(ObjectSuffix): Hardware/Text.cpp $(IntermediateDirectory)/Hardware_Text.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Hardware/Text.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Hardware_Text.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Hardware_Text.cpp$(DependSuffix): Hardware/Text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Hardware_Text.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Hardware_Text.cpp$(DependSuffix) -MM "Hardware/Text.cpp"

$(IntermediateDirectory)/Hardware_Text.cpp$(PreprocessSuffix): Hardware/Text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Hardware_Text.cpp$(PreprocessSuffix) "Hardware/Text.cpp"

$(IntermediateDirectory)/Engine_Image.cpp$(ObjectSuffix): Engine/Image.cpp $(IntermediateDirectory)/Engine_Image.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/Image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_Image.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_Image.cpp$(DependSuffix): Engine/Image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_Image.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_Image.cpp$(DependSuffix) -MM "Engine/Image.cpp"

$(IntermediateDirectory)/Engine_Image.cpp$(PreprocessSuffix): Engine/Image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_Image.cpp$(PreprocessSuffix) "Engine/Image.cpp"

$(IntermediateDirectory)/Engine_ResourceManager.cpp$(ObjectSuffix): Engine/ResourceManager.cpp $(IntermediateDirectory)/Engine_ResourceManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/ResourceManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_ResourceManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_ResourceManager.cpp$(DependSuffix): Engine/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_ResourceManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_ResourceManager.cpp$(DependSuffix) -MM "Engine/ResourceManager.cpp"

$(IntermediateDirectory)/Engine_ResourceManager.cpp$(PreprocessSuffix): Engine/ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_ResourceManager.cpp$(PreprocessSuffix) "Engine/ResourceManager.cpp"

$(IntermediateDirectory)/Engine_System.cpp$(ObjectSuffix): Engine/System.cpp $(IntermediateDirectory)/Engine_System.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/System.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_System.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_System.cpp$(DependSuffix): Engine/System.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_System.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_System.cpp$(DependSuffix) -MM "Engine/System.cpp"

$(IntermediateDirectory)/Engine_System.cpp$(PreprocessSuffix): Engine/System.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_System.cpp$(PreprocessSuffix) "Engine/System.cpp"

$(IntermediateDirectory)/Engine_Utilities.cpp$(ObjectSuffix): Engine/Utilities.cpp $(IntermediateDirectory)/Engine_Utilities.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Engine/Utilities.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Engine_Utilities.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Engine_Utilities.cpp$(DependSuffix): Engine/Utilities.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Engine_Utilities.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Engine_Utilities.cpp$(DependSuffix) -MM "Engine/Utilities.cpp"

$(IntermediateDirectory)/Engine_Utilities.cpp$(PreprocessSuffix): Engine/Utilities.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Engine_Utilities.cpp$(PreprocessSuffix) "Engine/Utilities.cpp"

$(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(ObjectSuffix): Libraries/TinyXML2/tinyxml2.cpp $(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Libraries/TinyXML2/tinyxml2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(DependSuffix): Libraries/TinyXML2/tinyxml2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(DependSuffix) -MM "Libraries/TinyXML2/tinyxml2.cpp"

$(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(PreprocessSuffix): Libraries/TinyXML2/tinyxml2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TinyXML2_tinyxml2.cpp$(PreprocessSuffix) "Libraries/TinyXML2/tinyxml2.cpp"

$(IntermediateDirectory)/stb_image_stb_image.cpp$(ObjectSuffix): Libraries/stb_image/stb_image.cpp $(IntermediateDirectory)/stb_image_stb_image.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Libraries/stb_image/stb_image.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/stb_image_stb_image.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stb_image_stb_image.cpp$(DependSuffix): Libraries/stb_image/stb_image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/stb_image_stb_image.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/stb_image_stb_image.cpp$(DependSuffix) -MM "Libraries/stb_image/stb_image.cpp"

$(IntermediateDirectory)/stb_image_stb_image.cpp$(PreprocessSuffix): Libraries/stb_image/stb_image.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stb_image_stb_image.cpp$(PreprocessSuffix) "Libraries/stb_image/stb_image.cpp"

$(IntermediateDirectory)/mtrand_mtrand.cpp$(ObjectSuffix): Libraries/mtrand/mtrand.cpp $(IntermediateDirectory)/mtrand_mtrand.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SuperPlayLib/Libraries/mtrand/mtrand.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mtrand_mtrand.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mtrand_mtrand.cpp$(DependSuffix): Libraries/mtrand/mtrand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mtrand_mtrand.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/mtrand_mtrand.cpp$(DependSuffix) -MM "Libraries/mtrand/mtrand.cpp"

$(IntermediateDirectory)/mtrand_mtrand.cpp$(PreprocessSuffix): Libraries/mtrand/mtrand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mtrand_mtrand.cpp$(PreprocessSuffix) "Libraries/mtrand/mtrand.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-release/SuperPlay"


