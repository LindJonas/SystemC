#include "lights.h"
#include <iostream>

using namespace std;



Light::Light(sc_module_name name) : sc_module(name)
{
  cout << "A";
  green = false;
  //green.initialize(false);
  cout << "B";
  SC_METHOD(change_lights);
  cout << "C";
  dont_initialize();
  cout << "D";
  sensitive << control;
  cout << "E";
}
// Light::
void Light::change_lights()
{
  green = control;
  cout << "light allows passing: " << green << endl;
}
