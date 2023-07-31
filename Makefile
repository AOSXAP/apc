rootdir = $(realpath .)

CC = gcc
CFLAGS  = -g -ggdb3 -Wall -Werror

HEADERS = -I$(rootdir)/headers
MINIAUDIO_HEADERS =  -I$(rootdir)/dependencies/miniaudio/include 

FILES = $(wildcard src/*.c) 
LMINI = -L. -lminiaudio -lm

#colors
COLOUR_GREEN ='\033[0;32m'
COLOUR_RED	 ='\033[0;31m'
COLOUR_BLUE	 ='\033[0;34m'
END_COLOUR	 =	 '\033[0m'

define NEWLINE

endef


lines:
	@echo $(shell git ls-files | xargs wc -l)

cl_tidy:
	@echo $(shell clang-tidy $(FILES))

compile_miniaudio:
	make_scripts/init_miniaudio.sh

compile: $(FILES)
ifeq ($(shell test -e libminiaudio.a && echo -n yes),yes)
	@echo -e $(COLOUR_GREEN)Static lib exists.$(END_COLOUR) 

else
	make_scripts/init_miniaudio.sh 
	@echo -e $(COLOUR_BLUE) Static lib initalized.$(END_COLOUR)

endif
	@echo Proceeding to compile.
	@echo -e $(NEWLINE)

	$(CC) $(CFLAGS) $(MINIAUDIO_HEADERS) $(HEADERS) $(FILES) -o ./bin/apc $(LMINI)
	@echo -e $(NEWLINE)

	@echo -e $(COLOUR_GREEN)Binary generated in ./bin/apc$(END_COLOUR)
