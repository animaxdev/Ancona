#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

void nop(const Entity & e1,const Entity & e2) {}

CollisionSystem::CollisionSystem(SystemManager & manager, BasePhysicsSystem & positions)
    : UnorderedSystem<CollisionComponent>(manager,UpdateStep::Update), _positions(positions)
{
    _nextType = 0;

}

void CollisionSystem::Update(float delta)
{
    //Update all of the entities.  This is required for the position to be up to date.
    for(EntityComponentPair pair : * this)
    {
        pair.second->Update();
    }

    for(EntityComponentPair pairA : * this)
    {
        for(EntityComponentPair pairB : * this)
        {
            if(pairA.second->Collides(*pairB.second))
            {
                auto typeA = pairA.second->GetType();
                auto typeB = pairB.second->GetType();
                _callbackTable[typeA][typeB](pairA.first, pairB.first);
            }
        }
    }

}

CollisionComponent * CollisionSystem::CreateComponent(const Entity & entity,
        const sf::Vector3f & dim,
        CollisionType type,
        BodyTypeEnum bodyType)
{
    Assert(type < _nextType, "Cannot use a collision type that is undefined");
    auto position = _positions[entity];
    auto component = new CollisionComponent(*position, dim, type, bodyType);

    AttachComponent(entity, component);

    return component;
}

CollisionType CollisionSystem::CreateType()
{
    CollisionType newType = _nextType++;

    //Add slot for new collision type to the existing vectors.
    for(auto & callbackList : _callbackTable)
    {
        callbackList.push_back(nop);
    }

    _callbackTable.push_back(std::vector<CollisionCallback>());

    //Create the vector for the new collision type.
    auto & back = _callbackTable.back();
    for(int i = 0; i < _nextType; i++)
    {
        back.push_back(nop);
    }
    
    return newType;
}

void CollisionSystem::SetHandler(CollisionType typeA, CollisionType typeB, CollisionCallback callback)
{
    Assert(typeA < _nextType, "The given typeA does not exist");
    Assert(typeB < _nextType, "The given typeB does not exist");

    _callbackTable[typeA][typeB] = callback;
}
