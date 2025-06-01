#include "UGManager.h"
#include "FileUtils.h"
#include "FilePaths.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


UGManager::UGManager() {}
UGManager::~UGManager() {}

void UGManager::showMenu() {
    int choice;
    do {
        cout << "\n=== University General Management ===\n"
            << "[1] Events Management\n"
            << "[2] Notice Board\n"
            << "[3] Library Management\n"
            << "[4] Sports Complex\n"
            << "[5] Hostel Info\n"
            << "[6] Labs Management\n"
            << "[7] Transport Info\n"
            << "[8] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: manageEvents(); break;
        case 2: manageNoticeBoard(); break;
        case 3: manageLibrary(); break;
        case 4: manageSportsComplex(); break;
        case 5: manageHostelInfo(); break;
        case 6: manageLabs(); break;
        case 7: manageTransport(); break;
        case 8: break;
        default: showError("Invalid option.");
        }
    } while (choice != 8);
}

// ================= EVENTS =====================

void UGManager::manageEvents() {
    int choice;
    do {
        cout << "\n--- Events Management ---\n"
            << "[1] Add Event\n"
            << "[2] View Events\n"
            << "[3] Edit Event\n"
            << "[4] Delete Event\n"
            << "[5] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addEvent(); break;
        case 2: viewEvents(); break;
        case 3: editEvent(); break;
        case 4: deleteEvent(); break;
        case 5: break;
        default: showError("Invalid option.");
        }
    } while (choice != 5);
}

void UGManager::addEvent() {
    auto events = readCSV(EVENTS_FILE);
    map<string, string> event;
    string id, name, date, venue;
    cout << "Enter Event ID: ";
    getline(cin, id);
    if (any_of(events.begin(), events.end(), [&](auto& e) { return e.at("ID") == id; })) {
        showError("Event ID already exists.");
        return;
    }
    cout << "Enter Event Name: ";
    getline(cin, name);
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter Venue: ";
    getline(cin, venue);
    event["ID"] = id; event["Name"] = name; event["Date"] = date; event["Venue"] = venue;
    events.push_back(event);
    writeCSV(EVENTS_FILE, events);
    cout << "Event added.\n";
}

void UGManager::viewEvents() {
    auto events = readCSV(EVENTS_FILE);
    if (events.empty()) { cout << "No events found.\n"; return; }
    cout << "\nEvents:\n";
    for (auto& e : events)
        cout << "ID: " << e["ID"] << ", Name: " << e["Name"] << ", Date: " << e["Date"] << ", Venue: " << e["Venue"] << "\n";
}

void UGManager::editEvent() {
    auto events = readCSV(EVENTS_FILE);
    if (events.empty()) { showError("No events."); return; }
    string id;
    cout << "Enter Event ID to edit: ";
    getline(cin, id);
    auto it = find_if(events.begin(), events.end(), [&](auto& e) { return e.at("ID") == id; });
    if (it == events.end()) { showError("Event not found."); return; }
    string name, date, venue;
    cout << "New name [" << (*it)["Name"] << "]: "; getline(cin, name);
    cout << "New date [" << (*it)["Date"] << "]: "; getline(cin, date);
    cout << "New venue [" << (*it)["Venue"] << "]: "; getline(cin, venue);
    if (!name.empty()) (*it)["Name"] = name;
    if (!date.empty()) (*it)["Date"] = date;
    if (!venue.empty()) (*it)["Venue"] = venue;
    writeCSV(EVENTS_FILE, events);
    cout << "Event updated.\n";
}

void UGManager::deleteEvent() {
    auto events = readCSV(EVENTS_FILE);
    if (events.empty()) { showError("No events."); return; }
    string id;
    cout << "Enter Event ID to delete: ";
    getline(cin, id);
    auto it = find_if(events.begin(), events.end(), [&](auto& e) { return e.at("ID") == id; });
    if (it == events.end()) { showError("Event not found."); return; }
    events.erase(it);
    writeCSV(EVENTS_FILE, events);
    cout << "Event deleted.\n";
}

// ================= NOTICE BOARD =====================

