#pragma once
#include <string>
using namespace std;

// Abstract Base Class
class UGM {
public:
    // Events
    virtual void Add() = 0;
    virtual void View() = 0;
    virtual void Edit() = 0;
    virtual void Delete() = 0;

    // Notice Board
    virtual void Post(const string& filename = "notices.txt") = 0;
    virtual void ViewNotices() = 0;

    // Library
    virtual void AddBook() = 0;
    virtual void ViewBooks() = 0;
    virtual void IssueBook() = 0;
    virtual void ReturnBook() = 0;

    // Sports Complex
    virtual void BookSlot() = 0;
    virtual void ViewEquipment() = 0;

    // Hostel Info
    virtual void AllotRoom() = 0;
    virtual void ViewRoomData() = 0;

    // Labs
    virtual void AddOrUpdateCompLab() = 0;
    virtual void AddOrUpdatePhysicsLab() = 0;

    // Transport Info
    virtual void RegisterTransport() = 0;
    virtual void ViewBusRoutes() = 0;

    virtual ~UGM() {}
};

// ---------- Derived Sub-Classes ----------

// Events Management
class EventsManager : public UGM {
public:
    void Add() override;
    void View() override;
    void Edit() override;
    void Delete() override;

    // Unused inherited
    void Post(const string&) override {}
    void ViewNotices() override {}
    void AddBook() override {}
    void ViewBooks() override {}
    void IssueBook() override {}
    void ReturnBook() override {}
    void BookSlot() override {}
    void ViewEquipment() override {}
    void AllotRoom() override {}
    void ViewRoomData() override {}
    void AddOrUpdateCompLab() override {}
    void AddOrUpdatePhysicsLab() override {}
    void RegisterTransport() override {}
    void ViewBusRoutes() override {}
};

// Notice Board
class NoticeBoard : public UGM {
public:
    void Post(const string& filename = "notices.txt") override;
    void ViewNotices() override;

    // Unused inherited
    void Add() override {}
    void View() override {}
    void Edit() override {}
    void Delete() override {}
    void AddBook() override {}
    void ViewBooks() override {}
    void IssueBook() override {}
    void ReturnBook() override {}
    void BookSlot() override {}
    void ViewEquipment() override {}
    void AllotRoom() override {}
    void ViewRoomData() override {}
    void AddOrUpdateCompLab() override {}
    void AddOrUpdatePhysicsLab() override {}
    void RegisterTransport() override {}
    void ViewBusRoutes() override {}
};

// Library
class Library : public UGM {
public:
    void AddBook() override;
    void ViewBooks() override;
    void IssueBook() override;
    void ReturnBook() override;

    // Unused inherited
    void Add() override {}
    void View() override {}
    void Edit() override {}
    void Delete() override {}
    void Post(const string&) override {}
    void ViewNotices() override {}
    void BookSlot() override {}
    void ViewEquipment() override {}
    void AllotRoom() override {}
    void ViewRoomData() override {}
    void AddOrUpdateCompLab() override {}
    void AddOrUpdatePhysicsLab() override {}
    void RegisterTransport() override {}
    void ViewBusRoutes() override {}
};

// Sports Complex
class SportsComplex : public UGM {
public:
    void BookSlot() override;
    void ViewEquipment() override;

    // Unused inherited
    void Add() override {}
    void View() override {}
    void Edit() override {}
    void Delete() override {}
    void Post(const string&) override {}
    void ViewNotices() override {}
    void AddBook() override {}
    void ViewBooks() override {}
    void IssueBook() override {}
    void ReturnBook() override {}
    void AllotRoom() override {}
    void ViewRoomData() override {}
    void AddOrUpdateCompLab() override {}
    void AddOrUpdatePhysicsLab() override {}
    void RegisterTransport() override {}
    void ViewBusRoutes() override {}
};

// Hostel Info
class HostelInfo : public UGM {
public:
    void AllotRoom() override;
    void ViewRoomData() override;

    // Unused inherited
    void Add() override {}
    void View() override {}
    void Edit() override {}
    void Delete() override {}
    void Post(const string&) override {}
    void ViewNotices() override {}
    void AddBook() override {}
    void ViewBooks() override {}
    void IssueBook() override {}
    void ReturnBook() override {}
    void BookSlot() override {}
    void ViewEquipment() override {}
    void AddOrUpdateCompLab() override {}
    void AddOrUpdatePhysicsLab() override {}
    void RegisterTransport() override {}
    void ViewBusRoutes() override {}
};

// Labs
class LabsManager : public UGM {
public:
    void AddOrUpdateCompLab() override;
    void AddOrUpdatePhysicsLab() override;

    // Unused inherited
    void Add() override {}
    void View() override {}
    void Edit() override {}
    void Delete() override {}
    void Post(const string&) override {}
    void ViewNotices() override {}
    void AddBook() override {}
    void ViewBooks() override {}
    void IssueBook() override {}
    void ReturnBook() override {}
    void BookSlot() override {}
    void ViewEquipment() override {}
    void AllotRoom() override {}
    void ViewRoomData() override {}
    void RegisterTransport() override {}
    void ViewBusRoutes() override {}
};

// Transport Info
class TransportInfo : public UGM {
public:
    void RegisterTransport() override;
    void ViewBusRoutes() override;

    // Unused inherited
    void Add() override {}
    void View() override {}
    void Edit() override {}
    void Delete() override {}
    void Post(const string&) override {}
    void ViewNotices() override {}
    void AddBook() override {}
    void ViewBooks() override {}
    void IssueBook() override {}
    void ReturnBook() override {}
    void BookSlot() override {}
    void ViewEquipment() override {}
    void AllotRoom() override {}
    void ViewRoomData() override {}
    void AddOrUpdateCompLab() override {}
    void AddOrUpdatePhysicsLab() override {}
};