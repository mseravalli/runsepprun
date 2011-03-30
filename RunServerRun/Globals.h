#ifndef GLOBALS_H
#define GLOBALS_H

#define GRAVITY_FORCE 1.02

#define MAX_PLAYERS 4

#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1
#define NO_DIRECTION 0
#define UP_DIRECTION 1
#define DOWN_DIRECTION -1

#define BASE_X_RESOLUTION 800
#define BASE_Y_RESOLUTION 600
#define TIMER_X_MSEC 15
#define PLAYER_X 100
#define PLAYER_Y 60
#define PLAYER_WIDTH 22
#define PLAYER_HEIGHT 49
#define PLAYER_COLOR "black"

#define PLAYER_X_VELOCITY 2.0
#define PLAYER_Y_VELOCITY -4.0


#define LEVEL_LOADED 0
#define FILE_NOT_FOUND 1
#define NOT_WELL_FORMED 2
#define INCONSISTENT_VALUES 4

#define EGG_X_VELOCITY 6.0
#define EGG_Y_VELOCITY -1.0
#define EGG_SIZE 7
#define EGG_COLOR "red"
#define NO_OF_EGGS 10

#define ENEMY_X_VELOCITY 1
#define ENEMY_Y_VELOCITY -2.5

#define JUMP_RATE 85
#define TURN_RATE 350

#define AA_BORDER 1
#define CENAL_AREA_LEFT 300
#define CENAL_AREA_RIGHT 500

#define NOT_COLLIDING 			0
#define ENVIRONMENT_COLLIDING 	1
#define DEATHLY_COLLIDING  		2
#define COLLECTABLE_COLLIDING 	3
#define IMMEDIATE_DEATH 		4

#define TEXTURE_OFFSET 30



// SERVER GENERALS
#define SERVER_INCOMING_PORT_UDP 45454
#define SERVER_INCOMING_PORT_TCP 45453
#define CLIENT_INCOMING_PORT_UDP 45455
#define SEPARATOR '\x99'
#define SEND_INT 15


// PACKETS DESTINATED TO SERVER
#define HELLO_PACKET '\x50'
#define HELLO_PACKET_SIZE 1


#define ACK_PACKET '\x51'
#define ACK_PACKET_SIZE 2


#define LEVEL_ID_PACKET '\x52'
#define LEVEL_ID_PACKET_SIZE 3

#define ACK2_PACKET '\x55'
#define ACK2_PACKET_SIZE 2

#define READY_PACKET '\x53'
#define READY_PACKET_SIZE 2


#define KEY_INPUT_PACKET '\x54'
#define KEY_INPUT_PACKET_SIZE 5



// PACKETS DESTINATED TO CLIENT
#define ID_PACKET '\x80'
#define ID_PACKET_SIZE 3
#define ID_PACKET_RIGHTS_NEW '\x90'
#define ID_PACKET_RIGHTS_JOIN '\x91'
#define ID_PACKET_RIGHTS_VFC '\x92'

#define LEVELLIST_PACKET '\x81'


#define LEVEL_PACKET '\x82'

#define ITEM_PACKET '\x83'

#define END_PACKET '\x84'
#define END_PACKET_SIZE 1

#define NEXT_LEVEL_PACKET '\x85'
#define NEXT_LEVEL_PACKET_SIZE 2

// PLAYER ID
#define LEADER_PLAYER 0
#define VFC_PLAYER -1

// PLAYER STATES
#define UNNOWN_STATE -1

class Player;
class Egg;
class QThread;
class ConnectionThread;
class QHostAddress;

#include <QtNetwork>

typedef struct
{
    int id;
    Player* player;
    Egg** eggs;
    int state;
    ConnectionThread* thread;
    QHostAddress ip;
}clientListItem;


// COMPRESSION
#define ARCH_ID1 '\x12'
#define ARCH_ID2 '\x24'

#define LEVEL_DIR "./levels"
#define LEVEL_SOURCE_DIR "/usr/games/levels"

#endif
