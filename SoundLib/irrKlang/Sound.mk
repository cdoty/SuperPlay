##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Sound
ConfigurationName      :=Release
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/SoundLib/irrKlang"
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
OutputFile             :=../../Lib/Linux/irrKlang/lib$(ProjectName).a
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
Objects0=$(IntermediateDirectory)/Sound.cpp$(ObjectSuffix) $(IntermediateDirectory)/SoundSystem.cpp$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-release/Sound"

./Release:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Sound.cpp$(ObjectSuffix): Sound.cpp $(IntermediateDirectory)/Sound.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SoundLib/irrKlang/Sound.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sound.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sound.cpp$(DependSuffix): Sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sound.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Sound.cpp$(DependSuffix) -MM "Sound.cpp"

$(IntermediateDirectory)/Sound.cpp$(PreprocessSuffix): Sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sound.cpp$(PreprocessSuffix) "Sound.cpp"

$(IntermediateDirectory)/SoundSystem.cpp$(ObjectSuffix): SoundSystem.cpp $(IntermediateDirectory)/SoundSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/SoundLib/irrKlang/SoundSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SoundSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SoundSystem.cpp$(DependSuffix): SoundSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SoundSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SoundSystem.cpp$(DependSuffix) -MM "SoundSystem.cpp"

$(IntermediateDirectory)/SoundSystem.cpp$(PreprocessSuffix): SoundSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SoundSystem.cpp$(PreprocessSuffix) "SoundSystem.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-release/Sound"


