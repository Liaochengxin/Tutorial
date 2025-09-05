#include "Particle.h"
#include <cmath>
#include <string>

//default Particle
////new stand for allocate at heap
Particle::Particle(): mass(0.0), energy(0.0), name(nullptr) {};
// paramter
Particle::Particle(double m, double e, std::string* n): mass(m), energy(e), name(n){};
Particle::Particle(double m, double e, const std::string& n) : mass(m), energy(e), name(new std::string(n)){};

//deconstructor
Particle::~Particle() {
  delete name;
};
//copy constructor 
Particle::Particle(const Particle& other): mass(other.mass), energy(other.energy), name(other.name ? new std::string(*other.name):nullptr){
};
//copy assigment operator 
Particle &Particle::operator=(const Particle& other){
  if(this != &other){
    
    mass = other.getMass();
    energy = other.getEnergy();

    delete name;

    name = other.name;
  }
  return *this;
};

//mv constructor
Particle::Particle(Particle&& other) : mass(other.mass), energy(other.energy), name(other.name ? new std::string(*other.name):nullptr){
  other.name=nullptr;
};

//mv assignment operator 
Particle &Particle::operator=(Particle&& other){
  if(this != &other){
    mass = other.mass;
    energy = other.energy;
    delete name;
    name = other.name ? new std::string(*other.name) : nullptr;
    other.name=nullptr;
  }
  return *this;
};

double Particle::getMass() const {
  return mass;
};

void Particle::setMass(double m){
  mass = m;
};

double Particle::getEnergy() const{
  return energy;
};

void Particle::setEnergy(double e) {
  energy = e;
};

std::string Particle::getName() const{
  if (name == nullptr){
    return "UNKNOWN";
  }

  return *name;
};

void Particle::setName(std::string* n){
  name = n;
};

void ParticleVector::Print_info() {
  for (const auto& p : *this){
    std::cout << "Particle name is " << p.getName() << std::endl;
  }
};
