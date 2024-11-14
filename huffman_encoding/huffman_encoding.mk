##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=huffman_encoding
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/Users/Admin/Desktop/huffman_encoding
ProjectPath            :=C:/Users/Admin/Desktop/huffman_encoding/huffman_encoding
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/huffman_encoding
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Admin
Date                   :=06/11/2024
CodeLitePath           :="C:/Program Files/CodeLite"
MakeDirCommand         :=mkdir -p
LinkerName             :=C:/cygwin64/bin/gcc.exe
SharedObjectLinkerName :=C:/cygwin64/bin/gcc.exe -shared -fPIC
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
OutputDirectory        :=C:/Users/Admin/Desktop/huffman_encoding/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName).exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -static
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := C:/cygwin64/bin/ar.exe rcu
CXX      := C:/cygwin64/bin/x86_64-pc-cygwin-g++.exe
CC       := C:/cygwin64/bin/gcc.exe
CXXFLAGS :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
CFLAGS   :=  -O0 -gdwarf-2 -std=c99 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/cygwin64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/huffman.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@$(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/huffman.c$(ObjectSuffix): huffman.c $(IntermediateDirectory)/huffman.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Admin/Desktop/huffman_encoding/huffman_encoding/huffman.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/huffman.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/huffman.c$(DependSuffix): huffman.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/huffman.c$(ObjectSuffix) -MF$(IntermediateDirectory)/huffman.c$(DependSuffix) -MM huffman.c

$(IntermediateDirectory)/huffman.c$(PreprocessSuffix): huffman.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/huffman.c$(PreprocessSuffix) huffman.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


