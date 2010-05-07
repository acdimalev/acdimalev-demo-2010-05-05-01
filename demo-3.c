#include <cairo.h>

#include "core.h"

static float y_bearing = 3/4.0;
static float x_bearing = 1/8.0;
static float width     = 1/2.0;
static float pen_width = 1/64.0;

#define height     y_bearing
#define x_advance  (width + 2 * x_bearing)

void hseg(cairo_t *cr) {
  double w = width;
  double r = 1/16.0;
  double g = 1/32.0;
  double x, y;

  cairo_save(cr);

  cairo_get_current_point(cr, &x, &y);
  cairo_translate(cr, x, y);
  cairo_move_to(cr, g, 0);
  cairo_line_to(cr, g + r, -r);
  cairo_line_to(cr, w - g - r, -r);
  cairo_line_to(cr, w - g, 0);
  cairo_line_to(cr, w - g - r,  r);
  cairo_line_to(cr, g + r,  r);
  cairo_close_path(cr);
  cairo_fill(cr);

  cairo_restore(cr);
}

void vseg(cairo_t *cr) {
  double h = height / 2.0;
  double r = 1/16.0;
  double g = 1/32.0;
  double x, y;

  cairo_save(cr);

  cairo_get_current_point(cr, &x, &y);
  cairo_translate(cr, x, y);
  cairo_move_to(cr,  0, g);
  cairo_line_to(cr,  r, g + r);
  cairo_line_to(cr,  r, h - g - r);
  cairo_line_to(cr,  0, h - g);
  cairo_line_to(cr, -r, h - g - r);
  cairo_line_to(cr, -r, g + r);
  cairo_close_path(cr);
  cairo_fill(cr);

  cairo_restore(cr);
}

void glyph(cairo_t *cr) {
  double a = x_bearing;
  double w = width;
  double h = height;
  double x, y;

  cairo_save(cr);
  cairo_get_current_point(cr, &x, &y);
  cairo_translate(cr, x, y);

  cairo_move_to(cr, a, 0);
  hseg(cr);
  cairo_move_to(cr, a, h/2.0);
  hseg(cr);
  cairo_move_to(cr, a, h);
  hseg(cr);

  cairo_move_to(cr, a, 0);
  vseg(cr);
  cairo_move_to(cr, a, h/2.0);
  vseg(cr);

  cairo_move_to(cr, a + w, 0);
  vseg(cr);
  cairo_move_to(cr, a + w, h/2.0);
  vseg(cr);

  cairo_restore(cr);
}

void render(cairo_t *cr) {
  h_guide(cr, -1/2.0 + height - y_bearing);
  h_guide(cr, -1/2.0 + y_bearing);
  v_guide(cr, -width/2.0);
  v_guide(cr,  width/2.0);

  bullet(cr, -width/2.0 - x_bearing, -1/2.0);
  bullet(cr, -width/2.0 - x_bearing + x_advance, -1/2.0);

  cairo_move_to(cr, -width/2.0 - x_bearing, -1/2.0);
  glyph(cr);
}
