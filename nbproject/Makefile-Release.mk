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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/config.o \
	${OBJECTDIR}/src/db-code.o \
	${OBJECTDIR}/src/device-table.o \
	${OBJECTDIR}/src/fda.o \
	${OBJECTDIR}/src/fields-input-iterator.o \
	${OBJECTDIR}/src/input_validator.o \
	${OBJECTDIR}/src/maude-ifstream.o \
	${OBJECTDIR}/src/mdr-report-key.o \
	${OBJECTDIR}/src/mdr-table.o \
	${OBJECTDIR}/src/medwatch-table.o \
	${OBJECTDIR}/src/table-factory.o \
	${OBJECTDIR}/src/text-table.o \
	${OBJECTDIR}/src/utility.o


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
LDLIBSOPTIONS=-lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fda

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fda: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/fda ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/config.o: src/config.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/config.o src/config.cpp

${OBJECTDIR}/src/db-code.o: src/db-code.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/db-code.o src/db-code.cpp

${OBJECTDIR}/src/device-table.o: src/device-table.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/device-table.o src/device-table.cpp

${OBJECTDIR}/src/fda.o: src/fda.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/fda.o src/fda.cpp

${OBJECTDIR}/src/fields-input-iterator.o: src/fields-input-iterator.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/fields-input-iterator.o src/fields-input-iterator.cpp

${OBJECTDIR}/src/input_validator.o: src/input_validator.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/input_validator.o src/input_validator.cpp

${OBJECTDIR}/src/maude-ifstream.o: src/maude-ifstream.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/maude-ifstream.o src/maude-ifstream.cpp

${OBJECTDIR}/src/mdr-report-key.o: src/mdr-report-key.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mdr-report-key.o src/mdr-report-key.cpp

${OBJECTDIR}/src/mdr-table.o: src/mdr-table.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mdr-table.o src/mdr-table.cpp

${OBJECTDIR}/src/medwatch-table.o: src/medwatch-table.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/medwatch-table.o src/medwatch-table.cpp

${OBJECTDIR}/src/table-factory.o: src/table-factory.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/table-factory.o src/table-factory.cpp

${OBJECTDIR}/src/text-table.o: src/text-table.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/text-table.o src/text-table.cpp

${OBJECTDIR}/src/utility.o: src/utility.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utility.o src/utility.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
