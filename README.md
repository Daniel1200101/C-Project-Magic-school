Hogwarts Management System (C Project)
A comprehensive school management system inspired by the world of Harry Potter, developed in C. This system manages students, houses, magic wands, brooms, and spells, featuring interactive game mechanics and memory-efficient data storage.

🛠 Features
1. School Management
Hogwarts Core: Manages 4 houses (Gryffindor, Hufflepuff, Ravenclaw, Slytherin), courses, and spell catalogs.

Sorting Hat: Automatically assigns new students to houses.

House Leadership: Dynamically elects the "Head of House" based on the student with the highest credit points.

2. Student & Academic Tracking
Progress System: Students accumulate credits from courses to advance through 6 academic years.

Prerequisites: Spells have minimum year requirements based on student level.

Sorting & Searching: Students can be sorted and searched by credits, wand ID, name length, or year.

3. Interactive Mechanics
Spell Duels: A 3-round battle system between students using spell power, difficulty, and a randomized "mastery" factor.

Broom Races: Competition based on broom speed and random student handling skills.

The Magic Factory: A central registry for wands and brooms that prevents duplicate IDs.

4. Technical Optimization: Bit-Level Compression
To optimize memory, the Spell structure uses bit-packing to compress multiple attributes into a minimal byte footprint:

Difficulty: 2 bits (Easy, Medium, Hard).

Power: 6 bits (Max value 60).

Year Requirement: 3 bits (Years 1-6).

Name Length: 5 bits (Supports up to 31 characters).

📂 Project Structure
Wand: Year of manufacture and unique 3-letter ID.

Broom: Dynamic name allocation, speed, and competition history.

Spell: Compressed data structure for magical abilities.

Course: Credit system (0.0 - 3.0) and unique 5-digit ID.

Student: Personal details, credits, and linked magical items.

House: Dynamic array of pointers to students.

Hogwarts: The central entity managing all arrays and global data.

🚀 How to Run
Clone the repository.

Compile the source files using gcc or open the .sln file in Visual Studio.

Run the executable and follow the on-screen menu (13 management options).
