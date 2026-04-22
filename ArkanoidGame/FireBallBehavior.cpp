#include "FireBallBehavior.h"
#include "Ball.h"
#include "Block.h"
#include "Platform.h"
#include "GameSettings.h"
#include <cmath>
#include <iostream>

namespace ArkanoidGame
{
    void DefaultBallBehavior::Update(Ball* ball, float timeDelta)
    {
        const auto pos = ball->GetPosition() + SETTINGS.BALL_SPEED * timeDelta * ball->GetDirection();
        ball->SetPosition(pos);

        if (pos.x - SETTINGS.BALL_SIZE / 2.f <= 0 || pos.x + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_WIDTH)
            ball->InvertDirectionX();

        if (pos.y - SETTINGS.BALL_SIZE / 2.f <= 0)
            ball->InvertDirectionY();

        if (pos.y + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_HEIGHT)
            ball->Emit();
    }

    bool DefaultBallBehavior::HandleBlockCollision(Ball* ball, std::shared_ptr<Block> block)
    {
        return true;
    }

    void DefaultBallBehavior::HandlePlatformCollision(Ball* ball, Platform* platform)
    {
    }

    void DefaultBallBehavior::OnActivate(Ball* ball)
    {
        ball->SetColor(sf::Color::White);
    }

    void FireballBehavior::Update(Ball* ball, float timeDelta)
    {
        const float speed = SETTINGS.BALL_SPEED * GetSpeedMultiplier();
        const auto pos = ball->GetPosition() + SETTINGS.BALL_SPEED * timeDelta * ball->GetDirection();
        ball->SetPosition(pos);

        if (pos.x - SETTINGS.BALL_SIZE / 2.f <= 0 || pos.x + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_WIDTH)
            ball->InvertDirectionX();

        if (pos.y - SETTINGS.BALL_SIZE / 2.f <= 0)
            ball->InvertDirectionY();

        if (pos.y + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_HEIGHT)
            ball->Emit();
    }

    bool FireballBehavior::HandleBlockCollision(Ball* ball, std::shared_ptr<Block> block)
    {
        //block->TakeDamage(999);
        return false;
    }

    void FireballBehavior::HandlePlatformCollision(Ball* ball, Platform* platform)
    {
    }

    void FireballBehavior::OnActivate(Ball* ball)
    {
        ball->SetColor(sf::Color::Red);
        std::cout << "FireballBehavior activated - ball turned red" << std::endl;
    }

    void FireballBehavior::OnDeactivate(Ball* ball)
    {
        ball->SetColor(sf::Color::White);
        std::cout << "FireballBehavior deactivated - ball turned white" << std::endl;
    }
}