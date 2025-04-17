#include <stdio.h>
#include "include/raylib.h"
#include "include/raymath.h"
#define VERSION "development"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "boids");
    SetTargetFPS(60);

    Vector2 ballPosition = { (float) screenWidth / 2, (float) screenHeight / 2 };
    Vector2 previousBallPosition = {};

    while(!WindowShouldClose()) {

        previousBallPosition = ballPosition;
        if (IsKeyDown(KEY_D)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_A)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_W)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_S)) ballPosition.y += 2.0f;

        float velocity = Vector2Distance(previousBallPosition, ballPosition) / GetFrameTime();

        BeginDrawing();
            ClearBackground(WHITE);
            DrawText(TextFormat("Velocity: %.4f", velocity), 200, 200, 20, BLACK);
            DrawCircleV(ballPosition, 50, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
