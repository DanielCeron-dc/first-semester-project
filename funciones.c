#include <stdio.h> 
#include <time.h> 
#include "raylib.h"
#include "funciones.h"
#include "Estructuras.h"
#include "string.h"


void delay(int number_of_seconds) 
{ 
	// Converting time into milli_seconds 
	int milli_seconds = 1000 * number_of_seconds;
	// Stroing start time 
	clock_t start_time = clock(); 
	// looping till required time is not acheived 
	while (clock() < start_time + milli_seconds); 
} 
void dibujar_interfaz()	
{
	DrawRectangle( 10, 10, 250, 110, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines( 10, 10, 250, 110, BLUE);
	DrawText("controles:", 20, 20, 10, BLACK);
	DrawText("-con las teclas: W, A, S, D", 40, 40, 10, DARKGRAY);
	DrawText("-Mueve el mause para ver alrededor", 40, 60, 10, DARKGRAY);
	DrawFPS(40, 80); 
}

void dibujar_cooredanadas(Camera * camera){
	int fs = 18;
	DrawRectangle( 10, 10, 220, 70, MAGENTA); //Fade(SKYBLUE, 0.5f)
	DrawRectangleLines( 10, 10, 220, 70, BLUE);
	DrawText("Pos:", 15, 20, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->position.x), 45, 20, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->position.y), 85, 20, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->position.z), 125, 20, fs, WHITE);
	DrawText("Up:", 15, 40, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->up.x), 40, 40, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->up.y), 80, 40, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->up.z), 120, 40, fs, WHITE);
	DrawText("Tar:", 15, 60, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->target.x), 50, 60, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->target.y), 90, 60, fs, WHITE);
	DrawText(FormatText("%5.1f", camera->target.z), 130, 60, fs, WHITE);	
}
double Mousex=0; //variables para las posiciones no actualizadas 
double mousey=0;  

void obtener_posicion_mouse(){
	if (Mousex!=GetMouseX()){
		printf("posicion mouse x = %d\n",GetMouseX());
		Mousex=GetMouseX();}
	if (mousey!=GetMouseY()){
		printf("posicion mouse Y = %d\n",GetMouseY());
		mousey=GetMouseY();}
}

void lobby(){
	DrawPlane((Vector3){ 130.0f, 0.0f, 120.0f }, (Vector2){ 55.0f, 55.0f }, DARKGRAY);	
	DrawCube((Vector3){ 126.0f, 2.5f, 146.9f }, -65.0f, -5.0f, 0.2f, GREEN); 
	DrawCube((Vector3){ 126.0f, 2.5f, 94.9f }, -65.0f, -5.0f, 0.2f, GREEN); 
	DrawCube((Vector3){ 102.0f, 2.5f, 120.9f }, 0.2, -5.0f, -65.0f, GREEN); 
	DrawCube((Vector3){ 155.0f, 2.5f, 120.9f }, 0.2, -5.0f, -65.0f, GREEN); 
	DrawSphere((Vector3) {123.0f, 2.0f, 100.0f}, 2, SKYBLUE); //transportador primer laberinto
	DrawSphere((Vector3) {131.1f, 2.0f, 100.0f}, 2, RED); //transportador segundo laberinto
	DrawSphere((Vector3) {138.2f, 2.0f, 100.0f}, 2, DARKPURPLE);//transportador tercer laberinto
}

int define_closeness(double actual_x, double actual_z, double teleporterX, double teleporterZ){
	
	double closeness1 = actual_x - teleporterX;
    double closeness2 = actual_z - teleporterZ;
	if (closeness1 < 0){
		closeness1 = closeness1 * (-1);
	}
	
	if (closeness2 < 0){
		closeness2 = closeness2 * (-1);
	}
	
	if (closeness1 < 1 && closeness2 < 1){
		return cerca; 
	}
	return lejos;
	
}



void teleportation(Camera * camera,double teleporterX,double teleporterZ, double x,double y, double z)//en teleporter se coloca la x del lugar del teletransportador
{  
	
	double actual_x = camera->position.x;
	double actual_z = camera->position.z;
	int posicion_actual = lejos;
	posicion_actual = define_closeness(actual_x, actual_z, teleporterX, teleporterZ);
	
	if (posicion_actual==cerca){ 
		camera->position.x=x;
		camera->position.z=z;
		camera->position.y=y;
	}
}

