/**
 * @author Jaroslav Fikar
*/

#pragma once

enum class EEnemyMovementMode
{
    /** The enemy just walks forward */
    ENEMY_MOVEMENT_MODE_WALK_FORWARD = 0,
    /** The enemy moves randomly and turns randomly. */
    ENEMY_MOVEMENT_MODE_RANDOM = 1,
    /** Enemy is tries to catch and kill the player. */
   /* ENEMY_MOVEMENT_MODE_FOLLOW_THE_PLAYER = 2,*/
    /** Enemy protects random collectible. */
    /*ENEMY_MOVEMENT_MODE_PROTECT_COLLECTIBLE = 3,*/
    /** Items count. */
    ENEMY_MOVEMENT_MODE_NR_ITEMS = 2
};

