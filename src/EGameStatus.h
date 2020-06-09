/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

/**
 * Game states.
 */
enum class EGameStatus
{
    /** The game is running. Players are able to move and die. */
    GAME_STATUS_RUNNING = 0,
    /** Game is paused and all update methods are stopped.*/
    GAMESTATUS_PAUSED = 1,
    /**
     * Current round is over because the player was killed.
     * But the player is not completely dead.
     * Player will place same round again.
     */
    GAME_STATUS_ROUND_OVER = 2,
    /**
     * Player finished the round.
     * Next round will be loaded.
     */
    GAME_STATUS_NEXT_ROUND = 3,
    /** Player is completely dead. */
    GAME_STATUS_GAME_OVER = 4,
    /** Game is over and the player want to leave it. */
    GAME_STATUS_EXIT = 5
};