//Se asignan las coordenadas de los cubos
void Assing_Valeu_Small(Block* lab1)	
{  
	FILE *file_maze_small;
	file_maze_small = fopen("C:/Users/damus/OneDrive/Escritorio/programacion/lenguaje c/Zinjai programs/proyecto - primer semestre/resources/maze_small.txt","r");
	int cont = 0;
	char texto[11];
	int basura=0;
	char basura2[10];
	if (file_maze_small == NULL)
	{
		printf("\nError de apertura del archivo. \n\n");
	}
	else
	{ 
		
		while (cont < 94){
			fgets(texto, 11, file_maze_small);
			sscanf(texto,"%d %f %s", &basura, &lab1[cont].x, basura2);
			//printf(" cont [%d] basura: [%d] coordenadas:  [%f]  enter del final [%s] \n", cont, basura, lab1[cont].x, basura2);
			cont=cont +1;
			fgets(texto, 11, file_maze_small);
			sscanf(texto,"%d %f %s", &basura, &lab1[cont].z, basura2);
			//printf(" cont [%d] basura: [%d] coordenadas:  [%f]  enter del final: [%s] \n",cont, basura, lab1[cont].z, basura2);
			cont=cont +1;
		}
		
	}
	for (int i =0; i < 47; i++)
	{
		lab1[i].y = 1.5f;
	}
	fclose(file_maze_small);
}

