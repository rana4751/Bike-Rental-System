#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Define BikeModel and BikeRental structs
struct BikeModel {
    int model_id;
    int price;
};

struct BikeRental {
    vector<BikeModel> bike_models;
    int cheapest_price;
    int distance;
    bool emergency;
    bool membership;

    // Constructor
    BikeRental(vector<BikeModel> models, int price, int dist, bool emg, bool mem) : bike_models(models), cheapest_price(price), distance(dist), emergency(emg), membership(mem) {}

    // Comparison operator for sorting in sets
    bool operator<(const BikeRental &other) const {
        if (emergency != other.emergency)
            return emergency < other.emergency;
        if (cheapest_price != other.cheapest_price)
            return cheapest_price < other.cheapest_price;
        if (distance != other.distance)
            return distance < other.distance;
        return membership < other.membership;
    }
};

// Database initialization
set<BikeRental> addBikeRentals() {
    set<BikeRental> rental_database;

    vector<BikeModel> rental1_models = {{1, 10}, {2, 15}, {3, 20}, {33, 56}, {34, 67}, {44, 90}};
    rental_database.insert(BikeRental(rental1_models, 10, 5, false, false));

    vector<BikeModel> rental2_models = {{4, 12}, {3, 20}, {33, 56}, {34, 67}, {5, 18}, {6, 25}};
    rental_database.insert(BikeRental(rental2_models, 12, 8, true, true));

    vector<BikeModel> rental3_models = {{7, 9}, {8, 14}, {1, 10}, {34, 67}, {5, 18}, {9, 22}};
    rental_database.insert(BikeRental(rental3_models, 9, 6, false, true));

    // Add more rentals...
    vector<BikeModel> rental4_models = {{10, 11}, {8, 14}, {1, 10}, {34, 67}, {11, 16}, {12, 23}};
    rental_database.insert(BikeRental(rental4_models, 11, 7, true, false));

    vector<BikeModel> rental5_models = {{13, 13}, {14, 17}, {15, 24}};
    rental_database.insert(BikeRental(rental5_models, 13, 9, false, true));

    vector<BikeModel> rental6_models = {{16, 8}, {17, 13}, {18, 21}};
    rental_database.insert(BikeRental(rental6_models, 8, 4, true, false));

    vector<BikeModel> rental7_models = {{19, 14}, {20, 19}, {21, 26},{18, 21}};
    rental_database.insert(BikeRental(rental7_models, 14, 10, false, true));

    vector<BikeModel> rental8_models = {{22, 12}, {23, 17}, {24, 24}, {14, 17}, {15, 24}};
    rental_database.insert(BikeRental(rental8_models, 12, 8, true, false));

    vector<BikeModel> rental9_models = {{25, 11}, {26, 16}, {27, 23},{23, 17}, {24, 24}};
    rental_database.insert(BikeRental(rental9_models, 11, 7, false, true));

    vector<BikeModel> rental10_models = {{28, 13}, {29, 18}, {30, 25}};
    rental_database.insert(BikeRental(rental10_models, 13, 9, true, false));

    return rental_database;
}

// Find the best matching rental
BikeRental findBestMatch(const set<BikeRental> &database, int price, int distance, bool emergency, bool membership) {
    for (const auto &rental : database) {
        if (rental.cheapest_price <= price && rental.distance <= distance && rental.emergency == emergency && rental.membership == membership) {
            return rental; // Found a match
        }
    }
    // No matching rental found
    return BikeRental({}, -1, -1, false, false);
}

int main() {
    // Initialize the rental database
    set<BikeRental> rental_database = addBikeRentals();

    // User input for their requirements
    int user_price, user_distance;
    bool user_emergency, user_membership;
    cout << "ENTER YOUR REQUIREMENTS :\n";
    cout << "Price limit: ";
    cin >> user_price;
    cout << "Maximum distance: ";
    cin >> user_distance;
    cout << "Emergency (1 for yes, 0 for no): ";
    cin >> user_emergency;
    cout << "Membership (1 for yes, 0 for no): ";
    cin >> user_membership;

    // Find the best matching rental
    BikeRental best_match = findBestMatch(rental_database, user_price, user_distance, user_emergency, user_membership);

    // Display the best matching rental
    if (best_match.cheapest_price != -1) {
        cout << "\nBEST MATCHING RENTAL :\n";
        cout << "Cheapest price: " << best_match.cheapest_price << endl;
        cout << "Distance: " << best_match.distance << endl;
        cout << "Emergency available: " << (best_match.emergency ? "Yes" : "No") << endl;
        cout << "Membership required: " << (best_match.membership ? "Yes" : "No") << endl;
    } else {
        cout << "\nSorry matching rental is not found.\nTry for another specifications!\n";
    }

    return 0;
}
