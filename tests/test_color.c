// test_color.c
#include "color.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_write_color_black(void)
{
  char buf[64] = {0};
  FILE *f = fmemopen(buf, sizeof(buf), "w");
  assert(f != NULL);

  color c = {0.0, 0.0, 0.0};
  write_color(f, c);
  fclose(f); // flushes the buffer — required before reading buf

  assert(strcmp(buf, "0 0 0\n") == 0);
  printf("test_write_color_black passed\n");
}

void test_write_color_white(void)
{
  char buf[64] = {0};
  FILE *f = fmemopen(buf, sizeof(buf), "w");
  assert(f != NULL);

  // 1.0 * 255.999 truncates to 255 -- confirms the max end of the range
  color c = {1.0, 1.0, 1.0};
  write_color(f, c);
  fclose(f);

  assert(strcmp(buf, "255 255 255\n") == 0);
  printf("test_write_color_white passed\n");
}

void test_write_color_midtone(void)
{
  char buf[64] = {0};
  FILE *f = fmemopen(buf, sizeof(buf), "w");
  assert(f != NULL);

  // 0.5 * 255.999 = 127.9995, truncates to 127 -- catches an off-by-one
  // if someone later "fixes" this to round instead of truncate
  color c = {0.5, 0.5, 0.5};
  write_color(f, c);
  fclose(f);

  assert(strcmp(buf, "127 127 127\n") == 0);
  printf("test_write_color_midtone passed\n");
}

int main(void)
{
  test_write_color_black();
  test_write_color_white();
  test_write_color_midtone();
  printf("All color tests passed.\n");
  return 0;
}
