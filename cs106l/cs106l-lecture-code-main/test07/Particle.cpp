#include "Particle.h"

Particle::Particle(float pt_value) {
    pt = pt_value;  // Constructor can access private pt
}

float Particle::getPt() const {
    return pt;  // Getter can access private pt
}

void Particle::setPt(float pt_value) {
    if (pt_value >= 0) {  // Ensure pt is non-negative
        pt = pt_value;  // Setter can access private pt
    }
}
