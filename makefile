# Compiler:
CC = g++

# Compiler options:
#   -Wall    - this enables all the warnings
#   -g       - produce debugging information
#   -O0      - reduce compilation time and make debugging produce the expected results
#   -D name  - predefine name as a macro
CFLAGS = -Wall -g -O0 -D DEBUG -D OSX

# List of modules
MODULES = shared graph

# Target definitions. "all" is the default.
SRC_DIR = $(addprefix src/,$(MODULES))
BUILD_DIR = $(addprefix obj/,$(MODULES)) bin

SRC = $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cc))
OBJ = $(patsubst src/%.cc,obj/%.o,$(SRC))
INCLUDES = -I src $(addprefix -I ,$(SRC_DIR))

vpath %.cc $(SRC_DIR)

define link
$1/%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: build checkdirs clean dwarf

build: clean checkdirs bin/dwarf bin/test_runner

bin/dwarf: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ src/dwarf.cc -o $@

bin/test_runner: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -I tests $^ tests/test_runner.cc -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

dwarf:
	./bin/dwarf

test:
	./bin/test_runner

$(foreach bdir,$(BUILD_DIR),$(eval $(call link,$(bdir))))