void UGManager::manageNoticeBoard() {
    int choice;
    do {
        cout << "\n--- Notice Board ---\n"
            << "[1] Post Notice\n"
            << "[2] View Notices\n"
            << "[3] Delete Notice\n"
            << "[4] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: postNotice(); break;
        case 2: viewNotices(); break;
        case 3: deleteNotice(); break;
        case 4: break;
        default: showError("Invalid option.");
        }
    } while (choice != 4);
}

void UGManager::postNotice() {
    auto notices = readCSV(NOTICES_FILE);
    map<string, string> notice;
    string id, text, date;
    cout << "Enter Notice ID: ";
    getline(cin, id);
    if (any_of(notices.begin(), notices.end(), [&](auto& n) { return n.at("ID") == id; })) {
        showError("Notice ID already exists.");
        return;
    }
    cout << "Enter Notice Text: ";
    getline(cin, text);
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    notice["ID"] = id; notice["Text"] = text; notice["Date"] = date;
    notices.push_back(notice);
    writeCSV(NOTICES_FILE, notices);
    cout << "Notice posted.\n";
}

void UGManager::viewNotices() {
    auto notices = readCSV(NOTICES_FILE);
    if (notices.empty()) { cout << "No notices found.\n"; return; }
    cout << "\nNotices:\n";
    for (auto& n : notices)
        cout << "ID: " << n["ID"] << ", Date: " << n["Date"] << ", Text: " << n["Text"] << "\n";
}

void UGManager::deleteNotice() {
    auto notices = readCSV(NOTICES_FILE);
    if (notices.empty()) { showError("No notices."); return; }
    string id;
    cout << "Enter Notice ID to delete: ";
    getline(cin, id);
    auto it = find_if(notices.begin(), notices.end(), [&](auto& n) { return n.at("ID") == id; });
    if (it == notices.end()) { showError("Notice not found."); return; }
    notices.erase(it);
    writeCSV(NOTICES_FILE, notices);
    cout << "Notice deleted.\n";
}

// ================= LIBRARY =====================

void UGManager::manageLibrary() {
    int choice;
    do {
        cout << "\n--- Library Management ---\n"
            << "[1] Add Book\n"
            << "[2] View Books\n"
            << "[3] Issue Book\n"
            << "[4] Return Book\n"
            << "[5] Delete Book\n"
            << "[6] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addBook(); break;
        case 2: viewBooks(); break;
        case 3: issueBook(); break;
        case 4: returnBook(); break;
        case 5: deleteBook(); break;
        case 6: break;
        default: showError("Invalid option.");
        }
    } while (choice != 6);
}

void UGManager::addBook() {
    auto books = readCSV(LIBRARY_FILE);
    map<string, string> book;
    string id, title, author, status = "Available", issuedTo;
    cout << "Enter Book ID: ";
    getline(cin, id);
    if (any_of(books.begin(), books.end(), [&](auto& b) { return b.at("ID") == id; })) {
        showError("Book ID already exists.");
        return;
    }
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    book["ID"] = id; book["Title"] = title; book["Author"] = author; book["Status"] = status; book["IssuedTo"] = "";
    books.push_back(book);
    writeCSV(LIBRARY_FILE, books);
    cout << "Book added.\n";
}

void UGManager::viewBooks() {
    auto books = readCSV(LIBRARY_FILE);
    if (books.empty()) { cout << "No books found.\n"; return; }
    cout << "\nBooks:\n";
    for (auto& b : books)
        cout << "ID: " << b["ID"] << ", Title: " << b["Title"] << ", Author: " << b["Author"]
        << ", Status: " << b["Status"] << (b["Status"] == "Issued" ? (", Issued To: " + b["IssuedTo"]) : "") << "\n";
}

void UGManager::issueBook() {
    auto books = readCSV(LIBRARY_FILE);
    if (books.empty()) { showError("No books."); return; }
    string id;
    cout << "Enter Book ID to issue: ";
    getline(cin, id);
    auto it = find_if(books.begin(), books.end(), [&](auto& b) { return b.at("ID") == id; });
    if (it == books.end()) { showError("Book not found."); return; }
    if ((*it)["Status"] == "Issued") {
        showError("Book already issued.");
        return;
    }
    string issuedTo;
    cout << "Enter Student ID to issue to: ";
    getline(cin, issuedTo);
    (*it)["Status"] = "Issued"; (*it)["IssuedTo"] = issuedTo;
    writeCSV(LIBRARY_FILE, books);
    cout << "Book issued.\n";
}

