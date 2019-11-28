
# making sure devkitARM exists and is set up
ifeq ($(strip $(DEVKITARM)),)
  $(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

# including devkitARM tool definitions
include $(DEVKITARM)/base_tools

EADIR := $(realpath .)/Tools/EventAssembler

ifeq ($(OS),Windows_NT)
  EXE := .exe
  EA  := $(EADIR)/ColorzCore.exe
else
  EXE :=
  EA  := mono $(EADIR)/ColorzCore.exe
endif

# Making sure we are using python 3
ifeq ($(shell python -c 'import sys; print(int(sys.version_info[0] > 2))'),1)
  export PYTHON3 := python
else
  export PYTHON3 := python3
endif

# Tools included with EA
export PARSEFILE         := $(EADIR)/Tools/ParseFile$(EXE)
export PORTRAITFORMATTER := $(EADIR)/Tools/PortraitFormatter$(EXE)
export PNG2DMP           := $(EADIR)/Tools/Png2Dmp$(EXE)
export COMPRESS          := $(EADIR)/Tools/compress$(EXE)

# Tools included with PyTools
export PORTRAIT_PROCESS  := $(PYTHON3) $(realpath .)/Tools/Py/portrait-process.py
export TEXT_PROCESS      := $(PYTHON3) $(realpath .)/Tools/Py/text-process-classic.py
export C2EA              := $(PYTHON3) $(realpath .)/Tools/Py/NMM2CSV/c2ea.py
export TMX2EA            := $(PYTHON3) $(realpath .)/Tools/Py/TMX2EA/tmx2ea.py

# Additional tools
export EADEP             := $(realpath .)/Tools/ea-dep$(EXE)
export LYN               := $(realpath .)/Tools/lyn$(EXE)

NOTIFY_PROCESS = @echo "$(notdir $<) => $(notdir $@)"
