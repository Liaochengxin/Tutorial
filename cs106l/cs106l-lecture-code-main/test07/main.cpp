#include <iostream>
//#include "Particle.h"

//int main() {
//    // Create a Particle object
//    Particle tau(50.0);  // A tau with pt = 50 GeV
//
//    // Access pt using the public getter (this works)
//    std::cout << "Tau pt (via getter): " << tau.getPt() << " GeV" << std::endl;
//
//    // Modify pt using the public setter (this works)
//    tau.setPt(75.0);
//    std::cout << "Tau pt (after setter): " << tau.getPt() << " GeV" << std::endl;
//
//    // Try to access pt directly (this will cause a compilation error)
//    std::cout << "Tau pt (direct access): " << tau.pt << " GeV" << std::endl;
//
//    // Try to modify pt directly (this will also cause a compilation error)
//    tau.pt = 100.0;
//
//    return 0;
//}

void counter() {
    static int count = 0;  // Static local variable
    int count2 = 0;
    count++;
    count2++;
    std::cout << "Count: " << count << "\n";
    std::cout << "Count: " << count2 << "\n";
}

int main() {
    counter();  // Outputs: Count: 1
    counter();  // Outputs: Count: 2
    counter();  // Outputs: Count: 3
    return 0;
}
