#pragma once
#include "Bonus.h"
#include <memory>
#include <vector>

namespace ArkanoidGame
{
    class IBlockDamageState;
    class NormalBlockState;
    class FragileBlockState;
    class BlockDamageContext;

    class IBlockDamageState
    {
    public:
        virtual ~IBlockDamageState() = default;
        virtual int CalculateDamage(int currentHp, int maxHp) const = 0;
        virtual float GetDamageMultiplier() const { return 1.0f; }
        virtual const char* GetStateName() const = 0;
        virtual sf::Color GetBlockTintColor() const { return sf::Color::White; }
    };

    class NormalBlockState : public IBlockDamageState
    {
    public:
        int CalculateDamage(int currentHp, int maxHp) const override { return 1; }
        const char* GetStateName() const override { return "Normal"; }
    };

    class FragileBlockState : public IBlockDamageState
    {
    public:
        int CalculateDamage(int currentHp, int maxHp) const override { return maxHp; }
        float GetDamageMultiplier() const override { return 999.0f; }
        const char* GetStateName() const override { return "Fragile"; }
        sf::Color GetBlockTintColor() const override { return sf::Color(255, 200, 200, 255); }
    };

    class DoubleDamageBlockState : public IBlockDamageState
    {
    public:
        int CalculateDamage(int currentHp, int maxHp) const override { return 2; }
        float GetDamageMultiplier() const override { return 2.0f; }
        const char* GetStateName() const override { return "DoubleDamage"; }
        sf::Color GetBlockTintColor() const override { return sf::Color(255, 150, 150, 255); }
    };

    class BlockDamageContext
    {
    public:
        static BlockDamageContext& Instance();

        void SetState(std::shared_ptr<IBlockDamageState> newState);
        void ResetToNormalState();

        int GetDamage(int currentHp, int maxHp) const;
        float GetDamageMultiplier() const;
        sf::Color GetBlockTintColor() const;

        const char* GetCurrentStateName() const;
        bool IsNormalState() const;
        bool IsFragileState() const;
        bool IsDoubleDamageState() const;

        void ActivateFragileState(float duration = 6.0f);
        void ActivateDoubleDamageState(float duration = 5.0f);

        void Update(float deltaTime);

        float GetRemainingTime() const { return hasTemporaryState ? stateTimer : 0.0f; }
        float GetTotalDuration() const { return totalDuration; }

    private:
        BlockDamageContext();
        ~BlockDamageContext() = default;
        BlockDamageContext(const BlockDamageContext&) = delete;
        BlockDamageContext& operator=(const BlockDamageContext&) = delete;

        std::shared_ptr<IBlockDamageState> currentState;
        std::shared_ptr<IBlockDamageState> previousState;
        float stateTimer = 0.0f;
        float totalDuration = 0.0f;
        bool hasTemporaryState = false;
    };

#define BLOCK_DAMAGE_CONTEXT BlockDamageContext::Instance()

    class FragileBlocksBonus : public Bonus
    {
    public:
        FragileBlocksBonus(const sf::Vector2f& position);
        ~FragileBlocksBonus() = default;

        void Activate() override;
        void Update(float timeDelta) override;

    private:
        float pulseTimer = 0.0f;
    };
}