void Assing_Valeu_Medium(Block* lab)
{
	for (int i = 0; i < 90; i++)		
	{
		lab[i].y= 2.0f;
	}
	
	lab[0].x= 35.0f;
	
	lab[0].z= -30.0f;
	
	lab[1].x= 30.0f;
	
	lab[1].z= -20.0f;
	
	lab[2].x= 30.0f;
	
	lab[2].z= -15.0f;
	
	lab[3].x= 30.0f;
	
	lab[3].z= -10.0f;
	
	lab[4].x= 30.0f;
	
	lab[4].z= -5.0f;
	
	lab[5].x= 30.0f;
	
	lab[5].z= 0.0f;
	
	lab[6].x= 30.0f;
	
	lab[6].z= 5.0f;
	
	lab[7].x= 30.0f;
	
	lab[7].z= 10.0f;
	
	lab[8].x= 30.0f;
	
	lab[8].z= 15.0f;
	
	lab[9].x= 30.0f;
	
	lab[9].z= 25.0f;
	
	lab[10].x= 30.0f;
	
	lab[10].z=	30.0f;
	
	lab[11].x= 30.0f;
	
	lab[11].z=	35.0f;
	
	lab[12].x= 25.0f;
	
	lab[12].z=	-30.0f;
	
	lab[13].x= 25.0f;
	
	lab[13].z= 15.0f;
	
	lab[14].x= 20.0f;
	
	lab[14].z= -30.f;
	
	lab[15].x= 20.0f;
	
	lab[15].z= -20.0f;
	
	lab[16].x= 20.0f;
	
	lab[16].z= -10.0f;
	
	lab[17].x= 20.0f;
	
	lab[17].z= 0.0f;
	
	lab[18].x= 20.0f;
	
	lab[18].z= 5.0f;
	
	lab[19].x= 20.0f;
	
	lab[19].z= 15.0f;
	
	lab[20].x= 20.0f;
	
	lab[20].z= 25.0f;
	
	lab[21].x= 20.0f;
	
	lab[21].z= 35.0f;
	
	lab[22].x= 15.0f;
	
	lab[22].z=	35.0f;
	
	lab[23].x= 15.0f;
	
	lab[23].z= -30.0f;
	
	lab[24].x= 15.0f;
	
	lab[24].z= -15.0f;
	
	lab[25].x= 15.0f;
	
	lab[25].z= 5.0f;
	
	lab[26].x= 15.0f;
	
	lab[26].z= 15.0f;
	
	lab[27].x= 15.0f;
	
	lab[27].z= 25.0f;
	
	lab[28].x= 10.0f;
	
	lab[28].z= -25.0f;
	
	lab[29].x= 10.0f;
	
	lab[29].z= -15.0f;
	
	lab[30].x= 10.0f;
	
	lab[30].z= 0.0f;
	
	lab[31].x= 10.0f;
	
	lab[31].z= 20.0f;
	
	lab[32].x= 10.0f;
	
	lab[32].z= 25.0f;
	
	lab[33].x= 5.0f;
	
	lab[33].z= -15.0f;
	
	lab[34].x= 5.0f;
	
	lab[34].z= -5.0f;
	
	lab[35].x= 5.0f;
	
	lab[35].z= 0.0f;
	
	lab[36].x= 5.0f;
	
	lab[36].z= 5.0f;
	
	lab[37].x= 5.0f;
	
	lab[37].z= 10.0f;
	
	lab[38].x= 5.0f;
	
	lab[38].z= 35.0f;
	
	lab[39].x= 0.0f;
	
	lab[39].z= 35.0f;
	
	lab[40].x= 0.0f;
	
	lab[40].z= -30.0f;
	
	lab[41].x= 0.0f;
	
	lab[41].z= -25.0f;
	
	lab[42].x= 0.0f;
	
	lab[42].z= -15.0f;
	
	lab[43].x= 0.0f;
	
	lab[43].z= 10.0f;
	
	lab[44].x= 0.0f;
	
	lab[44].z= 15.f;
	
	lab[45].x= 0.0f;
	
	lab[45].z= 25.0f;
	
	lab[46].x= -5.0f;
	
	lab[46].z= -30.0f;
	
	lab[47].x= -5.0f;
	
	lab[47].z= -25.0f;
	
	lab[48].x= -5.0f;
	
	lab[48].z= -15.0f;
	
	lab[49].x= -5.0f;
	
	lab[49].z= -10.0f;
	
	lab[50].x= -5.0f;
	
	lab[50].z= -5.0f;
	
	lab[51].x= -5.0f;
	
	lab[51].z= 10.0f;
	
	lab[52].x= -5.0f;
	
	lab[52].z= 20.0f;
	
	lab[53].x= -5.0f;
	
	lab[53].z= 25.0f;
	
	lab[54].x= -5.0f;
	
	lab[54].z= 35.0f;
	
	lab[55].x= -10.0f;
	
	lab[55].z= -25.0f;
	
	lab[56].x= -10.0f;
	
	lab[56].z= -5.0f;
	
	lab[57].x= -15.0f;
	
	lab[57].z= -25.0f;
	
	lab[58].x= -15.0f;
	
	lab[58].z= -15.0f;
	
	lab[59].x= -15.0f;
	
	lab[59].z= -10.0f;
	
	lab[60].x= -15.0f;
	
	lab[60].z= -5.0f;
	
	lab[61].x= -15.0f;
	
	lab[61].z= 0.0f;
	
	lab[62].x= -15.0f;
	
	lab[62].z= 15.0f;
	
	lab[63].x= -15.0f;
	
	lab[63].z= 20.0f;
	
	lab[64].x= -15.0f;
	
	lab[64].z= 25.0f;
	
	lab[65].x= -15.0f;
	
	lab[65].z= 30.0f;
	
	lab[66].x= -15.0f;
	
	lab[66].z= 35.0f;
	
	lab[67].x= -20.0f;
	
	lab[67].z= -30.0f;
	
	lab[68].x= -20.0f;
	
	lab[68].z= 25.0f;
	
	lab[69].x= -20.0f;
	
	lab[69].z= -15.0f;
	
	lab[70].x= -20.0f;
	
	lab[70].z= 0.0;
	
	lab[71].x= -20.0f;
	
	lab[71].z= 5.0f;
	
	lab[72].x= -25.0f;
	
	lab[72].z= -10.0f;
	
	lab[73].x= -25.0f;
	
	lab[73].z= 5.0f;
	
	lab[74].x= -25.0f;
	
	lab[74].z= 10.0f;
	
	lab[75].x= -25.0f;
	
	lab[75].z= 15.0f;
	
	lab[76].x= -25.0f;
	
	lab[76].z= 25.0f;
	
	lab[77].x= -25.0f;
	
	lab[77].z= 30.0f;
	
	lab[78].x= -30.0f;
	
	lab[78].z= -30.0f;
	
	lab[79].x= -30.0f;
	
	lab[79].z= -25.0f;
	
	lab[80].x= -30.0f;
	
	lab[80].z= -20.0f;
	
	lab[81].x= -30.0f;
	
	lab[81].z= -5.0f;
	
	lab[82].x= -30.0f;
	
	lab[82].z= 15.0f;
	
	lab[83].x= -30.0f;
	
	lab[83].z= 25.0f;
	
	lab[84].x= -30.0f;
	
	lab[84].z= 30.0f;
	
	lab[85].x= -30.0f;
	
	lab[85].z= 35.0f;
	
	lab[86].x= -35.0f;
	
	lab[86].z= -25.0f;
	
	lab[87].x= -35.0f;
	
	lab[87].z= -20.0f;
	
	lab[88].x= -35.0f;
	
	lab[88].z= -15.0f;
	
	lab[89].x= -35.0f;
	
	lab[89].z= 15.0f;	
	
}



