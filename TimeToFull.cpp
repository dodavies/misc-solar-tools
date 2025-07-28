#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <percent_per_hour> <current_percent>\n";
        return 1;
    }

    // Parse inputs
    double chargeRate = std::atof(argv[1]);
    double currentLevel = std::atof(argv[2]);

    if (chargeRate <= 0 || currentLevel < 0 || currentLevel > 100) {
        std::cerr << "Error: Invalid inputs.\n"
                  << " - charge rate must be > 0\n"
                  << " - current level must be between 0 and 100\n";
        return 1;
    }

    // Calculate time left
    double remainingPercent = 100.0 - currentLevel;
    double hoursLeft = remainingPercent / chargeRate;
    int fullHours = static_cast<int>(hoursLeft);
    int minutes = static_cast<int>((hoursLeft - fullHours) * 60);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Charging at " << chargeRate << "% per hour.\n";
    std::cout << "Current charge level: " << currentLevel << "%\n";
    std::cout << "Time left to full charge: " << fullHours << " hours and " << minutes << " minutes.\n";

    return 0;
}
