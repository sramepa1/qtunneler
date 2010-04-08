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

//Tank
#define TANK_RADIUS 32

#define DEFAULT_TANK_ROTATION NORTH
#define DEFAULT_TANK_HP 1024 //100%
#define DEFAULT_TANK_ENERGY 1024 //100%

//Matrix
#define MATRIX_DIMENSION (10 * 1024)


#endif	/* _DEFAULTVALUES_H */

