#include "raylib.h"

int main(void)
{
  // configuração da tela
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Jogo ainda sem nome");

  // Player
  Vector2 playerPos = {400, 255};
  float speed = 200.0f;
  float playerRadius = 20.0f;

  // Camera Top-Down
  Camera2D camera = {0};
  camera.target = playerPos;
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  // Textura do chão
  Texture2D grass = LoadTexture("grass.jpg");
  int mapWidth = 1600;
  int mapHeight = 900;

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();

    // movimento
    if (IsKeyDown(KEY_W))
      playerPos.y -= speed * dt;
    if (IsKeyDown(KEY_S))
      playerPos.y += speed * dt;
    if (IsKeyDown(KEY_A))
      playerPos.x -= speed * dt;
    if (IsKeyDown(KEY_D))
      playerPos.x += speed * dt;

    // limites da tela
    if (playerPos.x < playerRadius)
      playerPos.x = playerRadius;
    if (playerPos.x > screenWidth - playerRadius)
      playerPos.x = screenWidth - playerRadius;
    if (playerPos.y < playerRadius)
      playerPos.y = playerRadius;
    if (playerPos.y > screenHeight - playerRadius)
      playerPos.y = screenHeight - playerRadius;

    // Atualiza a camera para seguir o jogador
    camera.target = playerPos;

    // desenho
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // tudo será afetado pela camera
    BeginMode2D(camera);
    for (int y = 0; y < mapHeight; y += grass.height)
    {
      for (int x = 0; x < mapWidth; x += grass.width)
      {
        DrawTexture(grass, x, y, WHITE);
      }
    }
    // Player
    DrawCircleV(playerPos, playerRadius, BLUE); // jogador
    // Aqui ficará o mapa, paredes, objetos
    EndMode2D();

    // UI fixa
    DrawText("WASD para mover", 10, 10, 20, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}