void UGManager::returnBook() {
    auto books = readCSV(LIBRARY_FILE);
    if (books.empty()) { showError("No books."); return; }
    string id;
    cout << "Enter Book ID to return: ";
    getline(cin, id);
    auto it = find_if(books.begin(), books.end(), [&](auto& b) { return b.at("ID") == id; });
    if (it == books.end()) { showError("Book not found."); return; }
    if ((*it)["Status"] != "Issued") {
        showError("Book is not issued.");
        return;
    }
    (*it)["Status"] = "Available";
    (*it)["IssuedTo"] = "";
    writeCSV(LIBRARY_FILE, books);
    cout << "Book returned.\n";
}

void UGManager::deleteBook() {
    auto books = readCSV(LIBRARY_FILE);
    if (books.empty()) { showError("No books."); return; }
    string id;
    cout << "Enter Book ID to delete: ";
    getline(cin, id);
    auto it = find_if(books.begin(), books.end(), [&](auto& b) { return b.at("ID") == id; });
    if (it == books.end()) { showError("Book not found."); return; }
    books.erase(it);
    writeCSV(LIBRARY_FILE, books);
    cout << "Book deleted.\n";
}

// ================= SPORTS COMPLEX =====================

void UGManager::manageSportsComplex() {
    int choice;
    do {
        cout << "\n--- Sports Complex ---\n"
            << "[1] View Facilities\n"
            << "[2] Book Slot\n"
            << "[3] View Bookings\n"
            << "[4] Delete Booking\n"
            << "[5] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: viewFacilities(); break;
        case 2: bookSlot(); break;
        case 3: viewBookings(); break;
        case 4: deleteBooking(); break;
        case 5: break;
        default: showError("Invalid option.");
        }
    } while (choice != 5);
}

void UGManager::viewFacilities() {
    auto sports = readCSV(SPORTS_FILE);
    if (sports.empty()) { cout << "No sports facilities found.\n"; return; }
    cout << "\nFacilities:\n";
    for (auto& s : sports)
        cout << "Facility: " << s["Facility"] << ", Info: " << s["Info"] << "\n";
}

void UGManager::bookSlot() {
    auto sports = readCSV(SPORTS_FILE);
    map<string, string> booking;
    string id, facility, user, slot;
    cout << "Enter Booking ID: ";
    getline(cin, id);
    if (any_of(sports.begin(), sports.end(), [&](auto& s) { return s.at("BookingID") == id; })) {
        showError("Booking ID already exists.");
        return;
    }
    cout << "Enter Facility: ";
    getline(cin, facility);
    cout << "Enter User ID: ";
    getline(cin, user);
    cout << "Enter Time Slot: ";
    getline(cin, slot);
    booking["BookingID"] = id; booking["Facility"] = facility; booking["User"] = user; booking["Slot"] = slot;
    sports.push_back(booking);
    writeCSV(SPORTS_FILE, sports);
    cout << "Slot booked.\n";
}

void UGManager::viewBookings() {
    auto sports = readCSV(SPORTS_FILE);
    if (sports.empty()) { cout << "No bookings found.\n"; return; }
    cout << "\nBookings:\n";
    for (auto& s : sports)
        if (s.count("BookingID"))
            cout << "BookingID: " << s["BookingID"] << ", Facility: " << s["Facility"]
            << ", User: " << s["User"] << ", Slot: " << s["Slot"] << "\n";
}

void UGManager::deleteBooking() {
    auto sports = readCSV(SPORTS_FILE);
    if (sports.empty()) { showError("No bookings."); return; }
    string id;
    cout << "Enter Booking ID to delete: ";
    getline(cin, id);
    auto it = find_if(sports.begin(), sports.end(), [&](auto& s) { return s.count("BookingID") && s.at("BookingID") == id; });
    if (it == sports.end()) { showError("Booking not found."); return; }
    sports.erase(it);
    writeCSV(SPORTS_FILE, sports);
    cout << "Booking deleted.\n";
}

// ================= HOSTEL INFO =====================

