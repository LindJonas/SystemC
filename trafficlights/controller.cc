#include "controller.h"
#include <iostream>


using namespace std;

Controller::Controller(sc_module_name name) : sc_module(name)
{

  // take back initialize();
  // also specify size in vector.

  for(int i = 0; i < nr_lights; i++)
  {
    cout << i << "...";
    //arrive[i].initialize(false);
    controls[i].initialize(false);
    waiting_cars[i] = 0;
    green[i] = false;
    arrive_old[i] = false;
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
    if(!arrive_old[i] && arrive[i])
    {
      waiting_cars[i]++;
      cerr << "Added car, direction: " << dirConvert(i)  << " \n";
      // mabye signal that cars have arrived here!
    }
    arrive_old[i] = arrive[i];
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
      print_method();
      //since cars have arived and are waiting print light status.
      green[current_max_direction] = true; // turn green on longest queue
      controls[current_max_direction] = true;
      cerr << "Green on: " << dirConvert(current_max_direction) << "\n";
      opposite_light = (current_max_direction + 2) % 4;

      for(int i = 0; i < 5; i++)
      {
	wait(1,SC_SEC);

	if (waiting_cars[opposite_light] > 0) // if opposite queue have cars waiting
	{
	  if (green[opposite_light] == false)
	    cerr << "Green on: " << dirConvert(opposite_light) << "\n";
	  green[opposite_light] = true; // let them pass aswell
	  controls[opposite_light] = true;

	}

	if (waiting_cars[current_max_direction] > 0)
	{
	  waiting_cars[current_max_direction]--;
	  cerr << "Car drives past from: " << dirConvert(current_max_direction) << " (Max direction)\n";
	}

	if (green[opposite_light])
	  if (waiting_cars[opposite_light] > 0)
	  {
	    waiting_cars[opposite_light]--;
	    cerr << "Car drives past from: " << dirConvert(opposite_light) << " (Opposite)\n";
	  }
      }

      green[opposite_light] = false;
      controls[opposite_light] = false;
      cerr << "Red on: " << dirConvert(opposite_light) << "\n";

      green[current_max_direction] = false;
      controls[current_max_direction] = false;
      cerr << "Red on: " << dirConvert(current_max_direction) << "\n";
    } // all lights turned off
    else
    {
      //print_method();
      wait(0.2,SC_SEC);
    }
  }
}

void Controller::print_method()
{
  cerr << "======================================\n"
       << "Cars waiting:\n";
  for(int i = 0; i < nr_lights; i++)
    cerr << waiting_cars[i] << " Cars waiting at: " << dirConvert(i) << endl;
  cerr << "======================================\n";
}

string Controller::dirConvert(const int dir)
{
  if (dir == 0)
    return "North";
  else if (dir == 1)
    return "West";
  else if (dir == 2)
    return "South";
  else if (dir == 3)
    return "East";
  else
    return "Invalid direction!!";
}
