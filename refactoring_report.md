# C++ Chat Application (v2.0) Refactoring Report

This report outlines the extensive refactoring performed to elevate the codebase from a student-level project to a clean, scalable, production-quality C++ architecture.

---

## 1. What Was Wrong

Before the refactoring, the codebase suffered from several critical anti-patterns common in early-stage C++ projects:
- **Severe Memory Leaks and Dangling Pointers**: Extensive use of raw pointers (`User*`, `Message*`) with manual `new`/`delete` calls, especially inside standard containers (`std::vector<Message*>`).
- **Poor Const-Correctness**: Getter methods and function arguments lacked `const` qualifiers, making the codebase vulnerable to accidental state modification and less optimizable by the compiler.
- **Pass-By-Value Inefficiencies**: Large strings and objects were being passed by value, leading to unnecessary deep copies.
- **Lack of Error Handling**: File operations silently failed without adequately informing the user or application state, leading to unpredictable crashes. Constructors lacked input validation.
- **Platform-Dependent File Operations**: Using `system("mkdir...")` is insecure, slow, and specific to Windows.
- **Duplicated Logic**: The `EncryptedMessage` class duplicated the exact Caesar Cipher logic already present in the `EncryptionManager`.

---

## 2. What Was Improved

### Memory Management & Safety
- **Raw Pointers Eliminated**: Replaced all raw owning pointers (`User*`, `Message*`) with `std::unique_ptr<User>` and `std::unique_ptr<Message>`. The application now benefits from strictly deterministic, zero-overhead automated memory management.
- **Const-Correctness Implemented**: Added `const` to all getters, validation functions, and read-only operations (e.g., `display() const`, `getType() const`).
- **Pass-By-Const-Reference**: Changed function signatures to use `const std::string&` instead of `std::string`, eliminating unnecessary memory allocations.

### Error Handling
- **Exceptions Introduced**: Replaced silent failures with explicit `std::invalid_argument` throws for empty credentials or messages. Added `std::runtime_error` and `std::filesystem::filesystem_error` for I/O operations.
- **Input Validation**: Added robust `cin` clearing and bounds checking to prevent the CLI from infinite looping on invalid numeric inputs.

### Architectural & OOP Design Improvements
- **Standardized Virtual Destructors**: Explicitly marked overriding destructors with `~Class() override;` and `= default;` to ensure well-defined polymorphic deletion.
- **Composition Over Duplication**: Modified `EncryptedMessage` to hold an instance of `EncryptionManager` (Composition). This completely removed the duplicated Caesar cipher logic.
- **Type Conversion Operator**: Added a demonstration of compile-time polymorphism using an explicit `operator std::string() const` inside the `User` class.

### File Handling & STL
- **Modern C++17 Filesystem**: Replaced `<dirent.h>` and `system()` calls with `<filesystem>`. Directory creation and file iterations are now entirely cross-platform, robust, and safe.
- **Safe Trimming**: Replaced unsafe `<ctime>` character manipulation with standard string sub-string algorithms.
- **Algorithm Usage**: Integrated `<algorithm>` tools like `std::find_if` for user lookup, leveraging lambda expressions to simplify iterative searches.

---

## 3. Improvements Summary

| Category | Specific Improvement | Benefit |
| :--- | :--- | :--- |
| **Safety** | Migrated to `std::unique_ptr` | Eliminates memory leaks and dangling pointers. Prevents segmentation faults on exit. |
| **Performance** | Pass-by-const-reference (`const Type&`) | Avoids expensive string copies during function calls, significantly reducing heap allocations. |
| **Performance** | `std::unordered_map` for private chats | Changed from `std::map` (O(log n)) to `std::unordered_map` (O(1)) for faster chat lookups. |
| **Stability** | Modern `<filesystem>` integration | Ensures the app runs reliably on any OS without relying on vulnerable shell commands. |
| **Architecture** | Composition in `EncryptedMessage` | Adheres strictly to the DRY (Don't Repeat Yourself) principle, centralizing encryption logic. |
| **Resilience** | `try-catch` blocks and input validation | Prevents file corruption and application crashes due to unexpected user behavior or missing files. |

## 4. Final Result
The system is now fully compliant with modern C++17 standards, compiles cleanly with `-Wall -Wextra`, and is robust enough for academic submission, GitHub portfolio inclusion, and rigorous viva demonstration.
