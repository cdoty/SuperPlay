##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ExpansionLib
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/ExpansionLib"
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
Objects0=$(IntermediateDirectory)/FontLoader_FontLoader$(ObjectSuffix) $(IntermediateDirectory)/AudioLoader_AudioLoader$(ObjectSuffix) $(IntermediateDirectory)/HDMALoader_HDMALoader$(ObjectSuffix) $(IntermediateDirectory)/MapLoader_MapLoader$(ObjectSuffix) $(IntermediateDirectory)/SpriteLoader_SpriteLoader$(ObjectSuffix) $(IntermediateDirectory)/yspng_yspng$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-debug/ExpansionLib"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/FontLoader_FontLoader$(ObjectSuffix): FontLoader/FontLoader.cpp $(IntermediateDirectory)/FontLoader_FontLoader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/FontLoader/FontLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FontLoader_FontLoader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FontLoader_FontLoader$(DependSuffix): FontLoader/FontLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FontLoader_FontLoader$(ObjectSuffix) -MF$(IntermediateDirectory)/FontLoader_FontLoader$(DependSuffix) -MM "FontLoader/FontLoader.cpp"

$(IntermediateDirectory)/FontLoader_FontLoader$(PreprocessSuffix): FontLoader/FontLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FontLoader_FontLoader$(PreprocessSuffix) "FontLoader/FontLoader.cpp"

$(IntermediateDirectory)/AudioLoader_AudioLoader$(ObjectSuffix): AudioLoader/AudioLoader.cpp $(IntermediateDirectory)/AudioLoader_AudioLoader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/AudioLoader/AudioLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AudioLoader_AudioLoader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AudioLoader_AudioLoader$(DependSuffix): AudioLoader/AudioLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AudioLoader_AudioLoader$(ObjectSuffix) -MF$(IntermediateDirectory)/AudioLoader_AudioLoader$(DependSuffix) -MM "AudioLoader/AudioLoader.cpp"

$(IntermediateDirectory)/AudioLoader_AudioLoader$(PreprocessSuffix): AudioLoader/AudioLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AudioLoader_AudioLoader$(PreprocessSuffix) "AudioLoader/AudioLoader.cpp"

$(IntermediateDirectory)/HDMALoader_HDMALoader$(ObjectSuffix): HDMALoader/HDMALoader.cpp $(IntermediateDirectory)/HDMALoader_HDMALoader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/HDMALoader/HDMALoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HDMALoader_HDMALoader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HDMALoader_HDMALoader$(DependSuffix): HDMALoader/HDMALoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HDMALoader_HDMALoader$(ObjectSuffix) -MF$(IntermediateDirectory)/HDMALoader_HDMALoader$(DependSuffix) -MM "HDMALoader/HDMALoader.cpp"

$(IntermediateDirectory)/HDMALoader_HDMALoader$(PreprocessSuffix): HDMALoader/HDMALoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HDMALoader_HDMALoader$(PreprocessSuffix) "HDMALoader/HDMALoader.cpp"

$(IntermediateDirectory)/MapLoader_MapLoader$(ObjectSuffix): MapLoader/MapLoader.cpp $(IntermediateDirectory)/MapLoader_MapLoader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/MapLoader/MapLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MapLoader_MapLoader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MapLoader_MapLoader$(DependSuffix): MapLoader/MapLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MapLoader_MapLoader$(ObjectSuffix) -MF$(IntermediateDirectory)/MapLoader_MapLoader$(DependSuffix) -MM "MapLoader/MapLoader.cpp"

$(IntermediateDirectory)/MapLoader_MapLoader$(PreprocessSuffix): MapLoader/MapLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MapLoader_MapLoader$(PreprocessSuffix) "MapLoader/MapLoader.cpp"

$(IntermediateDirectory)/SpriteLoader_SpriteLoader$(ObjectSuffix): SpriteLoader/SpriteLoader.cpp $(IntermediateDirectory)/SpriteLoader_SpriteLoader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/SpriteLoader/SpriteLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpriteLoader_SpriteLoader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpriteLoader_SpriteLoader$(DependSuffix): SpriteLoader/SpriteLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpriteLoader_SpriteLoader$(ObjectSuffix) -MF$(IntermediateDirectory)/SpriteLoader_SpriteLoader$(DependSuffix) -MM "SpriteLoader/SpriteLoader.cpp"

$(IntermediateDirectory)/SpriteLoader_SpriteLoader$(PreprocessSuffix): SpriteLoader/SpriteLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpriteLoader_SpriteLoader$(PreprocessSuffix) "SpriteLoader/SpriteLoader.cpp"

$(IntermediateDirectory)/yspng_yspng$(ObjectSuffix): FontLoader/yspng/yspng.cpp $(IntermediateDirectory)/yspng_yspng$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/ExpansionLib/FontLoader/yspng/yspng.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/yspng_yspng$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/yspng_yspng$(DependSuffix): FontLoader/yspng/yspng.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/yspng_yspng$(ObjectSuffix) -MF$(IntermediateDirectory)/yspng_yspng$(DependSuffix) -MM "FontLoader/yspng/yspng.cpp"

$(IntermediateDirectory)/yspng_yspng$(PreprocessSuffix): FontLoader/yspng/yspng.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/yspng_yspng$(PreprocessSuffix) "FontLoader/yspng/yspng.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/FontLoader_FontLoader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/FontLoader_FontLoader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/FontLoader_FontLoader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/AudioLoader_AudioLoader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/AudioLoader_AudioLoader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/AudioLoader_AudioLoader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/HDMALoader_HDMALoader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/HDMALoader_HDMALoader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/HDMALoader_HDMALoader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/MapLoader_MapLoader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MapLoader_MapLoader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/MapLoader_MapLoader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SpriteLoader_SpriteLoader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SpriteLoader_SpriteLoader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SpriteLoader_SpriteLoader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/yspng_yspng$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/yspng_yspng$(DependSuffix)
	$(RM) $(IntermediateDirectory)/yspng_yspng$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/ExpansionLib"