void Assing_Valeu_Big(Block* lab)
{
	
	for (int i =0; i <187 ; i++)
		
	{
		
		lab[i].y= 0.1f;
		
	}
	
	
	
	lab[186].x= 50.0f;
	
	lab[186].z= -15.0f;
	
	
	
	lab[0].x= 50.0f;
	
	lab[0].z= -10.0f;
	
	
	
	lab[1].x= 50.0f;
	
	lab[1].z= 10.0f;
	
	
	
	lab[2].x= 50.0f;
	
	lab[2].z= 35.0f;
	
	
	
	lab[3].x= 45.0f;
	
	lab[3].z= -50.0f;
	
	
	
	lab[4].x= 45.0f;
	
	lab[4].z= -45.0f;
	
	
	
	lab[5].x= 45.0f;
	
	lab[5].z= -35.0f;
	
	
	
	lab[6].x= 45.0f;
	
	lab[6].z= -30.0f;
	
	
	
	lab[7].x= 45.0f;
	
	lab[7].z= -25.0f;
	
	
	
	lab[8].x= 45.0f;
	
	lab[8].z= 0.0f;
	
	
	
	lab[9].x= 45.0f;
	
	lab[9].z= 10.0f;
	
	
	
	lab[10].x= 45.0f;
	
	lab[10].z= 20.0f;
	
	
	
	lab[11].x= 45.0f;
	
	lab[11].z= 25.0f;
	
	
	
	lab[12].x= 45.0f;
	
	lab[12].z= 35.0f;
	
	
	
	lab[13].x= 45.0f;
	
	lab[13].z= 45.0f;
	
	
	
	lab[14].x= 45.0f;
	
	lab[14].z= 50.0f;
	
	
	
	lab[15].x= 40.0f;
	
	lab[15].z= -45.0f;
	
	
	
	lab[16].x= 40.0f;
	
	lab[16].z= -25.0f;
	
	
	
	lab[17].x= 40.0f;
	
	lab[17].z= -20.0f;
	
	
	
	lab[18].x= 40.0f;
	
	lab[18].z= -15.f;
	
	
	
	lab[19].x= 40.0f;
	
	lab[19].z= -10.0f;
	
	
	
	lab[20].x= 40.0f;
	
	lab[20].z= -5.0f;
	
	
	
	lab[21].x= 40.0f;
	
	lab[21].z= 0.0f;
	
	
	
	lab[22].x= 40.0f;
	
	lab[22].z= 10.0f;
	
	
	
	lab[23].x= 40.0f;
	
	lab[23].z= 15.0f;
	
	
	
	lab[24].x= 40.0f;
	
	lab[24].z= 20.0f;
	
	
	
	lab[25].x= 40.0f;
	
	lab[25].z= 25.0f;
	
	
	
	lab[26].x= 40.0f;
	
	lab[26].z= 35.0f;
	
	
	
	lab[27].x= 40.0f;
	
	lab[27].z= 45.0f;
	
	
	
	lab[28].x= 35.0f;
	
	lab[28].z= -45.0f;
	
	
	
	lab[29].x= 35.0f;
	
	lab[29].z= -35.0f;
	
	
	
	lab[30].x= 35.0f;
	
	lab[30].z= 35.0f;
	
	
	
	lab[31].x= 35.0f;
	
	lab[31].z= 45.0f;
	
	
	
	lab[32].x= 30.0f;
	
	lab[32].z= -40.0f;
	
	
	
	lab[33].x= 30.0f;
	
	lab[33].z= -35.0f;
	
	
	
	lab[34].x= 30.0f;
	
	lab[34].z= -30.0f;
	
	
	
	lab[35].x= 30.0f;
	
	lab[35].z= -15.0f;
	
	
	
	lab[36].x= 30.0f;
	
	lab[36].z= -10.0f;
	
	
	
	lab[37].x= 30.0f;
	
	lab[37].z= -5.0f;
	
	
	
	lab[38].x= 30.0f;
	
	lab[38].z= 10.0f;
	
	
	
	lab[39].x= 30.0f;
	
	lab[39].z= 15.0f;
	
	
	
	lab[40].x= 30.0f;
	
	lab[40].z= 20.0f;
	
	
	
	lab[41].x= 30.0f;
	
	lab[41].z= 25.0f;
	
	
	
	lab[42].x= 30.0f;
	
	lab[42].z= 30.0f;
	
	
	
	lab[43].x= 30.0f;
	
	lab[43].z= 35.0f;
	
	
	
	lab[44].x= 30.0f;
	
	lab[44].z= 45.0f;
	
	
	
	lab[45].x= 25.0f;
	
	lab[45].z= -50.0f;
	
	
	
	lab[46].x= 25.0f;
	
	lab[46].z= -35.0f;
	
	
	
	lab[47].x= 25.0f;
	
	lab[47].z= -30.0f;
	
	
	
	lab[48].x= 25.0f;
	
	lab[48].z= -20.0f;
	
	
	
	lab[49].x= 25.0f;
	
	lab[49].z= -5.0f;
	
	
	
	lab[50].x= 25.0f;
	
	lab[50].z= 5.0f;
	
	
	
	lab[51].x= 25.0f;
	
	lab[51].z= 30.0f;
	
	
	
	lab[52].x= 25.0f;
	
	lab[52].z= 45.0f;
	
	
	
	lab[53].x= 20.0f;
	
	lab[53].z= -50.0f;
	
	
	
	lab[54].x= 20.0f;
	
	lab[54].z= -45.0f;
	
	
	
	lab[55].x= 20.0f;
	
	lab[55].z= -30.0f;
	
	
	
	lab[56].x= 20.0f;
	
	lab[56].z= -15.0f;
	
	
	
	lab[57].x= 20.0f;
	
	lab[57].z= -5.0f;
	
	
	
	lab[58].x= 20.0f;
	
	lab[58].z= 5.0f;
	
	
	
	lab[59].x= 20.0f;
	
	lab[59].z= 10.0f;
	
	
	
	lab[60].x= 20.0f;
	
	lab[60].z= 15.0f;
	
	
	
	lab[61].x= 20.0f;
	
	lab[61].z= 25.0f;
	
	
	
	lab[62].x= 20.0f;
	
	lab[62].z= 30.0f;
	
	
	
	lab[63].x= 20.0f;
	
	lab[63].z= 40.0f;
	
	
	
	lab[64].x= 20.0f;
	
	lab[64].z= 40.0f;
	
	
	
	lab[65].x= 15.0f;
	
	lab[65].z= -50.0f;
	
	
	
	lab[66].x= 15.0f;
	
	lab[66].z= -40.0f;
	
	
	
	lab[67].x= 15.0f;
	
	lab[67].z= -30.0f;
	
	
	
	lab[68].x= 15.0f;
	
	lab[68].z= -20.0f;
	
	
	
	lab[69].x= 15.0f;
	
	lab[69].z= -5.0f;
	
	
	
	lab[70].x= 15.0f;
	
	lab[70].z= 15.0f;
	
	
	
	lab[71].x= 15.0f;
	
	lab[71].z= 40.0f;
	
	
	
	lab[72].x= 10.0f;
	
	lab[72].z= -50.0f;
	
	
	
	lab[73].x= 10.0f;
	
	lab[73].z= -40.0f;
	
	
	
	lab[74].x= 10.0f;
	
	lab[74].z= -30.0f;
	
	
	
	lab[75].x= 10.0f;
	
	lab[75].z= -10.0f;
	
	
	
	lab[76].x= 10.0f;
	
	lab[76].z= 5.0f;
	
	
	
	lab[77].x= 10.0f;
	
	lab[77].z= 15.0f;
	
	
	
	lab[78].x= 10.0f;
	
	lab[78].z= 25.0f;
	
	
	
	lab[79].x= 10.0f;
	
	lab[79].z= 30.0f;
	
	
	
	lab[80].x= 10.0f;
	
	lab[80].z= 40.0f;
	
	
	
	lab[81].x= 5.0f;
	
	lab[81].z= -50.0f;
	
	
	
	lab[82].x= 5.0f;
	
	lab[82].z= -40.0f;
	
	
	
	lab[83].x= 5.0f;
	
	lab[83].z= -30.0f;
	
	
	
	lab[84].x= 5.0f;
	
	lab[84].z= -25.0f;
	
	
	
	lab[85].x= 5.0f;
	
	lab[85].z= -20.0f;
	
	
	
	lab[86].x= 5.0f;
	
	lab[86].z= -15.0f;
	
	
	
	lab[87].x= 5.0f;
	
	lab[87].z= -5.0f;
	
	
	
	lab[88].x= 5.0f;
	
	lab[88].z= 5.0f;
	
	
	
	lab[89].x= 5.0f;
	
	lab[89].z= 15.0f;
	
	
	
	lab[90].x= 5.0f;
	
	lab[90].z= 30.0f;
	
	
	
	lab[91].x= 5.0f;
	
	lab[91].z= 40.0f;
	
	
	
	lab[92].x= 5.0f;
	
	lab[92].z= 45.0f;
	
	
	
	lab[93].x= 0.0f;
	
	lab[93].z= -50.0f;
	
	
	
	lab[94].x= 0.0f;
	
	lab[94].z= 5.0f;
	
	
	
	lab[95].x= 0.0f;
	
	lab[95].z= 15.0f;
	
	
	
	lab[96].x= 0.0f;
	
	lab[96].z= 30.0f;
	
	
	
	lab[97].x= -5.0f;
	
	lab[97].z= -40.0f;
	
	
	
	lab[98].x= -5.0f;
	
	lab[98].z= -35.0f;
	
	
	
	lab[99].x= -5.0f;
	
	lab[99].z= -25.0f;
	
	
	
	lab[100].x= -5.0f;
	
	lab[100].z= -20.0f;
	
	
	
	lab[101].x= -5.0f;
	
	lab[101].z= -15.0f;
	
	
	
	lab[102].x= -5.0f;
	
	lab[102].z= -10.0f;
	
	
	
	lab[103].x= -5.0f;
	
	lab[103].z= -5.0f;
	
	
	
	lab[104].x= -5.0f;
	
	lab[104].z= 0.0f;
	
	
	
	lab[105].x= -5.0f;
	
	lab[106].z= 15.0f;
	
	
	
	lab[107].x= -5.0f;
	
	lab[107].z= 30.0f;
	
	
	
	lab[108].x= -5.0f;
	
	lab[108].z= 35.0f;
	
	
	
	lab[109].x= -5.0f;
	
	lab[109].z= 40.0f;
	
	
	
	lab[110].x= -5.0f;
	
	lab[110].z= 45.0f;
	
	
	
	lab[111].x= -5.0f;
	
	lab[111].z= 50.0f;
	
	
	
	lab[112].x= -10.0f;
	
	lab[112].z= -40.0f;
	
	
	
	lab[113].x= -10.0f;
	
	lab[113].z= -30.0f;
	
	
	
	lab[114].x= -10.0f;
	
	lab[114].z= -15.0f;
	
	
	
	lab[115].x= -10.0f;
	
	lab[115].z= 0.0f;
	
	
	
	lab[116].x= -10.0f;
	
	lab[116].z= 15.0f;
	
	
	
	lab[117].x= -10.0f;
	
	lab[117].z= 20.0f;
	
	
	
	lab[118].x= -15.0f;
	
	lab[118].z= -45.0f;
	
	
	
	lab[119].x= -15.0f;
	
	lab[119].z= -40.0f;
	
	
	
	lab[120].x= -15.0f;
	
	lab[120].z= -20.0f;
	
	
	
	lab[121].x= -15.0f;
	
	lab[121].z= 20.0f;
	
	
	
	lab[122].x= -15.0f;
	
	lab[122].z= 30.0f;
	
	
	
	lab[123].x= -15.0f;
	
	lab[123].z= 35.0f;
	
	
	
	lab[124].x= -15.0f;
	
	lab[124].z= 40.0f;
	
	
	
	lab[125].x= -15.0f;
	
	lab[125].z= 45.0f;
	
	
	
	lab[126].x= -20.0f;
	
	lab[126].z= -45.0f;
	
	
	
	lab[127].x= -20.0f;
	
	lab[127].z= -40.0f;
	
	
	
	lab[128].x= -20.0f;
	
	lab[128].z= -25.0f;
	
	
	
	lab[129].x= -20.0f;
	
	lab[129].z= -10.0f;
	
	
	
	lab[130].x= -20.0f;
	
	lab[130].z= -5.0f;
	
	
	
	lab[131].x= -20.0f;
	
	lab[131].z= 5.0f;
	
	
	
	lab[132].x= -20.0f;
	
	lab[132].z= 10.0f;
	
	
	
	lab[133].x= -20.0f;
	
	lab[133].z= 15.0f;
	
	
	
	lab[134].x= -20.0f;
	
	lab[134].z= 20.0f;
	
	
	
	lab[135].x= -20.0f;
	
	lab[135].z= 35.0f;
	
	
	
	lab[136].x= -20.0f;
	
	lab[136].z= 45.0f;
	
	
	
	lab[137].x= -25.0f;
	
	lab[137].z= -45.0f;
	
	
	
	lab[138].x= -25.0f;
	
	lab[138].z= -20.0f;
	
	
	
	lab[139].x= -25.0f;
	
	lab[139].z= -5.0f;
	
	
	
	lab[140].x= -25.0f;
	
	lab[140].z= 5.0f;
	
	
	
	lab[141].x= -25.0f;
	
	lab[141].z= 30.0f;
	
	
	
	lab[142].x= -25.0f;
	
	lab[142].z= 35.0f;
	
	
	
	lab[143].x= -25.0f;
	
	lab[143].z= 45.0f;
	
	
	
	lab[144].x= -30.0f;
	
	lab[144].z= -45.0f;
	
	
	
	lab[145].x= -30.0f;
	
	lab[145].z= -40.0f;
	
	
	
	lab[146].x= -30.0f;
	
	lab[146].z= -35.0f;
	
	
	
	lab[147].x= -30.0f;
	
	lab[147].z= -30.0f;
	
	
	
	lab[148].x= -30.0f;
	
	lab[148].z= -20.0f;
	
	
	
	lab[149].x= -30.0f;
	
	lab[149].z= -15.0f;
	
	
	
	lab[150].x= -30.0f;
	
	lab[150].z= -10.0f;
	
	
	
	lab[151].x= -30.0f;
	
	lab[151].z= -5.0f;
	
	
	
	lab[152].x= -30.0f;
	
	lab[152].z= 0.0f;
	
	
	
	lab[153].x= -30.0f;
	
	lab[153].z= 5.0f;
	
	
	
	lab[154].x= -30.0f;
	
	lab[154].z= 10.0f;
	
	
	
	lab[155].x= -30.0f;
	
	lab[155].z=	15.0f;
	
	
	
	lab[156].x= -30.0f;
	
	lab[156].z= 20.0f;
	
	
	
	lab[157].x= -30.0f;
	
	lab[157].z= 45.0f;
	
	
	
	lab[158].x= -35.0f;
	
	lab[158].z= 25.0f;
	
	
	
	lab[159].x= -35.0f;
	
	lab[159].z= 30.0f;
	
	
	
	lab[160].x= -35.0f;
	
	lab[160].z= 35.0f;
	
	
	
	lab[161].x= -35.0f;
	
	lab[161].z=	45.0f;
	
	
	
	lab[162].x= -40.0f;
	
	lab[162].z=	-45.0f;
	
	
	
	lab[163].x= -40.0f;
	
	lab[163].z=	-40.0f;
	
	
	
	lab[164].x= -40.0f;
	
	lab[164].z=	-30.0f;
	
	
	
	lab[165].x= -40.0f;
	
	lab[165].z=	-20.0f;
	
	
	
	lab[166].x= -40.0f;
	
	lab[166].z=	-15.0f;
	
	
	
	lab[167].x= -40.0f;
	
	lab[167].z=	-10.0f;
	
	
	
	lab[167].x= -40.0f;
	
	lab[167].z=	-5.0f;
	
	
	
	lab[168].x= -40.0f;
	
	lab[168].z=	5.0f;
	
	
	
	lab[169].x= -40.0f;
	
	lab[169].z=	35.0f;
	
	
	
	lab[170].x= -40.0f;
	
	lab[170].z=	45.0f;
	
	
	
	lab[171].x= -45.0f;
	
	lab[171].z=	-45.0f;
	
	
	
	lab[172].x= -45.0f;
	
	lab[172].z= -35.0f;
	
	
	
	lab[173].x= -45.0f;
	
	lab[173].z= -25.0f;
	
	
	
	lab[174].x= -45.0f;
	
	lab[174].z= -15.0f;
	
	
	
	lab[175].x= -45.0f;
	
	lab[175].z= -5.0f;
	
	
	
	lab[176].x= -45.0f;
	
	lab[176].z= 5.0f;
	
	
	
	lab[177].x= -45.0f;
	
	lab[177].z= 10.0f;
	
	
	
	lab[178].x= -45.0f;
	
	lab[178].z= 15.0f;
	
	
	
	lab[179].x= -45.0f;
	
	lab[179].z= 20.0f;
	
	
	
	lab[180].x= -45.0f;
	
	lab[180].z= 25.0f;
	
	
	
	lab[181].x= -45.0f;
	
	lab[181].z= 35.0f;
	
	
	
	lab[182].x= -45.0f;
	
	lab[182].z= 45.0f;
	
	
	
	lab[183].x= -50.0f;
	
	lab[183].z= -15.0f;
	
	
	
	lab[184].x= -50.0f;
	
	lab[184].z= 5.0f;
	
	
	
	lab[185].x= -50.0f;
	
	lab[185].z= 45.0f;
	
}

