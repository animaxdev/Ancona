#ifndef JumpyDuck_Screens_JumpyScreen_H_
#define JumpyDuck_Screens_JumpyScreen_H_

#include <memory>

#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include "../Systems/JumpyGameSystems.hpp"

namespace ild
{

class JumpyScreen : public AbstractScreen
{
    public:
        JumpyScreen(ScreenManager & manager);

        void Update(float delta);

        void Init();

        void Draw(float delta);

        /* getters and setters */
        ScreenSystemsContainer * systemsContainer() override { return _systems.get(); }
    private:
        std::unique_ptr<JumpyGameSystems> _systems;
        Entity player;

};

}
#endif
