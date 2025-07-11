#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "SDL/SDL.h"
// #undef main // For some reason SDL defines a main somewhere.
#include "globals.h"
#include <queue>
#include <vector>

class Texture
{
public:
    Texture();
    Texture(const char* fullfilename);
    ~Texture();

    inline bool         is_loaded() const { return loaded; }
    bool                load_from_bmp(const char* fullfilename);
    void                set_sdl_surface(SDL_Surface* surface);
    inline SDL_Surface* get_sdl_surface() const { return sdl_surface; }
private:
    bool loaded;
    SDL_Surface*  sdl_surface;

    void free_texture();
    void clean();
};

class Renderer;

class Sprite
{
public:
    Sprite(Texture* spritesheet_, int src_x, int src_y, int src_wx, int src_wy);
    ~Sprite();

    void                set_src_rect(int x, int y, int wx, int wy);
    void                set_dst_rect(int x, int y, int wx, int wy);
    inline SDL_Rect*    get_src_rect() const { return src; }
    inline SDL_Rect*    get_dst_rect() const { return dst; }
    uint                get_sprite_width() const;
    uint                get_sprite_height() const;
    Texture*            get_spritesheet() const { return spritesheet; }
    Component_types     component_type() const { return ctype; }

    void                draw(Renderer* render);
private:
    static const Component_types ctype;
    Texture* spritesheet;
    SDL_Rect* src;
    SDL_Rect* dst;
};

class Renderer
{
public:
    Renderer(const char* title, uint screen_x, uint screen_y, uint size_x, uint size_y);
    ~Renderer();

    void draw(Sprite* sprite);
    void clear_screen();
private:
    SDL_Window* window;
    SDL_Surface* screen;

};
#endif