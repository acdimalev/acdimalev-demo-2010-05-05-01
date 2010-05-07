#include <cairo.h>
#include <math.h>

#include "SDL.h"
#include "config.h"

#define SCALE ( (WIDTH < HEIGHT ? WIDTH : HEIGHT) / (3/2.0) )

void h_guide(cairo_t *cr, float y) {
  cairo_move_to(cr, -3/4.0, y);
  cairo_line_to(cr,  3/4.0, y);
  cairo_set_line_width(cr, 1/128.0);
  cairo_stroke(cr);
}

void v_guide(cairo_t *cr, float x) {
  cairo_move_to(cr, x, -3/4.0);
  cairo_line_to(cr, x,  3/4.0);
  cairo_set_line_width(cr, 1/128.0);
  cairo_stroke(cr);
}

void bullet(cairo_t *cr, float x, float y) {
  cairo_arc(cr, x, y, 1/32.0, 0, 2*M_PI);
  cairo_fill(cr);
}

int main(int argc, char **argv) {
  SDL_Surface *sdl_surface;
  cairo_t *cr;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
  SDL_ShowCursor(0);
  SDL_SetVideoMode(WIDTH, HEIGHT, 32, 0);

  sdl_surface = SDL_GetVideoSurface();

  { /* Initialize Canvas */
    cairo_surface_t *cr_surface;
    cr_surface = cairo_image_surface_create_for_data(
      sdl_surface->pixels,
      CAIRO_FORMAT_RGB24,
      sdl_surface->w,
      sdl_surface->h,
      sdl_surface->pitch
      );
    cr = cairo_create(cr_surface);
    cairo_surface_destroy(cr_surface);
  }

  // Cartesian
  cairo_translate(cr, WIDTH/2.0, HEIGHT/2.0);
  cairo_scale(cr,  1, -1);

  // fixed scale
  cairo_scale(cr, SCALE, SCALE);

  SDL_LockSurface(sdl_surface);

  /* Render Frame */
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_rectangle(cr, -1/2.0, -1/2.0, 1, 1);
  cairo_move_to(cr, -1/2.0,  1/2.0);
  cairo_line_to(cr,  1/2.0, -1/2.0);
  cairo_set_line_width(cr, 1/64.0);
  cairo_stroke(cr);
  cairo_arc(cr, 0, 0, 1/2.0, 0, 2*M_PI);
  cairo_move_to(cr, -3/4.0, 0);
  cairo_line_to(cr,  3/4.0, 0);
  cairo_move_to(cr, 0, -3/4.0);
  cairo_line_to(cr, 0,  3/4.0);
  cairo_set_line_width(cr, 1/128.0);
  cairo_stroke(cr);

  render(cr);

  /* Update Display */
  SDL_UnlockSurface(sdl_surface);
  SDL_Flip(sdl_surface);
  SDL_LockSurface(sdl_surface);

  while (1) { /* Game Logic */
    SDL_Event event;

    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_q) {
        break;
      }
    }
  }

  SDL_UnlockSurface(sdl_surface);

  cairo_destroy(cr);
  SDL_Quit();

  return 0;
}
