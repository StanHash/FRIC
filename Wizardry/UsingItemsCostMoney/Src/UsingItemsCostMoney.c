
#include "gbafe.h"

enum { TEXT_SPECIAL_G = 30 };

enum { USE_COUNTER_MAX = 50 };

void ItemsMoney_DrawDurabilityRaw(int item, int color, u16* tm)
{
	DrawUiNumberOrDoubleDashes(tm + 1, color == TEXT_COLOR_BLUE ? TEXT_COLOR_GOLD : color, GetItemCostPerUse(item));
}

//! Replaces 
void NuDrawItemMenuLine(struct TextHandle* text, int item, s8 isUsable, u16* mapOut)
{
	Text_SetParameters(text, 0, (isUsable ? TEXT_COLOR_NORMAL : TEXT_COLOR_GRAY));
	Text_DrawString(text, GetItemName(item));

	Text_Display(text, mapOut + 2);

	DrawUiNumberOrDoubleDashes(mapOut + 11, isUsable ? TEXT_COLOR_GOLD : TEXT_COLOR_GRAY, GetItemCostPerUse(item));

	DrawIcon(mapOut, GetItemIconId(item), 0x4000);
}

//! Replaces 
void NuDrawItemMenuLineLong(struct TextHandle* text, int item, s8 isUsable, u16* mapOut)
{
	Text_SetParameters(text, 0, (isUsable ? TEXT_COLOR_NORMAL : TEXT_COLOR_GRAY));
	Text_DrawString(text, GetItemName(item));

	Text_Display(text, mapOut + 2);

	DrawUiNumberOrDoubleDashes(mapOut + 12, isUsable ? TEXT_COLOR_BLUE : TEXT_COLOR_GRAY, GetItemCostPerUse(item));
	DrawSpecialUiChar(mapOut + 13, isUsable ? TEXT_COLOR_GOLD : TEXT_COLOR_GRAY, TEXT_SPECIAL_G);

	DrawIcon(mapOut, GetItemIconId(item), 0x4000);
}

//! Replaces 
void NuDrawItemMenuLineNoColor(struct TextHandle* text, int item, u16* mapOut)
{
	Text_SetXCursor(text, 0);
	Text_DrawString(text, GetItemName(item));

	Text_Display(text, mapOut + 2);

	DrawUiNumberOrDoubleDashes(mapOut + 11, Text_GetColorId(text), GetItemCostPerUse(item));

	DrawIcon(mapOut, GetItemIconId(item), 0x4000);
}

//! Replaces 
void NuDrawItemStatScreenLine(struct TextHandle* text, int item, int nameColor, u16* mapOut)
{
	int color;

	Text_Clear(text);

	color = nameColor;
	Text_SetColorId(text, color);

	Text_DrawString(text, GetItemName(item));

	Text_Display(text, mapOut + 2);

	color = (nameColor == TEXT_COLOR_GRAY) ? TEXT_COLOR_GRAY : TEXT_COLOR_GOLD;
	DrawSpecialUiChar(mapOut + 14, color, TEXT_SPECIAL_G);

	color = (nameColor != TEXT_COLOR_GRAY) ? TEXT_COLOR_BLUE : TEXT_COLOR_GRAY;
	DrawUiNumberOrDoubleDashes(mapOut + 13, color, GetItemCostPerUse(item));

	DrawIcon(mapOut, GetItemIconId(item), 0x4000);
}

//! Replaces 
int NuggetNewItem(int item)
{
	if (item == 0)
		return 0;

	return GetItemIndex(item);
}

//! Replaces 
u16 NuggetItemAfterUse(int item)
{
	if (GetItemAttributes(item) & IA_UNBREAKABLE)
		return item; // unbreakable items don't care for uses!

	if (item < (USE_COUNTER_MAX << 8))
		item += (1 << 8); // gain one 'use'

	return item;
}

//! Replaces 
int NuggetItemCostPerUse(int item)
{
	int base = GetItemData(GetItemIndex(item))->costPerUse;

	if (GetItemAttributes(item) & IA_UNBREAKABLE)
		return base;

	int uses = GetItemUses(item);

	return Div(base * (USE_COUNTER_MAX + uses), USE_COUNTER_MAX);
}

//! Replaces 
int NuggetItemCost(int item)
{
	int base = GetItemData(GetItemIndex(item))->costPerUse;

	if (GetItemAttributes(item) & IA_UNBREAKABLE)
		return 30 * base;

	int uses = GetItemUses(item);

	return Div(GetItemMaxUses(item) * base * (USE_COUNTER_MAX - uses / 2), USE_COUNTER_MAX);
}

//! Replaces 
void NuUnitUpdateUsedItem(struct Unit* unit, int slot)
{
	u16* itemref = unit->items + slot;

	if (*itemref)
	{
		int cost = GetItemCostPerUse(*itemref);
		*itemref = GetItemAfterUse(*itemref);

		UnitRemoveInvalidItems(unit);

		if (UNIT_FACTION(unit) == FACTION_BLUE)
			SetPartyGoldAmount(GetPartyGoldAmount() - cost);
	}
}

//! Add to Battle2UnitFuncList
void UsingWeaponsCostsMoney(struct Unit* unit, struct BattleUnit* bu)
{
	if (UNIT_FACTION(unit) != FACTION_BLUE)
		return;

	if (!bu->weapon || !bu->weaponBefore)
		return;

	int uses = bu->weaponBefore
		? GetItemUses(bu->weapon) - GetItemUses(bu->weaponBefore)
		: 1;

	if (uses == 0)
		uses = 1;

	int cost = GetItemCostPerUse(bu->weaponBefore);

	SetPartyGoldAmount(GetPartyGoldAmount() - cost * uses);
}
