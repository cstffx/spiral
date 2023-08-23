#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A_90  M_PI / 2;
#define A_180 M_PI;
#define A_270 (M_PI / 2) + M_PI;
#define A_360 M_PI * 2; 

#define min(a, b) a < b ? a : b

double angles[4][2] = {
  {M_PI / 2 + M_PI, 0},
  {M_PI, M_PI / 2 + M_PI},
  {M_PI / 2, M_PI},
  {0, M_PI / 2},
};

int main() {
  int width = 640;
  int height = 480;

  cairo_t *cr;
  cairo_surface_t *surface;
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_rectangle(cr, 0.0, 0.0, width, height);
  cairo_fill(cr);

  cairo_set_line_width(cr, 1);
  cairo_set_source_rgb(cr, 1.0/255, 115.0/255, 208.0/255);
  cairo_set_source_rgb(cr, 1, 1, 1);

  int x = div(width, 2).quot;
  int y = div(height, 2).quot;
  cairo_translate(cr, x, y);

  double r = 0.2;
  int a = 1, b = 1, c = a + b;
  int q = 0;
  double s, e;

  for (int n = 0; n < 15; n++) {
    cairo_arc(cr, 0, 0, a *r, 
      angles[q][0], angles[q][1]);

    cairo_stroke(cr);

    switch(q){
    case 0:
      x = 0;
      y = (b*r - a*r);
      break;
    case 1:
      x = (b*r - a*r);
      y = 0;
      break;
    case 2:
      x = 0;
      y = -(b*r - a*r);
      break;
    case 3:
      x = -(b*r - a*r);
      y = 0;
      break;
    }

    cairo_translate(cr, x, y);

    // Get next term.
    a = b;
    b = c;
    c = a + b;

    q = q + 1;
    if(q > 3) q = 0;
   }

  cairo_surface_flush(surface);

  cairo_surface_write_to_png(surface, "./spiral.png");

  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  return 0;
}