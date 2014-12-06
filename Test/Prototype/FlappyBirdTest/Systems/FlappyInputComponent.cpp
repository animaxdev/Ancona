#include "FlappyInputComponent.hpp"
#include <SFML/System.hpp>

using namespace ild;

FlappyInputComponent::FlappyInputComponent(
        Entity & flapper,
        PositionComponent & positionComponent,
        FlappyRotateComponent & rotateComponent,
        FlappyKeyboard & inputHandler)
    : InputControlComponent(inputHandler),
      _positionComponent(positionComponent),
      _rotateComponent(rotateComponent)
{
    inputHandler.RegisterInputComponent(this);
}

void FlappyInputComponent::Jump() 
{
    _rotateComponent.SetRotateDir(-1);
    _positionComponent.Velocity.y = -130;
}
