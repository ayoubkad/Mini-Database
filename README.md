# 🎓 Mini Student Database Engine in C

A lightweight, high-performance database engine built from scratch in C. This project implements a **Student Management System** using **Singly Linked Lists** for dynamic memory management, **Binary Search Trees** for efficient sorting, and **Binary Files** for data persistence.

## 🚀 Features

- **Dynamic Memory Management:** Uses `malloc` and `free` to handle data without fixed-size array limitations.
- **Efficient Data Structures:** 
  - Implements a Singly Linked List with both **Head** and **Tail** pointers for $O(1)$ insertion time.
  - Uses **Binary Search Tree (BST)** for efficient in-order traversal and sorting operations.
- **Complete CRUD Operations:**
    - **Create:** Add new students dynamically with extended information (name, firstname, birth date, CNE, field of study, average grade).
    - **Read:** Display all registered students with formatted output.
    - **Update:** Modify student information (name, firstname, birth date, field of study, or average grade) by CNE.
    - **Delete:** Remove students by unique ID (CNE) or delete all students at once.
- **Advanced Search & Sort:**
    - **Search by CNE:** Quickly find a specific student by their unique identifier.
    - **Sort by Grade:** Display students sorted by average grade using a **Binary Search Tree (BST)** with in-order traversal for optimal sorting.
- **Undo/Redo System:** 
    - **Operation History:** Stack-based undo system that tracks all Add, Delete, and Modify operations.
    - **Rollback Support:** Undo the last operation with full data restoration.
    - **History Display:** View complete action history with operation details.
- **Data Persistence:** Saves and loads data using **Binary Serialization** (`.db` files) to ensure data survives program restart.
- **Input Validation:** Grade validation (0-20 range) with error handling.
- **Interactive CLI:** Clean and easy-to-use Command Line Interface with 9 menu options.

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

### Binary Search Tree Structure
```c
typedef struct ab_node_student {
    student *std;                    // Pointer to student data
    struct ab_node_student *filsg;   // Left child (smaller grades)
    struct ab_node_student *filsd;   // Right child (larger grades)
} ab_node_student;

typedef struct ab_racine_student {
    ab_node_student *racine;         // Root pointer
} ab_racine_student;
```

### Undo Stack Structure
```c
typedef enum {
    ADD_OPERATION,
    DELETE_OPERATION,
    MODIFY_OPERATION
} OperationType;

typedef struct UndoNode {
    OperationType type;
    student_data backup_data;
    struct UndoNode *next;
} UndoNode;

typedef struct {
    UndoNode *top;
} UndoStack;
```

## 📁 File Structure

