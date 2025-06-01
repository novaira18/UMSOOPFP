#pragma once

#include <string>

class UGManager {
public:
    UGManager();
    ~UGManager();

    void showMenu();

    // Events Management
    void manageEvents();
    void addEvent();
    void viewEvents();
    void editEvent();
    void deleteEvent();

    // Notice Board
    void manageNoticeBoard();
    void postNotice();
    void viewNotices();
    void deleteNotice();

    // Library Management
    void manageLibrary();
    void addBook();
    void viewBooks();
    void issueBook();
    void returnBook();
    void deleteBook();

    // Sports Complex
    void manageSportsComplex();
    void viewFacilities();
    void bookSlot();
    void viewBookings();
    void deleteBooking();

    // Hostel Info
    void manageHostelInfo();
    void addRoom();
    void viewRooms();
    void allotRoom();
    void vacateRoom();
    void deleteRoom();

    // Labs Management
    void manageLabs();
    void addLab();
    void viewLabs();
    void deleteLab();

    // Transport Info
    void manageTransport();
    void addBusRoute();
    void viewBusRoutes();
    void deleteBusRoute();

private:
    void showError(const std::string& message) const;
};