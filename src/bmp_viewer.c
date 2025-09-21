#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

// Bitmap File Header (14 bytes)
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType;      // File type: should be 'BM'
    uint32_t bfSize;      // File size in bytes
    uint16_t bfReserved1; // Reserved, must be 0
    uint16_t bfReserved2; // Reserved, must be 0
    uint32_t bfOffBits;   // Offset to pixel data
} BITMAPFILEHEADER;

// DIB Header (BITMAPINFOHEADER - 40 bytes)
typedef struct
{
    uint32_t biSize;         // Header size (40 bytes)
    int32_t biWidth;         // Image width
    int32_t biHeight;        // Image height
    uint16_t biPlanes;       // Always 1
    uint16_t biBitCount;     // Bits per pixel
    uint32_t biCompression;  // Compression (0 = none)
    uint32_t biSizeImage;    // Image size (can be 0 if uncompressed)
    int32_t biXPelsPerMeter; // Horizontal resolution
    int32_t biYPelsPerMeter; // Vertical resolution
    uint32_t biClrUsed;      // Colors used
    uint32_t biClrImportant; // Important colors
} BITMAPINFOHEADER;
#pragma pack(pop)

void draw_image(unsigned char *data, int width, int height, int row_padded, SDL_Surface *surface);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <image.bmp>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    if (fileHeader.bfType != 0x4D42)
    {
        printf("Not a valid BMP file!\n");
        fclose(fp);
        return 1;
    }

    if (infoHeader.biBitCount != 24 || infoHeader.biCompression != 0)
    {
        printf("Only uncompressed 24-bit BMP supported!\n");
        fclose(fp);
        return 1;
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int row_padded = (width * 3 + 3) & (~3);

    unsigned char *data = (unsigned char *)malloc(row_padded * height);
    fseek(fp, fileHeader.bfOffBits, SEEK_SET);
    fread(data, row_padded, height, fp);
    fclose(fp);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        free(data);
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("BMP Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    // Draw image
    draw_image(data, width, height, row_padded, surface);
    SDL_UpdateWindowSurface(window);

    SDL_Event event;
    SDL_bool running = SDL_TRUE;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    free(data);

    return 0;
}

void draw_image(unsigned char *data, int width, int height, int row_padded, SDL_Surface *surface)
{
    Uint32 color;
    SDL_Rect rect;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * row_padded + x * 3;

            unsigned char blue = data[index];
            unsigned char green = data[index + 1];
            unsigned char red = data[index + 2];

            color = SDL_MapRGB(surface->format, red, green, blue);

            rect.x = x;
            rect.y = height - y - 1; // BMP bottom-up hota hai
            rect.w = 1;
            rect.h = 1;

            SDL_FillRect(surface, &rect, color);
        }
    }
}