#pragma once
#include "Bonus.h"

namespace ArkanoidGame
{
    class FireballBonusItem : public Bonus
    {
    public:
        FireballBonusItem(const sf::Vector2f& position);
        ~FireballBonusItem() = default;

        void Activate() override;
        void Update(float timeDelta) override;
    private:
        float pulseTimer = 0.0f;
    };
}