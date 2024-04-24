#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Define BikeModel and BikeRental structs
struct BikeModel
{
    int model_id;
    int price;
};

struct BikeRental
{
    vector<BikeModel> bike_models;
    int cheapest_price;
    int distance;
    bool emergency;
    bool membership;

    // Constructor
    BikeRental(vector<BikeModel> models, int price, int dist, bool emg, bool mem) : bike_models(models), cheapest_price(price), distance(dist), emergency(emg), membership(mem) {}

    // Comparison operator for priority_queue
    
    bool operator<(const BikeRental &other) const
{
    if (emergency)
        return emergency < other.emergency; 
    if (cheapest_price > other.cheapest_price)
        return cheapest_price > other.cheapest_price; 
    if (distance > other.distance)
        return distance < other.distance; 
           return emergency < other.emergency; 
    return membership < other.membership; 
}
};
//Database
void addBikeRentals(priority_queue<BikeRental> &database)
{
    vector<BikeModel> rental1_models = {{1, 10}, {2, 15}, {3, 20}, {33, 56}, {34, 67}, {44, 90}};
    BikeRental rental1(rental1_models, 10, 5, false, false);

    vector<BikeModel> rental2_models = {{4, 12}, {3, 20}, {33, 56}, {34, 67}, {5, 18}, {6, 25}};
    BikeRental rental2(rental2_models, 12, 8, true, true);

    vector<BikeModel> rental3_models = {{7, 9}, {8, 14}, {1, 10}, {34, 67}, {5, 18}, {9, 22}};
    BikeRental rental3(rental3_models, 9, 6, false, true);

    vector<BikeModel> rental4_models = {{10, 11}, {8, 14}, {1, 10}, {34, 67}, {11, 16}, {12, 23}};
    BikeRental rental4(rental4_models, 11, 7, true, false);

    vector<BikeModel> rental5_models = {{13, 13}, {14, 17}, {15, 24}};
    BikeRental rental5(rental5_models, 13, 9, false, true);

    vector<BikeModel> rental6_models = {{16, 8}, {17, 13}, {18, 21}};
    BikeRental rental6(rental6_models, 8, 4, true, false);

    vector<BikeModel> rental7_models = {{19, 14}, {20, 19}, {21, 26},{18, 21}};
    BikeRental rental7(rental7_models, 14, 10, false, true);

    vector<BikeModel> rental8_models = {{22, 12}, {23, 17}, {24, 24}, {14, 17}, {15, 24}};
    BikeRental rental8(rental8_models, 12, 8, true, false);

    vector<BikeModel> rental9_models = {{25, 11}, {26, 16}, {27, 23},{23, 17}, {24, 24}};
    BikeRental rental9(rental9_models, 11, 7, false, true);

    vector<BikeModel> rental10_models = {{28, 13}, {29, 18}, {30, 25}};
    BikeRental rental10(rental10_models, 13, 9, true, false);

    // Add rentals to the database
    database.push(rental1);
    database.push(rental2);
    database.push(rental3);
    database.push(rental4);
    database.push(rental5);
    database.push(rental6);
    database.push(rental7);
    database.push(rental8);
    database.push(rental9);
    database.push(rental10);
}
BikeRental findBestMatch(priority_queue<BikeRental> &database, int price, int distance, bool emergency, bool membership)
{
    vector<BikeRental> temp; 
    while (!database.empty())
    {
        BikeRental top_rental = database.top();
        database.pop(); 
        // Check if the rental meets the user's requirements
        if (top_rental.cheapest_price <= price &&
            top_rental.distance <= distance &&
            top_rental.emergency == emergency &&
            top_rental.membership == membership)
        {
            // Push back all popped elements to maintain the original priority queue to maintain database
            for (const auto &rental : temp)
            {
                database.push(rental);
            }
            return top_rental; // Found a match
        }
        temp.push_back(top_rental);
    }
    // No matching rental found
    // Push back all popped elements to maintain the original priority queue
    for (const auto &rental : temp)
    {
        database.push(rental);
    }
    // Return a default rental with empty attributes
    return BikeRental({}, -1, -1, false, false);
}
int main()
{
    // Create a priority queue to store bike rentals
    priority_queue<BikeRental> rental_database;
    // Add bike rentals to the database
    addBikeRentals(rental_database);
    // User input for their requirements
    int user_price, user_distance;
    bool user_emergency, user_membership;
    system("COLOR 46");
    cout<<"\t\t\t\n"<<endl;
    cout<<"\t\t\t\t\t ---- WELCOME TO BIKE RENTAL SYSTEM ----"<<endl;
    cout<<"\t\t\t\t\t\t\n"<<endl;
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
    if (best_match.cheapest_price != -1)
    {
        cout << "\nBEST MATCHING RENTAL :\n";
        cout << "Cheapest price: " << best_match.cheapest_price << endl;
        cout << "Distance: " << best_match.distance << endl;
        cout << "Emergency available: " << (best_match.emergency ? "Yes" : "No") << endl;
        cout << "Membership required: " << (best_match.membership ? "Yes" : "No") << endl;
    }
    else
    {
        cout << "Sorry matching rental is not found.\nTry for another specifications!\n";
    }
    return 0;
}