void Calculate_BoundingBox(BoundingBox* box, Block wall, float width, float height, float lenght)	
{
	box->min = (Vector3){wall.x-width/2, wall.y, wall.z-lenght/2};
	box->max = (Vector3){wall.x+width/2, wall.y+height, wall.z+lenght/2};	
}

float width = 5.0f;
float width1 = 5.0f;
float height1 = -2.5f;
Color color1 = BLACK;
Block maze_small[50];
void Draw_MazeSmall(int active_maze_1, Camera * camera)
{
	if (active_maze_1==activado){
		ClearBackground(SKYBLUE);
		teleportation(&*camera,-30.6, 24.9, 127.8f, 2.0f, 121.6f); //vuelta al lobby (encontro salida en el maze_small)
		DrawPlane((Vector3){-30.6f, 0.0f, 24.9f }, (Vector2){ 5.0f, 5.0f }, GREEN); // Draw exit
		DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 55.0f, 55.0f }, LIGHTGRAY); // Draw ground
		DrawCube((Vector3){ 0.0f, 2.5f, 30.0f }, -65.0f, -5.0f, -5.0f, BLACK); 
		DrawCube((Vector3){ 0.0f, 2.5f, -30.0f }, -55.0f, -5.0f, -5.0f, BLACK);
		DrawCube((Vector3){ 30.0f, 2.5f, 0.0f }, -5.0f, -5.0f, -65.0f, BLACK);  
		DrawCube((Vector3){ -30.0f, 2.5f, -5.0f }, -5.0f, -5.0f, -55.0f, BLACK); 
		Assing_Valeu_Small(maze_small);
		for(int i = 0; i < 47; i++)
		{
			DrawCube((Vector3){maze_small[i].x, maze_small[i].y, maze_small[i].z}, width, height1, width1, color1);
		}
	}
}

