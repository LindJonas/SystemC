#include "sensor.h"
#include <stdlib.h>

using namespace std;


Sensor::Sensor(sc_module_name name) : sc_module(name)
{
  SC_THREAD(generate_output);
  car_arrive.initialize(false);
}

int Sensor::random(int min, int max)
{
  static bool first = true;
  if (first)
  {
    srand(time(NULL));
    first = false;
  }
  return min + rand() % (( max + 1) - min);
}
void Sensor::generate_output()
{
  for(;;)
  {
    // wait random time from 0 - 5 then arrive new car.
    // turn signal on
    // turn signal off.
    //cout << "test + \n";

    wait(random(3,6),SC_SEC);
    car_arrive -> write(true);
    wait(0.1, SC_SEC);
    car_arrive -> write(false);
    // should be turned off by signal form controller.
//    wait(0.5,SC_SEC);
    //   car_arrive -> write(false);
  }
}
