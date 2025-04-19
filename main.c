#include "include/raylib.h"
#include "include/raymath.h"
#define VERSION "development"

typedef struct particle_s {
    float radius;
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
} Particle;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const float JUMP_ACCEL = 1200000.0f;
const float MOV_ACCEL = 1500.0f;
const float GRAV_ACCEL = 9800.0f;
const float FRIC = 4.0f;
const float RADIUS = 6.0f;
const float SQUISH = 0.8f;

const float LEFT = RADIUS;
const float RIGHT = SCREEN_WIDTH - RADIUS;
const float TOP = RADIUS;
const float BOTTOM = SCREEN_HEIGHT - RADIUS;
const Vector2 SCREEN_ZERO = (Vector2) {RADIUS, RADIUS};
const Vector2 SCREEN_MIDTOP = (Vector2) {SCREEN_WIDTH / 2.0f, RADIUS};

void ball_physics(Particle *p, float dt) {
    /* bounce off walls */
    if (p->pos.x < LEFT) { p->pos.x = LEFT; p->vel.x *= -SQUISH; }
    if (p->pos.x > RIGHT) { p->pos.x = RIGHT; p->vel.x *= -SQUISH; }
    if (p->pos.y < TOP) { p->pos.y = TOP; p->vel.y *= -SQUISH; }
    if (p->pos.y > BOTTOM) { p->pos.y = BOTTOM; p->vel.y *= -SQUISH; }

    /* bounce off other balls */
    

    /* if the velocity is very low, set it to zero */
    /* apply friction to acceleration */
    if (Vector2LengthSqr(p->vel) < 0.1f) {
        p->vel = Vector2Zero();
    }
    else {
        Vector2 friction = Vector2Scale(p->vel, -FRIC);
        p->acc = Vector2Add(p->acc, friction);
    }

    /* integrate acc to get vel, and pos */
    p->vel = Vector2Add(p->vel, Vector2Scale(p->acc, dt));
    p->pos = Vector2Add(p->pos, Vector2Scale(p->vel, dt));
}

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "[LIQUID]");
    SetTargetFPS(240);
    

    Particle p = {RADIUS, SCREEN_MIDTOP, Vector2Zero(), Vector2Zero()};
    while(!WindowShouldClose()) {

        float dt = GetFrameTime();
        p.acc.y = GRAV_ACCEL;

        ball_physics(&p, dt);
       
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText(TextFormat("FPS: %d", GetFPS()), 10, 70, 20, LIGHTGRAY);
            DrawCircleV(p.pos, RADIUS, BLACK);
            
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