float width2 = 5.0f;
float width3 = 5.0f;
float height = -2.5f;
Color color = DARKBLUE;
Block maze_medium[90];

void Draw_MazeMedium(int state_mazeMedium, Camera * camera)
{
	if(state_mazeMedium==activado){
		teleportation(&*camera,-40.5,37.8f, 127.8f, 2.0f, 121.6f); // vuelta al lobby (encontro salida en maze_medium)
		DrawPlane((Vector3){ -40.5f, -0.001f, 37.8f}, (Vector2){ 5.0f, 5.0f }, GREEN); // Draw exit
		ClearBackground(RED);
		DrawPlane((Vector3){ 0.0f, -0.001f, 0.0f }, (Vector2){ 75.0f, 75.0f }, LIGHTGRAY); // Draw ground
		DrawCube((Vector3){ 0.0f, 2.5f, 40.0f }, -75.0f, -5.0f, -5.0f, SKYBLUE); 
		DrawCube((Vector3){ 0.0f, 2.5f, -35.0f }, -75.0f, -5.0f, -5.0f, SKYBLUE);
		DrawCube((Vector3){ 40.0f, 2.5f, 0.0f }, -5.0f, -5.0f, -90.0f, SKYBLUE);  
		DrawCube((Vector3){ -40.0f, 2.5f, -5.0f }, -5.0f, -5.0f, -80.0f, SKYBLUE); 
		Assing_Valeu_Medium(maze_medium);
		for(int i=0; i<94; i++)
		{
			DrawCube((Vector3){maze_medium[i].x, maze_medium[i].y, maze_medium[i].z}, width2, height, width3, color);
		}
	}
}

