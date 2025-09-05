/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include <iostream>
#include "Particle.h"
#include <string>

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  double m_e = 9.1093837e-31;
  double electronRestEnergy = 8.187e-14;
  std::string name = "ELECTRON";
  Particle ELECTRON(m_e, electronRestEnergy, name);
  std::cout << "Electron at Rest:" << std::endl;
  std::cout << "Name: " << ELECTRON.getName() << std::endl;
  std::cout << "Mass: " << ELECTRON.getMass() << " kg" << std::endl;
  std::cout << "Energy:"<< ELECTRON.getEnergy() << " J" << std::endl;
}
