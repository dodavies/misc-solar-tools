#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

// Helper to calculate duration between two times in HHMM format
double calculate_hours(int start, int end) {
    int start_hour = start / 100;
    int start_min = start % 100;
    int end_hour = end / 100;
    int end_min = end % 100;

    double start_total = start_hour + start_min / 60.0;
    double end_total = end_hour + end_min / 60.0;

    if (end_total >= start_total) {
        return end_total - start_total;
    } else {
        return (24.0 - start_total) + end_total;  // crosses midnight
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Solar Savings Calculator\n";
        std::cout << "-------------------------\n";
        std::cout << "Estimates savings from solar generation and battery use.\n\n";
        std::cout << "Inputs required:\n";
        std::cout << "  <daily_usage_kWh>       e.g. 20\n";
        std::cout << "  <daily_solar_kWh>       e.g. 60\n";
        std::cout << "  <daily_battery_use_kWh> e.g. 20\n";
        std::cout << "\nBuilt-in values:\n";
        std::cout << "  high_rate_pence  = 29\n";
        std::cout << "  low_rate_pence   = 7\n";
        std::cout << "  export_rate_pence = 15\n";
        std::cout << "  low rate hours    = 23:30–05:30\n";
        std::cout << "\nExample usage:\n";
        std::cout << "  " << argv[0] << " 20 60 20\n";
        return 0;
    }

    if (argc != 4) {
        std::cout << "Error: Expected 3 arguments.\n";
        std::cout << "Usage: " << argv[0] << " <daily_usage_kWh> <daily_solar_kWh> <daily_battery_use_kWh>\n";
        return 1;
    }

// Parse user inputs
    double daily_usage = std::stod(argv[1]);
    double daily_solar = std::stod(argv[2]);
    double daily_battery = std::stod(argv[3]);

    // Built-in rate values
    double high_rate = 29.0 / 100.0;
    double low_rate = 7.0 / 100.0;
    double export_rate = 15.0 / 100.0;

    // Built-in time window: 23:30 to 05:30
    int low_start = 2330;
    int low_end = 530;

    // Time split
    double low_hours = calculate_hours(low_start, low_end);
    double high_hours = 24.0 - low_hours;

    double usage_per_hour = daily_usage / 24.0;
    double low_usage = usage_per_hour * low_hours;
    double high_usage = usage_per_hour * high_hours;

    // Solar & battery logic
    double self_consumed_solar = std::min(daily_solar, high_usage);
    double battery_used = std::min(daily_battery, high_usage - self_consumed_solar);
    double excess_solar = std::max(0.0, daily_solar - (self_consumed_solar + battery_used));

    // Savings calculations
    double saving_from_self = self_consumed_solar * high_rate;
    double saving_from_battery = battery_used * (high_rate - low_rate);
    double export_earnings = excess_solar * export_rate;

    double total_daily_benefit = saving_from_self + saving_from_battery + export_earnings;
    double annual_benefit = total_daily_benefit * 365;

    // Output
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Low rate period: " << low_start << " to " << low_end << " (" << low_hours << " hrs)\n\n";

    std::cout << "Inputs:\n";
    std::cout << "  Daily usage:         " << daily_usage << " kWh\n";
    std::cout << "  Solar generation:    " << daily_solar << " kWh\n";
    std::cout << "  Battery usage:       " << daily_battery << " kWh\n\n";

    std::cout << "Rates:\n";
    std::cout << "  High rate:           £" << high_rate << " /kWh (built-in)\n";
    std::cout << "  Low rate:            £" << low_rate << " /kWh (built-in)\n";
    std::cout << "  Export rate:         £" << export_rate << " /kWh (built-in)\n\n";

    std::cout << "Calculated usage:\n";
    std::cout << "  High rate usage:     " << high_usage << " kWh\n";
    std::cout << "  Low rate usage:      " << low_usage << " kWh\n";
    std::cout << "  Self-consumed solar: " << self_consumed_solar << " kWh\n";
    std::cout << "  Battery used:        " << battery_used << " kWh\n";
    std::cout << "  Exported solar:      " << excess_solar << " kWh\n\n";

    std::cout << "Savings and earnings:\n";
    std::cout << "  Savings from solar:  £" << saving_from_self << "\n";
    std::cout << "  Battery savings:     £" << saving_from_battery << "\n";
    std::cout << "  Export earnings:     £" << export_earnings << "\n\n";

    std::cout << "Total daily benefit:   £" << total_daily_benefit << "\n";
    std::cout << "Estimated annual benefit: £" << annual_benefit << "\n";

    return 0;
}
