rootdir = $(realpath .)

CC = gcc
CFLAGS  = -g -lm -Wall -Werror

HEADERS = -I$(rootdir)/headers
MINIAUDIO_HEADERS =  -I$(rootdir)/dependencies/miniaudio/include 

FILES = $(wildcard src/*.c) 
LMINI = -L. -lminiaudio


lines:
	@echo $(shell git ls-files | xargs wc -l)

cl_tidy:
	@echo $(shell clang-tidy $(FILES))

compile_miniaudio:
	make_scripts/init_miniaudio.sh

compile: $(FILES)
ifeq ($(shell test -e libminiaudio.a && echo -n yes),yes)
	@echo Static lib exists.

else
	make_scripts/init_miniaudio.sh 
	@echo Static lib initalized.

endif

	$(CC) $(CFLAGS) $(MINIAUDIO_HEADERS) $(HEADERS) $(FILES) -o ./main $(LMINI)