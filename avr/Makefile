# AVR GCC Makefile
#
# Note:
# The warnings which appear while converting ELF to AVR Extended COFF (make extcoff) can be ignored
#
#
# Make Targets:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF (for use with AVR Studio 3.x or VMLAB).
#
# make extcoff = Convert ELF to AVR Extended COFF (for use with AVR Studio
#                4.07 or greater).
#
# make program = Download the hex file to the device, using avrdude.  Please
#                customize the avrdude settings below first!
#
# make filename.s = Just compile filename.c into the assembler code only
#
# To rebuild project do "make clean" then "make all".

# -------------------------------------------------------------
# Project Settings

# The name of the executable to be created
TARGET := blink

# Compiler used
CC = avr-gcc

# Microcontroller
MCU ?= atmega328p

# Programming Interface ('arduino' for Arduino, 'avrispmkII' for the AVRISP mkII, or `usbtiny` for the Sparkfun AVR Pocket Programmer)
PROGRAMMER ?= arduino

# Port where the programmer is connected (ex: usb, com5, ttyACM0)
PROGRAMMER_PORT ?= usb

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS =

# Optimization level, can be [0, 1, 2, 3, s]. 0 turns off optimization.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Extension of source files used in the project
SRC_EXT = c

# Extension of assembly source files
ASRC_EXT = .S

# Path to the source directory, relative to the makefile
SRC_PATH = .

# Space-separated pkg-config libraries used by this project
LIBS =

# Main Compiler Flags
COMPILE_FLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)

# Optional compiler flags.
#  -g:        generate debugging information (for GDB, or for COFF conversion)
#  -O*:       optimization level
#  -f...:     tuning, see gcc manual and avr-libc documentation
#  -Wall...:  warning level
#  -Wa,...:   tell GCC to pass this to the assembler.
#    -ahlms:  create assembler listing
COMPILE_FLAGS = -g -O$(OPT) \
-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wstrict-prototypes \
-Wa,-adhlns=$(<:.c=.lst) \
$(patsubst %,-I%,$(EXTRAINCDIRS))

# Set a "language standard" compiler flag.
#   Unremark just one line below to set the language standard to use.
#   gnu99 = C99 + GNU extensions. See GCC manual for more information.
COMPILE_FLAGS += -std=gnu99

# Optional assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs

# Additional release-specific flags
RCOMPILE_FLAGS = -D NDEBUG

# Additional debug-specific flags
DCOMPILE_FLAGS = -D DEBUG

# General linker settings
#  -Wl,...:   tell GCC to pass this to linker.
#  -Map:      create map file
#  --cref:    add cross reference to  map file
LINK_FLAGS = -Wl,-Map=$(TARGET).map,--cref

# Additional release-specific linker settings
RLINK_FLAGS =

# Additional debug-specific linker settings
DLINK_FLAGS =

# Destination directory, like a jail or mounted system
DESTDIR = /

# Install path (bin/ is appended automatically)
INSTALL_PREFIX = usr/local

#### END PROJECT SETTINGS ####
# Generally should not need to edit below this line
# -------------------------------------------------------------
# Programming support using avrdude. Settings and variables.
#
# Programming hardware: alf avr910 avrisp bascom bsd
# dt006 pavr picoweb pony-stk200 sp12 stk200 stk500
#
# Type: avrdude -c ?
# to get a full listing.
#
AVRDUDE = avrdude

AVRDUDE_PROGRAMMER = $(PROGRAMMER)

AVRDUDE_PORT = $(PROGRAMMER_PORT)	   # programmer connected to serial device

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
# AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE += -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_FLAGS += -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_FLAGS += -v -v
#
# -------------------------------------------------------------
# Other AVR Utilities
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size

HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf
# -------------------------------------------------------------
# Obtains the OS type, either 'Darwin' (OS X) or 'Linux'
UNAME_S:=$(shell uname -s)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Shell used in this makefile
# bash is used for 'echo -en'
SHELL = /bin/bash

# Clear built-in rules
.SUFFIXES:
# -------------------------------------------------------------
# Programs for installation
INSTALL = install
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
# -------------------------------------------------------------
# Append pkg-config specific libraries if need be
ifneq ($(LIBS),)
	COMPILE_FLAGS += $(shell pkg-config --cflags $(LIBS))
	LINK_FLAGS += $(shell pkg-config --libs $(LIBS))
endif
# -------------------------------------------------------------
# Verbose option, to output compile and link commands
export V := true
export CMD_PREFIX := @
ifeq ($(V),true)
	CMD_PREFIX :=
