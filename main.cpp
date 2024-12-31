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
    int windowDimensions[2]; 
    windowDimensions[0] = 512; 
    windowDimensions[1] = 380; 

    // initialize window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/sec)/sec 
    const int gravity = 1000;

    // scarfy variables 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData; 
    scarfyData.rec.width = scarfy.width/6; 
    scarfyData.rec.height = scarfy.height; 
    scarfyData.rec.x = 0; 
    scarfyData.rec.y = 0; 
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2; 
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height; 
    scarfyData.frame = 0; 
    scarfyData.updateTime = 1.0/12.0; 
    scarfyData.runningTime = 0.0; 

    // nebula variables 
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); 

    const int sizeOfNebulae = 6;
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++) 
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0; 
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0; 
        nebulae[i].runningTime = 0.0; 
        nebulae[i].updateTime = 1.0/16.0; 
    }

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

        isInAir = (scarfyData.pos.y < windowDimensions[1] - scarfyData.rec.height); 

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

        // jump check 
        if(IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVelocity; 
        }

        for (int i = 0; i < sizeOfNebulae; i++) 
        {
            // update the position of each nebula 
            nebulae[i].pos.x += nebulaVelocity * dT; 
        }

        // update scarfy position 
        scarfyData.pos.y += (velocity * dT); 

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

        for (int i = 0; i < sizeOfNebulae; i++) 
        { 
            nebulae[i].runningTime += dT; 
            if (nebulae[i].runningTime >= nebulae[i].runningTime) 
            {
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width; 
                nebulae[i].frame++; 
                if(nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
                nebulae[i].runningTime = 0.0; 
            }
        }

        for (int i = 0; i < sizeOfNebulae; i++) 
        {
            // draw nebula
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE); 
        
        // stop drawing 
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}