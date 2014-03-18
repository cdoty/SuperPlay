##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=BLT
ConfigurationName      :=Debug
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/Examples/BLT"
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
ObjectsFileList        :="BLT.txt"
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
CXXFLAGS :=  -g -O0 $(Preprocessors)
CFLAGS   :=  -g -O0 $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Background$(ObjectSuffix) $(IntermediateDirectory)/BaseSprite$(ObjectSuffix) $(IntermediateDirectory)/BulletManager$(ObjectSuffix) $(IntermediateDirectory)/BulletSprite$(ObjectSuffix) $(IntermediateDirectory)/EnemyManager$(ObjectSuffix) $(IntermediateDirectory)/EnemySprite$(ObjectSuffix) $(IntermediateDirectory)/FPS$(ObjectSuffix) $(IntermediateDirectory)/Game$(ObjectSuffix) $(IntermediateDirectory)/GameHeader$(ObjectSuffix) $(IntermediateDirectory)/PlayerSprite$(ObjectSuffix) \
	$(IntermediateDirectory)/ResourceManager$(ObjectSuffix) $(IntermediateDirectory)/ScoreBar$(ObjectSuffix) 



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
$(IntermediateDirectory)/Background$(ObjectSuffix): Background.cpp $(IntermediateDirectory)/Background$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/Background.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Background$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Background$(DependSuffix): Background.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Background$(ObjectSuffix) -MF$(IntermediateDirectory)/Background$(DependSuffix) -MM "Background.cpp"

$(IntermediateDirectory)/Background$(PreprocessSuffix): Background.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Background$(PreprocessSuffix) "Background.cpp"

$(IntermediateDirectory)/BaseSprite$(ObjectSuffix): BaseSprite.cpp $(IntermediateDirectory)/BaseSprite$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/BaseSprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BaseSprite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BaseSprite$(DependSuffix): BaseSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BaseSprite$(ObjectSuffix) -MF$(IntermediateDirectory)/BaseSprite$(DependSuffix) -MM "BaseSprite.cpp"

$(IntermediateDirectory)/BaseSprite$(PreprocessSuffix): BaseSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BaseSprite$(PreprocessSuffix) "BaseSprite.cpp"

$(IntermediateDirectory)/BulletManager$(ObjectSuffix): BulletManager.cpp $(IntermediateDirectory)/BulletManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/BulletManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BulletManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BulletManager$(DependSuffix): BulletManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BulletManager$(ObjectSuffix) -MF$(IntermediateDirectory)/BulletManager$(DependSuffix) -MM "BulletManager.cpp"

$(IntermediateDirectory)/BulletManager$(PreprocessSuffix): BulletManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BulletManager$(PreprocessSuffix) "BulletManager.cpp"

$(IntermediateDirectory)/BulletSprite$(ObjectSuffix): BulletSprite.cpp $(IntermediateDirectory)/BulletSprite$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/BulletSprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BulletSprite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BulletSprite$(DependSuffix): BulletSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BulletSprite$(ObjectSuffix) -MF$(IntermediateDirectory)/BulletSprite$(DependSuffix) -MM "BulletSprite.cpp"

$(IntermediateDirectory)/BulletSprite$(PreprocessSuffix): BulletSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BulletSprite$(PreprocessSuffix) "BulletSprite.cpp"

$(IntermediateDirectory)/EnemyManager$(ObjectSuffix): EnemyManager.cpp $(IntermediateDirectory)/EnemyManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/EnemyManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EnemyManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EnemyManager$(DependSuffix): EnemyManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EnemyManager$(ObjectSuffix) -MF$(IntermediateDirectory)/EnemyManager$(DependSuffix) -MM "EnemyManager.cpp"

$(IntermediateDirectory)/EnemyManager$(PreprocessSuffix): EnemyManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EnemyManager$(PreprocessSuffix) "EnemyManager.cpp"

$(IntermediateDirectory)/EnemySprite$(ObjectSuffix): EnemySprite.cpp $(IntermediateDirectory)/EnemySprite$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/EnemySprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EnemySprite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EnemySprite$(DependSuffix): EnemySprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EnemySprite$(ObjectSuffix) -MF$(IntermediateDirectory)/EnemySprite$(DependSuffix) -MM "EnemySprite.cpp"

