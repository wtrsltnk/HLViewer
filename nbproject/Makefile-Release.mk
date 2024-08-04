#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/miptexbasedfile.o \
	${OBJECTDIR}/mdlfile.o \
	${OBJECTDIR}/basefile.o \
	${OBJECTDIR}/Common/string.o \
	${OBJECTDIR}/treeviewitem.o \
	${OBJECTDIR}/error.o \
	${OBJECTDIR}/label.o \
	${OBJECTDIR}/textureview.o \
	${OBJECTDIR}/texturedialog.o \
	${OBJECTDIR}/bspfile.o \
	${OBJECTDIR}/containerview.o \
	${OBJECTDIR}/control.o \
	${OBJECTDIR}/listviewitem.o \
	${OBJECTDIR}/Common/common.o \
	${OBJECTDIR}/listview.o \
	${OBJECTDIR}/button.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/window.o \
	${OBJECTDIR}/treeview.o \
	${OBJECTDIR}/glcontrol.o \
	${OBJECTDIR}/dialog.o \
	${OBJECTDIR}/Common/stringlist.o \
	${OBJECTDIR}/wadfile.o \
	${OBJECTDIR}/wnd.o \
	${OBJECTDIR}/program.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lcomdlg32 -lcomctl32 -lglu32 -lgdi32 -lopengl32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/MinGW-Windows/hlviewer.exe

dist/Release/MinGW-Windows/hlviewer.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/MinGW-Windows
	${LINK.cc} -mwindows -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hlviewer.exe ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/miptexbasedfile.o: nbproject/Makefile-${CND_CONF}.mk miptexbasedfile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/miptexbasedfile.o miptexbasedfile.cpp

${OBJECTDIR}/mdlfile.o: nbproject/Makefile-${CND_CONF}.mk mdlfile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/mdlfile.o mdlfile.cpp

${OBJECTDIR}/basefile.o: nbproject/Makefile-${CND_CONF}.mk basefile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/basefile.o basefile.cpp

${OBJECTDIR}/Common/string.o: nbproject/Makefile-${CND_CONF}.mk Common/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/Common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Common/string.o Common/string.cpp

${OBJECTDIR}/treeviewitem.o: nbproject/Makefile-${CND_CONF}.mk treeviewitem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/treeviewitem.o treeviewitem.cpp

${OBJECTDIR}/error.o: nbproject/Makefile-${CND_CONF}.mk error.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/error.o error.cpp

${OBJECTDIR}/label.o: nbproject/Makefile-${CND_CONF}.mk label.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/label.o label.cpp

${OBJECTDIR}/textureview.o: nbproject/Makefile-${CND_CONF}.mk textureview.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/textureview.o textureview.cpp

${OBJECTDIR}/texturedialog.o: nbproject/Makefile-${CND_CONF}.mk texturedialog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/texturedialog.o texturedialog.cpp

${OBJECTDIR}/bspfile.o: nbproject/Makefile-${CND_CONF}.mk bspfile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/bspfile.o bspfile.cpp

${OBJECTDIR}/containerview.o: nbproject/Makefile-${CND_CONF}.mk containerview.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/containerview.o containerview.cpp

${OBJECTDIR}/control.o: nbproject/Makefile-${CND_CONF}.mk control.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/control.o control.cpp

${OBJECTDIR}/listviewitem.o: nbproject/Makefile-${CND_CONF}.mk listviewitem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/listviewitem.o listviewitem.cpp

${OBJECTDIR}/Common/common.o: nbproject/Makefile-${CND_CONF}.mk Common/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/Common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Common/common.o Common/common.cpp

${OBJECTDIR}/listview.o: nbproject/Makefile-${CND_CONF}.mk listview.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/listview.o listview.cpp

${OBJECTDIR}/button.o: nbproject/Makefile-${CND_CONF}.mk button.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/button.o button.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/window.o: nbproject/Makefile-${CND_CONF}.mk window.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/window.o window.cpp

${OBJECTDIR}/treeview.o: nbproject/Makefile-${CND_CONF}.mk treeview.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/treeview.o treeview.cpp

${OBJECTDIR}/glcontrol.o: nbproject/Makefile-${CND_CONF}.mk glcontrol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/glcontrol.o glcontrol.cpp

${OBJECTDIR}/dialog.o: nbproject/Makefile-${CND_CONF}.mk dialog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/dialog.o dialog.cpp

${OBJECTDIR}/Common/stringlist.o: nbproject/Makefile-${CND_CONF}.mk Common/stringlist.cpp 
	${MKDIR} -p ${OBJECTDIR}/Common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Common/stringlist.o Common/stringlist.cpp

${OBJECTDIR}/wadfile.o: nbproject/Makefile-${CND_CONF}.mk wadfile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/wadfile.o wadfile.cpp

${OBJECTDIR}/wnd.o: nbproject/Makefile-${CND_CONF}.mk wnd.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/wnd.o wnd.cpp

${OBJECTDIR}/program.o: nbproject/Makefile-${CND_CONF}.mk program.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/program.o program.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/MinGW-Windows/hlviewer.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
