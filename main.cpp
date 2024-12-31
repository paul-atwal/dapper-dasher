#include "raylib.h"

struct AnimData
{
    Rectangle rec; 
    Vector2 pos; 
    int frame;
    float updateTime; 
    float runningTime; 
};

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
    AnimData scarfyData; 
    scarfyData.rec.width = scarfy.width/6; 
    scarfyData.rec.height = scarfy.height; 
    scarfyData.rec.x = 0; 
    scarfyData.rec.y = 0; 
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2; 
    scarfyData.pos.y = windowHeight - scarfyData.rec.height; 
    scarfyData.frame = 0; 
    scarfyData.updateTime = 1.0/12.0; 
    scarfyData.runningTime = 0.0; 

    // nebula variables 
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); 

    // AnimData for nebula 
    AnimData nebData
    {
        {0.0f, 0.0f, static_cast<float>(nebula.width)/8.0f, static_cast<float>(nebula.height)/8.0f}, // Rectangle
        {static_cast<float>(windowWidth), static_cast<float>(windowHeight) - nebula.height/8}, // Vector2
        0, // frame 
        1.0/12.0, // updateTime 
        0.0 // runningTime 
    };

    AnimData neb2Data 
    {
        {0.0f, 0.0f, static_cast<float>(nebula.width)/8.0f, static_cast<float>(nebula.height)/8.0f}, 
        {static_cast<float>(windowWidth + 300), static_cast<float>(windowHeight) - nebula.height/8},
        0,
        1.0/16.0,
        0.0
    };

    // nebula x velocity (pixels/second)
    int nebulaVelocity = -200; 

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

        isInAir = (scarfyData.pos.y < windowHeight - scarfyData.rec.height); 

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
        scarfyData.pos.y += (velocity * dT); 

        // update nebula position 
        nebData.pos.x += nebulaVelocity * dT; 

        // update second nebula's position
        neb2Data.pos.x += nebulaVelocity * dT; 

        // update running time 
        scarfyData.runningTime += dT; 

        if (scarfyData.runningTime >= scarfyData.updateTime && !isInAir)
        {
            // update animation frame
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width; 
            scarfyData.frame++; 
            if(scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }
            scarfyData.runningTime = 0.0; 
        }

        // update nebula animation time 
        nebData.runningTime += dT; 
        if (nebData.runningTime >= nebData.runningTime) 
        {
            nebData.rec.x = nebData.frame * nebData.rec.width; 
            nebData.frame++; 
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }
            nebData.runningTime = 0.0; 
        }

        // update second nebula animation time 
        neb2Data.runningTime += dT; 
        if (neb2Data.runningTime >= neb2Data.runningTime) 
        {
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width; 
            neb2Data.frame++; 
            if(neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
            neb2Data.runningTime = 0.0; 
        }

        // draw nebula 
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE); 

        // draw nebula 
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE); 

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE); 
        
        // stop drawing 
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}