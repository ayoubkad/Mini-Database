# 🎓 Mini Student Database Engine in C

A lightweight, high-performance database engine built from scratch in C. This project implements a **Student Management System** using **Singly Linked Lists** for dynamic memory management and **Binary Files** for data persistence.

## 🚀 Features

- **Dynamic Memory Management:** Uses `malloc` and `free` to handle data without fixed-size array limitations.
- **Efficient Data Structures:** Implements a Singly Linked List with both **Head** and **Tail** pointers for $O(1)$ insertion time.
- **Complete CRUD Operations:**
    - **Create:** Add new students dynamically with extended information (name, firstname, birth date, CNE, field of study, average grade).
    - **Read:** Display all registered students with formatted output.
    - **Update:** Modify student information (name, firstname, birth date, field of study, or average grade) by CNE.
    - **Delete:** Remove students by unique ID (CNE) or delete all students at once.
- **Advanced Search & Sort:**
    - **Search by CNE:** Quickly find a specific student by their unique identifier.
    - **Sort by Grade:** Automatically sort students by average grade in descending order using Merge Sort algorithm.
- **Data Persistence:** Saves and loads data using **Binary Serialization** (`.db` files) to ensure data survives program restart.
- **Input Validation:** Grade validation (0-20 range) with error handling.
- **Interactive CLI:** Clean and easy-to-use Command Line Interface with 8 menu options.

## 🛠️ Technical Architecture

### Data Structure
The core of the system relies on custom structures:
```c
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct student {
    char nom[20];
    char prenom[20];
    Date date_naissance;
    char CNE[15];       // Unique Identifier
    char filiere[30];   // Field of study
    float moyenne;      // Average grade (0-20)
    struct student *next;
} student;
```

### List Structure
```c
typedef struct ListStudent {
    student *tete;   // Head pointer
    student *queues; // Tail pointer
} list_student;
```

## 📁 File Structure

```
Mini-Database/
├── main.c              # Entry point with interactive CLI menu
├── student.h           # Header file with data structures and function declarations
├── student.c           # Core implementation (CRUD + File I/O)
├── CMakeLists.txt      # Build configuration
├── my_data.db          # Binary database file (auto-generated)
└── README.md           # This file
```

## 🔧 Prerequisites

- **C Compiler:** GCC, Clang, or MSVC
- **Build System:** CMake (version 3.0 or higher)
- **Standard Library:** C standard library (stdio, stdlib, string)

## 🏗️ How to Build & Run

### Using CMake (Recommended)
```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile
cmake --build .

# Run
./Mini_Database  # Linux/Mac
Mini_Database.exe  # Windows
```

### Using GCC Directly
```bash
gcc main.c student.c -o mini_db
./mini_db  # Linux/Mac
mini_db.exe  # Windows
```

## 💻 Usage Example

```
=== MINI DATABASE MENU ===
1. Ajouter un etudiant
2. Afficher tout
3. Supprimer un etudiant
4. Modifier les donnees d'etudiant
5. Rechercher un etudiant par CNE
6. Trier les etudiants par moyenne
7. Supprimer tous les etudiants
8. Sauvegarder et Quitter
Votre choix: 1

Entrez Nom: Alami
Entrez Prenom: Hassan
Entrez Date de naissance (jour mois annee): 15 3 2003
Entrez CNE: R123456789
Entrez Filiere: Informatique
Entre Moyenne (doit etre entre 0 a 20): 16.5

=== MINI DATABASE MENU ===
Votre choix: 2

+--------------------------------------------+
|             INFORMATION ETUDIANT 1         |
+--------------------------------------------+
| CNE            : R123456789               |
| Nom            : Alami                    |
| Prenom         : Hassan                   |
| Date Naissance : 15/03/2003               |
| Filiere        : Informatique             |
| Moyenne        : 16.50                    |
+--------------------------------------------+

=== MINI DATABASE MENU ===
Votre choix: 5

Entrez le CNE de l'etudiant a rechercher : R123456789
+--------------------------------------------+
|             INFORMATION ETUDIANT           |
+--------------------------------------------+
| CNE            : R123456789               |
| Nom            : Alami                    |
| Prenom         : Hassan                   |
| Date Naissance : 15/03/2003               |
| Filiere        : Informatique             |
| Moyenne        : 16.50                    |
+--------------------------------------------+
```

