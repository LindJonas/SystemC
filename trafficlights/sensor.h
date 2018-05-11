#ifndef SENSOR_H
#define SENSOR_H

#include <systemc.h>

SC_MODULE(Sensor)
{
  sc_out<bool> car_arrive;

  SC_HAS_PROCESS(Sensor);
  Sensor(sc_module_name name);

  int random(int,int);
  void generate_output();

};

#endif
