# 🎓 Mini Student Database Engine in C

A lightweight, high-performance database engine built from scratch in C. This project implements a **Student Management System** using **Singly Linked Lists** for dynamic memory management and **Binary Files** for data persistence.

## 🚀 Features

- **Dynamic Memory Management:** Uses `malloc` and `free` to handle data without fixed-size array limitations.
- **Efficient Data Structures:** Implements a Singly Linked List with both **Head** and **Tail** pointers for $O(1)$ insertion time.
- **CRUD Operations:**
    - **Create:** Add new students dynamically.
    - **Read:** Display all registered students.
    - **Delete:** Remove students by unique ID (CNE) handling all edge cases (Head, Middle, Tail).
- **Data Persistence:** Saves and loads data using **Binary Serialization** (`.db` files) to ensure data survives program restart.
- **Interactive CLI:** Clean and easy-to-use Command Line Interface.

## 🛠️ Technical Architecture

### Data Structure
The core of the system relies on a custom `struct`:
```c
typedef struct student {
    char nom[20];
    char prenom[20];
    int age;
    char CNE[10]; // Unique Identifier
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
4. Sauvegarder et Quitter
Votre choix: 1

Entrez Nom: Alami
Entrez Prenom: Hassan
Entrez Age: 21
Entrez CNE: R123456789

=== MINI DATABASE MENU ===
1. Ajouter un etudiant
2. Afficher tout
3. Supprimer un etudiant
4. Sauvegarder et Quitter
Votre choix: 2

-------les information d'etudiant 1-------
Nom : Alami
Prenom : Hassan
CNE : R123456789
Age : 21
```

## ⚡ Performance Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Add Student (end) | O(1) | O(1) |
| Display All | O(n) | O(1) |
| Delete by CNE | O(n) | O(1) |
| Load from DB | O(n) | O(n) |
| Save to DB | O(n) | O(1) |

**Note:** The tail pointer optimization ensures constant-time insertion at the end.

## 🎯 Key Implementation Details

### Binary File Serialization
- Uses `fwrite()` and `fread()` for efficient binary I/O
- Data persists between program executions
- No parsing overhead (unlike text-based formats)

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

## 🚧 Future Enhancements

- [ ] **Update Operation:** Modify existing student records
- [ ] **Search by Name:** Find students without CNE
- [ ] **Sorting:** Sort students by name or age
- [ ] **Input Validation:** Prevent duplicate CNEs
- [ ] **CSV Export:** Export data for spreadsheet applications
- [ ] **Hash Table:** O(1) search by CNE
- [ ] **Multiple Databases:** Switch between different `.db` files

## 🐛 Known Limitations

- No input validation for duplicate CNEs
- Fixed-size strings (20 chars for names)
- No transaction support (changes are immediate)
- Single-threaded (no concurrent access)

## 📚 Learning Outcomes

This project demonstrates:
- ✅ Dynamic memory allocation in C
- ✅ Pointer manipulation and linked list implementation
- ✅ File I/O operations (binary mode)
- ✅ Modular programming (separation of concerns)
- ✅ Data persistence techniques

## 👨‍💻 Author

**Mini Database Project**
- Built with C and CMake
- Educational project for data structures and systems programming

## 📄 License

This project is open-source and available for educational purposes.

---

**Note:** This is a learning project. For production use, consider robust databases like SQLite, PostgreSQL, or MySQL.
