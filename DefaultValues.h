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

//NET
#define CONNECTION_TIMEOUT 3000
#define SERVER_HELLO "Shields up!\n"
#define SERVER_HELLO_BUFF_SIZE 16
#define CLIENT_HELLO "Beam me up, Scotty!\n"
#define CLIENT_HELLO_BUFF_SIZE 24

//Projectile
#define PROJECTILE_RADIUS 4

//Expolsion
#define EXPLOSION_RADIUS 24
#define EXPLOSION_DAMAGE 500 //100% of explosion damage, decrease with distance linearly

//Tank
#define TANK_RADIUS 32

#define TANK_ENERGY_COST_OF_MOVE 1
#define TANK_ENERGY_COST_OF_MOVE_IN_CLUE 10
#define TANK_ENERGY_COST_OF_FIRE 100

#define DEFAULT_TANK_ROTATION NORTH
#define DEFAULT_TANK_HP 10000 //100%
#define DEFAULT_TANK_ENERGY 10000 //100%

//Matrix
#define MATRIX_DIMENSION (10 * 1024)

//Map
#define BORDER_SIZE 20


#endif	/* _DEFAULTVALUES_H */

