# Project 9: Result Processing System Using Templates

**Course:** OOPS Lab Mini Project | CIC-211
**Language:** C++ (C++11 or later)

## Objective
A small, menu-driven result processor that works with marks/scores of different numeric types (`int` and `double`) using C++ templates.

## Features
- **Function template** `largestOfThree<T>()` finds the largest of three values.
- **Class template** `Student<T>` stores a student's name and score.
- **Class template** `ResultBook<T>` manages a collection of students (add, display, average, search, save, load).
- Displays scores and calculates the **average** (plus the topper).
- Demonstrated with **integer** and **floating-point** scores.
- **Search** by name (case-insensitive, partial match).
- **File handling**: save/load records (`results_int.txt`, `results_float.txt`).
- **Input validation**: invalid numbers, out-of-range scores and empty names are rejected.

## OOP Concepts Demonstrated
| Concept | Where |
|---|---|
| Function templates | `largestOfThree<T>`, `readNumber<T>`, menu helpers |
| Class templates | `Student<T>`, `ResultBook<T>` |
| Generic programming | Same logic reused for `int` and `double` |
| Functions | Input helpers and menu actions |
| Basic classes | Encapsulation (private data, public methods), constructors |

## Project Structure
```
.
├── output/              # Program screenshots
│   ├── menu.png
│   ├── StudentRecords.png
│   ├── LargestScore.png
│   ├── average.png
│   ├── Searching.png
│   ├── FileHandling.png
│   ├── InvalidInput.png
│   └── ExitWindow.png
├── project/
│   ├── MINI PROJECT.pdf
│   └── main.cpp         # Complete source code
└── README.md
```

## How to Compile and Run
```bash
cd project
g++ -std=c++11 main.cpp -o result_system
./result_system          # Windows: result_system.exe
```

## Menu
```
1. Add student record
2. Display student records
3. Find largest of three scores
4. Calculate average
5. Search student by name
6. Save records to file
7. Load records from file
8. Exit
```
Options 1 and 3-7 first ask whether to use **Integer** or **Floating-point** scores.

## Sample Run
```
Enter your choice (1-8): 3
Select score type: 2
Enter three scores to compare:
 Score 1: 9.5
 Score 2: 9.75
 Score 3: 3.2
Largest score = 9.75
```


## Author
Saket kumar (20314803125) and Rahul Yadav (20414803125) 
