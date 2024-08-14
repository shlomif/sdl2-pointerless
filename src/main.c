
/*
 * I use:
 *
 * gcc -DSDLVER=2 -O3 -march=native -Wall -Wextra `pkg-config --cflags --libs
 * sdl2` src/main.c -lm
 *
 *
 * to build
 * */
// Define screen dimensions
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)

// Max grid dimension
#define GRID_MAX_X_CELLS (10)
#define GRID_MAX_Y_CELLS (10)

#define GRID_DEFAULT_COLOR COLOR_WHITE
#define GRID_DEFAULT_BORDER_SIZE (2)
#define GRID_DEFAULT_BORDER_COLOR COLOR_WHITE

#define USE_AZERTY_KEYBOARD 0

//***************************************************************************************
// IMPORTANT NOTE:
//
//      To start coding, go down in this file to the 'FREE CODING' section.
//      All your code should be written inside the 'draw' function (line 1725).
//      There is also a 'DOCUMENTATION' section just above the 'FREE CODING'
//      section.
//
//      Read the README.md file for more details.
//
//***************************************************************************************

/*
 * Copyright (c) 2018, 2019, 2021 Amine Ben Hassouna
 <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * ---------------------------------------------------------------------------------
 * The 4x6 font:
 *  - Upper case letters
 *  - Lower case letters
 *  - Exclamation mark
 *  - Piriod (punctuation)
 *
 * Belongs to https://github.com/filmote
 * Source: https://github.com/filmote/Font4x6/blob/master/src/fonts/Font4x6.cpp
 * License: https://github.com/filmote/Font4x6/blob/master/LICENSE

    BSD 3-Clause License

    Copyright (c) 2018, Filmote
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    * Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------------
 *
 * The 4x6 font modification/extension:
 * Some lower case letters have been modifed and the remaining font characters
 are made
 * by "Amine Ben Hassouna" and are distributed under the same license as this
 file.
 *
 */

//****************************************************************************************
// LIBRARY SECTION
//****************************************************************************************

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

// Define MAX and MIN macros
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

#define _COLOR(RED, GREEN, BLUE) {RED, GREEN, BLUE, 0xFF}
#define COLOR(RED, GREEN, BLUE) ((SDL_Color){RED, GREEN, BLUE, 0xFF})

const SDL_Color COLOR_BLACK = _COLOR(0, 0, 0);
const SDL_Color COLOR_WHITE = _COLOR(0xFF, 0xFF, 0xFF);
const SDL_Color NO_COLOR = COLOR_WHITE;

enum
{
    SDLK_DIVIDE = SDLK_SLASH,
    SDLK_MULTIPLY = SDLK_ASTERISK,
};

SDL_Keycode normalize_key(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_KP_0:
        return SDLK_0;
    case SDLK_KP_1:
        return SDLK_1;
    case SDLK_KP_2:
        return SDLK_2;
    case SDLK_KP_3:
        return SDLK_3;
    case SDLK_KP_4:
        return SDLK_4;
    case SDLK_KP_5:
        return SDLK_5;
    case SDLK_KP_6:
        return SDLK_6;
    case SDLK_KP_7:
        return SDLK_7;
    case SDLK_KP_8:
        return SDLK_8;
    case SDLK_KP_9:
        return SDLK_9;
    case SDLK_KP_ENTER:
        return SDLK_RETURN;
    case SDLK_KP_PERIOD:
        return SDLK_PERIOD;
    case SDLK_KP_COMMA:
        return SDLK_COMMA;
    case SDLK_KP_COLON:
        return SDLK_COLON;
    case SDLK_KP_PERCENT:
        return SDLK_PERCENT;
#if USE_AZERTY_KEYBOARD
    case 249:
        return SDLK_PERCENT;
#endif
    case SDLK_KP_PLUS:
        return SDLK_PLUS;
    case SDLK_KP_MINUS:
        return SDLK_MINUS;
    case SDLK_KP_MULTIPLY:
        return SDLK_MULTIPLY;
    case SDLK_KP_DIVIDE:
        return SDLK_DIVIDE;
    case SDLK_KP_EQUALS:
        return SDLK_EQUALS;
    default:
        break;
    }

    return key;
}

