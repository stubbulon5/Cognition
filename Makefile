# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
    OF_ROOT=$(realpath ../../..)
endif

# CXXFLAGS += -Wno-sign-compare -Wno-unknown-pragmas -Wno-unused-variable -Wno-switch -Wno-reorder -Wno-comment -Wno-unused-but-set-variable -Wno-parentheses -Wno-class-memacces -Wno-conversion-null
# CXXFLAGS += -w # hide all compilation warnings - dangeroud to use 
CXXFLAGS += -Wfatal-errors -Wno-sign-compare -Wno-unknown-pragmas -Wno-unused-variable -Wno-switch -Wno-reorder -Wno-comment -Wno-unused-but-set-variable -Wno-parentheses -Wno-class-memacces -Wno-conversion-null # Stop compilation on 1st fatal error

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

