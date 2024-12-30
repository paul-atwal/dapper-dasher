#include "raylib.h"

int main() {

    // window dimensions 
    const int windowWidth = 512;
    const int windowHeight = 380;

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // acceleration due to gravity (pixels/sec)/sec 
    const int gravity = 1000;

    // scarfy variables 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRectangle = {0.0f, 0.0f, static_cast<float>(scarfy.width)/6.0f, static_cast<float>(scarfy.height)};
    Vector2 scarfyPosition = 
    {
        windowWidth/2 - scarfyRectangle.width/2, 
        windowHeight - scarfyRectangle.height
    };

    // nebula variables 
    Texture2D nebula = LoadTexture("texture/12_nebula_spritesheet.png"); 
    Rectangle nebulaRectangle = { 0.0f, 0.0f, static_cast<float>(nebula.width)/8.0f, static_cast<float>(nebula.height)/8.0f };
    Vector2 nebulaPosition{windowWidth, windowHeight - nebulaRectangle.height}; 

    // nebula x velocity (pixels/second)
    int nebulaVelocity = -600; 

    // animation frame
    int frame = 0; 
    const float updateTime = 1.0/12.0; 
    float runningTime = 0; 

    // is rectangle in air 
    bool isInAir = false;
    // jump velocity (pixels/second)
    const int jumpVelocity = -600; 

    int velocity = 0; 

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        
        // start drawing 
        BeginDrawing();
        ClearBackground(WHITE);

        isInAir = (scarfyPosition.y < windowHeight - scarfyRectangle.height); 

        // delta time (time since last frame)
        const float dT = GetFrameTime();

        // perform ground check
        if (!isInAir) {
            // rectangle is on the ground 
            velocity = 0;
        } else {
            // rectangle is in the air 
            velocity += (gravity * dT); 
        }

        if(IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVelocity; 
        }

        // update scarfy position 
        scarfyPosition.y += (velocity * dT); 

        // update nebula position 
        nebulaPosition.x += nebulaVelocity * dT; 

        // update running time 
        runningTime += dT; 

        if (runningTime >= updateTime && !isInAir)
        {
            // update animation frame
            scarfyRectangle.x = frame * scarfyRectangle.width; 
            frame++; 
            if(frame > 5)
            {
                frame = 0;
            }
            runningTime = 0.0; 
        }
        
        // draw nebula 
        DrawTextureRec(nebula, nebulaRectangle, nebulaPosition, WHITE); 

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRectangle, scarfyPosition, WHITE); 
        
        // stop drawing 
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}