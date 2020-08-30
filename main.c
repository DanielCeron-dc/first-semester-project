#include <stdio.h> 
#include <time.h> 
#include <string.h>
#include "raylib.h"
#include "funciones.h"
#include "Estructuras.h"
int main(void)
{// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "JUEGO PRUEBA 3D PARA PROYECTO");
	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = { 0 };
	camera.position = (Vector3){ 127.8f, 2.0f, 121.6f }; //que aparezca en el lobby 
	camera.target = (Vector3){ -5.0f, 1.8f, 0.0f };
	camera.up = (Vector3){ 10.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.type = CAMERA_PERSPECTIVE;
	//colocar la ubicacion del archivo
	Texture2D Escudo = LoadTexture("C:/Users/damus/OneDrive/Escritorio/programacion/lenguaje c/Zinjai programs/proyecto - primer semestre/resources/universidad.png");
	Vector3 EscudoPosition = { 120.3, 39.0f, 50.5 };
	SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode
	SetTargetFPS(1000);   // Set our game to run at 60 frames-per-second
	int state_mazeSmall=desactivado;
	int state_mazeMedium=desactivado;
	int state_mazeBig=desactivado;
	//----------------------------------------------------------------------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())  // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		UpdateCamera(&camera);   // Update camera
		GetCameraMatrix(camera);
		//obtener_posicion_mouse();
		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		
		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode3D(camera);
		activate_maze(&camera, &state_mazeSmall, &state_mazeMedium, &state_mazeBig);
		if(state_mazeSmall == desactivado && state_mazeMedium == desactivado && state_mazeBig == desactivado){
			DrawBillboard(camera, Escudo, EscudoPosition, 100.0, WHITE);
		}
		Draw_MazeSmall(state_mazeSmall, &camera);
		Draw_MazeMedium(state_mazeMedium, &camera);
		Draw_MazeBig(state_mazeBig, &camera);
		lobby();
		define_teleporters(&camera);
		EndMode3D();
		dibujar_interfaz();
		dibujar_cooredanadas(&camera);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(Escudo);
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	return 0;
}