void UGManager::manageHostelInfo() {
    int choice;
    do {
        cout << "\n--- Hostel Info ---\n"
            << "[1] Add Room\n"
            << "[2] View Rooms\n"
            << "[3] Allot Room\n"
            << "[4] Vacate Room\n"
            << "[5] Delete Room\n"
            << "[6] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addRoom(); break;
        case 2: viewRooms(); break;
        case 3: allotRoom(); break;
        case 4: vacateRoom(); break;
        case 5: deleteRoom(); break;
        case 6: break;
        default: showError("Invalid option.");
        }
    } while (choice != 6);
}

void UGManager::addRoom() {
    auto hostels = readCSV(HOSTELS_FILE);
    map<string, string> room;
    string id, hostel, status = "Vacant", occupant;
    cout << "Enter Room ID: ";
    getline(cin, id);
    if (any_of(hostels.begin(), hostels.end(), [&](auto& r) { return r.at("ID") == id; })) {
        showError("Room ID already exists.");
        return;
    }
    cout << "Enter Hostel Name: ";
    getline(cin, hostel);
    room["ID"] = id; room["Hostel"] = hostel; room["Status"] = status; room["Occupant"] = "";
    hostels.push_back(room);
    writeCSV(HOSTELS_FILE, hostels);
    cout << "Room added.\n";
}

void UGManager::viewRooms() {
    auto hostels = readCSV(HOSTELS_FILE);
    if (hostels.empty()) { cout << "No rooms found.\n"; return; }
    cout << "\nRooms:\n";
    for (auto& r : hostels)
        cout << "ID: " << r["ID"] << ", Hostel: " << r["Hostel"]
        << ", Status: " << r["Status"]
        << (r["Status"] == "Allotted" ? (", Occupant: " + r["Occupant"]) : "") << "\n";
}

void UGManager::allotRoom() {
    auto hostels = readCSV(HOSTELS_FILE);
    if (hostels.empty()) { showError("No rooms."); return; }
    string id;
    cout << "Enter Room ID to allot: ";
    getline(cin, id);
    auto it = find_if(hostels.begin(), hostels.end(), [&](auto& r) { return r.at("ID") == id; });
    if (it == hostels.end()) { showError("Room not found."); return; }
    if ((*it)["Status"] == "Allotted") {
        showError("Room already allotted.");
        return;
    }
    string occupant;
    cout << "Enter Student ID to allot: ";
    getline(cin, occupant);
    (*it)["Status"] = "Allotted"; (*it)["Occupant"] = occupant;
    writeCSV(HOSTELS_FILE, hostels);
    cout << "Room allotted.\n";
}

void UGManager::vacateRoom() {
    auto hostels = readCSV(HOSTELS_FILE);
    if (hostels.empty()) { showError("No rooms."); return; }
    string id;
    cout << "Enter Room ID to vacate: ";
    getline(cin, id);
    auto it = find_if(hostels.begin(), hostels.end(), [&](auto& r) { return r.at("ID") == id; });
    if (it == hostels.end()) { showError("Room not found."); return; }
    if ((*it)["Status"] == "Vacant") {
        showError("Room already vacant.");
        return;
    }
    (*it)["Status"] = "Vacant";
    (*it)["Occupant"] = "";
    writeCSV(HOSTELS_FILE, hostels);
    cout << "Room vacated.\n";
}

void UGManager::deleteRoom() {
    auto hostels = readCSV(HOSTELS_FILE);
    if (hostels.empty()) { showError("No rooms."); return; }
    string id;
    cout << "Enter Room ID to delete: ";
    getline(cin, id);
    auto it = find_if(hostels.begin(), hostels.end(), [&](auto& r) { return r.at("ID") == id; });
    if (it == hostels.end()) { showError("Room not found."); return; }
    hostels.erase(it);
    writeCSV(HOSTELS_FILE, hostels);
    cout << "Room deleted.\n";
}

// ================= LABS =====================

void UGManager::manageLabs() {
    int choice;
    do {
        cout << "\n--- Labs Management ---\n"
            << "[1] Add Lab\n"
            << "[2] View Labs\n"
            << "[3] Delete Lab\n"
            << "[4] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addLab(); break;
        case 2: viewLabs(); break;
        case 3: deleteLab(); break;
        case 4: break;
        default: showError("Invalid option.");
        }
    } while (choice != 4);
}