bool is_key_letter(SDL_Keycode key) { return key >= SDLK_a && key <= SDLK_z; }

bool is_key_digit(SDL_Keycode key) { return key >= SDLK_0 && key <= SDLK_9; }

bool is_key_arithmetic_op(SDL_Keycode key)
{
    return key == SDLK_PLUS || key == SDLK_MINUS || key == SDLK_DIVIDE ||
           key == SDLK_MULTIPLY || key == SDLK_PERCENT;
}

char key_to_char(SDL_Keycode key)
{
    key = normalize_key(key);

    if (is_key_letter(key))
    {
        return (char)(key - SDLK_a + 'A');
    }
    else if (key >= SDLK_SPACE && key <= SDLK_BACKQUOTE)
    {
        return (char)key;
    }

    return 0;
}

char key_to_char_lowercase(SDL_Keycode key)
{
    if (is_key_letter(key))
    {
        return (char)key;
    }
    else
    {
        return key_to_char(key);
    }
}

int key_to_int(SDL_Keycode key)
{
    key = normalize_key(key);

    if (is_key_digit(key))
    {
        return (int)(key - SDLK_0);
    }
    else
    {
        return -1;
    }
}

SDL_Keycode digit_to_key(int digit) { return (abs(digit) % 10) + SDLK_0; }

char digit_to_char(int digit) { return (abs(digit) % 10) + '0'; }

int char_to_digit(char c) { return c - '0'; }

typedef struct
{
    // Rect dimensions and color
    SDL_Rect rect;
    SDL_Color rect_color;

    // Border dimensions and color
    SDL_Rect border;
    SDL_Color border_color;
} Cell;

typedef struct
{
    // x, y, width, height
    SDL_Rect rect;

    // Grid background color
    SDL_Color background_color;

    // Grid border thickness and color
    unsigned int border;
    SDL_Color border_color;

    // Number of cells over the x axis
    int x_cells;
    // Number of cells over the y axis
    int y_cells;

    // Cells boder thickness and color
    unsigned int cells_border;
    SDL_Color cells_border_color;

    // Matrix of Cells
    Cell cells[GRID_MAX_X_CELLS][GRID_MAX_Y_CELLS];
} Grid;

