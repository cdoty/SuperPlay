##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=ExpansionLib
ConfigurationName      :=Release
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/ExpansionLib"
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
ObjectsFileList        :="ExpansionLib.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../Include $(IncludeSwitch)../Include/Expansion $(IncludeSwitch)../SuperPlayLib/Include 
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
Objects0=$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/MapLoader_MapLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/yspng_yspng.cpp$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-release/ExpansionLib"

./Release:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(ObjectSuffix): FontLoader/FontLoader.cpp $(IntermediateDirectory)/FontLoader_FontLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/FontLoader/FontLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(DependSuffix): FontLoader/FontLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(DependSuffix) -MM "FontLoader/FontLoader.cpp"

$(IntermediateDirectory)/FontLoader_FontLoader.cpp$(PreprocessSuffix): FontLoader/FontLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FontLoader_FontLoader.cpp$(PreprocessSuffix) "FontLoader/FontLoader.cpp"

$(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(ObjectSuffix): AudioLoader/AudioLoader.cpp $(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/AudioLoader/AudioLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(DependSuffix): AudioLoader/AudioLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(DependSuffix) -MM "AudioLoader/AudioLoader.cpp"

$(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(PreprocessSuffix): AudioLoader/AudioLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AudioLoader_AudioLoader.cpp$(PreprocessSuffix) "AudioLoader/AudioLoader.cpp"

$(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(ObjectSuffix): HDMALoader/HDMALoader.cpp $(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/HDMALoader/HDMALoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(DependSuffix): HDMALoader/HDMALoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(DependSuffix) -MM "HDMALoader/HDMALoader.cpp"

$(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(PreprocessSuffix): HDMALoader/HDMALoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HDMALoader_HDMALoader.cpp$(PreprocessSuffix) "HDMALoader/HDMALoader.cpp"

$(IntermediateDirectory)/MapLoader_MapLoader.cpp$(ObjectSuffix): MapLoader/MapLoader.cpp $(IntermediateDirectory)/MapLoader_MapLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/MapLoader/MapLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MapLoader_MapLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MapLoader_MapLoader.cpp$(DependSuffix): MapLoader/MapLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MapLoader_MapLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MapLoader_MapLoader.cpp$(DependSuffix) -MM "MapLoader/MapLoader.cpp"

$(IntermediateDirectory)/MapLoader_MapLoader.cpp$(PreprocessSuffix): MapLoader/MapLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MapLoader_MapLoader.cpp$(PreprocessSuffix) "MapLoader/MapLoader.cpp"

$(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(ObjectSuffix): SpriteLoader/SpriteLoader.cpp $(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/SpriteLoader/SpriteLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(DependSuffix): SpriteLoader/SpriteLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(DependSuffix) -MM "SpriteLoader/SpriteLoader.cpp"

$(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(PreprocessSuffix): SpriteLoader/SpriteLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpriteLoader_SpriteLoader.cpp$(PreprocessSuffix) "SpriteLoader/SpriteLoader.cpp"

$(IntermediateDirectory)/yspng_yspng.cpp$(ObjectSuffix): FontLoader/yspng/yspng.cpp $(IntermediateDirectory)/yspng_yspng.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/FontLoader/yspng/yspng.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/yspng_yspng.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/yspng_yspng.cpp$(DependSuffix): FontLoader/yspng/yspng.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/yspng_yspng.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/yspng_yspng.cpp$(DependSuffix) -MM "FontLoader/yspng/yspng.cpp"

$(IntermediateDirectory)/yspng_yspng.cpp$(PreprocessSuffix): FontLoader/yspng/yspng.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/yspng_yspng.cpp$(PreprocessSuffix) "FontLoader/yspng/yspng.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-release/ExpansionLib"


