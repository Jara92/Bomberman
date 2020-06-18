/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <queue>
#include "CEnemy.h"
#include "CPlayer.h"
#include "../blocks/collectibles/CCollectible.h"

class CEnemySmart : public CEnemy
{
public:
    /**
    * CEnemySmart contructor.
    * @param texturePack Texturepack to be rendered.
    * @param location Starting location. (Must be passable)
    * @param size Object size.
    * @param score Score to be claimed.
    * @param speed Enemy speed.
    * @param wallPass Can this Enemy walk through destructible walls?
    * @param lives How many lives doest this monster have?
    */
    explicit CEnemySmart(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size = CCoord<>(1, 1),
                         int score = 0, double speed = 0.005, bool wallPass = false, int lives = 1)
            : CEnemy(std::move(texturePack), location, size, score, speed, wallPass, lives, 1),
              m_PersecutedPlayer(nullptr)
    {}

    CEnemySmart(const CEnemySmart &other) = default;

    CEnemySmart &operator=(const CEnemySmart &other) = default;

    virtual ~CEnemySmart() = default;

    virtual void Update(CBoard &board, int deltaTime) override;

protected:
    const CPlayer *m_PersecutedPlayer;

    virtual void UpdateMovementMode() override;

    virtual void Move(const CBoard &board, int deltaTime) override;

    /**
     * Enemy finds best way to target location.
     * @param board Game board.
     * @param location Target location.
     * @return New movement vector.
     */
    CCoord<> FindWayToLocation(const CBoard &board, CCoord<unsigned int> location);


    bool FindWayToLocationRec(std::vector<std::vector<bool>> map, CCoord<unsigned int> oldLocation,
                              CCoord<unsigned int> currentLocation,
                              CCoord<unsigned int> targetLocation);

    /**
     * Enemy follows the player.
     * @param board Game board.
     */
    bool FollowThePlayer(const CBoard &board);

    /* std::vector<CCoord<>> FindPath(std::vector<std::vector<bool>> map)
     {
         int m = map.size();

         std::vector<CCoord<>> result;

         std::vector
     }*/

    std::vector<CCoord<int>> m_PathToPlayer;

    std::vector<CCoord<int>> findPath(std::vector<std::vector<bool>> &map, CCoord<unsigned int> currentLocation,
                                      CCoord<unsigned int> targetLocation)
    {
        std::vector<CCoord<int>> temp;
        std::vector<CCoord<int>> list;
        std::vector<CCoord<int>> tempDirections;
        std::vector<CCoord<int>> directions;

        dfs(map, currentLocation.m_X, currentLocation.m_Y, temp, list, tempDirections, directions, targetLocation);

        list.insert(list.begin(), this->GetLocationCell().ToInt());
        directions.clear();

        std::cout << "Location and path: " << std::endl;
        for(int i = 0; i < list.size(); i++)
        {
          //  std::cout << list[i] << std::endl;
           // std::cout << directions[i] << std::endl;
          if(i > 0)
          { std::cout << list[i] - list [i - 1] << std::endl; directions.push_back(list[i] - list [i - 1]);}
        }


        return directions;
    }

    void dfs(std::vector<std::vector<bool>> &map, int i, int j,
             std::vector<CCoord<int>> &temp, std::vector<CCoord<int>> &list, std::vector<CCoord<int>> &tempDirections,
             std::vector<CCoord<int>> &directions, CCoord<unsigned int> targetLocation)
    {

        int m = map.size();

        if (i == targetLocation.m_X && j == targetLocation.m_Y)
        {
            list.clear();
            list.insert(list.end(), temp.begin(), temp.end());

            directions.clear();
            directions.insert(directions.end(), tempDirections.begin(), tempDirections.end());
            return;
        }

       /* int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};*/

        std::vector<CCoord<int>> possibleDirections = {{-1, 0},
                                                    {1,  0},
                                                    {0,  -1},
                                                    {0,  1}};

        for (int k = 0; k < 4; k++)
        {
            int x = i + possibleDirections[k].m_X;
            int y = j + possibleDirections[k].m_Y;

            if (x >= 0 && y >= 0 && x <= m - 1 && y <= m - 1 && map[x][y] == true)
            {
                  temp.push_back(CCoord<int>(x, y));
                tempDirections.push_back(possibleDirections[k]);

                bool prev = map[x][y];
                map[x][y] = false;

                dfs(map, x, y, temp, list, tempDirections, directions, targetLocation);

                map[x][y] = prev;
                 temp.erase(temp.end() - 1);
                tempDirections.erase(tempDirections.end() - 1);
            }
        }
    }
};

