#include <raylib.h>

int main(){

	const int screenW = 800;
	const int screenH = 450;

	InitWindow(screenW, screenH, "GOTY");
	SetTargetFPS(60);

	RenderTexture2D target = LoadRenderTexture(screenW, screenH);
	Rectangle recSource = {0, 0, (float)target.texture.width, (float)-target.texture.height};

	Texture2D schar = LoadTexture("Sprites/ScharWalk.png");
	Vector2 scharPos = {screenW/3.0f, screenH/2.0f};
	Rectangle scharAnim{ 0 , 0, (float)schar.width/4, (float)schar.height};
	int scharSpeed = 2;
	bool scharWalking = false;
	
	int currentFrame = 0;
	int frameCounter = 0;
	int frameSpeed = 5;

	while(!WindowShouldClose()){

		frameCounter++;

		if(IsKeyPressed(KEY_F)) ToggleFullscreen();

		if(IsKeyDown(KEY_A) && frameCounter >= 60/frameSpeed ){ 
			
			scharWalking = true;
			scharPos.x -= scharSpeed;

  			frameCounter = 0;
			currentFrame++;

			if(currentFrame > 3) currentFrame = 0;

			scharAnim.x = (float)currentFrame*(float)schar.width/4; 


		}
		
		if(IsKeyDown(KEY_D) && frameCounter >= 60/frameSpeed ){ 
			
			scharWalking = true;
			scharPos.x += scharSpeed;

  			frameCounter = 0;
			currentFrame++;

			if(currentFrame > 3) currentFrame = 0;

			scharAnim.x = (float)currentFrame*(float)schar.width/4; 


		}
		
	
		BeginTextureMode(target);
		ClearBackground(WHITE);

			DrawTextureRec(schar, scharAnim, scharPos, WHITE);

		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);

			DrawTextureRec(target.texture, recSource, (Vector2){0, 0}, WHITE);

		EndDrawing();

	}

	UnloadRenderTexture(target);
	CloseWindow();

return 0;
}
