#include <cairo.h>

#include "core.h"

void render(cairo_t *cr) {
  cairo_font_extents_t fe;
  cairo_text_extents_t te;

  cairo_select_font_face(cr, "Georgia",
    CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, 1);
  cairo_font_extents(cr, &fe);
  cairo_text_extents(cr, "8", &te);

  // bearings are vertically inverted.

  h_guide(cr, -1/2.0 + -te.y_bearing - te.height);
  h_guide(cr, -1/2.0 + -te.y_bearing);
  v_guide(cr, -te.width/2.0);
  v_guide(cr,  te.width/2.0);

  bullet(cr, -te.width/2.0 - te.x_bearing, -1/2.0);
  bullet(cr, -te.width/2.0 - te.x_bearing + te.x_advance, -1/2.0);

  // font rendering is also vertically inverted.

  cairo_move_to(cr, -te.width/2.0 - te.x_bearing, -1/2.0);
  cairo_scale(cr, 1, -1);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_show_text(cr, "8");
}
