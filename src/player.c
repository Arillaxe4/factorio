#include "player.h"
#include "globals.h"
#include "raymath.h"

Player createPlayer(Sprite sprite, Vector2 position)
{
	Player player;

	player.sprite = sprite;
	player.position = position;
	player.velocity = (Vector2){0, 0};

	return player;
}

void updatePlayer(Player *player)
{
	handlePlayerInputs(player);

	float deltaTime = GetFrameTime();
	player->position = Vector2Add(player->position, Vector2Scale(player->velocity, deltaTime));
	updateSprite(&player->sprite);
	player->sprite.dstRect.x = player->position.x;
	player->sprite.dstRect.y = player->position.y;
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
		float zoomFactor = (scrollDelta > 0) ? 1.1f : 0.9f; // Scale up or down
		camera.zoom = Clamp(camera.zoom * zoomFactor, 0.05f, 3.f);
	}
}

void drawPlayer(Player *player)
{
	drawSprite(&player->sprite);
}
