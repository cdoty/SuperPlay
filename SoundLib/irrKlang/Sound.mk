##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Sound
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/SoundLib/irrKlang"
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
OutputFile             :=../../Lib/Linux/irrKlang/lib$(ProjectName)_d.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Sound.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../Include $(IncludeSwitch)../../Include $(IncludeSwitch)../../External/irrKlang-1.4.0b/include $(IncludeSwitch)../../PlatformLib/Include $(IncludeSwitch)../../PlatformLib/Linux $(IncludeSwitch)../../SuperPlayLib/Include 
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
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Sound$(ObjectSuffix) $(IntermediateDirectory)/SoundSystem$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-debug/Sound"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Sound$(ObjectSuffix): Sound.cpp $(IntermediateDirectory)/Sound$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SoundLib/irrKlang/Sound.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sound$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sound$(DependSuffix): Sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sound$(ObjectSuffix) -MF$(IntermediateDirectory)/Sound$(DependSuffix) -MM "Sound.cpp"

$(IntermediateDirectory)/Sound$(PreprocessSuffix): Sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sound$(PreprocessSuffix) "Sound.cpp"

$(IntermediateDirectory)/SoundSystem$(ObjectSuffix): SoundSystem.cpp $(IntermediateDirectory)/SoundSystem$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SoundLib/irrKlang/SoundSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SoundSystem$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SoundSystem$(DependSuffix): SoundSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SoundSystem$(ObjectSuffix) -MF$(IntermediateDirectory)/SoundSystem$(DependSuffix) -MM "SoundSystem.cpp"

$(IntermediateDirectory)/SoundSystem$(PreprocessSuffix): SoundSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SoundSystem$(PreprocessSuffix) "SoundSystem.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Sound$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Sound$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Sound$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SoundSystem$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SoundSystem$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SoundSystem$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-debug/Sound"