static void set_color(SDL_Renderer *renderer, SDL_Color color)
{
    // Initialize renderer color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void set_background_color(SDL_Renderer *renderer, SDL_Color color)
{
    // Initialize renderer color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Clear screen
    // SDL_RenderClear(renderer);
}

int random_int(int min, int max) { return (rand() % (max + 1)) + min; }

bool is_color_equal(SDL_Color color1, SDL_Color color2)
{
    return *((Sint32 *)&color1) == *((Sint32 *)&color2);
}

bool init_grid(Grid* grid)
{
    if (!grid->rect.w || !grid->rect.h || !grid->x_cells || !grid->y_cells)
    {
        fprintf(
            stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    if (grid->x_cells > GRID_MAX_X_CELLS || grid->y_cells > GRID_MAX_Y_CELLS)
    {
        fprintf(stderr,
            "Grid number of cells (%d,%d) is greater than (%d,%d) !\n",
            grid->x_cells, grid->y_cells, GRID_MAX_X_CELLS, GRID_MAX_Y_CELLS);
        return false;
    }
    return true;
}

static void putpixel(SDL_Renderer *renderer, int x, int y, SDL_Color color)
{
    // Set renderer color to cell color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 1;
    rect.h = 1;
// #define DEBUG
#ifdef DEBUG
    fprintf(stdout, "putpixel[x=%d , y=%d]\n", x, y);
    fflush(stdout);
#endif
    // Render filled cell
    SDL_RenderFillRect(renderer, &(rect));
}

static void render_grid(Grid* grid, SDL_Renderer* renderer)
{
//    if(grid->border != 0) // Grid border thickness different from 0
    {
        // Set renderer color to draw the grid border
        SDL_SetRenderDrawColor(renderer, grid->border_color.r,
            grid->border_color.g, grid->border_color.b, grid->border_color.a);

        // Render grid border
        SDL_RenderFillRect(renderer, &(grid->rect));
    }

    return;
}

int ajust_grid_size(Grid *grid)
{
    if (!grid->rect.w || !grid->rect.h || !grid->x_cells || !grid->y_cells)
    {
        fprintf(
            stderr, "Grid dimensions or number of cells not initialised !\n");
        return false;
    }

    // Init rect
    int interspace_width = grid->x_cells * grid->cells_border * 2;
    grid->rect.w -=
        (grid->rect.w - (grid->border * 2) - interspace_width) % grid->x_cells;

    int interspace_heigth = grid->y_cells * grid->cells_border * 2;
    grid->rect.h -=
        (grid->rect.h - (grid->border * 2) - interspace_heigth) % grid->y_cells;

    return true;
}

void center_grid(Grid *grid, int screen_width, int screen_height)
{
    grid->rect.x = (screen_width - grid->rect.w) / 2;
    grid->rect.y = (screen_height - grid->rect.h) / 2;
}

SDL_Color get_grid_border_color(Grid *grid) { return grid->border_color; }

SDL_Keycode get_key(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        return event->key.keysym.sym;
    }

    return SDLK_UNKNOWN;
}

bool start(SDL_Renderer *renderer, int width, int height);

int main(int argc, char *argv[])
{
    // Unused argc, argv
    (void)argc;
    (void)argv;

    // Initialize the pseudo-random number generator
    srand(time(NULL));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr,
            "SDL could not be initialized!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        fprintf(stderr, "SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("Simple grid with C and SDL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr,
            "Window could not be created!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer =
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            fprintf(stderr,
                "Renderer could not be created!\n"
                "SDL_Error: %s\n",
                SDL_GetError());
        }
        else
        {
            // Start rendering
            start(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL
    SDL_Quit();

    return 0;
}

void delay(SDL_Renderer *renderer, Uint32 ms, SDL_Event *event)
{
    event->type = 0;

    Uint32 start = SDL_GetTicks();
    int step = ms >= 10 ? 10 : 1;
    while (SDL_GetTicks() - start < ms)
    {
        // Update screen
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_WaitEventTimeout(&e, step))
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                exit(0);
                break;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                *event = e;
                event->key.keysym.sym = normalize_key(event->key.keysym.sym);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                *event = e;
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                *event = e;
            }
        }
    }
}

static int counter = 0;
bool render_and_delay(SDL_Renderer *renderer, SDL_Color background_color,
    Uint32 ms, SDL_Event *event)
{
#if 1
    if (!counter)
    {
        ++counter;
        // Set white background
        set_background_color(renderer, background_color);
        SDL_RenderClear(renderer);
    }
#endif

#if 0
    // Render grid
    render_grid(grid, renderer);
#endif
    // Wait
    delay(renderer, ms, event);

    return true;
}

// Global variables
SDL_Renderer *g_renderer = NULL;
Grid g_grid = {0};
const SDL_Color g_background_color = COLOR_BLACK;
SDL_Event g_event = {0};

static void draw();

bool start(SDL_Renderer *renderer, int width, int height)
{
    g_grid.background_color = g_background_color;
    g_grid.border_color = g_background_color;

    // Init global renderer
    g_renderer = renderer;
    set_background_color(renderer, g_background_color);

    // Set number of cells
    g_grid.x_cells = GRID_MAX_X_CELLS;
    g_grid.y_cells = GRID_MAX_Y_CELLS;

    // Set grid dimensions
    g_grid.rect.w = width;
    g_grid.rect.h = height;

    // Set grid backgroud
    g_grid.background_color = GRID_DEFAULT_COLOR;

    // Set grid border thickness and color
    g_grid.border = GRID_DEFAULT_BORDER_SIZE;
    // g_grid.border_color = GRID_DEFAULT_BORDER_COLOR;

    // Set cells border thickness and color
    g_grid.cells_border = g_grid.border;
    g_grid.cells_border_color = g_grid.border_color;

    // Ajust size and center
    ajust_grid_size(&g_grid);
    center_grid(&g_grid, width, height);

    if (!init_grid(&g_grid))
    {
        fprintf(stderr, "Grid fail to initialize !\n");
        return false;
    }

    // Set white background
    set_background_color(renderer, g_background_color);
    g_grid.background_color = g_background_color;

    g_grid.rect.x = 0;
    g_grid.rect.y = 0;
    g_grid.rect.w = width;
    g_grid.rect.h = height;
#if 1
    // Render grid
    render_grid(&g_grid, renderer);
#endif

    // Update screen
    SDL_RenderPresent(renderer);

    // Draw shapes
    draw();

    // Set white background
    set_background_color(renderer, g_background_color);
    g_grid.background_color = g_background_color;

    // Render grid
    render_grid(&g_grid, renderer);

    // Update screen
    SDL_RenderPresent(renderer);

    // Event loop exit flag
    bool quit = false;

    // Event loop
    while (!quit)
    {
        SDL_Event e;

        // Wait indefinitely for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        SDL_RenderPresent(renderer);
    }

    return true;
}

#if 0
#define set_background_color(color) (g_background_color = color)
#define get_background_color() (g_background_color)
#endif
#define get_grid_border_color() get_grid_border_color(&g_grid)
#define delay(ms) render_and_delay(g_renderer, g_background_color, ms, &g_event)
#define get_key() get_key(&g_event)
#define exit() exit(0)

//***************************************************************************************
// DOCUMENTATION
//***************************************************************************************

//***************************************************************************************
//
// Available function:
//
//      set_background_color(color)
//          Set the background color to one of the predefined colors
//
//      get_background_color()
//          Get the current background color
//
//      get_cell_color(x, y)
//          Get the current color of the cell at coordinates (x, y)
//
//      get_grid_border_color()
//          Get the current grid border color
//
//      delay(ms)
//          Wait a specified number of milliseconds
//
//      get_key()
//          Get the pressed key
//
//      is_key_letter(key)
//          Check if a key is a letter
//
//      is_key_digit(key)
//          Check if a key is a digit
//
//      is_key_arithmetic_op(key)
//          Check if a key is an arithmetic operator (+, -, *, /, %)
//
//      key_to_char(key)
//          Convert a key to a character
//
//      key_to_char_lowercase(key)
//          Convert a key to a lowercase character
//
//      key_to_int(key)
//          Convert a key to a digit (integer)
//
//      digit_to_key(digit)
//          Convert a digit (integer) to a key
//
//      digit_to_char(digit)
//          Convert a digit (integer) to a character
//
//      char_to_digit(c)
//          Convert a character to a digit (integer)
//
//      random_int(min, max)
//          Get a random integer between min and max
//
//      is_color_equal(color1, color2)
//          Check if 'color1' is equal to 'color2' (return a boolean)
//
//      exit()
//          Exit the program
//
// Available colors:
//
//      COLOR_BLACK
//      COLOR_WHITE
//
// Custom color:
//
//      COLOR( red, green, blue )
//
// Available keys:
//  (Full list at https://wiki.libsdl.org/SDL_Keycode)
//
//      SDLK_RETURN
//      SDLK_SPACE
//      SDLK_BACKSPACE
//      SDLK_ESCAPE
//      SDLK_{character}
//      SDLK_{digit}
//      SDLK_UP
//      SDLK_DOWN
//      SDLK_RIGHT
//      SDLK_LEFT
//      SDLK_EXCLAIM
//      SDLK_PERIOD
//      SDLK_COLON
//      SDLK_EQUALS
//      SDLK_PLUS
//      SDLK_MINUS
//      SDLK_DIVIDE
//      SDLK_MULTIPLY
//      SDLK_PERCENT
//
//
//***************************************************************************************

//***************************************************************************************
// FREE CODING SECTION
//***************************************************************************************

#define LOG2_DEGREES_RANGE 9
#define DEGREES_RANGE (1 << (LOG2_DEGREES_RANGE))
#define DEG_MOD(x) ((x) & (DEGREES_RANGE - 1))

static bool mycont = true;
static void draw()
{
    const int x_num_points = 20;
    const int y_num_points = 10;
    const int x_x_offset = 20;
    const int x_y_offset = 0;
    const int y_x_offset = 3;
    const int y_y_offset = 10;
    double y_amplitude = 10.0;
    int y_amp_delta = 50;
    int x_amp_delta = 20;
    /* This is so it won't get out of the end of the screen */
    int y_abs_offset = 20;
    int x_abs_offset = 10;
    int sin_lookup[DEGREES_RANGE];

    int x, y, t, prev_t;
    int prev_y_height;
    int this_y_height;
    int x_pos, y_pos;

    int y_acc_degree, y_x_acc_degree;
    int prev_y_acc_degree, prev_y_x_acc_degree;
    int y_acc_y_pos, y_acc_x_pos;
#ifdef WITH_RECTS
    SDL_Rect *rects;
    SDL_Rect *the_rect;
#endif
#define PI 3.14159265358
    int a;

    for (a = 0; a < DEGREES_RANGE; a++)
    {
        sin_lookup[a] = (int)(sin((2 * PI / DEGREES_RANGE) * a) * y_amplitude);
    }

#ifdef WITH_RECTS
    rects = (SDL_Rect *)malloc(sizeof(rects[0]) * x_num_points * y_num_points);
    for (a = 0; a < x_num_points * y_num_points; a++)
    {
        rects[a].w = 1;
        rects[a].h = 2;
    }

#if 0
    fprintf(stdout, "%d\n", SDL_MUSTLOCK(screen));
    fflush(stdout);
#endif

    /*
     * Calculate all the x positions of the rects in advance
     * */
    the_rect = rects;
    y_acc_x_pos = x_abs_offset;
    for (y = 0; y < y_num_points; y++)
    {
        x_pos = y_acc_x_pos;
        for (x = 0; x < x_num_points; x++)
        {
            the_rect->x = x_pos;
            the_rect++;
            x_pos += x_x_offset;
        }
        y_acc_x_pos += y_x_offset;
    }
#endif

#if 0
    {
        SDL_Rect whole_screen_rect;
        whole_screen_rect.x = whole_screen_rect.y = 0;
        whole_screen_rect.w = 640;
        whole_screen_rect.h = 480;
        SDL_FillRect(screen,&whole_screen_rect, fill_color);
        /* The 0's indicate that the whole screen needs to be updated */
        SDL_UpdateRect(screen,0,0,0,0);
    }
#endif
    prev_t = 0;
    for (t = 1; mycont; t = ((t + 1) & (DEGREES_RANGE - 1)))
    {
#ifdef WITH_RECTS
        the_rect = rects;
#endif

        y_acc_degree = t;
        prev_y_acc_degree = prev_t;
        y_acc_y_pos = y_abs_offset;
        y_acc_x_pos = x_abs_offset;
        for (y = 0; y < y_num_points; y++)
        {
            y_x_acc_degree = y_acc_degree;
            prev_y_x_acc_degree = prev_y_acc_degree;

            x_pos = y_acc_x_pos;
            y_pos = y_acc_y_pos;
            for (x = 0; x < x_num_points; x++)
            {
                prev_y_height = y_pos + sin_lookup[prev_y_x_acc_degree];
                this_y_height = y_pos + sin_lookup[y_x_acc_degree];

#ifdef WITH_RECTS
                the_rect->y = min(prev_y_height, this_y_height);
                the_rect++;
#endif

                /* I don't need to lock the screen, so I'm omitting it */

#define screen g_renderer
// #error right
#define fill_color COLOR_BLACK
#define pen_color COLOR_WHITE
                putpixel(screen, x_pos, prev_y_height, fill_color);

                putpixel(screen, x_pos, this_y_height, pen_color);

                set_color(screen, fill_color);
                set_background_color(g_renderer, g_grid.background_color);

                y_x_acc_degree = DEG_MOD(y_x_acc_degree + x_amp_delta);
                prev_y_x_acc_degree =
                    DEG_MOD(prev_y_x_acc_degree + x_amp_delta);
                x_pos += x_x_offset;
                y_pos += x_y_offset;
            }
            y_acc_degree = DEG_MOD(y_acc_degree + y_amp_delta);
            prev_y_acc_degree = DEG_MOD(prev_y_acc_degree + y_amp_delta);
            y_acc_y_pos += y_y_offset;
            y_acc_x_pos += y_x_offset;
        }
        prev_t = t;
        delay(1);
#if 0
        SDL_UpdateRects(screen, x_num_points*y_num_points, rects);
#endif
        // SDL_RenderPresent(g_renderer);
#undef screen
    }
}
