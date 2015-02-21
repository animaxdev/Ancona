#include <Ancona/Util/Collision/Math.hpp>
#include <cmath>

using namespace ild;

std::pair<float,float> Math::CreatePoint(
        float sinValue, float cosValue,
        float xSize, float ySize,
        float xOffset, float yOffset)
{
    float xPos = xSize * cosValue - ySize * sinValue + xOffset;
    float yPos = xSize * sinValue + ySize * cosValue + yOffset; 

    return std::pair<float,float>(xPos,yPos);
}

Math::Vector2 Math::GetEdge(const Point2 & vertexA, const Point2 & vertexB)
{
    return Vector2(vertexA.first - vertexB.first, vertexA.second - vertexB.second);
}

Math::Vector2 Math::GetNormal(const Vector2 & edge)
{
    return Vector2(-edge.second, edge.first);
}


float Math::Dot(const Math::Vector2 & a, const Math::Vector2 & b)
{
    return a.first * b.first + a.second * b.second;        
}

Math::Projection2 Math::GetProjection(const Vertices2 & shapeA, const Vector2 & normal)
{
    auto max = -INFINITY;
    auto min = INFINITY;

    for(auto & point : shapeA)
    {
        auto dot = Dot(point, normal);
        max = fmax(max, dot);
        min = fmin(min, dot);
    }
    
    return Projection2(min,max);
}

bool Math::Intersect(const Projection2 & a, const Projection2 & b)
{
    return !(a.first > b.second || b.first > a.second);   
}

float Math::FixMagnitude(const Math::Projection2 & a, const Math::Projection2 & b)
{
    if(a.first >= b.second || b.first > a.second)
    {
        return 0;
    }

    float left = b.first - a.second;  
    float right = b.second - a.first;
    return fabs(left) > fabs(right) ? right : left;
}

Math::Point2 Math::Normalize(const Math::Point2 & vector)
{
    float magnitude = sqrt(vector.first * vector.first + vector.second * vector.second);
    return Point2(vector.first / magnitude, vector.second / magnitude);
}

//Only test the axis's defined by shapeA
static bool TestShapeAxis(const Math::Vertices2 & shapeA, const Math::Vertices2 & shapeB)
{
    using namespace Math;
    for(auto i = 0u; i < shapeA.size(); i++)
    {
        auto endIndex = i + 1 >= shapeA.size() ? 0 : i + 1;
        auto edge = GetEdge(shapeA[i], shapeA[endIndex]);
        auto normal = GetNormal(edge);

        auto projectionA = GetProjection(shapeA, normal);
        auto projectionB = GetProjection(shapeB, normal);

        if(!Intersect(projectionA, projectionB))
        {
            return false; 
        }
    }
    return true;
}

static Math::Point2 GetFixVector(const Math::Vertices2 & shapeA, const Math::Vertices2 & shapeB)
{
    using namespace Math;
    float min = INFINITY;
    Point2 normalOfMin;
    for(auto i = 0u; i < shapeA.size(); i++)
    {
        auto endIndex = i + 1 >= shapeA.size() ? 0 : i + 1;
        auto edge = GetEdge(shapeA[i], shapeA[endIndex]);
        auto normal = Normalize(GetNormal(edge));

        auto projectionA = GetProjection(shapeA, normal);
        auto projectionB = GetProjection(shapeB, normal);

        auto fix = FixMagnitude(projectionA, projectionB);

        if(fabs(fix) < fabs(min))
        {
            min = fix;  
            normalOfMin = normal;
        }
    }
    return Math::Point2(-normalOfMin.first * min, normalOfMin.second * min);
}

bool Math::Collide(const Vertices2 & shapeA, const Vertices2 & shapeB)
{
    return TestShapeAxis(shapeA,shapeB) && TestShapeAxis(shapeB,shapeA);
}

bool Math::Collide(const Vertices2 & shapeA, const Vertices2 & shapeB, Point2 & fixVector)
{
    if(TestShapeAxis(shapeA,shapeB) &&
        TestShapeAxis(shapeB,shapeA))
    {
        fixVector = GetFixVector(shapeA, shapeB);
        return true;
    }
    else
    {
        fixVector = Math::Point2(0,0);
        return false;
    }
}
