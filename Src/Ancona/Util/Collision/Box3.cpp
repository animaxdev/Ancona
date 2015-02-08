#include <Ancona/Util/Collision/Box3.hpp>

using namespace ild;

Box3::Box3(const sf::Vector3f & position,
           const sf::Vector3f & dimmension,
           const sf::Vector2f & rotation)
        : Position(position),Dimmension(dimmension),
          Rotation(rotation)
{


}

bool Intersects(const Box3 & box)
{
    return false;

}

bool Contains(const Box3 & box)
{
    return false;

}