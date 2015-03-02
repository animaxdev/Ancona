#ifndef Ancona_Engine_EntityFramework_SystemManager_H_
#define Ancona_Engine_EntityFramework_SystemManager_H_

#include <map>
#include <set>
#include <unordered_map>
#include <vector>

#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>
#include <Ancona/Engine/Loading/AbstractInflater.hpp>

namespace ild
{

class AbstractSystem;

/**
 * @brief Used to update entity systems and track entity state.
 *
 * @author Jeff Swenson
 */
class SystemManager
{
    public:
        /**
         * @brief Create and Initialize the SystemManager.
         */
        SystemManager();

        /**
         * @brief Will update all managers that were registered with the given updateStep.
         *
         * @param delta The amount of time in ms that has passed since the last update
         * @param updateStep Determines which managers should be updated
         */
        void Update(float delta, UpdateStepEnum updateStep);

        /**
         * @brief Delete the entity and free any components used by it.  An entity can only
         * be deleted once.  After an entity is deleted no reference to it or any of its
         * components should be used again.
         *
         * @param entity Entity that should be deleted.
         */
        void DeleteEntity(Entity entity);

        /**
         * @brief Queue the entity to delete at the end of the phase.
         *
         * @param entity Entity to be deleted.
         */
        void QueueDelete(Entity entity);

        /**
         * @brief Create a new unique Entity. Since no key is provided you will
         * be unable to retrieve the entity using GetEntity(std::string).
         *
         * @return A new anonymous entity.
         */
        Entity CreateEntity();

        /**
         * @brief Create a new unique Entity.  The key can be used to retrieve the
         * entity from the system using GetEntity(std::string).
         *
         * @param key String key used to retrieve the entity.
         *
         * @return A new keyed entity.
         */
        Entity CreateEntity(const std::string & key);

        /**
         * @brief Get the keyed entity.
         *
         * @param key Key of the Entity to be retrieved.
         *
         * @return The entity keyed by the string.  If no such entity entity
         * exists then nullentity is returned.
         */
        Entity GetEntity(const std::string & key);

        /**
         * @brief Register the System with the system manager.  This is needed in order for the
         * SystemManager to notify a system if an entity is deleted.  A system can only be
         * registered once.
         *
         * This method should only be called by the system that is being registered.
         *
         * @param systemName Name of the system.
         * @param system System that is being registered
         * @param updateStep Step that determines when the system is updated
         */
        void RegisterSystem(
                std::string systemName,
                AbstractSystem * system, 
                UpdateStepEnum updateStep);

        /**
         * @brief Called when a system is creating a new component for an entity.  This
         * method must be called in order for the system to be notified when the entity is
         * deleted.
         *
         * This method should only be called by the system that is being registered.
         *
         * @param entity Entity that the component is added to
         * @param owningSystem System that will control the component
         */
        void RegisterComponent(Entity entity, AbstractSystem * owningSystem);

        /**
         * @brief Called when a system is removing a component from an entity.
         *
         * This method should only be called by the system that contains the entity.
         *
         * @param entity Entity whose component is being deleted.
         * @param owningSystem System that is deleting the component.
         */
        void UnregisterComponent(Entity entity, AbstractSystem * owningSystem);


        /* getters and setters */
        std::vector<std::pair<std::string, AbstractInflater *>> GetComponentInflaters();
        std::vector<std::pair<std::string, AbstractSystem *>> GetKeyedSystems() { return _keyedSystems; }

    private:
        /**
         * @brief Used to track which systems are controlled by the manager and
         * when they should be updated.
         */
        std::map< UpdateStepEnum, std::vector<AbstractSystem * > > _systems;
        /**
         * @brief Used to track which systems manage a component for each entity
         */
        std::unordered_map< Entity, std::set<AbstractSystem * > > _components;
        /**
         * @brief Highest id that has been assigned to an entity.  Used to assign 
         * unique ids 
         */
        unsigned int _maxEntityId;
        /**
         * @brief Holds the entities queued for deletion
         */
        std::vector<Entity> _deleteQueue;
        /**
         * @brief A map used to key entities using strings.
         */
        std::map<std::string, Entity> _entities; 
        /**
         * @brief A map for doing reversal lookup of entity keys.
         */
        std::map<Entity, std::string> _entitiesReverse;
        /**
         * @brief The systems stored with their keys in the order they were added to the manager.
         */
        std::vector<std::pair<std::string, AbstractSystem *> > _keyedSystems;

        /**
         * @brief Deletes all the entities queued for deletion.
         */
        void DeleteQueuedEntities();

        /**
         * @brief Returns true if the systemName is already associated with a system being managed.
         */
        bool ContainsName(std::string & systemName);
};

}
#endif 
