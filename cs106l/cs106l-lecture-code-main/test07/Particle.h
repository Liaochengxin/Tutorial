#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
private:
    float pt;  // Private: Transverse momentum of the particle

public:
    Particle(float pt_value);  // Constructor
    float getPt() const;       // Public getter to access pt
    void setPt(float pt_value); // Public setter to modify pt
};

#endif // PARTICLE_H
