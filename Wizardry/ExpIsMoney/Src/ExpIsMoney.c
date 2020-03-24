
#include "gbafe.h"

extern u8 const EIM_DispImg[];
extern u16 const EIM_DispPal[];

static int Exp2Mone(int exp)
{
	return exp * 3;
}

void ExpGainIsMoneyGain(struct Unit* unit, struct BattleUnit* bu)
{
	if (UNIT_FACTION(unit) != FACTION_BLUE)
		return;

	SetPartyGoldAmount(GetPartyGoldAmount() + Exp2Mone(bu->expGain));
}

struct MAExpBarProc
{
    /* 00 */ PROC_HEADER;

    /* 29 */ u8    pad29[0x64 - 0x29];
    /* 64 */ short expFrom;
    /* 66 */ short expTo;
    /* 68 */ short actorId;
    /* 6A */ short unk6A;
};

struct MoneyGainDispProc
{
	/* 00 */ PROC_HEADER;

	/* 2C */ int yOff;
	/* 30 */ int amountGained;
	/* 34 */ s8 digits[4];
	/* 38 */ int digitCount;
};

void MoneyGainDispLoop(struct MoneyGainDispProc* proc)
{
	if (proc->yOff < 15)
		proc->yOff += 3;

	int const size = proc->digitCount*8 + 16;

	int const xStart = 120 - size / 2;
	int const yStart = 70 - proc->yOff;

	int const tileref = TILEREF(0x1A0, 2) + 0x0400;

	int const LAYER = 0;

	// +
	ObjInsert(LAYER, xStart + 0, yStart, &gObj_8x8, tileref + 10);

	// G
	ObjInsert(LAYER, xStart + size - 8, yStart, &gObj_8x8, tileref + 11);

	// Number
	for (int i = 0; i < proc->digitCount; ++i)
		ObjInsert(LAYER, xStart + 8 + i*8, yStart, &gObj_8x8, tileref + proc->digits[i]);
}

void MoneyGainDispInit(struct MoneyGainDispProc* proc)
{
	proc->yOff = 0;

	memset(proc->digits, -1, sizeof proc->digits);
	proc->digitCount = 0;

	int num = proc->amountGained;

	do
	{
		proc->digits[3] = proc->digits[2];
		proc->digits[2] = proc->digits[1];
		proc->digits[1] = proc->digits[0];
		proc->digits[0] = Mod(num, 10);

		num = Div(num, 10);

		proc->digitCount++;
	}
	while (num != 0);

	RegisterTileGraphics(EIM_DispImg, VRAM + 0x13400, 0x20 * 12);
	ApplyPalette(EIM_DispPal, 0x10 + 2);
}

struct ProcInstruction const ProcScr_MoneyGainOnExp[] =
{
	PROC_SET_NAME("Exp is Money!"),

	PROC_SLEEP(0),

	PROC_CALL_ROUTINE(MoneyGainDispInit),
	PROC_LOOP_ROUTINE(MoneyGainDispLoop),

	PROC_END,
};

void NuInitExpBarFilling(struct MAExpBarProc* proc)
{
	struct MoneyGainDispProc* nuproc = START_PROC(ProcScr_MoneyGainOnExp, proc);
	nuproc->amountGained = Exp2Mone(proc->expTo - proc->expFrom);

	// Replaced
	PlaySfx(0x74);
}

void NuClearExpBar(struct MAExpBarProc* proc)
{
	EndEachProc(ProcScr_MoneyGainOnExp);

	// Replaced
	SetPrimaryHBlankCallback(NULL);
	ClearBG0BG1();
}