endif
# -------------------------------------------------------------
# Combine compiler and linker flags
release: export CFLAGS := $(CFLAGS) $(COMPILE_FLAGS) $(RCOMPILE_FLAGS)
release: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(RLINK_FLAGS)
debug: export CFLAGS := $(CFLAGS) $(COMPILE_FLAGS) $(DCOMPILE_FLAGS)
debug: export LDFLAGS := $(LDFLAGS) $(LINK_FLAGS) $(DLINK_FLAGS)
# -------------------------------------------------------------
# Build and output paths
release: export BUILD_PATH := build/release
release: export BIN_PATH := bin/release
debug: export BUILD_PATH := build/debug
debug: export BIN_PATH := bin/debug
install: export BIN_PATH := bin/release
# -------------------------------------------------------------
# Find all source files in the source directory, sorted by most
# recently modified
ifeq ($(UNAME_S),Darwin)
	SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
	ASOURCES = $(shell find $(SRC_PATH)/ -name '*.$(ASRC_EXT)' | sort -k 1nr | cut -f2-)
else
	SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
	ASOURCES = $(shell find $(SRC_PATH)/ -name '*.$(ASRC_EXT)' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
endif

# fallback in case the above fails
rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2) \
						$(filter $(subst *,%,$2), $d))
ifeq ($(SOURCES),)
	SOURCES := $(call rwildcard, $(SRC_PATH)/, *.$(SRC_EXT))
	ASOURCES := $call rwildcard, $(SRC_PATH)/, *.$(ASRC_EXT))
endif
# -------------------------------------------------------------
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o) $(ASOURCES:$(SRC_PATH)/%.$(ASRC_EXT)=$(BUILD_PATH)/%.o)
LST = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.lst) $(ASOURCES:$(SRC_PATH)/%.$(ASRC_EXT)=$(BUILD_PATH)/%.lst)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)
# -------------------------------------------------------------
# Macros for timing compilation
ifeq ($(UNAME_S),Darwin)
	CUR_TIME = awk 'BEGIN{srand(); print srand()}'
	TIME_FILE = $(dir $@).$(notdir $@)_time
	START_TIME = $(CUR_TIME) > $(TIME_FILE)
	END_TIME = read st < $(TIME_FILE) ; \
		$(RM) $(TIME_FILE) ; \
		st=$$((`$(CUR_TIME)` - $$st)) ; \
		echo $$st
else
	TIME_FILE = $(dir $@).$(notdir $@)_time
	START_TIME = date '+%s' > $(TIME_FILE)
	END_TIME = read st < $(TIME_FILE) ; \
		$(RM) $(TIME_FILE) ; \
		st=$$((`date '+%s'` - $$st - 86400)) ; \
		echo `date -u -d @$$st '+%H:%M:%S'`
endif
# -------------------------------------------------------------
# Version macros
# Comment/remove this section to remove versioning
USE_VERSION := false
# If this isn't a git repo or the repo has no tags, git describe will return non-zero
ifeq ($(shell git describe > /dev/null 2>&1 ; echo $$?), 0)
	USE_VERSION := true
	VERSION := $(shell git describe --tags --long --dirty --always | \
		sed 's/v\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)-\?.*-\([0-9]*\)-\(.*\)/\1 \2 \3 \4 \5/g')
	VERSION_MAJOR := $(word 1, $(VERSION))
	VERSION_MINOR := $(word 2, $(VERSION))
	VERSION_PATCH := $(word 3, $(VERSION))
	VERSION_REVISION := $(word 4, $(VERSION))
	VERSION_HASH := $(word 5, $(VERSION))
	VERSION_STRING := \
		"$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_REVISION)-$(VERSION_HASH)"
	override CFLAGS := $(CFLAGS) \
		-D VERSION_MAJOR=$(VERSION_MAJOR) \
		-D VERSION_MINOR=$(VERSION_MINOR) \
		-D VERSION_PATCH=$(VERSION_PATCH) \
		-D VERSION_REVISION=$(VERSION_REVISION) \
		-D VERSION_HASH=\"$(VERSION_HASH)\"
endif
# -------------------------------------------------------------
# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
# -------------------------------------------------------------
# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo

gccversion :
	@$(CC) --version
# -------------------------------------------------------------
# (Semi-Optional) Oscillator setup: Default fuses are (H:07, E:D9, L:62)
# This command only changes the low fuse to remove the default divide-by-eight clock
# divider. This allow us to run at 8MHz instead of 1MHz, if needed.
#
# This is semi-optional because we don't *really* need to run at 8MHz. During testing
# we have been using 8MHz, but there is no reason we couldn't run at 1MHz or lower.
# If you decide not to run `make setup`, which will then use the 1MHz clock, remember
# to modify the `FOSC` macro and the math for the timers accordingly.
setup_8MHz:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0xe2:m

