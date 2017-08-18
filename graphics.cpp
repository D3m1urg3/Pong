#include "graphics.h"

// Texture
Texture::Texture()
    :loaded(false),
    sdl_surface(nullptr)
{
}

Texture::Texture(char* fullfilename)
    :loaded(false),
    sdl_surface(nullptr)
{
    loaded = load_from_bmp(fullfilename);
}

Texture::~Texture()
{
    clean();
}

void Texture::free_texture()
{
    if (loaded && sdl_surface != nullptr)
    {
        SDL_FreeSurface(sdl_surface);
        sdl_surface = nullptr;
        loaded = false;
    }
}

void Texture::clean()
{
    free_texture();
}

bool Texture::load_from_bmp(const char* fullfilename)
{
    if (fullfilename != nullptr)
    {
        free_texture();
        sdl_surface = SDL_LoadBMP(fullfilename);
        if (sdl_surface != nullptr)
        {
            return true;
        }
    }
    return false;
}

void Texture::set_sdl_surface(SDL_Surface* surface)
{
    if (surface != nullptr)
    {
        free_texture();
        sdl_surface = surface;
        loaded  = true;
    }
}

// Sprite
void Sprite::set_src_rect(int x, int y, int wx, int wy)
{
    if (src != nullptr)
    {
        delete src;
    }
    src = new SDL_Rect{ x, y, wx, wy }; 
}

void Sprite::set_dst_rect(int x, int y, int wx, int wy)
{
    if (dst != nullptr)
    {
        delete dst;
    }
    dst = new SDL_Rect{ x, y, wx, wy }; 
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
// Renderer
Renderer::Renderer(const char* title, uint screen_x, uint screen_y, uint size_x, uint size_y):
    window(nullptr),
    screen(nullptr)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (title != nullptr)
    {
        window = SDL_CreateWindow(title, screen_x, screen_y, size_x, size_y, SDL_WINDOW_SHOWN);
        screen = SDL_GetWindowSurface(window);
    }
}

Renderer::~Renderer()
{
    clean();
}

void Renderer::clean()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::draw(Sprite* sprite)
{
    Texture*  tex = sprite->get_spritesheet();
    SDL_Rect* src = sprite->get_src_rect();
    SDL_Rect* dst = sprite->get_dst_rect();
    if (tex != nullptr && tex->is_loaded())
    {
        SDL_BlitSurface(tex->get_sdl_surface(), src, screen, dst);
        SDL_UpdateWindowSurface(window);
    }
}