# 🚗 Smart Parking Management System

A structured and efficient C-based parking management system designed to simulate real-world parking operations using **Linked Lists** and dynamic memory allocation.

---

## 📌 Project Overview

This project simulates a smart parking system that manages vehicle entry, categorization (VIP / Normal), and fee calculation based on parking duration. It demonstrates strong use of data structures and modular programming in C.

---

## ✨ Features

* 🚘 Add vehicles (VIP / Normal)
* 🧠 Prevent duplicate vehicle entries
* 🅿️ Multi-parking structure (VIP + multiple floors ready)
* ⏱️ Time-based fee calculation
* 🧹 Remove vehicle after payment
* 💰 Income tracking system
* 📋 Display vehicles per section

---

## 🧠 Core Concepts Used

* C Programming Language
* Linked Lists (Singly Linked List)
* Pointers and Dynamic Memory Allocation (malloc/free)
* Modular programming (functions-based design)
* Input validation techniques

---

## ⚙️ How to Run

### Compile

```bash
gcc main.c -o main
```

### Run

```bash
./main
```

---

## 📂 Project Structure

```
Smart_Parking_Management_System/
│── main.c
│── .gitignore
│── README.md
```

---

## 📊 System Logic

* Vehicles are stored using linked lists
* VIP vehicles are separated from normal vehicles
* Fee is calculated based on parking duration (in minutes)
* Vehicles are removed automatically after payment
* Total income is tracked during runtime

---

## 👨‍💻 Author

**Elhadi-coder**

---

## 🚀 Notes

This project reflects a solid understanding of data structures and memory management in C, and is structured in a way that can be extended into a larger parking management system with databases or file storage in the future.
