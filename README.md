# ⚡ Hogwarts Management System
### *A memory-efficient C implementation of the Wizarding World*

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Final_School_Project-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows_/_Linux-lightgrey.svg)



## 📖 Overview
This project is a CLI-based management system for **Hogwarts School of Witchcraft and Wizardry**. Developed as a final school project by **Daniel and Iris**, it handles complex relationships between students, magical artifacts, and academic progress using **dynamic memory allocation** and **bit-level optimization**.

---

## 🛠 Architecture & Features

### 🏰 The School (Hogwarts)
* **House System:** Manages the four houses: 🦁 **Gryffindor**, 🐍 **Slytherin**, 🦡 **Hufflepuff**, and 🦅 **Ravenclaw**.
* **Sorting Hat:** Automatically assigns students to houses upon enrollment.
* **Academic Tracking:** Students advance through 6 years based on credit points. Promotion requires $Credits > (CurrentYear \times 10)$.

### 🪄 The Magic Factory
* **Wand & Broom Registry:** A centralized factory that prevents duplicate items using unique 3-letter IDs.
* **Dynamic Items:** Brooms feature dynamic naming and speed attributes used in racing logic.

### 🎮 Game Mechanics
* **Spell Duels:** A 3-round battle system calculating power based on:
  $$(Difficulty + Mastery + Power)$$
* **Broom Racing:** A competition simulation based on broom speed and randomized player handling.

---

## 💾 Technical Highlight: Bit-Packing
To minimize memory footprint, the **Spell** structure utilizes bit-packing to store multiple variables within just **2 Bytes**:

| Attribute | Bits | Logic / Range |
| :--- | :---: | :--- |
| **Difficulty** | 2 | Easy (00), Medium (01), Hard (11) |
| **Power** | 6 | Calculated as $(MinYear \times 10)$ |
| **Min Year** | 3 | Required level (Years 1-6) |
| **Name Length** | 5 | Supports up to 31 characters |

---

## 📂 System Menu
The system features a robust interactive menu with 13 management options:
1.  **Print Hogwarts Status** – Overview of staff, houses, and courses.
2.  **Inventory Check** – Detailed list of all wands and brooms.
3.  **Add Wand** – Register a new wand with ID validation.
4.  **Add Broom** – Register a new broom with speed attributes.
5.  **Enroll Student** – Add student, select favorite wizard, and trigger Sorting Hat.
6.  **Create Spell** – Add spells with "Dark Arts" validation (No *Avada Kedavra*).
7.  **Add Course** – Define new courses and credit values (Max 3.0).
8.  **Assign Course** – Add a course to a student's record and update credits.
9.  **Sort House** – Sort students by Credits, ID, Name Length, or Year.
10. **Find Student** – Search for students within a specific house.
11. **Elect Head of House** – Automatically selects the student with the most credits.
12. ⚔️ **Start Spell Duel** – Competitive 1v1 battle simulation.
13. 🧹 **Start Broom Race** – Distance-based racing simulation.

---

## 🚀 Getting Started

### Prerequisites
* GCC Compiler or **Visual Studio 2022**

### Installation & Compilation
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YourUsername/Hogwarts-C-Project.git](https://github.com/YourUsername/Hogwarts-C-Project.git)
