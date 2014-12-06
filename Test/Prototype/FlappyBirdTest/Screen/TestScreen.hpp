#ifndef Ancona_Game_Screen_TestScreen_H_
#define Ancona_Game_Screen_TestScreen_H_

#include <Ancona/Engine/Screen/AbstractScreen.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
namespace ild
{

class SystemManager;
class PositionSystem;
class InputControlSystem;
class SpriteSystem;
class GravitySystem;
class FlappyRotateSystem;
class PipeSpawnerSystem;

class TestScreen : public AbstractScreen
{
    public:
        TestScreen(ScreenManager & manager);

        void Update(float delta);

        void Init ();

        void Draw();
    private:
        SystemManager * _systemManager;
        PositionSystem  * _positionSystem;
        InputControlSystem * _inputSystem;
        SpriteSystem * _spriteSystem;
        GravitySystem * _gravitySystem;
        FlappyRotateSystem * _rotateSystem;
        PipeSpawnerSystem * _pipeSpawnerSystem;
        Entity _player;
        Entity _pipeSpawner;
        Entity _ground;
        Entity _bg;
        Entity _fg;
};

}

#endif

