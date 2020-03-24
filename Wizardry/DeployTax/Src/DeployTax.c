
#include "gbafe.h"

enum { TEXT_SPECIAL_G = 30 };

int GetUnitDeployTax(struct Unit* unit)
{
	enum { TAX_STEP = 8 };

	int tax = 0;

	tax += unit->maxHP;
	tax += unit->pow * 4;
	tax += unit->skl * 2;
	tax += unit->spd * 4;
	tax += unit->def * 3;
	tax += unit->res * 2;
	tax += unit->lck;
	tax += unit->movBonus * 10;
	tax += unit->conBonus;

	if (unit->statusIndex != 0)
		tax += 50;

	if (unit->state & US_RESCUING)
		tax *= 2;

	tax -= 50;

	if (tax < TAX_STEP)
		tax = TAX_STEP;

	return tax / TAX_STEP;
}

s8 DoDeployTax(struct Proc* parent)
{
	static char const* const POPUP_STR_PREFIX = "Unit Tax: ";
	static char const* const POPUP_STR_MINUS  = "-";
	static char const* const POPUP_STR_SUFFIX = "G";

	static u32 const POPUP[] =
	{
		8, TEXT_COLOR_NORMAL,
		7, (u32) POPUP_STR_PREFIX,


		8, TEXT_COLOR_BLUE,
		7, (u32) POPUP_STR_MINUS,
		11, 0,

		8, TEXT_COLOR_GOLD,
		7, (u32) POPUP_STR_SUFFIX,

		0, 0,
	};

	if (gChapterData.currentPhase != FACTION_BLUE)
		return TRUE;

	if (gChapterData.turnNumber < 2)
		return TRUE;

	int tax = 0;

	for (int id = 1; id < 0x40; ++id)
	{
		struct Unit* const unit = GetUnit(id);

		if (!UNIT_IS_VALID(unit))
			continue;

		if (unit->state & US_UNAVAILABLE)
			continue;

		tax += GetUnitDeployTax(unit);
	}

	SetPartyGoldAmount(GetPartyGoldAmount() - tax);
	SetPopupNumber(tax);

	Popup_Create(POPUP, 90, 0, parent);

	return FALSE;
}

void NuDrawStatScreenBwl(void)
{
	struct StatScreenSt
	{
		/* 00 */ u8 page;
		/* 01 */ u8 pageAmt;
		/* 02 */ u16 pageSlideKey; // 0, DPAD_RIGHT or DPAD_LEFT
		/* 04 */ short xDispOff; // Note: Always 0, not properly taked into account by most things
		/* 06 */ short yDispOff;
		/* 08 */ s8 inTransition;
		/* 0C */ struct Unit* unit;
		/* 10 */ void* mu;
		/* 14 */ const void* help;
		/* 18 */ struct TextHandle text[];
	};

	enum { STATSCREEN_TEXT_BWL = 34 };

	static struct StatScreenSt* const STATSCREEN = (struct StatScreenSt*) 0x02003BFC;
	static u16* const TM = (u16*) 0x02003D2C;

	if (UNIT_FACTION(STATSCREEN->unit) != FACTION_BLUE)
        return;

	struct TextHandle* const text = STATSCREEN->text + STATSCREEN_TEXT_BWL;

	Text_Clear(text);

	Text_SetColorId(text, TEXT_COLOR_NORMAL);
	Text_DrawString(text, "Unit Cost/Turn: ");

	/*

	Text_SetColorId(text, TEXT_COLOR_BLUE);
	Text_DrawNumber(text, GetUnitDeployTax(STATSCREEN->unit));

	Text_SetColorId(text, TEXT_COLOR_GOLD);
	Text_DrawString(text, "G");

	Text_SetColorId(text, TEXT_COLOR_NORMAL);
	Text_DrawString(text, ".");

	// */

	Text_Display(text, TM + TILEMAP_INDEX(2, 14));

	DrawUiNumber(TM + TILEMAP_INDEX(2 + 10, 14), TEXT_COLOR_BLUE, GetUnitDeployTax(STATSCREEN->unit));
	DrawSpecialUiChar(TM + TILEMAP_INDEX(2 + 11, 14), TEXT_COLOR_GOLD, TEXT_SPECIAL_G);
}
