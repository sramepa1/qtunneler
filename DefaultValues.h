/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#ifndef _DEFAULTVALUES_H
#define	_DEFAULTVALUES_H

//GUI
#define APP_NAME_STRING "QTunneler"

//Network
#define CONNECTION_TIMEOUT 3000

#define SERVER_HELLO "Shields up!\n"
#define SERVER_HELLO_BUFF_SIZE 16
#define CLIENT_HELLO "Beam me up, Scotty!\n"
#define CLIENT_HELLO_BUFF_SIZE 24

#define PACKET_BYTES 20

//Player
#define NO_PLAYER 0
#define RED_PLAYER 1
#define GREEN_PLAYER 2
#define BLUE_PLAYER 3

//Projectile
#define PROJECTILE_RADIUS 4
#define PROJECTILE_SPEED 32

//Matrix
#define MATRIX_DIMENSION (10 * 1024)

//Tank
#define TANK_RADIUS 32

#define TANK_ENERGY_COST_OF_MOVE 1
#define TANK_ENERGY_COST_OF_MOVE_IN_CLUE 10 // TODO remove - will be replaced by pixel munching
#define TANK_ENERGY_COST_OF_FIRE 100

#define DEFAULT_TANK_ROTATION NORTH //defined in OrientedRoundObj
#define DEFAULT_TANK_HP 10000 //100%
#define DEFAULT_TANK_ENERGY (5 * MATRIX_DIMENSION ) //100%

//Expolsion
#define EXPLOSION_RADIUS (TANK_RADIUS / 2)
#define EXPLOSION_DAMAGE 500 //100% of explosion damage, decrease with distance linearly
#define EXPLOSION_RAND_SOLID_PART 0.5

#define TANK_EXPLOSION_RADIUS (2 * TANK_RADIUS)

//Map
#define BORDER_SIZE (3 * TANK_RADIUS)
#define STONE_COUNT 150
#define STONES_MAX_WIDTH 360 / 8
#define STONES_MAX_HEIGHT 360 / 8

//Base and BaseWall
#define BASE_WIDTH 240
#define BASE_HEIGHT 240
#define BASE_MIN_DISTANCE_FROM_BORDER 240

#define TANK_ENERGY_GAIN_OWN_BASE 80
#define TANK_ENERGY_GAIN_ENEMY_BASE 40
#define TANK_HP_GAIN_OWN_BASE 80
#define TANK_HP_GAIN_ENEMY_BASE 40


//Evaluation
#define FRAME_MSECS 33
#define MAX_WINS 3

// Packets //
// Init packets
#define OP_NULL_PACKET 0

#define OP_INIT_START 1
#define OP_INIT_END 2
#define OP_INIT_CONFIRM 3

#define OP_START_GAME 4

// Client-to-server packets
#define OP_MOVE 5
// OP_MOVE - timecode yes, data1 = tank ID
// OP_MOVE - data2:
#define MOVE_STOP 0
#define MOVE_N 1
#define MOVE_NE 2
#define MOVE_E 3
#define MOVE_SE 4
#define MOVE_S 5
#define MOVE_SW 6
#define MOVE_W 7
#define MOVE_NW 8

#define OP_SHOOT 6
// OP_SHOOT - timecode yes, 
// OP_SHOOT - data1 = tank ID, data2: 1 = commence firing, 0 = cease fire

//Server-to-client packets
#define OP_TANK 7
// OP_TANK - timecode used for orientation
// OP_TANK - data1 = tank ID, data2 = X, data 3 = Y

#define OP_TANK_STATUS 8
// OP_TANK_STATUS - timecode used for rounds won
// OP_TANK_STATUS - data1 = tank ID, data2 = HP, data3 = energy

#define OP_PROJECTILE 9
// OP_PROJECTILE - timecode used for orientation
// OP_PROJECTILE - data1 = projectile ID, data2 = X, data 3 = Y

#define OP_EXPLOSION 10
// OP_EXPLOSION - timecode used for random seed
// OP_EXPLOSION - data1 = projectile ID, data2 = X, data 3 = Y

#define OP_TANK_EXPLOSION 11
// OP_TANK_EXPLOSION - timecode used for random seed
// OP_TANK_EXPLOSION - data1 = tank ID, data2 = X, data 3 = Y

#define OP_BASE 12
// OP_BASE - timecode not used, WARNING - this also declares a BaseWall
// OP_BASE - data1 = tank ID, data2 = X1, data3 = Y1

#define OP_STONE 13
// OP_STONE - timecode = x1, data1 = y1, data2 = width, data3 = height


// Server-to-Client control
#define OP_FRAME_BOUNDARY 14

#define OP_END_ROUND 15

#define OP_END_GAME 16
// OP_END_GAME - data1 = winner tank ID

#endif	/* _DEFAULTVALUES_H */

