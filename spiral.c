#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double angles[4][2] = {
    {M_PI / 2 + M_PI, 0},
    {M_PI, M_PI / 2 + M_PI},
    {M_PI / 2, M_PI},
    {0, M_PI / 2},
};

typedef struct {
  int r;
  int g;
  int b;
} Color;

Color color3 = {60, 68, 143};
Color color4 = {44, 245, 131};

Color interpolateColors(Color color1, Color color2, float t) {
  Color color;
  color.r = color1.r + ((color2.r - color1.r) * t);
  color.g = color1.g + ((color2.g - color1.g) * t);
  color.b = color1.b + ((color2.b - color1.b) * t);
  return color;
}

int main() {
  int width = 1024;
  int height = 1024;

  cairo_t *cr;
  cairo_surface_t *surface;
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_rectangle(cr, 0.0, 0.0, width, height);
  cairo_fill(cr);

  cairo_set_line_width(cr, 2);

  for (int i = 0; i < 1; i++) {
    
    cairo_identity_matrix(cr);

    int x = div(width, 2).quot;
    int y = div(height, 2).quot;

    cairo_translate(cr, x, y);

    double r = 0.2;
    int a = 1, b = 1, c = a + b;
    int q = 0;
    double s, e;

    // cairo_rotate(cr, M_PI / 180 * 290);
    cairo_rotate(cr, M_PI / 180 * i);

    for (int n = 0; n < 20; n++) {

      Color color = interpolateColors(color4, color3, n / 20.0);
      cairo_set_source_rgb(cr, color.r / 255.0, color.g / 255.0,
                           color.b / 255.0);

      cairo_arc(cr, 0, 0, a * r, angles[q][0], angles[q][1]);
      cairo_stroke(cr);

      switch (q) {
      case 0:
        x = 0;
        y = (b * r - a * r);
        break;
      case 1:
        x = (b * r - a * r);
        y = 0;
        break;
      case 2:
        x = 0;
        y = -(b * r - a * r);
        break;
      case 3:
        x = -(b * r - a * r);
        y = 0;
        break;
      }

      cairo_translate(cr, x, y);

      // Get next term.
      a = b;
      b = c;
      c = a + b;

      q = q + 1;
      if (q > 3)
        q = 0;
    }
  }

  cairo_surface_flush(surface);
  cairo_surface_write_to_png(surface, "./spiral.png");

  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  return 0;
}