void UGManager::addLab() {
    auto labs = readCSV(LABS_FILE);
    map<string, string> lab;
    string id, name, incharge;
    cout << "Enter Lab ID: ";
    getline(cin, id);
    if (any_of(labs.begin(), labs.end(), [&](auto& l) { return l.at("ID") == id; })) {
        showError("Lab ID already exists.");
        return;
    }
    cout << "Enter Lab Name: ";
    getline(cin, name);
    cout << "Enter Incharge Name: ";
    getline(cin, incharge);
    lab["ID"] = id; lab["Name"] = name; lab["Incharge"] = incharge;
    labs.push_back(lab);
    writeCSV(LABS_FILE, labs);
    cout << "Lab added.\n";
}

void UGManager::viewLabs() {
    auto labs = readCSV(LABS_FILE);
    if (labs.empty()) { cout << "No labs found.\n"; return; }
    cout << "\nLabs:\n";
    for (auto& l : labs)
        cout << "ID: " << l["ID"] << ", Name: " << l["Name"] << ", Incharge: " << l["Incharge"] << "\n";
}

void UGManager::deleteLab() {
    auto labs = readCSV(LABS_FILE);
    if (labs.empty()) { showError("No labs."); return; }
    string id;
    cout << "Enter Lab ID to delete: ";
    getline(cin, id);
    auto it = find_if(labs.begin(), labs.end(), [&](auto& l) { return l.at("ID") == id; });
    if (it == labs.end()) { showError("Lab not found."); return; }
    labs.erase(it);
    writeCSV(LABS_FILE, labs);
    cout << "Lab deleted.\n";
}

// ================= TRANSPORT =====================

void UGManager::manageTransport() {
    int choice;
    do {
        cout << "\n--- Transport Info ---\n"
            << "[1] Register Bus Route\n"
            << "[2] View Bus Routes\n"
            << "[3] Delete Bus Route\n"
            << "[4] Back\n"
            << "Enter Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addBusRoute(); break;
        case 2: viewBusRoutes(); break;
        case 3: deleteBusRoute(); break;
        case 4: break;
        default: showError("Invalid option.");
        }
    } while (choice != 4);
}

void UGManager::addBusRoute() {
    auto routes = readCSV(TRANSPORT_FILE);
    map<string, string> route;
    string id, start, end, stops;
    cout << "Enter Route ID: ";
    getline(cin, id);
    if (any_of(routes.begin(), routes.end(), [&](auto& r) { return r.at("ID") == id; })) {
        showError("Route ID already exists.");
        return;
    }
    cout << "Enter Start Point: ";
    getline(cin, start);
    cout << "Enter End Point: ";
    getline(cin, end);
    cout << "Enter Stops (comma separated): ";
    getline(cin, stops);
    route["ID"] = id; route["Start"] = start; route["End"] = end; route["Stops"] = stops;
    routes.push_back(route);
    writeCSV(TRANSPORT_FILE, routes);
    cout << "Bus route registered.\n";
}

void UGManager::viewBusRoutes() {
    auto routes = readCSV(TRANSPORT_FILE);
    if (routes.empty()) { cout << "No routes found.\n"; return; }
    cout << "\nBus Routes:\n";
    for (auto& r : routes)
        cout << "ID: " << r["ID"] << ", Start: " << r["Start"] << ", End: " << r["End"] << ", Stops: " << r["Stops"] << "\n";
}

void UGManager::deleteBusRoute() {
    auto routes = readCSV(TRANSPORT_FILE);
    if (routes.empty()) { showError("No routes."); return; }
    string id;
    cout << "Enter Route ID to delete: ";
    getline(cin, id);
    auto it = find_if(routes.begin(), routes.end(), [&](auto& r) { return r.at("ID") == id; });
    if (it == routes.end()) { showError("Route not found."); return; }
    routes.erase(it);
    writeCSV(TRANSPORT_FILE, routes);
    cout << "Route deleted.\n";
}

// ================= HELPER =====================

void UGManager::showError(const string& message) const {
    cerr << "[ERROR] " << message << endl;
}