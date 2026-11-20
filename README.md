# 💊 Medication Reminder System

A console-based Medication Reminder System developed in C that helps users manage their medicines, track daily doses, monitor pill stock, and maintain medicine records using file handling.

## 📌 Project Overview

The Medication Reminder System allows users to add medicines, view their records, search for specific medicines, track taken and missed doses, and delete medicine entries.

The program uses a text file (`meds.txt`) to store records, so the saved data remains available even after the program is closed.

## ✨ Features

- **Add Medicine:** Add a medicine with its name, scheduled time, and number of pills.
- **View All Medicines:** Display all saved medicines along with their details.
- **Search Medicine:** Search for a medicine by its exact name.
- **Dose Tracking:** Mark a medicine dose as Taken or Missed.
- **Pill Stock Management:** Automatically decrease the pill count when a dose is marked as taken.
- **Low Stock Alert:** Display a warning when the remaining pill count reaches 5 or below.
- **Missed Dose Alert:** Display a caregiver alert message when a dose is marked as missed.
- **Delete Medicine:** Remove a medicine using its ID.
- **File Handling:** Save and load medicine records using `meds.txt`.

## 🛠️ Technologies Used

- C Programming Language
- Structures
- Arrays
- Pointers
- Functions
- Recursion
- File Handling
- Loops and Conditional Statements
- String Handling

## 📂 Project Structure

```text
medication-Reminder-sys/
│
├── med.c
├── meds.txt
├── README.md
└── .gitignore
```

## 📋 Main Menu

```text
=========================================
        MEDICATION REMINDER SYSTEM
=========================================
1. Add Medicine
2. View All Medicines
3. Search Medicine by Name
4. Mark Dose (Taken / Missed)
5. Delete Medicine
6. Save & Exit

Enter choice:
```

## 💾 Data Storage

The program uses file handling to store medicine records in `meds.txt`.

Each record contains:

- Medicine ID
- Medicine Name
- Scheduled Time
- Number of Pills
- Taken Dose Count
- Missed Dose Count

Records are loaded when the program starts and updated whenever changes are made.

## 🎓 Learning Objectives

This project demonstrates the practical implementation of fundamental C programming concepts, including:

- Using structures to organize medicine records.
- Using pointers to modify data through functions.
- Applying recursion to display and search medicine records.
- Using file handling for permanent data storage.
- Managing arrays of structures.
- Implementing CRUD operations (Create, Read, Update, Delete).

## ⚠️ Note

This is a console-based academic project. The reminder and alert messages are displayed within the program; it does not send actual phone notifications or automatic reminders.

## 👩‍💻 Author

**Maimoona Akhter**

Developed as a C Programming project.