float width4 = 5.0f;
float width5 = 5.0f;
float height2 = 5.5f;
Color color2 = PURPLE;
Block maze_big[200];

void Draw_MazeBig(int state_mazeBig, Camera * camera)	
{
	
	if(state_mazeBig==activado)
		
	{
		DrawPlane((Vector3){ 0.0f, -3.5f, 0.0f }, (Vector2){ 110.0f, 110.0f }, LIGHTGRAY); // Draw ground
		DrawPlane((Vector3){ -57.9f, -2.5f, 50.2f }, (Vector2){ 5.0f, 5.0f }, GREEN); //Draw exit
		DrawCube((Vector3){ 0.0f, 0.1f, 55.1f }, -110.0f, -7.0f, -5.0f, BLUE); 
		DrawCube((Vector3){ 0.0f, 0.1f, -55.1f }, -110.0f, -7.0f, -5.0f, RED);
		DrawCube((Vector3){ 55.1f, 0.1f, 0.0f }, -5.0f, -7.0f, -110.0f, YELLOW);  
		DrawCube((Vector3){ -55.1f, 0.1f, -5.0f }, -5.0f, -7.0f, -105.0f, ORANGE); 
		teleportation(&*camera, -57.9f, 50.2f, 127.8f, 2.0f, 121.6f); //vuelta al lobby (encontro salida en maze_big)
		Assing_Valeu_Big(maze_big);
		
		for(int i = 0; i < 187; i++)
		{
			
			DrawCube((Vector3){maze_big[i].x, maze_big[i].y, maze_big[i].z}, width4, height2, width5, color2);
			
		}
	}
}
void activate_maze(Camera * camera,int * state_mazeSmall, int * state_mazeMedium, int * state_mazebig){
	double actual_x=camera->position.x;
	double actual_z=camera->position.z;
	int closeness=0;
	int closeness2=0;
	int closeness3=0;
	closeness=define_closeness(actual_x,actual_z,123.0f, 100.0f);
	if (closeness == cerca && *state_mazeSmall==desactivado){
		*state_mazeSmall=activado;
		*state_mazeMedium=desactivado;
		*state_mazebig=desactivado;
	}
	closeness2=define_closeness(actual_x,actual_z,131.0f, 100.0f);
	if (closeness2 == cerca && *state_mazeMedium==desactivado){
		*state_mazeSmall=desactivado;
		*state_mazeMedium=activado;
		*state_mazebig=desactivado;
	}
	closeness3=define_closeness(actual_x,actual_z,138.2f, 100.0f);
	if (closeness3 == cerca && *state_mazebig==desactivado){
		*state_mazeSmall=desactivado;
		*state_mazeMedium=desactivado;
		*state_mazebig=activado;
	}
}

void define_teleporters (Camera * camera){
	teleportation(&*camera,123.0f,100.0, 15.1f,3.0f, 0.9f);// teletransportacion a maze_small
	teleportation(&*camera,131.0f,100.0, 15.1f,3.0f, 0.9f);// teletransportacion a maze_medium
	teleportation(&*camera,138.2f,100.0, 15.1f,3.0f, 0.9f); //teletransportador a maze_big
};
	

