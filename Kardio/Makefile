# Project Name
TARGET = main

#######################################
# LDFLAGS
LDFLAGS += -u _printf_float

#######################################

# Sources
CPP_SOURCES = main.cpp\
$(wildcard Effects/Reverb/*.cpp) \

# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile