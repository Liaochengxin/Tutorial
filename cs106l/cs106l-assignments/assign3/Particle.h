//Copyright [2024] <Chengxin Liao>
#ifndef ASSIGN3_PARTICLE_H_
#define ASSIGN3_PARTICLE_H_

#include <string>
#include <cmath>
#include <vector>
#include <iostream>

class Particle {
  private:

    double mass;
    double energy;
    std::string* name;
    //double velocity;  //fraction of c

    double calMomentum() const{
        return std::sqrt(2*mass*energy);
    };

  public:

    //constructors
    Particle(); //default

    //parameter
    Particle(double m, double e, std::string* n); //by raw pointer
    Particle(double m, double e, const std::string& n); //Name by const ref (heap-allocates)

    //deconstructor
    ~Particle();

    //Copy constructor  
    Particle(const Particle& other);

    //Copy assigmnet operator 
    Particle& operator=(const Particle& other);

    //mv construtor
    Particle(Particle&& other);

    //mv assigment operator 
    Particle& operator=(Particle&& other);

    double getMass() const;  
    void setMass(double m); 

    double getEnergy() const; 
    void setEnergy(double e);

    std::string getName() const;
    void setName(std::string* n);

    double getMomentum() const{ return calMomentum(); }

    //other method
    //double getLorentzFactor() const;
    //void boost(double velocityChange );
    //double getMomentum() const;
    //void printinfo() const;
};

class ParticleVector : public std::vector<Particle>{
  public:
    //now it support the constructor for vector
    using std::vector<Particle>::vector;

    void Print_info();
};
#endif  //ASSIGN3_PARTICLE_H_
