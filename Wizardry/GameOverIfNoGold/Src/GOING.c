
#include "gbafe.h"

int NuggetGold(int amt)
{
    // No 5x nonsense
    return gChapterData.goldAmount;
}

void NuSetGold(int amt)
{
    if (amt < 0)
        amt = 0;

    if (amt > 999999)
        amt = 999999;

    gChapterData.goldAmount = amt;
}

int NuCountAvailableBlueUnits(void)
{
    if (GetPartyGoldAmount() == 0)
        return 0; // If we don't have gold, we return 0, which would cause a game over

    int result = 0;

    for (int id = 1; id < 0x40; ++id)
    {
        struct Unit* const unit = GetUnit(id);

        if (!UNIT_IS_VALID(unit))
            continue;

        if (unit->state & US_UNAVAILABLE)
            continue;

        result++;
    }

    return result;
}
