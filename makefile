##
## GENERAL
##

LIB_NAME = integrator
GIT_REPO = https://raw.githubusercontent.com/Gliptal/sumo-integrator/master


##
## DIRS
##

DIR_BIN     = bin
DIR_BUILD   = build
DIR_CONFIG  = config
DIR_DOC     = doc
DIR_INCLUDE = include
DIR_LIB     = lib
DIR_SRC     = src
DIR_TEST    = test


##
## TOOLS
##

CPP         = g++
CPP_FLAGS   = -std=c++11 -Wall
CPP_DEFINES = -DDEBUG_LEVEL=DEBUG_DATA
CPP_INCLUDE = -I .
CPP_LIBS    = -L$(DIR_BIN) -L$(DIR_LIB)/sumo -l$(LIB_NAME) -lsumo

LIB       = ar
LIB_FLAGS = -crs

WGET       = wget
WGET_FLAGS = -q

DOC = doxygen


##
## OUTPUT
##

COLOR_RESET  = $$(tput sgr0)
COLOR_TARGET = $$(tput bold)
COLOR_DOWN   = $$(tput setaf 93)
COLOR_CLEAN  = $$(tput setaf 3)
COLOR_BUILD  = $$(tput setaf 6)
COLOR_LINK   = $$(tput setaf 2)
COLOR_PACK   = $$(tput setaf 5)

print-title = printf "%s:\n" $1
print-help  = printf "%4s$(COLOR_TARGET)%-36s$(COLOR_RESET)%s\n" "" "$1" $2
print-down  = printf "$(COLOR_DOWN)%-12s$(COLOR_RESET)%s\n" "[ DOWN  ]" $1
print-clean = printf "$(COLOR_CLEAN)%-12s$(COLOR_RESET)%s\n" "[ CLEAN ]" $1
print-build = printf "$(COLOR_BUILD)%-12s$(COLOR_RESET)%s\n" "[ BUILD ]" $1
print-link  = printf "$(COLOR_LINK)%-12s$(COLOR_RESET)%s\n" "[ LINK  ]" $1
print-pack  = printf "$(COLOR_PACK)%-12s$(COLOR_RESET)%s\n" "[ PACK  ]" $1

filter-libs = $(filter-out $(DIR_LIB)/sumo/%.h,$1)


##
## OPTIONS
##

.PHONY: help all reset clean clean-docs clean-all docs-html library test-ego-basic test-output-basic


##
## UTILITY
##

help:
	@$(call print-title,"UTILITY")
	@$(call print-help,"help","lists all available targets")
	@$(call print-help,"all","builds everything")
	@$(call print-help,"reset","resets the configuration files")
	@$(call print-help,"clean","removes build files")
	@$(call print-help,"clean-docs","removes compiled documentation files")
	@$(call print-help,"clean-all","removes build and binary files")
	@$(call print-help,"docs-html","generates html documentation")
	@$(call print-title,"LIBRARY")
	@$(call print-help,"library","builds the library")
	@$(call print-title,"TESTS")
	@$(call print-help,"test-ego-basic","builds the ego-basic test")

all: library test-ego-basic test-output-basic

reset:
	@set -e; \
	for file in $(DIR_CONFIG)/test/*.h; do \
		$(call print-down,$$file); \
		$(WGET) $(WGET_FLAGS) -O $(DIR_CONFIG)/test/$$(basename $$file) $(GIT_REPO)/$(DIR_CONFIG)/test/$$(basename $$file); \
	done

clean:
	@$(call print-clean,"build folder")
	-@rm -f $(DIR_BUILD)/*.o $(DIR_BUILD)/*.d

clean-docs:
	@$(call print-clean,"compiled documentation folder")
	-@rm -rf $(DIR_DOC)/doxygen/output

clean-all: clean
	@$(call print-clean,"bin folder")
	-@rm -f $(DIR_BIN)/*.out $(DIR_BIN)/*.a

docs-html:
	@$(call print-build, "documentation")
	@cd doc/doxygen; \
	doxygen doxyfile


##
## LIBRARY
##

library: $(DIR_BIN)/lib$(LIB_NAME).a

$(DIR_BIN)/lib$(LIB_NAME).a: $(DIR_BUILD)/Sumo.o
	@$(call print-pack,"$^ in $@")
	@$(LIB) $(LIB_FLAGS) $@ $^

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cpp
	@$(call print-build,"$@ from $(call filter-libs,$^)")
	@$(CPP) $(CPP_FLAGS) $(CPP_DEFINES) -MMD -c -o $@ $< $(CPP_INCLUDE)


##
## TESTS
##

test-ego-basic: $(DIR_BIN)/egobasic.out

test-output-basic: $(DIR_BIN)/outputbasic.out

$(DIR_BIN)/egobasic.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/egobasic.o $(DIR_BUILD)/Driver.o $(DIR_BUILD)/StaticDriver.o
	@$(call print-link,"$^ to $@")
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BIN)/outputbasic.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/outputbasic.o
	@$(call print-link,"$^ to $@")
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BUILD)/%.o: $(DIR_TEST)/%.cpp
	@$(call print-build,"$@ from $(call filter-libs,$^)")
	@$(CPP) $(CPP_FLAGS) -MMD -c -o $@ $< $(CPP_INCLUDE)


##
## DEPENDENCIES
##

-include $(DIR_BUILD)/*.d