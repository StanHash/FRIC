
# =============
# = PORTRAITS =
# =============

PORTRAIT_LIST      := Spritans/PortraitList.txt
PORTRAIT_INSTALLER := Spritans/Portraits.event

# Make the portrait installer
$(PORTRAIT_INSTALLER): $(PORTRAIT_LIST) $(shell $(PORTRAIT_PROCESS) $(PORTRAIT_LIST) --list-files)
	$(NOTIFY_PROCESS)
	@$(PORTRAIT_PROCESS) $< --output $@

# Convert a png to portrait components
%_mug.dmp %_palette.dmp %_frames.dmp %_minimug.dmp: %.png
	$(NOTIFY_PROCESS)
	@$(PORTRAITFORMATTER) $<

# ==========================
# = GRAPHICS & COMPRESSION =
# ==========================

# PNG to 4bpp rule
%.4bpp: %.png
	$(NOTIFY_PROCESS)
	@$(PNG2DMP) $< -o $@
#	@$(GBAGFX) $< $@

# PNG to gbapal rule
%.gbapal: %.png
	$(NOTIFY_PROCESS)
	@$(PNG2DMP) $< -po $@ --palette-only
#	@$(GBAGFX) $< $@

# Anything to lz rule
%.lz: %
	$(NOTIFY_PROCESS)
	@$(COMPRESS) $< --to-stdout > $@
#	@$(GBAGFX) $< $@

ifeq ($(MAKECMDGOALS),clean)

  # Portraits and generated files
  PORTRAITS := $(wildcard Spritans/Portraits/*.png)

  PORTRAIT_GENERATED := \
    $(PORTRAITS:.png=_mug.dmp) $(PORTRAITS:.png=_palette.dmp) \
    $(PORTRAITS:.png=_frames.dmp) $(PORTRAITS:.png=_minimug.dmp)

  CLEAN_FILES += $(PORTRAIT_INSTALLER) $(PORTRAIT_GENERATED)

endif
