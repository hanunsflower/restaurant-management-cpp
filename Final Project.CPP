#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// ================= ENUMS =================
enum Category { FOOD = 1, DRINK, DESSERT };
enum FoodType { BREAKFAST = 1, LUNCH };
enum DrinkType { HOT = 1, COLD };
enum FastingType { FASTING = 1, NON_FASTING };

// ================= STRUCTURES =================
struct MenuItem {
    int id;
    string name;
    float price;
    int quantity;
    Category category;
    FoodType foodType;
    DrinkType drinkType;
    FastingType fastingType;
};

struct OrderItem {
    int orderId;
    int menuId;
    int quantity;
};

// ================= OWNER LOGIN =================
bool ownerLogin() {
    string password;
    int attempts = 3;
    while (attempts > 0) {
        cout << "Enter owner password: ";
        cin >> password;
        if (password == "owner123") {
            cout << "Access granted.\n";
            return true;
        } else {
            attempts--;
            cout << "Wrong password. Attempts left: " << attempts << endl;
        }
    }
    cout << "Access denied. Too many failed attempts.\n";
    return false;
}

// ================= ROLE SELECTION =================
int selectRole() {
    int choice;
    while (true) {
        cout << "\nSelect Role\n1. Owner\n2. Customer\nEnter choice: ";
        cin >> choice;
        if (choice == 1 || choice == 2) return choice;
        cout << "Invalid choice. Please enter 1 or 2.\n";
    }
}

// ================= FILE OPERATIONS =================
int loadMenu(MenuItem menu[]) {
    ifstream fin("menu.txt");
    int n = 0;
    if (!fin) return 0;

    int cat, fType, dType, fast;
    while (fin >> menu[n].id >> menu[n].price >> menu[n].quantity >> cat >> fType >> dType >> fast) {
        fin.ignore();
        getline(fin, menu[n].name);
        menu[n].category = static_cast<Category>(cat);
        menu[n].foodType = static_cast<FoodType>(fType);
        menu[n].drinkType = static_cast<DrinkType>(dType);
        menu[n].fastingType = static_cast<FastingType>(fast);
        n++;
    }
    fin.close();
    return n;
}

void saveMenu(MenuItem menu[], int n) {
    ofstream fout("menu.txt");
    for (int i = 0; i < n; i++) {
        fout << menu[i].id << " " << menu[i].price << " " << menu[i].quantity << " "
             << menu[i].category << " " << menu[i].foodType << " " << menu[i].drinkType << " " << menu[i].fastingType << endl;
        fout << menu[i].name << endl;
    }
    fout.close();
}

// ================= VIEW MENU =================
void viewMenu(MenuItem menu[], int n) {
    if (n == 0) {
        cout << "Menu is empty.\n";
        return;
    }

    // ---------- FOOD ----------
    cout << "\n--- FOOD ---\n";
    cout << "Breakfast\n";
    cout << "----------------------------------------------\n";

    int num = 1;
    for (int i = 0; i < n; i++) {
        if (menu[i].category == FOOD && menu[i].foodType == BREAKFAST) {
cout << "[" << menu[i].id << "] "
     << left << setw(18) << menu[i].name
     << " | " << setw(8)
     << (menu[i].fastingType == FASTING ? "Fasting" : "NonFast")
     << " | " << setw(6) << menu[i].price << " Birr"
     << " | Stock: " << menu[i].quantity << endl;

        }
    }

    cout << "Lunch\n";
    cout << "----------------------------------------------\n";

    num = 1;
    for (int i = 0; i < n; i++) {
        if (menu[i].category == FOOD && menu[i].foodType == LUNCH) {
cout << "[" << menu[i].id << "] "
     << left << setw(18) << menu[i].name
     << " | " << setw(8)
     << (menu[i].fastingType == FASTING ? "Fasting" : "NonFast")
     << " | " << setw(6) << menu[i].price << " Birr"
     << " | Stock: " << menu[i].quantity << endl;

        }
    }

    // ---------- DRINK ----------
    cout << "\n--- DRINK ---\n";
    cout << "----------------------------------------------\n";

    cout << "Hot\n";
    num = 1;
    for (int i = 0; i < n; i++) {
        if (menu[i].category == DRINK && menu[i].drinkType == HOT) {
cout << "[" << menu[i].id << "] "
     << left << setw(18) << menu[i].name
     << " | " << setw(8)
     << (menu[i].fastingType == FASTING ? "Fasting" : "NonFast")
     << " | " << setw(6) << menu[i].price << " Birr"
     << " | Stock: " << menu[i].quantity << endl;

        }
    }

    cout << "Cold\n";
    cout << "----------------------------------------------\n";

    num = 1;
    for (int i = 0; i < n; i++) {
        if (menu[i].category == DRINK && menu[i].drinkType == COLD) {
cout << "[" << menu[i].id << "] "
     << left << setw(18) << menu[i].name
     << " | " << setw(8)
     << (menu[i].fastingType == FASTING ? "Fasting" : "NonFast")
     << " | " << setw(6) << menu[i].price << " Birr"
     << " | Stock: " << menu[i].quantity << endl;

        }
    }

    // ---------- DESSERT ----------
    cout << "\n--- DESSERT ---\n";
    cout << "----------------------------------------------\n";

    num = 1;
    for (int i = 0; i < n; i++) {
        if (menu[i].category == DESSERT) {
cout << "[" << menu[i].id << "] "
     << left << setw(18) << menu[i].name
     << " | " << setw(8)
     << (menu[i].fastingType == FASTING ? "Fasting" : "NonFast")
     << " | " << setw(6) << menu[i].price << " Birr"
     << " | Stock: " << menu[i].quantity << endl;

        }
    }
}

