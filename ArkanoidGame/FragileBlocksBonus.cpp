#include "FragileBlocksBonus.h"
#include "BonusManager.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "randomizer.h"
#include <cmath>
#include <iostream>

namespace ArkanoidGame
{
    BlockDamageContext& BlockDamageContext::Instance()
    {
        static BlockDamageContext instance;
        return instance;
    }

    BlockDamageContext::BlockDamageContext()
    {
        currentState = std::make_shared<NormalBlockState>();
        previousState = nullptr;
    }

    void BlockDamageContext::SetState(std::shared_ptr<IBlockDamageState> newState)
    {
        if (newState)
        {
            previousState = currentState;
            currentState = newState;
        }
    }

    void BlockDamageContext::ResetToNormalState()
    {
        SetState(std::make_shared<NormalBlockState>());
        hasTemporaryState = false;
        stateTimer = 0.0f;
        totalDuration = 0.0f;
    }

    int BlockDamageContext::GetDamage(int currentHp, int maxHp) const
    {
        return currentState ? currentState->CalculateDamage(currentHp, maxHp) : 1;
    }

    float BlockDamageContext::GetDamageMultiplier() const
    {
        return currentState ? currentState->GetDamageMultiplier() : 1.0f;
    }

    sf::Color BlockDamageContext::GetBlockTintColor() const
    {
        return currentState ? currentState->GetBlockTintColor() : sf::Color::White;
    }

    const char* BlockDamageContext::GetCurrentStateName() const
    {
        return currentState ? currentState->GetStateName() : "Unknown";
    }

    bool BlockDamageContext::IsNormalState() const
    {
        return dynamic_cast<NormalBlockState*>(currentState.get()) != nullptr;
    }

    bool BlockDamageContext::IsFragileState() const
    {
        return dynamic_cast<FragileBlockState*>(currentState.get()) != nullptr;
    }

    bool BlockDamageContext::IsDoubleDamageState() const
    {
        return dynamic_cast<DoubleDamageBlockState*>(currentState.get()) != nullptr;
    }

    void BlockDamageContext::ActivateFragileState(float duration)
    {
        previousState = currentState;
        SetState(std::make_shared<FragileBlockState>());
        stateTimer = duration;
        totalDuration = duration;
        hasTemporaryState = true;
    }

    void BlockDamageContext::ActivateDoubleDamageState(float duration)
    {
        previousState = currentState;
        SetState(std::make_shared<DoubleDamageBlockState>());
        stateTimer = duration;
        totalDuration = duration;
        hasTemporaryState = true;
    }

    void BlockDamageContext::Update(float deltaTime)
    {
        if (hasTemporaryState)
        {
            stateTimer -= deltaTime;
            if (stateTimer <= 0.0f)
            {
                // Restore the previous state
                if (previousState)
                {
                    currentState = previousState;
                    previousState = nullptr;
                }
                else
                {
                    ResetToNormalState();
                }
                hasTemporaryState = false;
                totalDuration = 0.0f;
            }
        }
    }

    FragileBlocksBonus::FragileBlocksBonus(const sf::Vector2f& position)
        : Bonus(position)
    {
        SetSpriteSize(sprite, 30.f, 30.f);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
        sprite.setColor(sf::Color::Yellow);
    }

    void FragileBlocksBonus::Activate()
    {
        BLOCK_DAMAGE_CONTEXT.ActivateFragileState(6.0f);

        BONUS_MANAGER.ActivateBonus(BonusType::FragileBlocks, 6.0f);
    }

    void FragileBlocksBonus::Update(float timeDelta)
    {
        Bonus::Update(timeDelta);

        pulseTimer += timeDelta;
        float scale = 1.0f + 0.15f * std::sin(pulseTimer * 5.0f);
        sprite.setScale(scale, scale);

        BLOCK_DAMAGE_CONTEXT.Update(timeDelta);
    }

}