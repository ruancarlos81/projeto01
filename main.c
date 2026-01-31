#include "raylib.h"

int main(void)
{
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Jogo 3D com Plataformas");

  // Player
  Vector3 playerPos = {0.0f, 0.5f, 0.0f};
  float speed = 5.0f;
  float playerRadius = 0.5f;

  // Física do pulo
  float velocityY = 0.0f;
  float gravity = 20.0f;
  float jumpForce = 8.0f;
  bool isGrounded = true;

  // Camera 3D
  Camera3D camera = {0};
  camera.position = (Vector3){0.0f, 10.0f, 10.0f};
  camera.target = playerPos;
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // Plataformas
  Vector3 platformsPos[] = {
      {3.0f, 1.0f, 2.0f},
      {-4.0f, 2.0f, -3.0f},
      {6.0f, 3.0f, 0.0f}};

  Vector3 platformsSize[] = {
      {3.0f, 1.0f, 3.0f},
      {3.0f, 1.0f, 3.0f},
      {3.0f, 1.0f, 3.0f}};

  int platformCount = 3;

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();
    isGrounded = false;

    // Movimento XZ
    if (IsKeyDown(KEY_W))
      playerPos.z -= speed * dt;
    if (IsKeyDown(KEY_S))
      playerPos.z += speed * dt;
    if (IsKeyDown(KEY_A))
      playerPos.x -= speed * dt;
    if (IsKeyDown(KEY_D))
      playerPos.x += speed * dt;

    // Pulo
    if (IsKeyPressed(KEY_SPACE) && isGrounded)
    {
      velocityY = jumpForce;
    }

    // Gravidade
    velocityY -= gravity * dt;
    playerPos.y += velocityY * dt;

    // Colisão com o chão
    if (playerPos.y <= playerRadius)
    {
      playerPos.y = playerRadius;
      velocityY = 0.0f;
      isGrounded = true;
    }

    // BoundingBox do player
    BoundingBox playerBox = {
        (Vector3){playerPos.x - playerRadius, playerPos.y - playerRadius, playerPos.z - playerRadius},
        (Vector3){playerPos.x + playerRadius, playerPos.y + playerRadius, playerPos.z + playerRadius}};

    // Colisão com plataformas
    for (int i = 0; i < platformCount; i++)
    {
      BoundingBox platformBox = {
          (Vector3){
              platformsPos[i].x - platformsSize[i].x / 2,
              platformsPos[i].y,
              platformsPos[i].z - platformsSize[i].z / 2},
          (Vector3){
              platformsPos[i].x + platformsSize[i].x / 2,
              platformsPos[i].y + platformsSize[i].y,
              platformsPos[i].z + platformsSize[i].z / 2}};

      if (CheckCollisionBoxes(playerBox, platformBox) && velocityY <= 0.0f)
      {
        // Colisão vinda de cima
        playerPos.y = platformBox.max.y + playerRadius;
        velocityY = 0.0f;
        isGrounded = true;
      }
    }

    // Câmera segue o jogador
    camera.target = playerPos;
    camera.position.x = playerPos.x;
    camera.position.z = playerPos.z + 10.0f;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    // Chão
    DrawPlane(
        (Vector3){0.0f, 0.0f, 0.0f},
        (Vector2){50.0f, 50.0f},
        GREEN);

    // Plataformas
    for (int i = 0; i < platformCount; i++)
    {
      DrawCube(platformsPos[i], platformsSize[i].x, platformsSize[i].y, platformsSize[i].z, GRAY);
      DrawCubeWires(platformsPos[i], platformsSize[i].x, platformsSize[i].y, platformsSize[i].z, DARKGRAY);
    }

    // Player
    DrawSphere(playerPos, playerRadius, BLUE);

    DrawGrid(50, 1.0f);
    EndMode3D();

    DrawText("Jogo ainda Sem Nome", 10, 10, 20, DARKGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
