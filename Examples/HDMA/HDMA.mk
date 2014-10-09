##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=HDMA
ConfigurationName      :=Release
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/Examples/HDMA"
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
OutputFile             :=Environment/$(ProjectName)Demo
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="HDMA.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../Include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ExpansionLib $(LibrarySwitch)SuperPlay $(LibrarySwitch)Platform $(LibrarySwitch)Sound $(LibrarySwitch)Display $(LibrarySwitch)IrrKlang $(LibrarySwitch)SDL2 $(LibrarySwitch)X11 $(LibrarySwitch)GLU $(LibrarySwitch)GL $(LibrarySwitch)Xext 
ArLibs                 :=  "ExpansionLib" "SuperPlay" "Platform" "Sound" "Display" "IrrKlang" "SDL2" "X11" "GLU" "GL" "Xext" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../Lib/Linux $(LibraryPathSwitch)../../Lib/Linux/irrKlang $(LibraryPathSwitch)../../External/irrKlang-1.4.0b/lib/Linux 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) $(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix) $(IntermediateDirectory)/FPS.cpp$(ObjectSuffix) 



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
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Game.cpp$(ObjectSuffix): Game.cpp $(IntermediateDirectory)/Game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/HDMA/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Game.cpp$(DependSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Game.cpp$(DependSuffix) -MM "Game.cpp"

$(IntermediateDirectory)/Game.cpp$(PreprocessSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Game.cpp$(PreprocessSuffix) "Game.cpp"

$(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix): GameHeader.cpp $(IntermediateDirectory)/GameHeader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/HDMA/GameHeader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameHeader.cpp$(DependSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GameHeader.cpp$(DependSuffix) -MM "GameHeader.cpp"

$(IntermediateDirectory)/GameHeader.cpp$(PreprocessSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameHeader.cpp$(PreprocessSuffix) "GameHeader.cpp"

$(IntermediateDirectory)/FPS.cpp$(ObjectSuffix): FPS.cpp $(IntermediateDirectory)/FPS.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/HDMA/FPS.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FPS.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FPS.cpp$(DependSuffix): FPS.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FPS.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FPS.cpp$(DependSuffix) -MM "FPS.cpp"

$(IntermediateDirectory)/FPS.cpp$(PreprocessSuffix): FPS.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FPS.cpp$(PreprocessSuffix) "FPS.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-release/HDMA"


