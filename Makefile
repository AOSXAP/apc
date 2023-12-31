rootdir = $(realpath .)

CC = gcc
CFLAGS  = -std=c11 -g -D_GNU_SOURCE -ggdb3 -Wall -Werror
 
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

lines:
	@echo $(shell git ls-files | xargs wc -l)

tidy:
	@echo $(shell clang-tidy $(FILES) -- $(HEADERS) $(MINIAUDIO_HEADERS))

compile_miniaudio:
	make_scripts/init_miniaudio.sh