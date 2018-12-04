##
## SHELL
##

SHELL = /bin/bash


##
## GENERAL
##

LIB_NAME = sumointegrator
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
## FILES
##

MODULES = core types
MODULE_CORE = Sumo Concern Connection Ego Entities Simulation
MODULE_TYPES = base

addaround = $(addprefix $1,$(addsuffix $2,$3))


##
## TOOLS
##

CPP         = g++
CPP_FLAGS   = -std=c++11 -Wall
CPP_DEFINES = -DDEBUG_LEVEL=DEBUG_INFO
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
COLOR_NEW    = $$(tput bold)

print-deps =                                                    \
	allfiles="$4";                                              \
	allfiles=$${allfiles//sumo-integrator/...};                 \
	newfiles="$5";                                              \
	newfiles=$${newfiles//sumo-integrator/...};                 \
	printf "%s%-12s$(COLOR_RESET)%-36s%-12s" $1 $2 $3 "from";   \
	i=0;                                                        \
	set -e;                                                     \
	for allfile in $$allfiles; do                               \
		if (( ($$i != 0) && ($$i % 2 == 0) )); then             \
			printf "\n%60s" "";                                 \
		fi;                                                     \
		changed=0;                                              \
		for newfile in $$newfiles; do                           \
			if [ "$$allfile" == "$$newfile" ]; then             \
				changed=1;                                      \
				break;                                          \
			fi;                                                 \
		done;                                                   \
		if (( changed == 1 )); then                             \
			printf "$(COLOR_NEW)%-36s$(COLOR_RESET)" $$allfile; \
		else                                                    \
			printf "%-36s" $$allfile;                           \
		fi;                                                     \
		let i+=1;                                               \
	done;                                                       \
	printf "\n"

print-title = printf "%s:\n" $1
print-help  = printf "%4s$(COLOR_TARGET)%-36s$(COLOR_RESET)%s\n" "" "$1" $2
print-down  = printf "$(COLOR_DOWN)%-12s$(COLOR_RESET)%s\n" "[ DOWN  ]" $1
print-clean = printf "$(COLOR_CLEAN)%-12s$(COLOR_RESET)%s\n" "[ CLEAN ]" $1
print-build = $(call print-deps,$(COLOR_BUILD),"[ BUILD ]",$1,$2,$3)
print-link  = $(call print-deps,$(COLOR_LINK),"[ LINK  ]",$1,$2,$3)
print-pack  = $(call print-deps,$(COLOR_PACK),"[ PACK  ]",$1,$2,$3)

filter-libs = $(filter-out $(DIR_LIB)/sumo/%.h,$1)


##
## OPTIONS
##

.PHONY: help all reset clean clean-all clean-docs docs docs-html library library-core library-types tests test-output-basic test-output-sets test-ego-basic test-ego-async test-ego-subscribe


##
## UTILITY
##

help:
	@$(call print-title,"UTILITY")
	@$(call print-help,"help","lists all available targets")
	@$(call print-help,"all","builds everything")
	@$(call print-help,"reset","resets the configuration files")
	@$(call print-help,"clean","removes build files")
	@$(call print-help,"clean-all","removes build and binary files")
	@$(call print-help,"clean-docs","removes compiled documentation files")
	@$(call print-title,"DOCS")
	@$(call print-help,"docs","generates all documentation")
	@$(call print-help,"docs-html","generates html documentation")
	@$(call print-title,"LIBRARY")
	@$(call print-help,"library","builds and packs the entire library")
	@$(call print-help,"library-core","builds the library core")
	@$(call print-help,"library-core","builds the library types")
	@$(call print-title,"TESTS")
	@$(call print-help,"tests","builds all the tests")
	@$(call print-help,"test-output-basic","builds the output-basic test")
	@$(call print-help,"test-output-sets","builds the output-sets test")
	@$(call print-help,"test-ego-basic","builds the ego-basic test")
	@$(call print-help,"test-ego-async","builds the ego-async test")
	@$(call print-help,"test-ego-subscribe","builds the ego-subscribe test")

all: library tests

reset:
	@set -e;                                                                                                                \
	for file in $(DIR_CONFIG)/test/*.h; do                                                                                  \
		$(call print-down,$$file);                                                                                          \
		$(WGET) $(WGET_FLAGS) -O $(DIR_CONFIG)/test/$$(basename $$file) $(GIT_REPO)/$(DIR_CONFIG)/test/$$(basename $$file); \
	done

clean:
	@$(call print-clean,"build folder")
	-@rm -rf $(DIR_BUILD)/*

clean-all: clean
	@$(call print-clean,"bin folder")
	-@rm -rf $(DIR_BIN)/*

clean-docs:
	@$(call print-clean,"compiled documentation folder")
	-@rm -rf $(DIR_DOC)/doxygen/output

docs: docs-html

docs-html: $(DIR_DOC)/doxygen/output/index.html

$(DIR_DOC)/doxygen/output/index.html: $(DIR_INCLUDE)/sumo-integrator/*.h $(call addaround,$(DIR_INCLUDE)/sumo-integrator/,/*.h,$(MODULES)) $(DIR_DOC)/doxygen/doxyfile
	@$(call print-build,"documentation",$^,$?)
	@cd doc/doxygen; \
	doxygen doxyfile


##
## LIBRARY
##

library: library-core library-types $(DIR_BIN)/lib$(LIB_NAME).a

library-core: $(call addaround,$(DIR_BUILD)/library/core/,.o,$(MODULE_CORE))

library-types: $(call addaround,$(DIR_BUILD)/library/types/,.o,$(MODULE_TYPES))

$(DIR_BIN)/lib$(LIB_NAME).a: $(call addaround,$(DIR_BUILD)/library/core/,.o,$(MODULE_CORE)) $(call addaround,$(DIR_BUILD)/library/types/,.o,$(MODULE_TYPES))
	@$(call print-pack,"$@",$^,$?)
	@$(LIB) $(LIB_FLAGS) $@ $^

$(DIR_BUILD)/library/core/%.o: $(DIR_SRC)/core/%.cpp
	@$(call print-build,"$@",$(call filter-libs,$^),$?)
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(CPP_DEFINES) -MMD -c -o $@ $< $(CPP_INCLUDE)

$(DIR_BUILD)/library/types/%.o: $(DIR_SRC)/types/%.cpp
	@$(call print-build,"$@",$(call filter-libs,$^),$?)
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(CPP_DEFINES) -MMD -c -o $@ $< $(CPP_INCLUDE)


##
## TESTS
##

tests: test-output-basic test-output-sets test-ego-basic test-ego-async test-ego-subscribe

test-output-basic: $(DIR_BIN)/outputbasic.out

test-output-sets: $(DIR_BIN)/outputsets.out

test-ego-basic: $(DIR_BIN)/egobasic.out

test-ego-async: $(DIR_BIN)/egoasync.out

test-ego-subscribe: $(DIR_BIN)/egosubscribe.out

$(DIR_BIN)/outputbasic.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/test/outputbasic.o
	@$(call print-link,"$@",$^,$?)
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BIN)/outputsets.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/test/outputsets.o
	@$(call print-link,"$@",$^,$?)
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BIN)/egobasic.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/test/egobasic.o $(DIR_BUILD)/test/drivers/Driver.o $(DIR_BUILD)/test/drivers/StaticDriver.o
	@$(call print-link,"$@",$^,$?)
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BIN)/egoasync.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/test/egoasync.o $(DIR_BUILD)/test/drivers/Driver.o $(DIR_BUILD)/test/drivers/StaticDriver.o
	@$(call print-link,"$@",$^,$?)
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BIN)/egosubscribe.out: $(DIR_BIN)/lib$(LIB_NAME).a $(DIR_BUILD)/test/egosubscribe.o $(DIR_BUILD)/test/drivers/Driver.o $(DIR_BUILD)/test/drivers/StaticDriver.o
	@$(call print-link,"$@",$^,$?)
	@$(CPP) -o $@ $^ $(CPP_LIBS)

$(DIR_BUILD)/test/%.o: $(DIR_TEST)/%.cpp
	@$(call print-build,"$@",$(call filter-libs,$^),$?)
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) -MMD -c -o $@ $< $(CPP_INCLUDE)

$(DIR_BUILD)/test/drivers/%.o: $(DIR_TEST)/drivers/%.cpp
	@$(call print-build,"$@",$(call filter-libs,$^),$?)
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) -MMD -c -o $@ $< $(CPP_INCLUDE)


##
## DEPENDENCIES
##

-include $(DIR_BUILD)/*/*/*.d
