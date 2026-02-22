#include <iostream>
#include <math.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const int SEED = 2001;  // seed of perlin noise

static const unsigned char HASH[] = 
{
    208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
    185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
    9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
    70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
    203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
    164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
    228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
    232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
    193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
    101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
    135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
    114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
};

// Generate 2D noise
static int noise2(int x, int y) 
{
    int yindex = (y + SEED) % 256;
    if (yindex < 0)
        yindex += 256;
    int xindex = (HASH[yindex] + x) % 256;
    if (xindex < 0)
        xindex += 256;
    return HASH[xindex];
}

// Linear interpolation
static double lin_inter(double x, double y, double s) 
{
    return x + s * (y - x);
}

// Smooth interpolation
static double smooth_inter(double x, double y, double s) 
{
    return lin_inter(x, y, s * s * (3 - 2 * s));
}

// 2D Perlin noise
static double noise2d(double x, double y) 
{
    const int x_int = floor(x);
    const int y_int = floor(y);
    const double x_frac = x - x_int;
    const double y_frac = y - y_int;
    const int s = noise2(x_int, y_int);
    const int t = noise2(x_int + 1, y_int);
    const int u = noise2(x_int, y_int + 1);
    const int v = noise2(x_int + 1, y_int + 1);
    const double low = smooth_inter(s, t, x_frac);
    const double high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

// Generate Perlin noise with multiple octaves (depth)
double perlin2d(double x, double y, double freq, int depth) 
{
    double xa = x * freq;
    double ya = y * freq;
    double amp = 1.0;
    double fin = 0;
    double div = 0.0;
    for (int i = 0; i < depth; i++) {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin / div;
}

// Color picking based on the noise value
SDL_Color pickColor(int val) 
{
    SDL_Color arrColors[] = 
    {
        SDL_Color{40, 40, 40, 255},    // black
        SDL_Color{41, 54, 111, 255},   // dark blue
        SDL_Color{59, 93, 201, 255},
        SDL_Color{64, 166, 245, 255},
        SDL_Color{114, 239, 247, 255}, // light blue
        SDL_Color{148, 175, 194},      // light grey
        SDL_Color{86, 108, 134}        // dark grey
    };
    return arrColors[val];
}

int main(int argc, const char *argv[]) 
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_Window *win = SDL_CreateWindow("Procedural Terrain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    SDL_PixelFormat *formatPix = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    // --- World / screen coordinate separation ---
    // WORLD_W x WORLD_H defines the fixed field of view in world space.
    // No matter how large the window gets, these are the world units visible.
    // Screen pixels are just a scaled-up (or down) rendering of this fixed region.
    const float WORLD_W = 800.0f;
    const float WORLD_H = 600.0f;

    int xOrg = 100000;
    int yOrg = 100000;
    float freq  = 1.0f;
    int   depth = 5;
    int   scale = 16;   // how many world units map to one perlin unit

    int WIN_WIDTH  = 800;
    int WIN_HEIGHT = 600;

    // Pixel buffer sized to the current window; reallocated on resize.
    std::vector<Uint32> pixels(WIN_WIDTH * WIN_HEIGHT);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);

    bool quit = false;
    SDL_Event e;

    while (!quit) 
    {
        // --- Event handling ---
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                quit = true;
            } 
            else if (e.type == SDL_KEYDOWN) 
            {
                switch (e.key.keysym.sym) 
                {
                    case SDLK_UP:    yOrg -= 1; break;
                    case SDLK_DOWN:  yOrg += 1; break;
                    case SDLK_LEFT:  xOrg -= 1; break;
                    case SDLK_RIGHT: xOrg += 1; break;
                }
            } 
            else if (e.type == SDL_WINDOWEVENT &&e.window.event == SDL_WINDOWEVENT_RESIZED) 
            {
                WIN_WIDTH  = e.window.data1;
                WIN_HEIGHT = e.window.data2;

                SDL_DestroyTexture(texture);
                texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);
                pixels.resize(WIN_WIDTH * WIN_HEIGHT);
            }
        }

        // --- Terrain generation ---
        // For each screen pixel (sx, sy) we compute its position in the fixed
        // world viewport, then convert that to a perlin/world coordinate.
        //
        //   worldX = xOrg + (sx / WIN_WIDTH)  * WORLD_W / scale * freq  (conceptually)
        //
        // More explicitly:
        //   world_frac_x = sx / WIN_WIDTH          -> [0,1] across the screen
        //   world_unit_x = world_frac_x * WORLD_W  -> pixel position in the fixed viewport
        //   perlin_x     = xOrg + world_unit_x / scale
        //
        // This means the perlin sample always covers the same world region
        // regardless of WIN_WIDTH / WIN_HEIGHT.

        for (int sy = 0; sy < WIN_HEIGHT; sy++) 
        {
            for (int sx = 0; sx < WIN_WIDTH; sx++) 
            {
                // Screen -> world viewport coordinates (fixed FOV)
                float worldX = (sx / (float)WIN_WIDTH)  * WORLD_W;
                float worldY = (sy / (float)WIN_HEIGHT) * WORLD_H;

                // World viewport -> perlin space
                float perlinX = xOrg + worldX / scale;
                float perlinY = yOrg + worldY / scale;

                float value = perlin2d(perlinY, perlinX, freq, depth);
                SDL_Color col = pickColor((int)(value * 16) % 7);
                pixels[sy * WIN_WIDTH + sx] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
            }
        }

        SDL_UpdateTexture(texture, NULL, pixels.data(), sizeof(Uint32) * WIN_WIDTH);

        SDL_RenderClear(renderer);
        SDL_Rect rect{0, 0, WIN_WIDTH, WIN_HEIGHT};
        SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}