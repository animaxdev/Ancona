#include "FlappyInputHandler.hpp"
#include "../Systems/FlappyInputComponent.hpp"

using namespace ild;

FlappyInputHandler::FlappyInputHandler(
        ScreenManager & screenManager,
        MachineState initialState) : 
    _machine(FlappyStates::Count),
    _curState(initialState),
    _screenManager(screenManager)
{
    _machine.SetAction(FlappyStates::InAir, &FlappyInputHandler::InAirInput);
    _machine.SetAction(FlappyStates::OnGround, &FlappyInputHandler::OnGroundInput);
    _machine.SetAction(FlappyStates::GameIntro, &FlappyInputHandler::GameIntroInput);
}

void FlappyInputHandler::HandleInput()
{
    _machine.Update(*this, _curState); 
}

void FlappyInputHandler::RegisterInputComponent(
        FlappyInputComponent * component)
{
    _component = component;
}

void FlappyInputHandler::ChangeState(const MachineState & newState)
{
    if(AllowedTransition(newState)) 
    {
        _curState = newState;
    }
}

bool FlappyInputHandler::AllowedTransition(const MachineState & newState)
{
    switch(_curState)
    {
        case FlappyStates::InAir:
            return InAirTransitionCheck(newState);
            break;
        case FlappyStates::GameIntro:
            return GameIntroTransitionCheck(newState);
            break;
    }
    return false;
}

bool FlappyInputHandler::InAirTransitionCheck(const MachineState & newState)
{
    return newState == FlappyStates::OnGround;
}

bool FlappyInputHandler::GameIntroTransitionCheck(const MachineState & newState)
{
    return newState == FlappyStates::InAir;
}