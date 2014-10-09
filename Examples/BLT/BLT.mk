##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=BLT
ConfigurationName      :=Release
WorkspacePath          := "/home/cdoty/SuperPlay"
ProjectPath            := "/home/cdoty/SuperPlay/Examples/BLT"
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
OutputFile             :=Environment/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
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
Objects0=$(IntermediateDirectory)/Background.cpp$(ObjectSuffix) $(IntermediateDirectory)/BaseSprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/BulletManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/BulletSprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/EnemyManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/EnemySprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/FPS.cpp$(ObjectSuffix) $(IntermediateDirectory)/Game.cpp$(ObjectSuffix) $(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix) $(IntermediateDirectory)/PlayerSprite.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/ScoreBar.cpp$(ObjectSuffix) $(IntermediateDirectory)/GameResources.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/Background.cpp$(ObjectSuffix): Background.cpp $(IntermediateDirectory)/Background.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/Background.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Background.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Background.cpp$(DependSuffix): Background.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Background.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Background.cpp$(DependSuffix) -MM "Background.cpp"

$(IntermediateDirectory)/Background.cpp$(PreprocessSuffix): Background.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Background.cpp$(PreprocessSuffix) "Background.cpp"

$(IntermediateDirectory)/BaseSprite.cpp$(ObjectSuffix): BaseSprite.cpp $(IntermediateDirectory)/BaseSprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/BaseSprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BaseSprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BaseSprite.cpp$(DependSuffix): BaseSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BaseSprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BaseSprite.cpp$(DependSuffix) -MM "BaseSprite.cpp"

$(IntermediateDirectory)/BaseSprite.cpp$(PreprocessSuffix): BaseSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BaseSprite.cpp$(PreprocessSuffix) "BaseSprite.cpp"

$(IntermediateDirectory)/BulletManager.cpp$(ObjectSuffix): BulletManager.cpp $(IntermediateDirectory)/BulletManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/BulletManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BulletManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BulletManager.cpp$(DependSuffix): BulletManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BulletManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BulletManager.cpp$(DependSuffix) -MM "BulletManager.cpp"

$(IntermediateDirectory)/BulletManager.cpp$(PreprocessSuffix): BulletManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BulletManager.cpp$(PreprocessSuffix) "BulletManager.cpp"

$(IntermediateDirectory)/BulletSprite.cpp$(ObjectSuffix): BulletSprite.cpp $(IntermediateDirectory)/BulletSprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/BulletSprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BulletSprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BulletSprite.cpp$(DependSuffix): BulletSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BulletSprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/BulletSprite.cpp$(DependSuffix) -MM "BulletSprite.cpp"

$(IntermediateDirectory)/BulletSprite.cpp$(PreprocessSuffix): BulletSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BulletSprite.cpp$(PreprocessSuffix) "BulletSprite.cpp"

$(IntermediateDirectory)/EnemyManager.cpp$(ObjectSuffix): EnemyManager.cpp $(IntermediateDirectory)/EnemyManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/EnemyManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EnemyManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EnemyManager.cpp$(DependSuffix): EnemyManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EnemyManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/EnemyManager.cpp$(DependSuffix) -MM "EnemyManager.cpp"

$(IntermediateDirectory)/EnemyManager.cpp$(PreprocessSuffix): EnemyManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EnemyManager.cpp$(PreprocessSuffix) "EnemyManager.cpp"

$(IntermediateDirectory)/EnemySprite.cpp$(ObjectSuffix): EnemySprite.cpp $(IntermediateDirectory)/EnemySprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/EnemySprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EnemySprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EnemySprite.cpp$(DependSuffix): EnemySprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EnemySprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/EnemySprite.cpp$(DependSuffix) -MM "EnemySprite.cpp"

$(IntermediateDirectory)/EnemySprite.cpp$(PreprocessSuffix): EnemySprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EnemySprite.cpp$(PreprocessSuffix) "EnemySprite.cpp"

$(IntermediateDirectory)/FPS.cpp$(ObjectSuffix): FPS.cpp $(IntermediateDirectory)/FPS.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/FPS.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FPS.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FPS.cpp$(DependSuffix): FPS.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FPS.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FPS.cpp$(DependSuffix) -MM "FPS.cpp"

$(IntermediateDirectory)/FPS.cpp$(PreprocessSuffix): FPS.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FPS.cpp$(PreprocessSuffix) "FPS.cpp"

$(IntermediateDirectory)/Game.cpp$(ObjectSuffix): Game.cpp $(IntermediateDirectory)/Game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/Game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Game.cpp$(DependSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Game.cpp$(DependSuffix) -MM "Game.cpp"

$(IntermediateDirectory)/Game.cpp$(PreprocessSuffix): Game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Game.cpp$(PreprocessSuffix) "Game.cpp"

$(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix): GameHeader.cpp $(IntermediateDirectory)/GameHeader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/GameHeader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameHeader.cpp$(DependSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameHeader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GameHeader.cpp$(DependSuffix) -MM "GameHeader.cpp"

$(IntermediateDirectory)/GameHeader.cpp$(PreprocessSuffix): GameHeader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameHeader.cpp$(PreprocessSuffix) "GameHeader.cpp"

$(IntermediateDirectory)/PlayerSprite.cpp$(ObjectSuffix): PlayerSprite.cpp $(IntermediateDirectory)/PlayerSprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/PlayerSprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PlayerSprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PlayerSprite.cpp$(DependSuffix): PlayerSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PlayerSprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PlayerSprite.cpp$(DependSuffix) -MM "PlayerSprite.cpp"

$(IntermediateDirectory)/PlayerSprite.cpp$(PreprocessSuffix): PlayerSprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PlayerSprite.cpp$(PreprocessSuffix) "PlayerSprite.cpp"

$(IntermediateDirectory)/ScoreBar.cpp$(ObjectSuffix): ScoreBar.cpp $(IntermediateDirectory)/ScoreBar.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/ScoreBar.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ScoreBar.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ScoreBar.cpp$(DependSuffix): ScoreBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ScoreBar.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ScoreBar.cpp$(DependSuffix) -MM "ScoreBar.cpp"

$(IntermediateDirectory)/ScoreBar.cpp$(PreprocessSuffix): ScoreBar.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ScoreBar.cpp$(PreprocessSuffix) "ScoreBar.cpp"

$(IntermediateDirectory)/GameResources.cpp$(ObjectSuffix): GameResources.cpp $(IntermediateDirectory)/GameResources.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/cdoty/SuperPlay/Examples/BLT/GameResources.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameResources.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameResources.cpp$(DependSuffix): GameResources.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameResources.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GameResources.cpp$(DependSuffix) -MM "GameResources.cpp"

$(IntermediateDirectory)/GameResources.cpp$(PreprocessSuffix): GameResources.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameResources.cpp$(PreprocessSuffix) "GameResources.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Release/*$(ObjectSuffix)
	$(RM) ./Release/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../.build-release/BLT"


