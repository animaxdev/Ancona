#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Resource/ResourceLoaderInit.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Screens/LoadingScreen.hpp>
#include <Ancona/Game/Core/AnconaGame.hpp>

using namespace ild;

AnconaGame::AnconaGame(
        int windowWidth, 
        int windowHeight, 
        const std::string & title)
    : Game(windowWidth, windowHeight, title)
{
    ResourceLoaderInit::Init();
    CreateInitialScreen();
}

AnconaGame::~AnconaGame()
{
    ResourceLibrary::Return(*_requestList);
    delete _requestList;
}

void AnconaGame::CreateInitialScreen()
{
    _requestList = new RequestList("TestRequestList.txt");
    //_screenManager->Push(
    //        new TestScreen(*_screenManager));
    _screenManager->Push(
            new LoadingScreen(*_screenManager, *_requestList));
}
