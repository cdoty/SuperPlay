##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Display
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/DisplayLib/SDL"
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
Objects0=$(IntermediateDirectory)/Display$(ObjectSuffix) $(IntermediateDirectory)/IndexBuffer$(ObjectSuffix) $(IntermediateDirectory)/SpriteBatch$(ObjectSuffix) $(IntermediateDirectory)/Texture$(ObjectSuffix) $(IntermediateDirectory)/VertexBuffer$(ObjectSuffix) $(IntermediateDirectory)/glew$(ObjectSuffix) $(IntermediateDirectory)/GLPlatform$(ObjectSuffix) 



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
	@echo rebuilt > "/home/cdoty/SuperPlay/.build-debug/Display"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Display$(ObjectSuffix): Display.cpp $(IntermediateDirectory)/Display$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/Display.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Display$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Display$(DependSuffix): Display.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Display$(ObjectSuffix) -MF$(IntermediateDirectory)/Display$(DependSuffix) -MM "Display.cpp"

$(IntermediateDirectory)/Display$(PreprocessSuffix): Display.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Display$(PreprocessSuffix) "Display.cpp"

$(IntermediateDirectory)/IndexBuffer$(ObjectSuffix): IndexBuffer.cpp $(IntermediateDirectory)/IndexBuffer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/IndexBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IndexBuffer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IndexBuffer$(DependSuffix): IndexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IndexBuffer$(ObjectSuffix) -MF$(IntermediateDirectory)/IndexBuffer$(DependSuffix) -MM "IndexBuffer.cpp"

$(IntermediateDirectory)/IndexBuffer$(PreprocessSuffix): IndexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IndexBuffer$(PreprocessSuffix) "IndexBuffer.cpp"

$(IntermediateDirectory)/SpriteBatch$(ObjectSuffix): SpriteBatch.cpp $(IntermediateDirectory)/SpriteBatch$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/SpriteBatch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpriteBatch$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpriteBatch$(DependSuffix): SpriteBatch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpriteBatch$(ObjectSuffix) -MF$(IntermediateDirectory)/SpriteBatch$(DependSuffix) -MM "SpriteBatch.cpp"

$(IntermediateDirectory)/SpriteBatch$(PreprocessSuffix): SpriteBatch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpriteBatch$(PreprocessSuffix) "SpriteBatch.cpp"

$(IntermediateDirectory)/Texture$(ObjectSuffix): Texture.cpp $(IntermediateDirectory)/Texture$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/Texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Texture$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Texture$(DependSuffix): Texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Texture$(ObjectSuffix) -MF$(IntermediateDirectory)/Texture$(DependSuffix) -MM "Texture.cpp"

$(IntermediateDirectory)/Texture$(PreprocessSuffix): Texture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Texture$(PreprocessSuffix) "Texture.cpp"

$(IntermediateDirectory)/VertexBuffer$(ObjectSuffix): VertexBuffer.cpp $(IntermediateDirectory)/VertexBuffer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/VertexBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VertexBuffer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VertexBuffer$(DependSuffix): VertexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VertexBuffer$(ObjectSuffix) -MF$(IntermediateDirectory)/VertexBuffer$(DependSuffix) -MM "VertexBuffer.cpp"

$(IntermediateDirectory)/VertexBuffer$(PreprocessSuffix): VertexBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VertexBuffer$(PreprocessSuffix) "VertexBuffer.cpp"

$(IntermediateDirectory)/glew$(ObjectSuffix): glew.cpp $(IntermediateDirectory)/glew$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/glew.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/glew$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/glew$(DependSuffix): glew.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/glew$(ObjectSuffix) -MF$(IntermediateDirectory)/glew$(DependSuffix) -MM "glew.cpp"

$(IntermediateDirectory)/glew$(PreprocessSuffix): glew.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/glew$(PreprocessSuffix) "glew.cpp"

$(IntermediateDirectory)/GLPlatform$(ObjectSuffix): GLPlatform.cpp $(IntermediateDirectory)/GLPlatform$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/DisplayLib/SDL/GLPlatform.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GLPlatform$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GLPlatform$(DependSuffix): GLPlatform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GLPlatform$(ObjectSuffix) -MF$(IntermediateDirectory)/GLPlatform$(DependSuffix) -MM "GLPlatform.cpp"

$(IntermediateDirectory)/GLPlatform$(PreprocessSuffix): GLPlatform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GLPlatform$(PreprocessSuffix) "GLPlatform.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Display$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Display$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Display$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/IndexBuffer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/IndexBuffer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/IndexBuffer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SpriteBatch$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SpriteBatch$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SpriteBatch$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Texture$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Texture$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Texture$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/VertexBuffer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/VertexBuffer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/VertexBuffer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/glew$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/glew$(DependSuffix)
	$(RM) $(IntermediateDirectory)/glew$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GLPlatform$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GLPlatform$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GLPlatform$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-debug/Display"


