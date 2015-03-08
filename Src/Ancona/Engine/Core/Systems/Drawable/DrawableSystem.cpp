#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

#include <algorithm>
//TODO: remove iostream
#include <iostream>

#include <jsoncpp/json/json.h>

using namespace ild;


DrawableSystem::DrawableSystem(
        std::string systemName,
        sf::RenderWindow & window, 
        SystemManager & systemManager) :
    UnorderedSystem(systemName, systemManager, UpdateStep::Draw),
    _window(window)
{
}

void DrawableSystem::Update(float delta)
{
    for(CameraComponent * camera : _cameras)
    {
        camera->Draw(_window, delta);
    }
}

void DrawableSystem::AddCamera(CameraComponent * camera)
{
    _cameras.push_back(camera);
    std::sort(
            _cameras.begin(),
            _cameras.end(), 
            [](CameraComponent * lhs, CameraComponent * rhs)
            {
                return lhs->GetRenderPriority() < rhs->GetRenderPriority();
            });
}

void DrawableSystem::RemoveCamera(CameraComponent * camera)
{
    _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), camera), _cameras.end());
}

DrawableComponent * DrawableSystem::CreateComponent(const Entity & entity)
{
    Assert(_defaultCamera != nullptr, "Default camera not set");
    return CreateComponent(entity, *_defaultCamera);
}

DrawableComponent * DrawableSystem::CreateComponent(
        const Entity & entity,
        CameraComponent & camera)
{
    auto comp = new DrawableComponent(camera);

    // if the camera isn't already in the cameras vector, add it now
    if(std::find(_cameras.begin(), _cameras.end(), &camera) == _cameras.end())
    {
        _cameras.push_back(&camera); 
    }

    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    std::vector<Drawable * > compDrawables = component->GetDrawables();
    for(Drawable * drawable : compDrawables)
    {
        for(CameraComponent * camera : _cameras)
        {
            camera->RemoveDrawable(drawable);
        }
    }
}


void * DrawableSystem::Inflate(
        const Json::Value & object,
        const Entity & entity,
        LoadingContext * loadingContext)
{
    DrawableComponent * drawable = loadingContext->GetSystems().GetSystem<DrawableSystem>("drawable")->CreateComponent(entity);
    for(const Json::Value & drawablesJson : object["drawables"])
    {
        drawable->AddDrawable(
                drawablesJson["key"].asString(), 
                loadingContext->GetInflaterMap().GetInflater(drawablesJson["drawable"]["type"].asString())->InflateTo<Drawable>(
                    drawablesJson["drawable"],
                    entity,
                    loadingContext));
    }
    return drawable;
}
