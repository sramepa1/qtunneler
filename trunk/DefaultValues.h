/* 
 * File:   DefaultValues.h
 * Author: rh
 *
 * Definition of defalt values of the program.
 *
 * Created on 2. duben 2010, 12:10
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

//Projectile
#define PROJECTILE_RADIUS 4


//Matrix
#define MATRIX_DIMENSION (10 * 1024)

//Tank
#define TANK_RADIUS 32

#define TANK_ENERGY_COST_OF_MOVE 1
#define TANK_ENERGY_COST_OF_MOVE_IN_CLUE 10
#define TANK_ENERGY_COST_OF_FIRE 100

#define DEFAULT_TANK_ROTATION NORTH //defined in OrientedRoundObj
#define DEFAULT_TANK_HP 10000 //100%
#define DEFAULT_TANK_ENERGY (5 * MATRIX_DIMENSION ) //100%

//Expolsion
#define EXPLOSION_RADIUS (TANK_RADIUS / 2)
#define EXPLOSION_DAMAGE 500 //100% of explosion damage, decrease with distance linearly
#define EXPLOSION_RAND_SOLID_PART 0.5

//Map
#define BORDER_SIZE TANK_RADIUS

//Evaluation
#define FRAME_MSECS 33

//Packets
//
//  TODO use enum instead? <<<<<<<
//
#define OP_NULL_PACKET 0

#define OP_INIT_START 1
#define OP_INIT_END 2
#define OP_INIT_CONFIRM 3

#define OP_START_GAME 4

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
// OP_SHOOT - timecode yes, data1 = tank ID
// OP_SHOOT - data2: 1 = commence firing, 0 = cease fire

#endif	/* _DEFAULTVALUES_H */

