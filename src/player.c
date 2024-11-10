#include "player.h"
#include "globals.h"
#include "raymath.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

Player createPlayer(Sprite *sprites, Vector2 position, float w, float h)
{
	Player player;
	memset(&player, 0, sizeof(Player));

	player.sprites = sprites;
	player.sprite = &sprites[0];
	player.position = position;
	player.velocity = (Vector2){0, 0};
	player.isLookingRight = true;
	player.collider = (Rectangle){-20, 12, w, h};
	player.itemsCount = 0;
	player.maxItems = 20;
	player.items = malloc(player.maxItems * sizeof(Item *));
	memset(player.items, 0, player.maxItems * sizeof(Item *));
	player.activeItem = 0;

	return player;
}

bool checkAABBCollision(Rectangle a, Rectangle b)
{
	return (a.x < b.x + b.width &&
					a.x + a.width > b.x &&
					a.y < b.y + b.height &&
					a.y + a.height > b.y);
}

void updatePlayer(Player *player, Level *level)
{
	handlePlayerInputs(player);

	float deltaTime = GetFrameTime();
	Vector2 nextPosition = Vector2Add(player->position, Vector2Scale(player->velocity, deltaTime));
	bool didCollide = false;

	for (int i = 0; i < LEVEL_TILE_WIDTH; i++)
	{
		for (int j = 0; j < LEVEL_TILE_HEIGHT; j++)
		{
			if (level->tiles[i][j].type == TILE_WALL && checkAABBCollision((Rectangle){nextPosition.x + player->collider.x, nextPosition.y + player->collider.y, player->collider.width, player->collider.height}, (Rectangle){level->tiles[i][j].position.x, level->tiles[i][j].position.y, level->tiles[i][j].sprite.dstRect.width, level->tiles[i][j].sprite.dstRect.height}))
			{
				didCollide = true;
				break;
			}
		}

		if (didCollide)
		{
			break;
		}
	}

	if (!didCollide)
	{
		player->position = nextPosition;
	}

	for (int i = 0; i < level->itemsCount; i++)
	{
		if (!level->items[i]->isPickedUp)
		{
			if (CheckCollisionRecs(
							(Rectangle){level->items[i]->sprite.dstRect.x - level->items[i]->sprite.origin.x, level->items[i]->sprite.dstRect.y - level->items[i]->sprite.origin.y, level->items[i]->sprite.dstRect.width, level->items[i]->sprite.dstRect.height},
							(Rectangle){nextPosition.x + player->collider.x, nextPosition.y + player->collider.y, player->collider.width, player->collider.height}))
			{
				addItemToPlayer(player, level->items[i]);
				setActiveItem(player, 0);
			}
		}
	}

	if (player->activeItem != 0)
	{
		player->activeItem->x = player->position.x + (player->isLookingRight ? 15 : -15);
		player->activeItem->y = player->position.y + 15;
		float width = abs(player->activeItem->sprite.srcRect.width);
		player->activeItem->sprite.srcRect.width = player->isLookingRight ? width : -width;

		if (player->activeItem->type == ITEM_TYPE_SWINGABLE)
		{
			float absAngle = abs(player->activeItem->details.swingable.animationAngle);
			player->activeItem->sprite.angle = player->isLookingRight ? absAngle : -absAngle;
		}

		if (player->isLookingRight)
		{
			player->activeItem->sprite.origin.x = 2;
			player->activeItem->sprite.origin.y = 30;
		}
		else
		{
			player->activeItem->sprite.origin.x = 30;
			player->activeItem->sprite.origin.y = 30;
		}
	}

	player->sprite = &player->sprites[player->state];
	player->sprite->dstRect.x = player->position.x;
	player->sprite->dstRect.y = player->position.y;
	float width = abs(player->sprite->srcRect.width);
	player->sprite->srcRect.width = player->isLookingRight ? width : -width;
	updateSprite(player->sprite);
}

void handlePlayerInputs(Player *player)
{
	player->velocity.x = 0;
	player->velocity.y = 0;

	player->state = PLAYER_STATE_IDLE;

	if (IsKeyDown(KEY_W))
	{
		player->state = PLAYER_STATE_WALKING;
		player->velocity.y = -WALKING_SPEED;
	}
	else if (IsKeyDown(KEY_S))
	{
		player->state = PLAYER_STATE_WALKING;
		player->velocity.y = WALKING_SPEED;
	}

	if (IsKeyDown(KEY_A))
	{
		player->state = PLAYER_STATE_WALKING;
		player->isLookingRight = false;
		player->velocity.x = -WALKING_SPEED;
	}
	else if (IsKeyDown(KEY_D))
	{
		player->state = PLAYER_STATE_WALKING;
		player->isLookingRight = true;
		player->velocity.x = WALKING_SPEED;
	}

	player->velocity = Vector2Scale(Vector2Normalize(player->velocity), WALKING_SPEED);

	float scrollDelta = GetMouseWheelMove();

	if (scrollDelta != 0)
	{
		float zoomFactor = (scrollDelta > 0) ? 1.1f : 0.9f;
		camera.zoom = Clamp(camera.zoom * zoomFactor, 0.05f, 3.f);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if (player->activeItem->type == ITEM_TYPE_SWINGABLE)
		{
			swingSwingable(&player->activeItem->details.swingable);
		}
	}
}

void drawPlayer(Player *player)
{
	drawSprite(player->sprite);
	// DrawRectangleLinesEx((Rectangle){player->position.x + player->collider.x, player->position.y + player->collider.y, player->collider.width, player->collider.height}, 3, RED);
}

void addItemToPlayer(Player *player, Item *item)
{
	if (player->itemsCount < player->maxItems)
	{
		player->items[player->itemsCount++] = item;
		item->isDrawn = false;
		item->isPickedUp = true;
	}
}

void setActiveItem(Player *player, int slotId)
{
	if (player->items[slotId] != 0)
	{
		if (player->activeItem != 0)
		{
			player->activeItem->isDrawn = false;
		}
		player->activeItem = player->items[slotId];
		player->activeItem->isDrawn = true;
	}
}
