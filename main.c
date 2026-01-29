#include "raylib.h"

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Jogo ainda sem nome");

  Vector2 playerPos = {400, 255};
  float speed = 200.0f;

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_W))
      playerPos.y -= speed * dt;
    if (IsKeyDown(KEY_S))
      playerPos.y += speed * dt;
    if (IsKeyDown(KEY_A))
      playerPos.x -= speed * dt;
    if (IsKeyDown(KEY_D))
      playerPos.x += speed * dt;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircleV(playerPos, 20, BLUE);
    DrawText("WASD para mover", 10, 10, 20, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}