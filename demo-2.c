#include <cairo.h>

#include "core.h"

void render(cairo_t *cr) {
  float y_bearing = 3/4.0;
  float x_bearing = 1/8.0;
  float width     = 1/2.0;
  float pen_width = 1/64.0;

  float height = y_bearing;
  float x_advance = width + 2 * x_bearing;

  h_guide(cr, -1/2.0 + height - y_bearing);
  h_guide(cr, -1/2.0 + y_bearing);
  v_guide(cr, -width/2.0);
  v_guide(cr,  width/2.0);

  bullet(cr, -width/2.0 - x_bearing, -1/2.0);
  bullet(cr, -width/2.0 - x_bearing + x_advance, -1/2.0);

  cairo_move_to(cr, -width/2.0 - x_bearing, -1/2.0);
}
