##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Platform
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/PlatformLib/Linux"
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
OutputFile             :=../../Lib/Linux/lib$(ProjectName)_d.a
Preprocessors          :=$(PreprocessorSwitch)DEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Platform.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../Include $(IncludeSwitch)../../Include $(IncludeSwitch)../../DisplayLib/Include $(IncludeSwitch)../../SoundLib/Include $(IncludeSwitch)../../SuperPlayLib/Include 
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
Objects0=$(IntermediateDirectory)/File$(ObjectSuffix) $(IntermediateDirectory)/Input$(ObjectSuffix) $(IntermediateDirectory)/Log$(ObjectSuffix) $(IntermediateDirectory)/Main$(ObjectSuffix) $(IntermediateDirectory)/Platform$(ObjectSuffix) $(IntermediateDirectory)/Timer$(ObjectSuffix) $(IntermediateDirectory)/Window$(ObjectSuffix) $(IntermediateDirectory)/StoragePath$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-debug/Platform"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/File$(ObjectSuffix): File.cpp $(IntermediateDirectory)/File$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/File.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/File$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/File$(DependSuffix): File.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/File$(ObjectSuffix) -MF$(IntermediateDirectory)/File$(DependSuffix) -MM "File.cpp"

$(IntermediateDirectory)/File$(PreprocessSuffix): File.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/File$(PreprocessSuffix) "File.cpp"

$(IntermediateDirectory)/Input$(ObjectSuffix): Input.cpp $(IntermediateDirectory)/Input$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/Input.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Input$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Input$(DependSuffix): Input.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Input$(ObjectSuffix) -MF$(IntermediateDirectory)/Input$(DependSuffix) -MM "Input.cpp"

$(IntermediateDirectory)/Input$(PreprocessSuffix): Input.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Input$(PreprocessSuffix) "Input.cpp"

$(IntermediateDirectory)/Log$(ObjectSuffix): Log.cpp $(IntermediateDirectory)/Log$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/Log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Log$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Log$(DependSuffix): Log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Log$(ObjectSuffix) -MF$(IntermediateDirectory)/Log$(DependSuffix) -MM "Log.cpp"

$(IntermediateDirectory)/Log$(PreprocessSuffix): Log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Log$(PreprocessSuffix) "Log.cpp"

$(IntermediateDirectory)/Main$(ObjectSuffix): Main.cpp $(IntermediateDirectory)/Main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Main$(DependSuffix): Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Main$(ObjectSuffix) -MF$(IntermediateDirectory)/Main$(DependSuffix) -MM "Main.cpp"

$(IntermediateDirectory)/Main$(PreprocessSuffix): Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Main$(PreprocessSuffix) "Main.cpp"

$(IntermediateDirectory)/Platform$(ObjectSuffix): Platform.cpp $(IntermediateDirectory)/Platform$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/Platform.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Platform$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Platform$(DependSuffix): Platform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Platform$(ObjectSuffix) -MF$(IntermediateDirectory)/Platform$(DependSuffix) -MM "Platform.cpp"

$(IntermediateDirectory)/Platform$(PreprocessSuffix): Platform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Platform$(PreprocessSuffix) "Platform.cpp"

$(IntermediateDirectory)/Timer$(ObjectSuffix): Timer.cpp $(IntermediateDirectory)/Timer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/Timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Timer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Timer$(DependSuffix): Timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Timer$(ObjectSuffix) -MF$(IntermediateDirectory)/Timer$(DependSuffix) -MM "Timer.cpp"

$(IntermediateDirectory)/Timer$(PreprocessSuffix): Timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Timer$(PreprocessSuffix) "Timer.cpp"

$(IntermediateDirectory)/Window$(ObjectSuffix): Window.cpp $(IntermediateDirectory)/Window$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/Window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Window$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Window$(DependSuffix): Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Window$(ObjectSuffix) -MF$(IntermediateDirectory)/Window$(DependSuffix) -MM "Window.cpp"

$(IntermediateDirectory)/Window$(PreprocessSuffix): Window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Window$(PreprocessSuffix) "Window.cpp"

$(IntermediateDirectory)/StoragePath$(ObjectSuffix): StoragePath.cpp $(IntermediateDirectory)/StoragePath$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/PlatformLib/Linux/StoragePath.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StoragePath$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StoragePath$(DependSuffix): StoragePath.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StoragePath$(ObjectSuffix) -MF$(IntermediateDirectory)/StoragePath$(DependSuffix) -MM "StoragePath.cpp"

$(IntermediateDirectory)/StoragePath$(PreprocessSuffix): StoragePath.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StoragePath$(PreprocessSuffix) "StoragePath.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/File$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/File$(DependSuffix)
	$(RM) $(IntermediateDirectory)/File$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Input$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Input$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Input$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Log$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Log$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Log$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Platform$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Platform$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Platform$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Timer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Timer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Timer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Window$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Window$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Window$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/StoragePath$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/StoragePath$(DependSuffix)
	$(RM) $(IntermediateDirectory)/StoragePath$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-debug/Platform"


