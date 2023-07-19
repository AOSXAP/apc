CC = gcc
CFLAGS = -lm
FILES = main.c $(wildcard src/headers/*.c)

default: 
	@echo "Specify a rule: build / lines"
build: $(files)
	$(CC) $(CFLAGS) $(FILES) -o ./main
lines:
	git ls-files | grep -v "dep" | xargs wc -l         
clean:
	rm -rf ./main