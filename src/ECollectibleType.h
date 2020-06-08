/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

/**
 * Boost types which can be collected by the player.
 */
enum class ECollectibleType
{
    /** Adds speed to the player. */
    COLLECTIBLE_TYPE_SPEED = 0,
    /** Bombs planted by the player will have bigger explosion radius. */
    COLLECTIBLE_TYPE_EXPLOSION_RADIUS = 1,
    /** Player is able to plant more bombs in the board. */
    COLLECTIBLE_TYPE_MAX_BOMBS = 2,
    /** Player is able to manually detonate his bombs. */
    COLLECTIBLE_TYPE_REMOTE_EXPLOSION = 3,
    /** Player can walk through all bombs. */
    COLLECTIBLE_TYPE_BOMB_PASS = 4,
    /** Player can walk through destructible walls.  */
    COLLECTIBLE_TYPE_WALL_PASS = 5,
    /** Player cannot be killed by an explosion. */
    COLLECTIBLE_TYPE_FIRE_IMUNITY = 6,
    /** Player achieves score bonus. */
    COLLECTIBLE_TYPE_SCORE_BONUS = 7,
    /** Player will be moved in a next level. */
    COLLECTIBLE_TYPE_DOOR = 8
};
