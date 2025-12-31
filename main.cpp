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
	int jumpSpeed = 0;	

	bool scharWalking = false;
	bool scharCanJump = false;
	bool punch = false;

	int currentFrame = 0;
	int frameCounter = 0;
	int punchCounter = 0;
	int frameSpeed = 5;

	while(!WindowShouldClose()){

		float delta = GetFrameTime();

		frameCounter++;
		punchCounter++;
		scharPos.y += jumpSpeed;
		
		Rectangle punchCol = {(scharPos.x + ((float)scharAnim.width/2)), (scharPos.y + ((float)scharAnim.height/1.5f)), 50, 15};

		if(IsKeyPressed(KEY_F)){
		
			punch = true;
			punchCounter = 0;

		}else if(punchCounter >= 20) punch = false;

		if(IsKeyPressed(KEY_P)) ToggleFullscreen();

		if(IsKeyDown(KEY_A)){

			scharWalking = true;
			scharAnim.width = (float)-schar.width/4;
			punchCol.x = -(scharPos.x + ((float)scharAnim.width/2));
			scharPos.x -= scharSpeed;

  		}else if(IsKeyDown(KEY_D)){

			scharWalking = true;
			scharAnim.width = (float)schar.width/4;
			scharPos.x += scharSpeed;

		}else{
			
			scharWalking = false;
			currentFrame = 0;
			scharAnim.x = 0;

		}

		if(IsKeyDown(KEY_SPACE) && scharCanJump){
		
			jumpSpeed = -250*delta;
			scharPos.y += jumpSpeed;

		}else{

			jumpSpeed = 300*delta;
			scharCanJump = false;


		}

		if(scharPos.y >= (float)screenH/2){
	
			scharCanJump = true;
			jumpSpeed = 0;

		}else if(scharPos.y <= 100) scharCanJump = false;
	
		if(frameCounter >= 60/frameSpeed && scharWalking){

  			frameCounter = 0;
			currentFrame++;

			if(currentFrame > 3) currentFrame = 0;

			scharAnim.x = (float)currentFrame*(float)schar.width/4; 

		}	
				
		BeginTextureMode(target);
		ClearBackground(WHITE);

			DrawTextureRec(schar, scharAnim, scharPos, WHITE);

			if(punch) DrawRectangleRec(punchCol, RED);

		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);

			DrawTextureRec(target.texture, recSource, (Vector2){0, 0}, WHITE);	
			DrawText(TextFormat("%d", frameCounter), 20, 20, 20, BLACK);
		EndDrawing();

	}
		
	UnloadRenderTexture(target);
	CloseWindow();

return 0;
}