// ================= SEARCH =================
int searchMenuById(MenuItem menu[], int n, int id) {
    for (int i = 0; i < n; i++)
        if (menu[i].id == id)
            return i;
    return -1;
}

// ================= ADD ITEM =================
void addMenuItem() {
    char choice;
    MenuItem menu[100];
    int n = loadMenu(menu);

    do {
        MenuItem item;
        cout << "Enter ID: ";
        cin >> item.id;

        if (searchMenuById(menu, n, item.id) != -1) {
            cout << "ID already exists!\n";
        } else {
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, item.name);
            cout << "Enter Price: ";
            cin >> item.price;
            cout << "Enter Quantity: ";
            cin >> item.quantity;

            cout << "Category (1-Food,2-Drink,3-Dessert): ";
            cin >> (int&)item.category;

            if (item.category == FOOD) {
                cout << "Food Type (1-Breakfast,2-Lunch): ";
                cin >> (int&)item.foodType;
            } else if (item.category == DRINK) {
                cout << "Drink Type (1-Hot,2-Cold): ";
                cin >> (int&)item.drinkType;
            }

            cout << "Fasting Type (1-Fasting,2-Non-Fasting): ";
            cin >> (int&)item.fastingType;

            menu[n++] = item;
            saveMenu(menu, n);

            cout << "Item added successfully.\n";
        }

        cout << "Add another item? (Y/N): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'Y' || choice == 'y');
}

// ================= UPDATE ITEM =================
void updateMenuItem() {
    MenuItem menu[100];
    int n = loadMenu(menu);

    int id;
    cout << "Enter ID to update: ";
    cin >> id;
    int idx = searchMenuById(menu, n, id);
    if (idx == -1) { cout << "Item not found.\n"; return; }

    cin.ignore();
    cout << "New Name: "; getline(cin, menu[idx].name);
    cout << "New Price: "; cin >> menu[idx].price;
    cout << "New Quantity: "; cin >> menu[idx].quantity;

    cout << "Category (1-Food,2-Drink,3-Dessert): "; cin >> (int&)menu[idx].category;
    if (menu[idx].category == FOOD) { cout << "Food Type (1-Breakfast,2-Lunch): "; cin >> (int&)menu[idx].foodType; }
    else if (menu[idx].category == DRINK) { cout << "Drink Type (1-Hot,2-Cold): "; cin >> (int&)menu[idx].drinkType; }

    cout << "Fasting Type (1-Fasting,2-Non-Fasting): "; cin >> (int&)menu[idx].fastingType;

    saveMenu(menu, n);
    cout << "Item updated.\n";
}

// ================= ORDER =================
int generateOrderId() {
    ifstream fin("orders.txt");
    int lastId = 100, id, mid, qty;
    if(fin){
        while(fin >> id >> mid >> qty) lastId = id;
    }
    fin.close();
    return lastId + 1;
}


// ================= CALCULATE TOTAL =================
float calculateTotal(int orderId, OrderItem order[], int orderCount, MenuItem menu[], int menuCount) {
    float total = 0;
    for (int i = 0; i < orderCount; i++) {
        if (order[i].orderId == orderId) {
            int idx = -1;
            for (int j = 0; j < menuCount; j++) {
                if (menu[j].id == order[i].menuId) {
                    idx = j;
                    break;
                }
            }
            if (idx != -1)
                total += order[i].quantity * menu[idx].price;
        }
    }
    return total;
}

int loadOrders(OrderItem order[]) {
    ifstream fin("orders.txt");
    int n = 0;
    if(!fin) return 0;
    while(fin >> order[n].orderId >> order[n].menuId >> order[n].quantity)
        n++;
    fin.close();
    return n;
}

