#include <iostream>
#include <vector>
#include <cmath>
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

// Define Node for Splay Tree
struct Node {
    BikeRental data;
    Node* left;
    Node* right;

    // Constructor
    Node(BikeRental rental) : data(rental), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;

    // Rotations
    void rotateLeft(Node* &node) {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node = temp;
    }

    void rotateRight(Node* &node) {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node = temp;
    }

public:
    // Constructor
    SplayTree() : root(nullptr) {}

    // Insert a rental into the Splay Tree
    void insert(const BikeRental& rental) {
        insertHelper(root, rental);
    }

    void insertHelper(Node* &node, const BikeRental& rental) {
        if (!node) {
            node = new Node(rental);
            return;
        }
        if (rental < node->data) {
            insertHelper(node->left, rental);
            rotateRight(node);
        } else {
            insertHelper(node->right, rental);
            rotateLeft(node);
        }
    }

    // Find the best matching rental
    BikeRental findBestMatch(int price, int distance, bool emergency, bool membership) {
        root = findBestMatchHelper(root, price, distance, emergency, membership);
        return root ? root->data : BikeRental({}, -1, -1, false, false);
    }

    Node* findBestMatchHelper(Node* node, int price, int distance, bool emergency, bool membership) {
        if (!node) return nullptr;

        if (node->data.cheapest_price <= price && node->data.distance <= distance && node->data.emergency == emergency && node->data.membership == membership) {
            return node;
        }

        if (node->data < BikeRental({}, price, distance, emergency, membership)) {
            Node* temp = findBestMatchHelper(node->right, price, distance, emergency, membership);
            if (temp) {
                rotateLeft(node);
                return temp;
            }
        } else {
            Node* temp = findBestMatchHelper(node->left, price, distance, emergency, membership);
            if (temp) {
                rotateRight(node);
                return temp;
            }
        }
        return nullptr;
    }
};

// Database initialization
void addBikeRentals(SplayTree& database) {
    vector<BikeModel> rental1_models = {{1, 10}, {2, 15}, {3, 20}, {33, 56}, {34, 67}, {44, 90}};
    database.insert(BikeRental(rental1_models, 10, 5, false, false));

    vector<BikeModel> rental2_models = {{4, 12}, {3, 20}, {33, 56}, {34, 67}, {5, 18}, {6, 25}};
    database.insert(BikeRental(rental2_models, 12, 8, true, true));

    vector<BikeModel> rental3_models = {{7, 9}, {8, 14}, {1, 10}, {34, 67}, {5, 18}, {9, 22}};
    database.insert(BikeRental(rental3_models, 9, 6, false, true));

}

int main() {
    // Create a Splay Tree to store bike rentals
    SplayTree rental_database;

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
