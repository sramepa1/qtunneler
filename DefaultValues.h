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

//Expolsion
#define EXPLOSION_RADIUS 24
#define EXPLOSION_TANK_RADIUS 24
#define EXPLOSION_DAMAGE 500 //100% of explosion damage, decrease with distance linearly
#define EXPLOSION_RAND_INCREASE 0.3

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


//Map
#define BORDER_SIZE 20

//Evaluation
#define FRAME_MSECS 25

//Packets
//
//  TODO use enum instead? <<<<<<<
//
#define OP_NULL_PACKET 0

#define OP_INIT_START 1
#define OP_INIT_END 2
#define OP_INIT_CONFIRM 3

#define OP_START_GAME 4

#endif	/* _DEFAULTVALUES_H */

