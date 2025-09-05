/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include <iostream>
#include "Particle.h"
#include <string>

int main() {
  // STUDENT TODO: Construct an instance of your class!
  // these code is tested for pointer
  //double m_e = 9.1093837e-31;
  //double electronRestEnergy = 8.187e-14;
  //std::string name = "ELECTRON";
  //Particle ELECTRON(m_e, electronRestEnergy, name);
  //Particle electronCopy = ELECTRON;

  //std::cout << "Electron at Rest:" << std::endl;
  //std::cout << "Name: " << ELECTRON.getName() << std::endl;
  //std::cout << "Mass: " << ELECTRON.getMass() << " kg" << std::endl;
  //std::cout << "Energy:"<< ELECTRON.getEnergy() << " J" << std::endl;
  //std::cout << "Momentum:"<< ELECTRON.getMomentum() << " J" << std::endl;
  //return 0;
  //
  // these code is tested for container
  Particle p1(1.0, 2.0, "ELECTRON");
  Particle p2(2.0, 4.0, "PROTON");
  Particle p3(1.0, 2.0, "ELECTRON");

  ParticleVector particlevector;
  particlevector.push_back(p1); //copy and send
  particlevector.emplace_back(p2); //just send
  
  //particlevector.Print_info();
  //access element    
  //std::cout << "Particle name is " << particlevector[0].getName() << std::endl;
  //std::cout << "Particle name is " << particlevector.at(1).getName() << std::endl;
  //insertion or remove
  auto it = particlevector.begin() + 1;
  particlevector.insert(it, Particle(5.0, 6.0, new std::string("Neutron")));
  
  particlevector.Print_info();
  



 return 0;
}
