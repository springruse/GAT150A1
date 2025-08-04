#include "GameData.h"

namespace GameData
{
    std::vector<piMath::vec2> squarePoint{ // makes a square 
        {-5,-5},
        { 5,-5},
        { 5, 5},
        {-5, 5},
        {-5,-5}
    };

    std::vector<piMath::vec2> playerShipPoints{ // makes a player ship
        { 3, 0 },
        { -3, -3 },
        { -1, 0 },
        { -3, 3 },
        { 3, 0 },
    };
    std::vector<piMath::vec2> enemyShipPoints{ // makes a enemy ship
       { 3, 0 },
       { -3, -3 },
       { -1, 0 },
       { -3, 3 },
       { 3, 0 },
    };

    std::vector<piMath::vec2> rocketPoints{ // makes a rocket
        { 0, -5 },  // Top point
        { 2, 5 },   // Bottom right point
        { -2, 5 },  // Bottom left point
		{ 0, -5 }   // Closing the shape back to the top point
	};
}