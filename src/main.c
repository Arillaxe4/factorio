#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include "globals.h"
#include "player.h"

Camera2D camera = {0};

static void Render();

Texture knightIdleTexture;
Texture knightRunTexture;
Texture boneWeaponsTexture;

Player player;

int main()
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib");

  SetTargetFPS(GetMonitorRefreshRate(0));

  ChangeDirectory("./resources");
  knightIdleTexture = LoadTexture("./knight_idle.png");
  knightRunTexture = LoadTexture("./knight_run.png");
  boneWeaponsTexture = LoadTexture("./bone.png");

  Sprite playerSprite = createSprite(
      &knightIdleTexture,
      (Rectangle){0, 0, 32, 32},
      64,
      64);

  setSpriteAnimation(&playerSprite, 4, 0.175f);

  player = createPlayer(playerSprite, (Vector2){400, 225});

  camera.target = player.position;
  camera.offset = (Vector2){400, 225};
  camera.rotation = 0.0f;
  camera.zoom = .5f;

  while (!WindowShouldClose())
  {
    updatePlayer(&player);

    Render();
  }

  CloseWindow();

  return 0;
}

static void Render()
{
  BeginDrawing();
  ClearBackground(1 ? RAYWHITE : (Color){20, 23, 28});
  BeginMode2D(camera);

  drawPlayer(&player);

  EndMode2D();
  DrawFPS(10, 10);
  EndDrawing();
}
