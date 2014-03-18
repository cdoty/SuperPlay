##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Tilemap
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/Examples/Tilemap"
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
OutputFile             :=Environment/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Tilemap.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -pthread
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../Include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ExpansionLib_d $(LibrarySwitch)SuperPlay_d $(LibrarySwitch)Platform_d $(LibrarySwitch)Sound_d $(LibrarySwitch)Display_d $(LibrarySwitch)IrrKlang $(LibrarySwitch)SDL2 $(LibrarySwitch)X11 $(LibrarySwitch)GLU $(LibrarySwitch)GL $(LibrarySwitch)Xext 
ArLibs                 :=  "ExpansionLib_d" "SuperPlay_d" "Platform_d" "Sound_d" "Display_d" "IrrKlang" "SDL2" "X11" "GLU" "GL" "Xext" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../Lib/Linux $(LibraryPathSwitch)../../Lib/Linux/irrKlang $(LibraryPathSwitch)../../External/irrKlang-1.4.0b/lib/Linux 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Game$(ObjectSuffix) $(IntermediateDirectory)/GameHeader$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Game$(ObjectSuffix): Game.cpp $(IntermediateDirectory)/Game$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/Tilemap/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Game$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Game$(DependSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Game$(ObjectSuffix) -MF$(IntermediateDirectory)/Game$(DependSuffix) -MM "Game.cpp"

$(IntermediateDirectory)/Game$(PreprocessSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Game$(PreprocessSuffix) "Game.cpp"

$(IntermediateDirectory)/GameHeader$(ObjectSuffix): GameHeader.cpp $(IntermediateDirectory)/GameHeader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/Tilemap/GameHeader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameHeader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameHeader$(DependSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameHeader$(ObjectSuffix) -MF$(IntermediateDirectory)/GameHeader$(DependSuffix) -MM "GameHeader.cpp"

$(IntermediateDirectory)/GameHeader$(PreprocessSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameHeader$(PreprocessSuffix) "GameHeader.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Game$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Game$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Game$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameHeader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameHeader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameHeader$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-debug/Tilemap"


