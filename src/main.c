#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

static void Render();
static void HandleInputs();
static void UpdatePlayer();

Camera2D camera = { 0 };
Texture knightIdleTexture;
Texture knightRunTexture;
Texture boneWeaponsTexture;

float animationFrameDelay = 0.175f;
float animationTimer;

float weaponSpeed = .13f;
float weaponTimer = 0;
float weaponAngle = 0;
float weaponAngleMax = 120;

int runFrame = 0;
int idleFrame = 0;

Vector2 playerPosition = { 0 };
Vector2 playerVelocity = { 0 };
bool lookingRight = true;

typedef enum {
    PLAYER_STATE_IDLE,
    PLAYER_STATE_WALKING,
} PlayerState;

PlayerState playerState = PLAYER_STATE_IDLE;

float walkingSpeed = 300.f;

Vector2 weaponOffset = { 56, 16 };
float weaponBob = 8;
float weaponBobCurrent = 0;

Vector2 shieldOffset = { -16, 20 };
float shieldBob = 8;
float shieldBobCurrent = 0;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(GetMonitorRefreshRate(0));

    ChangeDirectory("./resources");
    knightIdleTexture = LoadTexture("./knight_idle.png");
    knightRunTexture = LoadTexture("./knight_run.png");
    boneWeaponsTexture = LoadTexture("./bone.png");

    animationTimer = animationFrameDelay;

    camera.target = playerPosition;
    camera.offset = (Vector2){ 400, 225 };
    // camera.rotation = 0.0f;
    camera.zoom = .5f;

    while (!WindowShouldClose()) {
        HandleInputs();
        UpdatePlayer();
        Render();
    }

    CloseWindow();

    return 0;
}

PlayerState previousState = PLAYER_STATE_IDLE;

static void Render() {
    BeginDrawing();

    ClearBackground(1 ? RAYWHITE :(Color){ 20, 23, 28 });

    float time = GetFrameTime();
    animationTimer -= time;

    if (playerState != previousState) {
        idleFrame = -1;
        runFrame = -1;
    }

    if (animationTimer <= 0) {
        animationTimer = playerState == PLAYER_STATE_IDLE ? animationFrameDelay : animationFrameDelay / 2;
        if (playerState == PLAYER_STATE_IDLE) {
            idleFrame++;
            idleFrame %= 4;
        } else if (playerState == PLAYER_STATE_WALKING) {
            runFrame++;
            runFrame %= 6;
        }

        float maxFrames = playerState == PLAYER_STATE_IDLE ? 4 : 6;
        float currentFrame = playerState == PLAYER_STATE_IDLE ? idleFrame : runFrame;

        float progress = (maxFrames - currentFrame) / maxFrames;

        float shieldBobAmplitude = shieldBob * 2.f;
        shieldBobCurrent = sinf(progress * PI) * shieldBobAmplitude / 2.f;

        float weaponBobAmplitude = weaponBob * 2.f;
        weaponBobCurrent = sinf(progress * PI) * weaponBobAmplitude / 2.f;
    }

    if (weaponTimer > 0) {
        weaponTimer -= time;
        float progress = (weaponSpeed - weaponTimer) / weaponSpeed;
        weaponAngle = (progress * progress * progress) * 120;
    } else {
        weaponAngle = 0;
    }

    previousState = playerState;

    BeginMode2D(camera);

    if (playerState == PLAYER_STATE_IDLE) {
        DrawTexturePro(
            knightIdleTexture,
            (Rectangle){ 0 + 32 * idleFrame, 0, lookingRight ? 32 : -32, 32 },
            (Rectangle){ playerPosition.x, playerPosition.y, 128, 128 },
            (Vector2){ 64, 64 },
            0,
            WHITE
        );
    } else if (playerState == PLAYER_STATE_WALKING) {
        DrawTexturePro(
            knightRunTexture,
            (Rectangle){ 0 + 64 * runFrame, 0, lookingRight ? 64 : -64, 64 },
            (Rectangle){ playerPosition.x, playerPosition.y, 256, 256 },
            (Vector2){ 128, 192 },
            0,
            WHITE
        );
    }

    DrawTexturePro(
        boneWeaponsTexture,
        (Rectangle){ 0, 0, !lookingRight ? 16 : -16, 48 },
        (Rectangle){ playerPosition.x + (lookingRight ? weaponOffset.x : -weaponOffset.x), playerPosition.y + weaponOffset.y + weaponBobCurrent, 64, 192 },
        (Vector2) { 28, 160 },
        lookingRight ? weaponAngle : -weaponAngle,
        WHITE
    );

    DrawTexturePro(
        boneWeaponsTexture,
        (Rectangle){ 128, 0, !lookingRight ? 16 : -16, 16 },
        (Rectangle){ playerPosition.x + (lookingRight ? shieldOffset.x : -shieldOffset.x), playerPosition.y + shieldOffset.y + shieldBobCurrent, 64, 64 },
        (Vector2) { 32, 32 },
        0,
        WHITE
    );

    EndMode2D();

    DrawFPS(10, 10);

    EndDrawing();
}

static void HandleInputs() {
    playerVelocity.x = 0;
    playerVelocity.y = 0;

    playerState = PLAYER_STATE_IDLE;

    if (IsKeyDown(KEY_W)) {
        playerState = PLAYER_STATE_WALKING;
        playerVelocity.y = -walkingSpeed;
    } else if (IsKeyDown(KEY_S)) {
        playerState = PLAYER_STATE_WALKING;
        playerVelocity.y = walkingSpeed;
    }

    if (IsKeyDown(KEY_A)) {
        playerState = PLAYER_STATE_WALKING;
        lookingRight = false;
        playerVelocity.x = -walkingSpeed;
    } else if (IsKeyDown(KEY_D)) {
        playerState = PLAYER_STATE_WALKING;
        lookingRight = true;
        playerVelocity.x = walkingSpeed;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (weaponTimer <= 0) {
            weaponTimer = weaponSpeed;
        }
    }

    playerVelocity = Vector2Scale(Vector2Normalize(playerVelocity), walkingSpeed);

    float scrollDelta = GetMouseWheelMove();

    if (scrollDelta != 0) {
        float zoomFactor = (scrollDelta > 0) ? 1.1f : 0.9f; // Scale up or down
        camera.zoom = Clamp(camera.zoom * zoomFactor, 0.05f, 3.f);
    }
}

static void UpdatePlayer() {
    float deltaTime = GetFrameTime();
    playerPosition = Vector2Add(playerPosition, Vector2Scale(playerVelocity, deltaTime));
}
