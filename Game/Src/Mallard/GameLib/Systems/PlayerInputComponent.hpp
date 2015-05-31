#ifndef Ancona_Game_Systems_PlayerInputComponent_H_
#define Ancona_Game_Systems_PlayerInputComponent_H_

#include <Ancona/Core2D/Systems/InputControlComponent.hpp>
#include <Mallard/GameLib/InputDevices/PlayerKeyboard.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

namespace ild 
{

class PlayerDirection
{
    public:
        static const int Up;
        static const int Down;
        static const int Left;
        static const int Right;
        static const int None;
};

typedef int PlayerDirectionEnum;

/**
 * @brief Contains the functions for manipulating the player's
 *        state based on input.
 *
 * @author Tucker Lein
 */
class PlayerInputComponent : public InputControlComponent
{
    public:
        PlayerInputComponent(
                Entity & player, 
                PlatformPhysicsComponent & positionComponent,
                PlayerKeyboard & inputHandler);

        void Move(PlayerDirectionEnum direction);
    private:
        PlatformPhysicsComponent & _positionComponent;

        VectorActionProxy _movementAction;

};

}

#endif