```
Mini-Database/
├── main.c              # Entry point with interactive CLI menu
├── student.h           # Student data structures and function declarations
├── student.c           # Core implementation (CRUD + File I/O)
├── arbres_binaire.h    # Binary Search Tree header
├── arbres_binaire.c    # BST implementation for sorting
├── undo_stack.h        # Undo/Redo system header
├── undo_stack.c        # Undo/Redo stack implementation
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
gcc main.c student.c arbres_binaire.c undo_stack.c -o mini_db
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
8. Gestion de l'Historique (Afficher / Annuler)
9. Sauvegarder et Quitter
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
Votre choix: 6

[Students displayed in sorted order by grade using BST traversal]

=== MINI DATABASE MENU ===
Votre choix: 8

--- MENU HISTORIQUE ---
1. Afficher la liste des actions (Voir l'historique)
2. Annuler la derniere action (Undo)
0. Retour au menu principal
Votre choix : 1

[Operation history displayed...]
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
| Sort by Grade (BST) | O(n log n) avg, O(n²) worst | O(n) |
| BST In-Order Traversal | O(n) | O(log n) avg |
| Load from DB | O(n) | O(n) |
| Save to DB | O(n) | O(1) |
| Push Undo Operation | O(1) | O(1) |
| Execute Undo | O(n) worst case | O(1) |
| Display History | O(h) | O(1) |

**Note:** 
- The tail pointer optimization ensures constant-time insertion at the end.
- BST performance depends on tree balance; worst case O(n²) occurs with sorted input (degenerates to linked list).
- Undo stack operations are O(1) for push, but undo execution may require O(n) for deletion/modification searches.
- History size `h` is the number of operations performed.

## 🎯 Key Implementation Details

### Binary File Serialization
- Uses `fwrite()` and `fread()` for efficient binary I/O
- Data persists between program executions
- No parsing overhead (unlike text-based formats)

### Binary Search Tree (BST) for Sorting
- **Dynamic BST construction:** Builds a temporary BST from the linked list for sorting operations
- **In-Order Traversal:** Left subtree → Root → Right subtree provides sorted output
- **Memory Efficient:** BST nodes only store pointers to existing student data (no duplication)
- **Automatic cleanup:** BST is freed after traversal to prevent memory leaks
- **Algorithm:**
  1. Create empty BST root
  2. Insert each student from linked list into BST (O(log n) per insert on average)
  3. Perform in-order traversal to display sorted students (O(n))
  4. Free all BST nodes (O(n))

### Undo/Redo System
- **Stack-Based Architecture:** Uses a linked list stack to store operation history
- **Operation Types Tracked:**
  - `ADD_OPERATION`: Stores student CNE for removal on undo
  - `DELETE_OPERATION`: Stores complete student backup for restoration
  - `MODIFY_OPERATION`: Stores previous student state for rollback
- **Data Backup:** Each operation creates a complete snapshot of affected student data
- **Undo Process:**
  - ADD → Removes the student from the list
  - DELETE → Re-inserts the student at original position
  - MODIFY → Restores previous field values
- **Memory Management:** Stack is freed on program exit to prevent leaks
- **Limitations:** 
  - "Delete All" operation is NOT tracked (too memory-intensive)
  - No redo functionality (only undo)

### Update Operation
- Allows modification of student data without deletion/re-creation
- Interactive menu for selecting which field to update:
  - Nom (Name)
  - Prenom (First Name)
  - Date de naissance (Birth Date)
  - Filiere (Field of Study)
  - Moyenne (Average Grade)
- **Operation is tracked in undo stack** with previous values backed up

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
- ✅ Undo on empty history (prevents stack underflow)
- ✅ BST construction from empty list
- ✅ Memory cleanup after BST operations

## 🚧 Future Enhancements

- [ ] **Input Validation:** Prevent duplicate CNEs during student creation
- [ ] **Search by Name:** Find students without CNE (partial name matching)
- [ ] **Sort by Name/Date:** Additional sorting options beyond grades
- [ ] **Balanced BST:** Implement AVL or Red-Black tree for guaranteed O(log n) insertion
- [ ] **Redo Functionality:** Add redo stack to complement undo operations
- [ ] **CSV Export:** Export data for spreadsheet applications
- [ ] **Hash Table:** O(1) search by CNE using hash-based indexing
- [ ] **Multiple Databases:** Switch between different `.db` files at runtime
- [ ] **Batch Import:** Load multiple students from CSV/text files
- [ ] **Statistics:** Display average grade, min/max grades, grade distribution
- [ ] **Date Validation:** Ensure valid birth dates (leap years, day/month ranges)
- [ ] **Persistent Undo History:** Save undo stack to disk for recovery after restart

## 🐛 Known Limitations

- No input validation for duplicate CNEs (same CNE can be added multiple times)
- Fixed-size strings (20 chars for names, 15 for CNE, 30 for filiere)
- No transaction support (changes are immediate, no rollback except through undo)
- Single-threaded (no concurrent access)
- No date validation (can enter invalid dates like 32/13/2025)
- Binary files are platform-dependent (not portable between different architectures)
- BST can degenerate to O(n²) if students are added in sorted order by grade
- Undo history is lost on program exit (not persisted to disk)
- "Delete All" operation cannot be undone (by design to save memory)

## 📚 Learning Outcomes

This project demonstrates:
- ✅ Dynamic memory allocation in C
- ✅ Pointer manipulation and linked list implementation
- ✅ Binary Search Tree (BST) construction and traversal
- ✅ File I/O operations (binary mode)
- ✅ Modular programming (separation of concerns)
- ✅ Data persistence techniques
- ✅ Stack-based undo system implementation
- ✅ Command pattern for operation tracking
- ✅ Input validation and error handling
- ✅ Interactive CLI design and user experience
- ✅ Memory leak prevention and resource cleanup

**📖 Want to learn more?** Check out [LEARN.md](LEARN.md) for a comprehensive tutorial covering all algorithms, data structures, and implementation details.

## 👨‍💻 Author

**Mini Database Project**
- Built with C and CMake
- Educational project for data structures and systems programming

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

This is an open-source educational project. Feel free to use, modify, and distribute for learning purposes.

---

**Note:** This is a learning project. For production use, consider robust databases like SQLite, PostgreSQL, or MySQL.