setup_1MHz:
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:0x62:m
# -------------------------------------------------------------
# Standard, non-optimized release build
.PHONY: release
release: dirs
ifeq ($(USE_VERSION), true)
	@echo "Beginning release build v$(VERSION_STRING)"
else
	@echo "Beginning release build"
endif
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)
# -------------------------------------------------------------
# Debug build for gdb debugging
.PHONY: debug
debug: dirs
ifeq ($(USE_VERSION), true)
	@echo "Beginning debug build v$(VERSION_STRING)"
else
	@echo "Beginning debug build"
endif
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)
# -------------------------------------------------------------
# Create the directories used in the build
.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)
# -------------------------------------------------------------
# Convert ELF to COFF for use in debugging / simulating in
# AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
	--change-section-address .data-0x800000 \
	--change-section-address .bss-0x800000 \
	--change-section-address .noinit-0x800000 \
	--change-section-address .eeprom-0x810000

coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof

extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof
# Installs to the set path
.PHONY: install
install:
	@echo "Installing to $(DESTDIR)$(INSTALL_PREFIX)/bin"
	@$(INSTALL_PROGRAM) $(BIN_PATH)/$(TARGET) $(DESTDIR)$(INSTALL_PREFIX)/bin
# -------------------------------------------------------------
# Uninstalls the program
.PHONY: uninstall
uninstall:
	@echo "Removing $(DESTDIR)$(INSTALL_PREFIX)/bin/$(TARGET)"
	@$(RM) $(DESTDIR)$(INSTALL_PREFIX)/bin/$(TARGET)
# -------------------------------------------------------------
# Removes all build files
.PHONY: clean
clean: begin clean_list finished end

clean_list:
	@echo
	@echo $(MSG_CLEANING)
	@echo "Deleting $(TARGET) symlink"
	@$(RM) $(TARGET)
	@echo "Deleting directories"
	@$(RM) -r build
	@$(RM) -r bin
# -------------------------------------------------------------
# Main rule, checks the executable and symlinks to the output
all: begin $(BIN_PATH)/$(TARGET).elf $(BIN_PATH)/$(TARGET).hex $(BIN_PATH)/$(TARGET).eep $(BIN_PATH)/$(TARGET).lss $(BIN_PATH)/$(TARGET).sym finished end
	@echo "Making symlink: $(TARGET) -> $<"
	@$(RM) $(TARGET)
	@ln -s $(BIN_PATH)/$(TARGET) $(TARGET)
# -------------------------------------------------------------
# Add dependency files, if they exist
-include $(DEPS)
# -------------------------------------------------------------
# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
# Compile: Create object files from C source files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)

# Assemble: Create object files from assembler source files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(ASRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)

# Compile: Create assembler files from C sources
$(BUILD_PATH)/%.s: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CC) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)
# -------------------------------------------------------------
# Program the device.
program: $(BUILD_PATH)/$(TARGET).hex $(BUILD_PATH)/$(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)
# -------------------------------------------------------------
# Create final output files (.hex, .eep) from ELF output file.
$(BUILD_PATH)/%.hex: $(BUILD_PATH)/%.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

$(BUILD_PATH)/%.eep: $(BUILD_PATH)/%.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@
# -------------------------------------------------------------
# Create extended listing file from ELF output file.
$(BUILD_PATH)/%.lss: $(BUILD_PATH)/%.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@
# -------------------------------------------------------------
# Create a symbol table from ELF output file.
$(BUILD_PATH)/%.sym: $(BUILD_PATH)/%.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	avr-nm -n $< > $@
# -------------------------------------------------------------
# Link: create ELF output file from object files.
.SECONDARY : $(BUILD_PATH)/$(TARGET).elf
.PRECIOUS : $(OBJECTS)
$(BUILD_PATH)/%.elf: $(OBJECTS)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(CFLAGS) $(OBJECTS) --output $@ $(LDFLAGS)
# -------------------------------------------------------------
# Automatically generate C source code dependencies.
# (Code originally taken from the GNU make user manual and modified
# (See README.txt Credits).)
#
# Note that this will work with sh (bash) and sed that is shipped with WinAVR
# (see the SHELL variable defined above).
# This may not work with other shells or other seds.
#
%.d: %.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@
# -------------------------------------------------------------
# Listing of phony targets.
.PHONY : begin finish end sizebefore sizeafter gccversion coff extcoff clean clean_list program
