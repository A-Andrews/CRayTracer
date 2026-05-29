#include "vec3.h"
#include <stdio.h>

int main(void) {
  // Image

  int image_width = 256;
  int image_height = 256;

  // Render

  FILE *file = fopen("image.ppm", "w");

  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  fprintf(file, "P3\n%d %d\n255\n", image_width, image_height);

  for (int j = 0; j < image_height; j++) {
    printf("Lines remaining: %d\n", image_height - j);
    for (int i = 0; i < image_width; i++) {

      Vec3 pixel =
          vec3_scale(255.999, (Vec3){(double)i / (image_width - 1),
                                     (double)j / (image_height - 1), 0.0});
      vec3_write(file, pixel);
    }
  }

  printf("Hello World!\n");
  fclose(file);
  return 0;
}