// ================= GENERATE BILL =================
void generateBill(int orderId, OrderItem order[], int orderCount, MenuItem menu[], int menuCount) {
	OrderItem allOrders[500];
int totalOrders = loadOrders(allOrders);
float subtotal = calculateTotal(orderId, allOrders, totalOrders, menu, menuCount);

    float tax = subtotal * 0.05; // 5% tax
    float total = subtotal + tax;

    cout << "\n=====================================\n";
    cout << "           YOUR BILL                 \n";
    cout << "Order ID: " << orderId << endl;
    cout << "-------------------------------------\n";

for (int i = 0; i < totalOrders; i++) {
    if (allOrders[i].orderId == orderId)
 {
            int idx = -1;
            for (int j = 0; j < menuCount; j++)
                if (menu[j].id == allOrders[i].menuId) idx = j;

            if (idx != -1)
cout << left << setw(20) << menu[idx].name
     << " x " << setw(3) << allOrders[i].quantity
     << " = " << allOrders[i].quantity * menu[idx].price << " Birr\n";

        }
    }

    cout << "-------------------------------------\n";
    cout << "Subtotal: " << subtotal << endl;
    cout << "Tax (5%): " << tax << endl;
    cout << "Total: " << total << endl;
    cout << "=====================================\n";
    cout << "Thank you for your order!\n";
    cout << "Enjoy our service and have a great day!\n";
    cout << "=====================================\n";
}

// ================= PLACE ORDER  =================
void placeOrder() {
MenuItem menu[100];
int n = loadMenu(menu);

MenuItem menuCopy[100];          // CREATE ONCE
for(int i=0;i<n;i++) menuCopy[i] = menu[i];

OrderItem order[100];
int count = 0;


    if (n == 0) {
        cout << "Menu empty.\n";
        return;
    }

    int orderId = generateOrderId();
    char more;

    do {
        int id, qty;
        cout << "Enter Menu ID: ";
        cin >> id;

        int index = searchMenuById(menu, n, id);
        if (index == -1) {
            cout << "Invalid ID.\n";
            continue;
        }

        cout << "Enter Quantity: ";
        cin >> qty;

        if (qty > menu[index].quantity) {
            cout << "Not enough stock.\n";
            continue;
        }

        order[count++] = {orderId, id, qty};


        menu[index].quantity -= qty;

        cout << "Add more items? (Y/N): ";
        cin >> more;

    } while (more == 'Y' || more == 'y');

    if (count == 0) {
        cout << "No items ordered.\n";
        return;
    }

    char confirm;
    cout << "\nConfirm order? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        ofstream fout("orders.txt", ios::app);
        for (int i = 0; i < count; i++)
            fout << order[i].orderId << " " << order[i].menuId << " " << order[i].quantity << endl;
        fout.close();

        saveMenu(menu, n);
        cout << "Order saved successfully.\n";

        // CALL GENERATE BILL HERE
generateBill(orderId, order, count, menuCopy, n);
    } else {
        cout << "Order canceled.\n";
    }
}


// ================= FEEDBACK =================
void giveFeedback() {
    ofstream fout("feedback.txt", ios::app);
    cin.ignore(1000, '\n');

    string name, feedback; int rating;
    cout << "Enter your name: "; getline(cin, name);
    do { cout << "Rate (1-5): "; cin >> rating; } while (rating < 1 || rating > 5);
    cin.ignore(1000, '\n');

    cout << "Enter feedback: "; getline(cin, feedback);
    fout << "Customer: " << name << " | Rating: " << rating << " | Feedback: " << feedback << endl;
    fout.close();
    cout << "Thank you for your feedback!\n";
}

void viewFeedback() {
    ifstream fin("feedback.txt"); string line; int num = 1;
    if (!fin) { cout << "No feedback.\n"; return; }
    cout << "\n--- FEEDBACK ---\n";
    while (getline(fin, line)) cout << num++ << ". " << line << endl;
    fin.close();
}

// ================= MENUS =================
void ownerMenu() {
    int choice; MenuItem menu[100]; int n;
    do {
        cout << "\n--- OWNER MENU ---\n1.Add Item\n2.View Menu\n3.Update Item\n4.View Feedback\n0.Exit\nChoice: ";
        cin >> choice;
        switch(choice){
            case 1: addMenuItem(); break;
            case 2: n = loadMenu(menu); viewMenu(menu,n); break;
            case 3: updateMenuItem(); break;
          
            case 4: viewFeedback(); break;
            case 0: cout<<"Exiting Owner Menu.\n"; break;
            default: cout<<"Invalid choice.\n";
        }
    } while(choice!=0);
}

void customerMenu() {
    int choice;
    MenuItem menu[100];
    int n;

    do{
        n = loadMenu(menu);
        if(n==0){ cout<<"Menu is empty.\n"; return; }

        cout<<"\n--- CUSTOMER MENU ---\n1.View & Order\n2.Give Feedback\n0.Exit\nChoice: ";
        cin>>choice;

        switch(choice){
            case 1: viewMenu(menu,n); placeOrder(); break;
            case 2: giveFeedback(); break;
            case 0: cout<<"Thank you!\n"; break;
            default: cout<<"Invalid choice.\n";
        }
    } while(choice!=0);
}


// ================= MAIN =================
int main(){
    int role = selectRole();
    if(role==1){ if(ownerLogin()) ownerMenu(); }
    else customerMenu();
    return 0;
}
