##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Display
ConfigurationName      :=Release
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/DisplayLib/SDL"
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
OutputFile             :=../../Lib/Linux/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Display.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../Include $(IncludeSwitch)../../Include $(IncludeSwitch)../../PlatformLib/Include $(IncludeSwitch)../../PlatformLib/Linux $(IncludeSwitch)../../SuperPlayLib/Include 
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
Objects0=$(IntermediateDirectory)/Display.cpp$(ObjectSuffix) $(IntermediateDirectory)/IndexBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpriteBatch.cpp$(ObjectSuffix) $(IntermediateDirectory)/Texture.cpp$(ObjectSuffix) $(IntermediateDirectory)/VertexBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/glew.cpp$(ObjectSuffix) $(IntermediateDirectory)/GLPlatform.cpp$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-release/Display"

./Release:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Display.cpp$(ObjectSuffix): Display.cpp $(IntermediateDirectory)/Display.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/Display.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Display.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Display.cpp$(DependSuffix): Display.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Display.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Display.cpp$(DependSuffix) -MM "Display.cpp"

$(IntermediateDirectory)/Display.cpp$(PreprocessSuffix): Display.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Display.cpp$(PreprocessSuffix) "Display.cpp"

$(IntermediateDirectory)/IndexBuffer.cpp$(ObjectSuffix): IndexBuffer.cpp $(IntermediateDirectory)/IndexBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/IndexBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IndexBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IndexBuffer.cpp$(DependSuffix): IndexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IndexBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IndexBuffer.cpp$(DependSuffix) -MM "IndexBuffer.cpp"

$(IntermediateDirectory)/IndexBuffer.cpp$(PreprocessSuffix): IndexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IndexBuffer.cpp$(PreprocessSuffix) "IndexBuffer.cpp"

$(IntermediateDirectory)/SpriteBatch.cpp$(ObjectSuffix): SpriteBatch.cpp $(IntermediateDirectory)/SpriteBatch.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/SpriteBatch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpriteBatch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpriteBatch.cpp$(DependSuffix): SpriteBatch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpriteBatch.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpriteBatch.cpp$(DependSuffix) -MM "SpriteBatch.cpp"

$(IntermediateDirectory)/SpriteBatch.cpp$(PreprocessSuffix): SpriteBatch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpriteBatch.cpp$(PreprocessSuffix) "SpriteBatch.cpp"

$(IntermediateDirectory)/Texture.cpp$(ObjectSuffix): Texture.cpp $(IntermediateDirectory)/Texture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/Texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Texture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Texture.cpp$(DependSuffix): Texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Texture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Texture.cpp$(DependSuffix) -MM "Texture.cpp"

$(IntermediateDirectory)/Texture.cpp$(PreprocessSuffix): Texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Texture.cpp$(PreprocessSuffix) "Texture.cpp"

$(IntermediateDirectory)/VertexBuffer.cpp$(ObjectSuffix): VertexBuffer.cpp $(IntermediateDirectory)/VertexBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/VertexBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VertexBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VertexBuffer.cpp$(DependSuffix): VertexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VertexBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/VertexBuffer.cpp$(DependSuffix) -MM "VertexBuffer.cpp"

$(IntermediateDirectory)/VertexBuffer.cpp$(PreprocessSuffix): VertexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VertexBuffer.cpp$(PreprocessSuffix) "VertexBuffer.cpp"

$(IntermediateDirectory)/glew.cpp$(ObjectSuffix): glew.cpp $(IntermediateDirectory)/glew.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/glew.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/glew.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/glew.cpp$(DependSuffix): glew.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/glew.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/glew.cpp$(DependSuffix) -MM "glew.cpp"

$(IntermediateDirectory)/glew.cpp$(PreprocessSuffix): glew.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/glew.cpp$(PreprocessSuffix) "glew.cpp"

$(IntermediateDirectory)/GLPlatform.cpp$(ObjectSuffix): GLPlatform.cpp $(IntermediateDirectory)/GLPlatform.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/GLPlatform.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GLPlatform.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GLPlatform.cpp$(DependSuffix): GLPlatform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GLPlatform.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GLPlatform.cpp$(DependSuffix) -MM "GLPlatform.cpp"

$(IntermediateDirectory)/GLPlatform.cpp$(PreprocessSuffix): GLPlatform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GLPlatform.cpp$(PreprocessSuffix) "GLPlatform.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-release/Display"


