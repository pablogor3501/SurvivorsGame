#include <iostream>
#include <math.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// ─── Sprite config ────────────────────────────────────────────────────────────
// Individual frame files — adjust the path prefix and indices to match yours
static const char *SPRITE_FRAMES_PATHS[] = {
    "assets/Floppy-Animation-Rainbow-002.png",
    "assets/Floppy-Animation-Rainbow-003.png",
    "assets/Floppy-Animation-Rainbow-004.png",
    "assets/Floppy-Animation-Rainbow-005.png",
    "assets/Floppy-Animation-Rainbow-006.png",
    "assets/Floppy-Animation-Rainbow-007.png",
};
static const int    SPRITE_FRAMES     = 6;
static const Uint32 FRAME_DURATION_MS = 125; // ms per frame (125 = 8 fps)
// ─────────────────────────────────────────────────────────────────────────────

static const int SEED = 2001;

static const unsigned char HASH[] = {
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

static int noise2(int x, int y) {
    int yindex = (y + SEED) % 256;
    if (yindex < 0) yindex += 256;
    int xindex = (HASH[yindex] + x) % 256;
    if (xindex < 0) xindex += 256;
    return HASH[xindex];
}

static double lin_inter(double x, double y, double s) { return x + s * (y - x); }
static double smooth_inter(double x, double y, double s) { return lin_inter(x, y, s * s * (3 - 2 * s)); }

static double noise2d(double x, double y) {
    const int x_int = floor(x), y_int = floor(y);
    const double x_frac = x - x_int, y_frac = y - y_int;
    const int s = noise2(x_int,     y_int);
    const int t = noise2(x_int + 1, y_int);
    const int u = noise2(x_int,     y_int + 1);
    const int v = noise2(x_int + 1, y_int + 1);
    return smooth_inter(smooth_inter(s, t, x_frac), smooth_inter(u, v, x_frac), y_frac);
}

double perlin2d(double x, double y, double freq, int depth) {
    double xa = x * freq, ya = y * freq, amp = 1.0, fin = 0, div = 0.0;
    for (int i = 0; i < depth; i++) {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2; xa *= 2; ya *= 2;
    }
    return fin / div;
}

SDL_Color pickColor(int val) {
    SDL_Color c[] = {
        {40,40,40,255}, {41,54,111,255}, {59,93,201,255}, {64,166,245,255},
        {114,239,247,255}, {148,175,194,255}, {86,108,134,255}
    };
    return c[val];
}

int main(int argc, const char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *win = SDL_CreateWindow(
        "Procedural Terrain",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
        SDL_WINDOW_RESIZABLE
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    SDL_PixelFormat *formatPix = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    // Fixed world FOV — window size only affects pixel density, not visible area
    const float WORLD_W = 800.0f, WORLD_H = 600.0f;

    int   xOrg = 100000, yOrg = 100000;
    float freq  = 1.0f;
    int   depth = 5, scale = 16;
    int   WIN_WIDTH = 800, WIN_HEIGHT = 600;

    std::vector<Uint32> pixels(WIN_WIDTH * WIN_HEIGHT);
    SDL_Texture *terrainTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);

    // ── Load individual frame textures ────────────────────────────────────────
    SDL_Texture *frames[SPRITE_FRAMES] = {};
    int frameW = 0, frameH = 0;

    for (int i = 0; i < SPRITE_FRAMES; i++) {
        frames[i] = IMG_LoadTexture(renderer, SPRITE_FRAMES_PATHS[i]);
        if (!frames[i]) {
            SDL_Log("Failed to load frame %d: %s", i, IMG_GetError());
            return 1;
        }
        SDL_SetTextureBlendMode(frames[i], SDL_BLENDMODE_BLEND);

        // All frames should be the same size; read it once from the first one
        if (i == 0)
            SDL_QueryTexture(frames[0], NULL, NULL, &frameW, &frameH);
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // ── Events ───────────────────────────────────────────────────────────
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    yOrg -= 1; break;
                    case SDLK_DOWN:  yOrg += 1; break;
                    case SDLK_LEFT:  xOrg -= 1; break;
                    case SDLK_RIGHT: xOrg += 1; break;
                }
            } else if (e.type == SDL_WINDOWEVENT &&
                       e.window.event == SDL_WINDOWEVENT_RESIZED) {
                WIN_WIDTH  = e.window.data1;
                WIN_HEIGHT = e.window.data2;
                SDL_DestroyTexture(terrainTex);
                terrainTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                    SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);
                pixels.resize(WIN_WIDTH * WIN_HEIGHT);
            }
        }

        // ── Terrain generation ────────────────────────────────────────────────
        for (int sy = 0; sy < WIN_HEIGHT; sy++) {
            for (int sx = 0; sx < WIN_WIDTH; sx++) {
                float worldX  = (sx / (float)WIN_WIDTH)  * WORLD_W;
                float worldY  = (sy / (float)WIN_HEIGHT) * WORLD_H;
                float perlinX = xOrg + worldX / scale;
                float perlinY = yOrg + worldY / scale;

                float value = perlin2d(perlinY, perlinX, freq, depth);
                SDL_Color col = pickColor((int)(value * 16) % 7);
                pixels[sy * WIN_WIDTH + sx] =
                    SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
            }
        }
        SDL_UpdateTexture(terrainTex, NULL, pixels.data(), sizeof(Uint32) * WIN_WIDTH);

        // ── Render ────────────────────────────────────────────────────────────
        SDL_RenderClear(renderer);

        // Layer 1 – terrain
        SDL_RenderCopy(renderer, terrainTex, NULL, NULL);

        // Layer 2 – animated sprite, centered on screen
        int frameIndex = (SDL_GetTicks() / FRAME_DURATION_MS) % SPRITE_FRAMES;

        SDL_Rect dst {
            (WIN_WIDTH  - frameW) / 2,
            (WIN_HEIGHT - frameH) / 2,
            frameW,
            frameH
        };

        SDL_RenderCopy(renderer, frames[frameIndex], NULL, &dst);

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < SPRITE_FRAMES; i++)
        SDL_DestroyTexture(frames[i]);
    SDL_DestroyTexture(terrainTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}