## ⚡ Performance Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Add Student (end) | O(1) | O(1) |
| Display All | O(n) | O(1) |
| Search by CNE | O(n) | O(1) |
| Update by CNE | O(n) | O(1) |
| Delete by CNE | O(n) | O(1) |
| Delete All Students | O(n) | O(1) |
| Sort by Grade (Merge Sort) | O(n log n) | O(log n) |
| Load from DB | O(n) | O(n) |
| Save to DB | O(n) | O(1) |

**Note:** The tail pointer optimization ensures constant-time insertion at the end.

## 🎯 Key Implementation Details

### Binary File Serialization
- Uses `fwrite()` and `fread()` for efficient binary I/O
- Data persists between program executions
- No parsing overhead (unlike text-based formats)

### Merge Sort Algorithm
- Implements efficient O(n log n) sorting by average grade
- Uses divide-and-conquer strategy with recursive splitting
- Sorts in descending order (highest grades first)
- Three helper functions:
  - `get_middle()`: Finds the middle node using slow/fast pointer technique
  - `merge_sorted_lists()`: Merges two sorted lists in descending order
  - `merge_sort_recursive()`: Recursively splits and sorts the list

### Update Operation
- Allows modification of student data without deletion/re-creation
- Interactive menu for selecting which field to update:
  - Nom (Name)
  - Prenom (First Name)
  - Date de naissance (Birth Date)
  - Filiere (Field of Study)
  - Moyenne (Average Grade)

### Memory Management
```c
student *s = malloc(sizeof(student));  // Allocation
free(current);                         // Deallocation
```

### Edge Cases Handled
- ✅ Deleting the head node
- ✅ Deleting the tail node
- ✅ Deleting a middle node
- ✅ Empty list operations
- ✅ File not found (graceful handling)
- ✅ Student not found during search/update/delete
- ✅ Grade validation (0-20 range)
- ✅ Confirmation prompt for delete all operation

## 🚧 Future Enhancements

- [ ] **Input Validation:** Prevent duplicate CNEs during student creation
- [ ] **Search by Name:** Find students without CNE (partial name matching)
- [ ] **Sort by Name/Date:** Additional sorting options beyond grades
- [ ] **CSV Export:** Export data for spreadsheet applications
- [ ] **Hash Table:** O(1) search by CNE using hash-based indexing
- [ ] **Multiple Databases:** Switch between different `.db` files at runtime
- [ ] **Undo/Redo:** Implement command pattern for operation history
- [ ] **Batch Import:** Load multiple students from CSV/text files
- [ ] **Statistics:** Display average grade, min/max grades, grade distribution
- [ ] **Date Validation:** Ensure valid birth dates (leap years, day/month ranges)

## 🐛 Known Limitations

- No input validation for duplicate CNEs (same CNE can be added multiple times)
- Fixed-size strings (20 chars for names, 15 for CNE, 30 for filiere)
- No transaction support (changes are immediate, no rollback)
- Single-threaded (no concurrent access)
- No date validation (can enter invalid dates like 32/13/2025)
- Binary files are platform-dependent (not portable between different architectures)

## 📚 Learning Outcomes

This project demonstrates:
- ✅ Dynamic memory allocation in C
- ✅ Pointer manipulation and linked list implementation
- ✅ File I/O operations (binary mode)
- ✅ Modular programming (separation of concerns)
- ✅ Data persistence techniques
- ✅ Advanced algorithms (Merge Sort for linked lists)
- ✅ Input validation and error handling
- ✅ Interactive CLI design and user experience

## 👨‍💻 Author

**Mini Database Project**
- Built with C and CMake
- Educational project for data structures and systems programming

## 📄 License

This project is open-source and available for educational purposes.

---

**Note:** This is a learning project. For production use, consider robust databases like SQLite, PostgreSQL, or MySQL.
