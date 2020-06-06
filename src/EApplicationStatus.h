/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

/** Application states. */
enum class EApplicationStatus
{
    /** Show menu where player can choose one option. */
    APPLICATION_STATUS_MENU = 0,
    /** Show settings form where player can change some options. */
    APPLICATION_STATUS_SETTINGS = 1,
    /** Run game for one player. */
    APPLICATION_STATUS_SOLO_GAME = 2,
    /** Run game for more players.*/
    APPLICATION_STATUS_MULTI_GAME = 3,
    /** Exit application. */
    APPLICATION_STATUS_EXIT = 4,
    /** Neutral apllication state. */
    APPLICATON_STATUS_NONE = 5
};

