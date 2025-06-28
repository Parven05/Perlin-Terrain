![Status](https://badgen.net/badge/Status/Experiment/orange?icon=github)
![Engine](https://badgen.net/badge/Engine/Raylib/blue)
![License](https://badgen.net/badge/license/MIT/green)

## **Terrain Generation using Perlin Noise**
![Perlin](https://github.com/user-attachments/assets/14231ded-5d8f-4e77-bd1f-d7eebe26b511)

A simple experiment using Perlin noise to generate and visualize terrain in Raylib. It maps noise values into smooth, natural heightmaps for exploring procedural generation and rendering.

Features:

- Perlin noise-based heightmap generation
- Real-time visualization with Raylib
- Adjustable octaves and frequency for noise control

## **Implementation**

https://github.com/Reputeless/PerlinNoise

**siv::PerlinNoise** is a header-only Perlin noise library for modern C++ (C++17/20), based on Ken Perlin's Improved Noise. It supports 1D, 2D, and 3D noise generation with octave support and deterministic output across platforms (except for floating point variations). It is distributed under the MIT license.

- Frequency: Controls the scale of the noise pattern. Higher frequency means more rapid changes and finer details in the noise. Lower frequency results in smoother, larger features.
- Octaves: Refers to layering multiple noise functions of increasing frequency and decreasing amplitude to create more complex and natural-looking noise. More octaves add detail and variation, but increase computation.

```c++
// --- Generate Heightmap using Perlin Noise ---
for (int y = 0; y < rows; ++y)
{
    for (int x = 0; x < cols; ++x)
    {
        // Calculate noise coordinates with frequency and offset for animation
        double nx = (x * frequency) + offsetx;
        double ny = (y * frequency) + offsetY;

        // Get Perlin noise value (0 to 1) with multiple octaves
        float noise = static_cast<float>(perlin.octave2D_01(nx, ny, octaves));

        // Scale noise by amplitude and store as height
        heightMap[y][x] = noise * amplitude;
    }
}
```
Below code draws the terrain as a 3D wireframe by connecting each grid cell’s four corner points. The corners use height values from the heightmap, and lines are drawn between them to form the mesh, visualizing the terrain shape.

```c++
// --- Draw Terrain Wireframe based on Heightmap ---
for (int y = 0; y < rows - 1; ++y)
{
    for (int x = 0; x < cols - 1; ++x)
    {
        // Define four corner points of the current grid cell
        Vector3 topLeft     = { x * cellsize,         heightMap[y][x],       y * cellsize };
        Vector3 topRight    = { (x + 1) * cellsize,   heightMap[y][x + 1],   y * cellsize };
        Vector3 bottomLeft  = { x * cellsize,         heightMap[y + 1][x],   (y + 1) * cellsize };
        Vector3 bottomRight = { (x + 1) * cellsize,   heightMap[y + 1][x + 1], (y + 1) * cellsize };

        // Draw lines between points to form a wireframe grid cell
        DrawLine3D(topLeft, topRight, GREEN);
        DrawLine3D(topRight, bottomRight, GREEN);
        DrawLine3D(bottomRight, bottomLeft, GREEN);
        DrawLine3D(bottomLeft, topLeft, GREEN);
    }
}
```

## **References**
[Perlin noise](https://en.wikipedia.org/wiki/Perlin_noise)

[Coding Challenge 11: 3D Terrain Generation with Perlin Noise in Processing](https://www.youtube.com/watch?v=IKB1hWWedMk&t=298s)

[The Most Famous Algorithm In Computer Graphics](https://www.youtube.com/watch?v=DxUY42r_6Cg)
