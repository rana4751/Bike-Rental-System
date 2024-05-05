#include <iostream>
#include <vector>
#include <cmath> // For pow function
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

    // Comparison operator for BikeRental struct
    bool operator<(const BikeRental &other) const {
        if (emergency != other.emergency)
            return emergency;
        if (cheapest_price != other.cheapest_price)
            return cheapest_price < other.cheapest_price;
        if (distance != other.distance)
            return distance < other.distance;
        return membership < other.membership;
    }
};

// Define Node for linked list
struct Node {
    BikeRental data;
    Node* parent;
    vector<Node*> children;

    // Constructor
    Node(BikeRental rental) : data(rental), parent(nullptr) {}
};

class D_aryHeap {
private:
    int d; // Degree of the heap
    Node* root; // Root of the heap
    vector<Node*> heap; // Vector to hold pointers to nodes

public:
    // Constructor
    D_aryHeap(int degree) : d(degree), root(nullptr) {}

    // Insert a rental into the heap
    void insert(const BikeRental& rental) {
        Node* newNode = new Node(rental);
        heap.push_back(newNode);
        if (!root) {
            root = newNode;
        } else {
            Node* parent = heap[(heap.size() - 2) / d]; // Calculate parent index
            parent->children.push_back(newNode);
            newNode->parent = parent;
            bubbleUp(newNode); // Maintain heap property
        }
    }

    // Bubble up the newly inserted node to maintain heap property
    void bubbleUp(Node* node) {
        while (node->parent && ((node->data) < (node->parent->data))) {
            swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    // Find the best matching rental
    BikeRental findBestMatch(int price, int distance, bool emergency, bool membership) {
        return findBestMatchHelper(root, price, distance, emergency, membership);
    }

    // Recursive helper function to find the best matching rental
    BikeRental findBestMatchHelper(Node* node, int price, int distance, bool emergency, bool membership) {
        if (!node) return BikeRental({}, -1, -1, false, false); // Empty node

        BikeRental bestMatch = BikeRental({}, -1, -1, false, false);
        if (node->data.cheapest_price <= price && node->data.distance <= distance && node->data.emergency == emergency && node->data.membership == membership) {
            bestMatch = node->data;
        }

        for (Node* child : node->children) {
            BikeRental childMatch = findBestMatchHelper(child, price, distance, emergency, membership);
            if (childMatch.cheapest_price != -1 && (bestMatch.cheapest_price == -1 || childMatch.cheapest_price < bestMatch.cheapest_price)) {
                bestMatch = childMatch;
            }
        }
        return bestMatch;
    }
};

// Database initialization
void addBikeRentals(D_aryHeap& database) {
    vector<BikeModel> rental1_models = {{1, 10}, {2, 15}, {3, 20}, {33, 56}, {34, 67}, {44, 90}};
    database.insert(BikeRental(rental1_models, 10, 5, false, false));

    vector<BikeModel> rental2_models = {{4, 12}, {3, 20}, {33, 56}, {34, 67}, {5, 18}, {6, 25}};
    database.insert(BikeRental(rental2_models, 12, 8, true, true));

    vector<BikeModel> rental3_models = {{7, 9}, {8, 14}, {1, 10}, {34, 67}, {5, 18}, {9, 22}};
    database.insert(BikeRental(rental3_models, 9, 6, false, true));

    // Add more rentals...
}

int main() {
    // Create a D-ary heap to store bike rentals
    int d = 2; // Change d for different degree of heap
    D_aryHeap rental_database(d);

    // Add bike rentals to the database
    addBikeRentals(rental_database);

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
    BikeRental best_match = rental_database.findBestMatch(user_price, user_distance, user_emergency, user_membership);

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
