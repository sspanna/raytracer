#include "sphere_list.h"
#include "interval.h"
#include <stdio.h>
#include <stdlib.h>

sphere_list sphere_list_new(int capacity)
{
  sphere_list list;
  list.items = malloc(sizeof(sphere) * capacity);
  if (list.items == NULL)
  {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  list.count = 0;
  list.capacity = capacity;
  return list;
}

void sphere_list_add(sphere_list *list, sphere s)
{
  if (list->count >= list->capacity)
  {
    fprintf(stderr, "sphere list full\n");
    exit(1);
  }
  list->items[list->count] = s;
  list->count += 1;
}

void sphere_list_free(sphere_list *list)
{
  free(list->items);
  list->items = NULL;
  list->count = 0;
  list->capacity = 0;
}

_Bool sphere_list_hit(sphere_list list, ray r, interval ray_t, hit_record *rec)
{
  hit_record current_rec;
  _Bool hit_anything = 0;
  double closest_t = ray_t.max;

  for (int i = 0; i < list.count; i++)
  {
    sphere s = list.items[i];
    if (sphere_hit(s, r, (interval){ray_t.min, closest_t}, &current_rec))
    {
      hit_anything = 1;
      closest_t = current_rec.t;
      *rec = current_rec;
    }
  }
  return hit_anything;
}
