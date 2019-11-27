
.SUFFIXES:
.PHONY:

include Tools.mak

# Common cache directory
# Used to generate dependency files in
CACHE_DIR := .MuhCache
$(shell mkdir -p $(CACHE_DIR) > /dev/null)

CLEAN_FILES :=
CLEAN_DIRS  :=

# ROMs
ROM_SOURCE    := FE8U.gba
ROM_TARGET    := HACK.gba

# ===============
# = MAIN TARGET =
# ===============

hack: $(ROM_TARGET);
.PHONY: hack

# =================
# = THE BUILDFILE =
# =================

# EA Input File
EVENT_MAIN    := Main.event

# EA depends
EVENT_DEPENDS := $(shell $(EADEP) $(EVENT_MAIN) -I $(realpath .)/Tools/EventAssembler --add-missings)

# Additional EA commandline flags
EAFLAGS := -raws:Tools/EA-Raws

$(ROM_TARGET): $(EVENT_MAIN) $(EVENT_DEPENDS) $(ROM_SOURCE)
	@echo Building $(ROM_TARGET).
	@cp -f $(ROM_SOURCE) $(ROM_TARGET)
	@$(EA) A FE8 -output:$(ROM_TARGET) -input:$(EVENT_MAIN) $(EAFLAGS) --nocash-sym || (rm $(ROM_TARGET) && false)
	@cat "$(ROM_SOURCE:.gba=.sym)" >> "$(ROM_TARGET:.gba=.sym)" || true

ifeq ($(MAKECMDGOALS),clean)
  CLEAN_FILES += $(ROM_TARGET) $(ROM_TARGET:.gba=.sym) $(EVENT_SYMBOLS)
endif

# ===================
# = COMPONENT RULES =
# ===================

include Spritans.mak
include Writans.mak
include GameData.mak
include Wizardry.mak

# ==============
# = MAKE CLEAN =
# ==============

clean:
	@rm -f  $(CLEAN_FILES)
	@rm -rf $(CLEAN_DIRS)

	@rm -rf $(CACHE_DIR)

	@echo all clean!

.PHONY: clean

# ========================
# = INCLUDE DEPENDENCIES =
# ========================

ifneq ($(MAKECMDGOALS),clean)
  -include $(wildcard $(CACHE_DIR)/*.d)
endif
