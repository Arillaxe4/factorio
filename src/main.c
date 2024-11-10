#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include "globals.h"
#include "player.h"
#include "level.h"
#include "item.h"
#include "inventory.h"

Camera2D camera = {0};

Texture knightIdleTexture;
Texture knightRunTexture;
Texture levelTexture;
Texture itemsTexture;
Texture panelTexture;
Texture slotTexture;

Player player;
Level level;
Item *items;

int main()
{
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib");

  SetTargetFPS(GetMonitorRefreshRate(0));

  ChangeDirectory("./resources");
  knightIdleTexture = LoadTexture("./knight_idle.png");
  knightRunTexture = LoadTexture("./knight_run.png");
  levelTexture = LoadTexture("./dungeon_tiles.png");
  itemsTexture = LoadTexture("./roguelikeitems.png");
  panelTexture = LoadTexture("./panel.png");
  slotTexture = LoadTexture("./slot.png");

  Sprite playerIdleSprite = createSprite(
      &knightIdleTexture,
      (Rectangle){0, 0, 32, 32},
      64, 64,
      (Vector2){32, 32});

  Sprite playerRunSprite = createSprite(
      &knightRunTexture,
      (Rectangle){0, 0, 64, 64},
      128, 128,
      (Vector2){64, 96});

  Sprite itemSprite = createSprite(
      &itemsTexture,
      (Rectangle){0 + 16 * 5, 0 + 16 * 6, 16, 16},
      32, 32,
      (Vector2){2, 30});

  Swingable pickaxeSwingable = createSwingable(0.175f);

  Item pickaxe = createItem(
      itemSprite,
      "Pickaxe",
      ITEM_TYPE_SWINGABLE,
      300, 200,
      (ItemDetails){.swingable = pickaxeSwingable});

  setSpriteAnimation(&playerIdleSprite, 4, 0.175f);
  setSpriteAnimation(&playerRunSprite, 6, 0.1f);

  player = createPlayer((Sprite[]){playerIdleSprite, playerRunSprite}, (Vector2){400, 225}, 40, 20);

  camera.target = (Vector2){player.position.x, player.position.y};
  camera.offset = (Vector2){400, 225};
  camera.rotation = 0.0f;
  camera.zoom = .5f;

  level = createDefaultLevel(&levelTexture);

  addItemToLevel(&level, &pickaxe);
  // addItem(&player, &pickaxe);
  // setActiveItem(&player, 0);

  Inventory inventory = createInventory(&panelTexture, &slotTexture);

  while (!WindowShouldClose())
  {
    handleInventoryInput(&inventory);
    updateLevel(&level);
    updatePlayer(&player, &level);

    BeginDrawing();
    ClearBackground(0 ? RAYWHITE : (Color){20, 23, 28});
    BeginMode2D(camera);

    drawLevel(&level);

    drawPlayer(&player);

    drawItem(&pickaxe);

    EndMode2D();

    drawInventory(&inventory, player.items);

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
