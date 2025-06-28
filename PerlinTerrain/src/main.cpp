#include "raylib.h"
#include <vector>
#include "../include/PerlinNoise.h"
#include "imgui.h"
#include "rlImgui.h"
#include <iostream>

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "3D Terrain with Noise");

    //ToggleBorderlessWindowed();

    const int cellsize = 12;
    const int cols = screenWidth / cellsize;
    const int rows = screenHeight / cellsize;

    float frequency = 0.11;
    int octaves = 4;

    int minAmplitude = 60;
    int maxAmplitude = 160;
    int amplitude = GetRandomValue(minAmplitude, maxAmplitude);

    float scrollSpeedX = 0.0;
    float scrollSpeedY = -2;

    // Perlin noise
    const siv::PerlinNoise::seed_type seed = 123456u;
    const siv::PerlinNoise perlin{ seed };

    // Generate height array
    std::vector<std::vector<float>> heightMap(rows, std::vector<float>(cols));

    // Setup 3D camera
    Camera3D camera = { 0 };
    camera.position = Vector3{ 400.0f, 300.0f, 600.0f };
    camera.target = Vector3{ 400.0f, 0.0f, 200.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    rlImGuiSetup(true);

    while (!WindowShouldClose())
    {
        float deltaTime = GetTime();
        double offsetx = deltaTime * scrollSpeedX;
        double offsetY = deltaTime * scrollSpeedY;

        // generate heightmap
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                double nx = (x * frequency) + offsetx;
                double ny = (y * frequency) + offsetY;
                float noise = static_cast<float>(perlin.octave2D_01(nx, ny, octaves));
                heightMap[y][x] = noise * amplitude;
            }
        }

        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(BLACK);

        rlImGuiBegin();

        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(320, 120), ImGuiCond_Once);

        ImGui::Begin("Terrain Controls", NULL);

        ImGui::Text("Noise Settings");
        ImGui::Separator();

        ImGui::SliderFloat("Frequency", &frequency, 0.01f, 0.2f);
        ImGui::SliderInt("Octaves", &octaves, 1, 8);

        ImGui::End();

        rlImGuiEnd();

        BeginMode3D(camera);

        // Draw the terrain wireframe using noise-based height
        for (int y = 0; y < rows - 1; ++y)
        {
            for (int x = 0; x < cols - 1; ++x)
            {
                Vector3 xLeft = { x * cellsize,     heightMap[y][x],     y * cellsize };
                Vector3 xRight = { (x + 1) * cellsize,   heightMap[y][x + 1],   y * cellsize };
                Vector3 yTop = { x * cellsize,     heightMap[y + 1][x],   (y + 1) * cellsize };
                Vector3 yBottom = { (x + 1) * cellsize,   heightMap[y + 1][x + 1], (y + 1) * cellsize };

                DrawLine3D(xLeft, xRight, GREEN);
                DrawLine3D(xRight, yBottom, GREEN);
                DrawLine3D(yBottom, yTop, GREEN);
                DrawLine3D(yTop, xLeft, GREEN);

            }
        }

        EndMode3D();

         DrawText("Terrain Generation with Perlin Noise", 400, 10, 20, RAYWHITE);
        // DrawFPS(10, 10);

        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();

    CloseWindow();
    return 0;
}
