#include "controller.h"
#include <iostream>


using namespace std;

Controller::Controller(sc_module_name name) : sc_module(name)
{

  // take back initialize();
  // also specify size in vector.

  for(int i = 0; i < nr_lights; i++)
  {
    //arrive[i].initialize(false);
    controls[i].write(false);//sc_signal<bool>("controls_" + c_str(i));
    waiting_cars[i] = 0;
    green[i] = false;
  }

  SC_METHOD(add_cars);
  dont_initialize();
  for(unsigned i=0; i < nr_lights; i++) // work?
    sensitive << arrive[i];



  SC_THREAD(control_lights);
}

void Controller::add_cars()
{
  for(int i = 0; i < nr_lights; i++)
  {
    if(arrive[i])
    {
      waiting_cars[i]++;
      // mabye signal that cars have arrived here!
    }
  }
}


void Controller::control_lights()
{
  int max_cars = 0;
  int current_max_direction = 0;
  int opposite_light = -1;

  while(1)
  {
    current_max_direction = -1;
    opposite_light = -1;

    for(int i = 0; i < nr_lights; i++)
    { // check what lane have the most cars in it.
      if(waiting_cars[i] > max_cars)
      {
	max_cars = waiting_cars[i];
	current_max_direction = i;
      }
    }

    if(current_max_direction != -1)
    {// if there is cars waiting somewhere
      green[current_max_direction] = true; // turn green on longest queue
      controls[current_max_direction] = true;

      opposite_light = (current_max_direction + 2) % 4;
      if (waiting_cars[opposite_light] > 0) // if opposite queue have cars waiting
      {
	green[opposite_light] = true; // let them pass aswell
	controls[opposite_light] = true;
      }

      for(int i = 0; i < 5; i++)
      {
	wait(1,SC_SEC);
	waiting_cars[current_max_direction]--; // wait 5 secounds and remove 5 cars periodically.
	if (green[opposite_light])
	  waiting_cars[opposite_light]--;
      }

      green[opposite_light] = false;
      controls[opposite_light] = false;

      green[current_max_direction] = false;
      controls[current_max_direction] = false;
    } // all lights turned off
  }
}

void Controller::print_method()
{
  // DONT FORGETTI THE TIMESTAMPI sc_time_stamp()
  cout << "#################################";
  cout << "Directions: N=0, W=1, S=2, E=3\n";
  cout << "Cars waiting:\n";

  for(int i = 0; i < nr_lights; i++)
    cout << sc_time_stamp << ": " << waiting_cars[i] << "Cars waiting at" << i << endl;;
  // PRINT CARS ARRIVING
  for(int i = 0; i < nr_lights; i++)
  {
    if(arrive[i].read())
      cout << sc_time_stamp << ": Car arrive at" << i << endl;
  }
  for(int i = 0; i < nr_lights; i++)
  {
    if(controls[i].read())
      cout << sc_time_stamp << ": Lights are ON at" << i << endl;
  }

}
