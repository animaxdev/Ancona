#ifndef Ancona_Engine_Physiscs_Actions_hpp
#define Ancona_Engine_Physiscs_Actions_hpp

#include <limits>
#include <memory>
#include <vector>

#include <Ancona/Engine/Core/Systems/Physics/Position.hpp>
#include <Ancona/Engine/Core/Systems/Physics/VectorAction.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>

namespace ild
{

namespace ActionDuration
{

const float PERSISTENT = std::numeric_limits<float>::infinity();
const float INSTANT = 0.0f;

}

typedef std::shared_ptr<VectorAction> VectorActionProxy;

/**
 * @brief Actions is used to contain all of the Actions that are effecting
 * an entity.  It also contains the logic for applying and updating the actions.
 * @author Jeff Swenson 
 */
class Actions
{
    public:
        /**
         * @brief Construct a container for actions.
         *
         * @param physicsSystem Physics system that the actions belong to.
         */
        Actions(BasePhysicsSystem * physicsSystem);

        /**
         * @brief Default constructor that should only be used for serialization.
         */
        Actions() {}

        /**
         * @brief Update the position based on active Actions in 
         * the object.
         *
         * @param position Position object to be updated.
         */
        void Apply(Position & position, float delta);

        /**
         * @brief Create an action for setting the position.
         *
         * @return A proxy to the position Action.
         */
        VectorActionProxy CreatePositionAction();

        /**
         * @brief Create an action for setting the velocity.
         *
         * @return A proxy to the velocity Action.
         */
        VectorActionProxy CreateVelocityAction();

        void Serialize(Archive & arc);

        /**
         * @brief Used to set if an entity is affected by gravity.  Defaults to true.
         *
         * @param value Boolean value determining if the entity is affected by gravity.
         */
        void SetAffectedByGravity(bool value) { _affectedByGravity = value; }

        /**
         * @brief Remove any acceleration that has been caused by gravity.
         */
        void StopFall();

        /* Getters and Setters */
        void SetPhysics(BasePhysicsSystem * physicsSystem) { _physicsSystem = physicsSystem; }
    private:
        /**
         * @brief Update the velocity based on Gravity.
         *
         * @param velocity Current velocity as determined by actions.
         */
        void ApplyGravity(Point & velocity, float delta);

        Point ApplyPositionActions(const Position & position, float delta);
        Point ApplyVelocityActions(const Position & position, float delta);

        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
        Point _totalGravity;
        BasePhysicsSystem * _physicsSystem;
        bool _affectedByGravity = false;
        bool _onGround = false;
};

}
#endif
