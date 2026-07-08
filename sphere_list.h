#pragma once
#include "hit_record.h"
#include "ray.h"
#include "sphere.h"

typedef struct
{
  sphere *items;
  int count;
  int capacity;
} sphere_list;

sphere_list sphere_list_new(int capacity);
void sphere_list_add(sphere_list *list, sphere s);
_Bool sphere_list_hit(sphere_list list, ray r, double ray_tmin, double ray_tmax,
                      hit_record *rec);
void sphere_list_free(sphere_list *list);
