# Variables
# Compiler:
CC = g++

# Compiler options:
#   -Wall  - this enables all the warnings
#   -g     - produce debugging information
#   -O0    - reduce compilation time and make debugging produce the expected results
CFLAGS = -Wall -g -O0

# List of modules
MODULES = shared

# Target definitions. "all" is the default.
SRC_DIR = $(addprefix src/,$(MODULES))
BUILD_DIR = $(addprefix obj/,$(MODULES)) bin

SRC = $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cc))
OBJ = $(patsubst src/%.cc,obj/%.o,$(SRC))
INCLUDES = $(addprefix -I ,$(SRC_DIR))

vpath %.cc $(SRC_DIR)

define link
$1/%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: clean checkdirs bin/app

bin/app: $(OBJ)
	$(CC) $(CFLAGS) $^ src/app.cc -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call link,$(bdir))))