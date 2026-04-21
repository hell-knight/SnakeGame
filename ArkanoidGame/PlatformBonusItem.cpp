#include "PlatformBonusItem.h"
#include "BonusManager.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cmath>

namespace ArkanoidGame
{
    PlatformBonusItem::PlatformBonusItem(const sf::Vector2f& position)
        : Bonus(position)
    {
        sprite.setColor(sf::Color::Blue);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
    }

    void PlatformBonusItem::Activate()
    {
        BONUS_MANAGER.ActivateBonus(BonusType::PlatformBonus, 8.0f);
    }

    void PlatformBonusItem::Update(float timeDelta)
    {
        Bonus::Update(timeDelta);
        sprite.rotate(90.0f * timeDelta);
    }

}