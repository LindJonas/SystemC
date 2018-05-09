#ifndef LIGHTS_H
#define LIGHTS_H

#include <systemc.h>


SC_MODULE(Light)
{
  sc_in<bool> control;
  bool green;

  SC_HAS_PROCESS(Light);
  Light(sc_module_name name);

  void change_lights();
};

#endif