$(IntermediateDirectory)/EnemySprite$(PreprocessSuffix): EnemySprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EnemySprite$(PreprocessSuffix) "EnemySprite.cpp"

$(IntermediateDirectory)/FPS$(ObjectSuffix): FPS.cpp $(IntermediateDirectory)/FPS$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/FPS.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FPS$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FPS$(DependSuffix): FPS.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FPS$(ObjectSuffix) -MF$(IntermediateDirectory)/FPS$(DependSuffix) -MM "FPS.cpp"

$(IntermediateDirectory)/FPS$(PreprocessSuffix): FPS.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FPS$(PreprocessSuffix) "FPS.cpp"

$(IntermediateDirectory)/Game$(ObjectSuffix): Game.cpp $(IntermediateDirectory)/Game$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Game$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Game$(DependSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Game$(ObjectSuffix) -MF$(IntermediateDirectory)/Game$(DependSuffix) -MM "Game.cpp"

$(IntermediateDirectory)/Game$(PreprocessSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Game$(PreprocessSuffix) "Game.cpp"

$(IntermediateDirectory)/GameHeader$(ObjectSuffix): GameHeader.cpp $(IntermediateDirectory)/GameHeader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/GameHeader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameHeader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameHeader$(DependSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameHeader$(ObjectSuffix) -MF$(IntermediateDirectory)/GameHeader$(DependSuffix) -MM "GameHeader.cpp"

$(IntermediateDirectory)/GameHeader$(PreprocessSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameHeader$(PreprocessSuffix) "GameHeader.cpp"

$(IntermediateDirectory)/PlayerSprite$(ObjectSuffix): PlayerSprite.cpp $(IntermediateDirectory)/PlayerSprite$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/PlayerSprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PlayerSprite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PlayerSprite$(DependSuffix): PlayerSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PlayerSprite$(ObjectSuffix) -MF$(IntermediateDirectory)/PlayerSprite$(DependSuffix) -MM "PlayerSprite.cpp"

$(IntermediateDirectory)/PlayerSprite$(PreprocessSuffix): PlayerSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PlayerSprite$(PreprocessSuffix) "PlayerSprite.cpp"

$(IntermediateDirectory)/ResourceManager$(ObjectSuffix): ResourceManager.cpp $(IntermediateDirectory)/ResourceManager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/ResourceManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ResourceManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ResourceManager$(DependSuffix): ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ResourceManager$(ObjectSuffix) -MF$(IntermediateDirectory)/ResourceManager$(DependSuffix) -MM "ResourceManager.cpp"

$(IntermediateDirectory)/ResourceManager$(PreprocessSuffix): ResourceManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ResourceManager$(PreprocessSuffix) "ResourceManager.cpp"

$(IntermediateDirectory)/ScoreBar$(ObjectSuffix): ScoreBar.cpp $(IntermediateDirectory)/ScoreBar$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/ScoreBar.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ScoreBar$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ScoreBar$(DependSuffix): ScoreBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ScoreBar$(ObjectSuffix) -MF$(IntermediateDirectory)/ScoreBar$(DependSuffix) -MM "ScoreBar.cpp"

$(IntermediateDirectory)/ScoreBar$(PreprocessSuffix): ScoreBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ScoreBar$(PreprocessSuffix) "ScoreBar.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Background$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Background$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Background$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/BaseSprite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/BaseSprite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/BaseSprite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/BulletManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/BulletManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/BulletManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/BulletSprite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/BulletSprite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/BulletSprite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/EnemyManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EnemyManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/EnemyManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/EnemySprite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EnemySprite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/EnemySprite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/FPS$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/FPS$(DependSuffix)
	$(RM) $(IntermediateDirectory)/FPS$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Game$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Game$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Game$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GameHeader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameHeader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameHeader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PlayerSprite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PlayerSprite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PlayerSprite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ResourceManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ResourceManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ResourceManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ScoreBar$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ScoreBar$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ScoreBar$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-debug/BLT"


