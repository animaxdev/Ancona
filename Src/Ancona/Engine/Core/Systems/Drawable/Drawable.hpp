#ifndef Ancona_Engine_Core_Systems_Drawable_H_
#define Ancona_Engine_Core_Systems_Drawable_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Engine/Loading/Loading.hpp>

namespace ild
{

namespace RenderPriority
{

    /**
     * @brief Determines when the drawable objects are rendered, the lower the priority the sooner they are rendered.
     *
     * @author Tucker Lein
     */
    enum RenderPriority
    {
        Background = -1000,
        Player = 0,
        Foreground = 1000,
    };
}

/**
 * @brief Defines when the sprite should be rendered
 *
 * @author Tucker Lein
 */
typedef RenderPriority::RenderPriority RenderPriorityEnum;

/**
 * @brief Defines a drawable element used in the DrawableSystem
 *
 * @author Tucker Lein
 */
class Drawable
{

    public:
        Drawable () {}
        /**
         * @brief Constructs a Drawable.
         *
         * @param positionSystem PositionSystem that can be used to fetch the position component.
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from the DrawableComponent's position.
         */
        Drawable(
                BasePhysicsSystem * positionSystem,
                const int priority,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the object to the window.
         *
         * @param window RenderWindow for the game.
         */
        virtual void Draw(
                sf::RenderWindow & window, 
                float delta) = 0;

        /* getters and setters */
        int GetRenderPriority() { return _renderPriority + _priorityOffset; }
        float GetRotation() { return _rotation; }
        void SetRotation(float rotation) { _rotation = rotation; }
        virtual sf::Vector2u GetSize() = 0;
        virtual int GetAlpha() = 0;
        virtual void SetAlpha(int alpha) = 0;

        virtual void FetchDependencies(const Entity & entity);

        virtual void Serialize(Archive & archive);

    protected:
        BasePhysicsSystem * _physicsSystem;
        /**
         * @brief Component that defines the entities position.
         */
        BasePhysicsComponent * _physicsComponent;
        /**
         * @brief Offset coordinate for this drawable element.
         */
        sf::Vector2f _positionOffset;
        /**
         * @brief Priority of rendering this obj.
         */
        int _renderPriority;
        /**
         * @brief Offsets the render priority.
         */
        int _priorityOffset;
        /**
         * @brief Amount to rotate the drawable element. 
         */
        float _rotation = 0;
};

}

GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(ild::Drawable)

#endif
