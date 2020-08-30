#ifndef FUNCIONES_H
#define FUNCIONES_H
#define MAX_COLUMNS 100
#define activado 1
#define desactivado 0
#define cerca 1
#define lejos 0
#include "Estructuras.h"
#define screenWidth 1200
#define screenHeight 800

void generar_cubos();
void dibujar_cubos();
void dibujar_paredes_y_piso();
void obtener_posicion_mouse();
void dibujar_cooredanadas(Camera * camera);
void activate_maze(Camera * camera,int * state_mazeSmall, int * state_mazeMedium, int * state_mazebig);
void Draw_MazeSmall(int state_mazeSmall, Camera * camera);
void Draw_MazeMedium(int state_mazeMedium, Camera * camera);
void Draw_MazeBig(int state_mazeBig, Camera * camera);
void lobby();
int define_closeness(double actual_x, double actual_z, double teleporterX, double teleporterZ);
void define_teleporters(Camera * camera);
void teleportation(Camera * camera,double teleporterX,double teleporterZ, double x,double y, double z);	
void Calculate_BoundingBox(BoundingBox* box, Block wall, float width, float height, float lenght);
void Assing_Valeu_Small(Block* lab1);
void Assing_Valeu_Medium(Block* lab);
void Assing_Valeu_Big(Block* lab);
// esta funcion hace que se demore un numero determinado de segundos para realizar una accion
//se ingresa como parametro el numero de segundos
void delay(int number_of_seconds);
void dibujar_lentamente(int numero_de_dibujos);
void dibujar_interfaz();



#endif

