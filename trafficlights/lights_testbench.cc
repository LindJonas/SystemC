#include <systemc.h>
#include "lights.h"
#include "controller.h"
#include "sensor.h"
#include <iostream>
#include <string>
#include <fstream>


int sc_main(int argc, char **argv)
{
// The command-line arguments are as follows:
// 1. the simulation time (in seconds),
// 2. the file with input data (see input.txt), and
// 3. the file to write output data.

  cout << "\n";

  if(argc != 2)
  {
    cout << "Run with [simulationtime]\n";
    exit(1);
  }
  cout << "set sim time...";
  sc_time sim_time(atof(argv[1]), SC_SEC);
  cout << " done\n";

// Create channels.

  cout << "create channels...";

  sc_signal<bool> car_arrive_N;
  sc_signal<bool> car_arrive_W;
  sc_signal<bool> car_arrive_S;
  sc_signal<bool> car_arrive_E;

  sc_signal<bool> sig_control_N;
  sc_signal<bool> sig_control_W;
  sc_signal<bool> sig_control_S;
  sc_signal<bool> sig_control_E;


  car_arrive_N = false;
  car_arrive_W = false;
  car_arrive_S = false;
  car_arrive_E = false;

  sig_control_N = false;
  sig_control_W = false;
  sig_control_S = false;
  sig_control_E = false;

  cout << " Done\n";

//  sc_signal<sc_uint<3> > o[4];

// Instantiate modules.

  cout << "create lights...";

  Light light_N("Light_N");
  cout << "1...";
  Light light_S("Light_S");
  cout << "2...";
  Light light_W("Light_W");
  cout << "3...";
  Light light_E("Light_E");
  cout << "4...";

  cout << " Done\n";

  cout << "create controller...";

  Controller controller("Controller");

  cout << " Done\n";

  cout << "create sensors...\n";
  Sensor sensor_N("Sensor_N");
  cout << "1...";
  Sensor sensor_S("Sensor_S");
  cout << "2...";
  Sensor sensor_W("Sensor_W");
  cout << "3...";
  Sensor sensor_E("Sensor_E");
  cout << "4...";
  cout << " Done\n";
// Connect the channels to the ports.

  cout << "connect lights...";

  light_N(sig_control_N);
  cout << "1...";
  light_W(sig_control_W);
  cout << "2...";
  light_S(sig_control_S);
  cout << "3...";
  light_E(sig_control_E);
  cout << "4...";

  cout << " Done\n";

  cout << "connect sensors...";
  sensor_N(car_arrive_N);
  cout << "1...";
  sensor_W(car_arrive_W);
  cout << "2...";
  sensor_S(car_arrive_S);
  cout << "3...";
  sensor_E(car_arrive_E);
  cout << "4...";
  cout << " Done\n";


  cout << "connect controller...";

  controller(car_arrive_N,car_arrive_W,car_arrive_S,car_arrive_E,
	     sig_control_N,sig_control_W,sig_control_S,sig_control_E);

  cout << " Done\n";

  cerr << "#############" << "[start simulation]" << "###############\n";

  sc_start(sim_time);

return 0;
}
