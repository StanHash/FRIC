
# FRIC

"Fric" is french slang for money.

This is a FE8U hack that makes the following changes to the game:

- You start with 776 gold.
- Getting to 0 gold causes a Game Over
  - Gold amount is displayed instead of goal (you probably know FE8 well enough to not need that, and even then you can always check the status screen).
- Each deployed unit cost a certain amount of gold per turn to the player. Amount gets higher the stronger the unit is(*).
  - Cost per turn is displayed on the stat screen.
- Item have unlimited uses. Instead, using items cost gold. The more a specific item has been used, the more gold it will cost to use it again (maxed out at twice the base cost after 50 uses).
  - Cost per use is displayed instead of uses.
- Gaining exp also means gaining money. (at a rate of twice the gained exp)
  - Money gained is displayed on top of the exp bar during map anims.

This was made at the occasion of 2020 April Fools.

(*): Unit "strength" is measured with their stats (some stats (such as speed) are weighed more than others (such as luck)) and weapon ranks. Having status and rescuing anyone also increase a unit's cost per turn.

## Known issues

- Battle preview doesn't show doubling when using a weapon that hasn't been used yet (including enemy weapons).
- Gold gained isn't displayed with battle anims on.
