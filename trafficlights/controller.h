#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <systemc.h>


const int nr_lights = 4;

SC_MODULE(Controller)
{
  // arriving cars.
  // initialize of size 4.'
  // use standard vector.

  sc_in<bool> arrive[nr_lights];
  bool arrive_old[nr_lights];

  sc_out<bool> controls[nr_lights];

  //std::vector<sc_in<bool> > arrive(nr_lights);
  //std::vector<sc_out<bool> > controls(nr_lights);

  sc_event cars_waiting;

  bool green[nr_lights];
  int waiting_cars[nr_lights];

  //std::vector<bool> green(nr_lights);
  //std::vector<int> waiting_cars(nr_lights);
  // 0 = N, 1 = W, 2 = S, 3 = E.

  SC_HAS_PROCESS(Controller);
  Controller(sc_module_name name);

  void add_cars();
  void control_lights();
  void print_method();

};

#endif
