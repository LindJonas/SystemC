#include "lights.h"
#include <iostream>

using namespace std;

Light::Light(sc_module_name name) : sc_module(name)
{
  green = false;
  SC_METHOD(change_lights);
  dont_initialize();
  sensitive << control;
}

void Light::change_lights()
{
  green = control;
}
