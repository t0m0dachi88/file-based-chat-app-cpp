# C++ Concept Verification Checklist
## File-Based Chat Application — Version 2.0
### Academic Evaluation Report

---

## 📊 1. Concept Checklist Table

| # | Concept | Status | Where Implemented | Explanation |
|---|---------|--------|-------------------|-------------|
| 1 | Tokens (keywords, identifiers, literals, operators) | ✅ | All files | Standard C++ tokens correctly used throughout: `class`, `virtual`, `public`, `private`, string literals, arithmetic operators |
| 2 | Expressions | ✅ | `User.cpp`, `SearchEngine.cpp`, `EncryptedMessage.cpp` | Relational (`==`, `!=`), logical (`&&`), and arithmetic expressions used correctly |
| 3 | Control Structures (if/else, while, for) | ✅ | `main.cpp`, `User.cpp`, `FileManager.cpp` | Nested `if/else`, `while(true)` loops, range-based `for` loops |
| 4 | Functions (definition, call, parameters) | ✅ | All `.cpp` files | Free functions (`clearInput()`, `displayMainMenu()`), member functions, helper functions |
| 5 | Classes and Objects | ✅ | All class files | 9 distinct classes defined and instantiated as objects |
| 6 | Encapsulation | ✅ | `User.h`, `Message.h`, `PrivateChat.h` | Private/protected members, public getters/setters only |
| 7 | Constructors | ✅ | All class `.cpp` files | Parameterized constructors with member-initializer lists |
| 8 | Destructors | ✅ | `PrivateChat.cpp`, `User.cpp`, `Message.cpp` | Virtual destructors, memory cleanup in `~PrivateChat()` |
| 9 | Inheritance (Single) | ✅ | `Admin.h`, `Member.h`, `TextMessage.h`, `EncryptedMessage.h` | `Admin : User`, `Member : User`, `TextMessage : Message`, `EncryptedMessage : Message` |
| 10 | Function Overriding | ✅ | `Admin.cpp`, `Member.cpp`, `TextMessage.cpp`, `EncryptedMessage.cpp` | `displayProfile()`, `canModerate()`, `display()`, `getType()` overridden with `override` keyword |
| 11 | Runtime Polymorphism | ✅ | `main.cpp` (lines 187–189, 323) | `User*` and `Message*` base pointers call derived implementations at runtime |
| 12 | Compile-time Polymorphism (Overloading) | ✅ | `SearchEngine.h/.cpp` | Two `search()` overloads — by keyword only, and by keyword + sender |
| 13 | Operator Overloading | ✅ | `User.cpp` (line 44), `Message.cpp` (line 15) | `operator<<` overloaded for both `User` and `Message` classes |
| 14 | Type Conversion Operator | ✅ | `User.h` (line 46) | `operator std::string() const` converts `User` to its username string implicitly |
| 15 | Pointers | ✅ | `main.cpp`, `FileManager.cpp`, `PrivateChat.cpp` | Raw pointers for `User*`, `Message*`, `PrivateChat*` with manual lifecycle management |
| 16 | Virtual Functions | ✅ | `User.h`, `Message.h` | `virtual void displayProfile()`, `virtual void display()`, `virtual std::string getType()` |
| 17 | Pure Virtual Functions / Abstract Class | ✅ | `User.h` (line 25, 28, 29), `Message.h` (line 21, 24, 25) | `= 0` on destructor and key methods; neither `User` nor `Message` can be instantiated directly |
| 18 | Base Pointer to Derived Object | ✅ | `main.cpp` (line 105–108), `FileManager.cpp` (line 51–53) | `User* newUser = new Admin(...)` / `new Member(...)` — classic base-pointer-to-derived pattern |
| 19 | Dynamic Binding | ✅ | `main.cpp` (line 323), `PrivateChat.cpp` (line 28) | `currentUser->displayProfile()`, `msg->display()` resolved at runtime via vtable |
| 20 | Templates | ✅ | `Logger.h` | `template<typename T> class Logger` — generic logging for any printable type |
| 21 | `std::vector` | ✅ | `PrivateChat.h`, `FileManager.h`, `SearchEngine.h`, `main.cpp` | Used for user lists, message lists, search results |
| 22 | `std::map` | ✅ | `main.cpp` (line 66) | `map<string, PrivateChat*> privateChats` — O(log n) keyed chat session cache |
| 23 | `std::set` | ✅ | `User.h` (line 16) | `set<string> blockedUsers` — unique elements, O(log n) lookup for block check |
| 24 | `ifstream` (file read) | ✅ | `FileManager.cpp` (lines 38, 90, 139) | Used to read `users.txt` and private chat files |
| 25 | `ofstream` (file write) | ✅ | `FileManager.cpp` (lines 21, 67) | Used to write `users.txt` and private chat files |
| 26 | Persistent Storage | ✅ | `FileManager.cpp` — full class | All users and chats are saved to disk and reloaded on next startup |
| 27 | Menu System (CLI) | ✅ | `main.cpp` (lines 27–58) | Hierarchical menus: Main → Dashboard/Admin → Private Chat submenu |
| 28 | Input/Output Handling | ✅ | `main.cpp` — `clearInput()`, all `cin >>` / `getline()` calls | Integer input validation with buffer flush; string input with `getline` |
| 29 | Exception Handling | ✅ | `main.cpp` (line 259–268), `FileManager.cpp` (lines 20–31, 64–83) | `try/catch` for empty messages and file I/O failures |
| 30 | `dynamic_cast` | ✅ | `FileManager.cpp` (lines 173–174) | Used in `getUserType()` to identify actual runtime type of a `User*` |
| 31 | `static` class member | ✅ | `User.h` (line 18) | `static const int MAX_LOGIN_ATTEMPTS = 3` — shared across all user instances |
| 32 | `std::filesystem` | ✅ | `FileManager.cpp` (lines 152–168) | Used in `getAllChatIdsForUser()` to iterate directory entries |
| 33 | `stringstream` | ✅ | `FileManager.cpp` (lines 45, 98, 107) | Used to parse CSV-formatted lines from files |
| 34 | `unordered_map` | ❌ | Not used | `std::map` is used instead; `unordered_map` is absent |
| 35 | `queue` | ❌ | Not used | No queue structure used anywhere in the project |
| 36 | `fstream` (read+write) | ⚠️ | Not used | Only separate `ifstream` and `ofstream` are used; no combined `fstream` |
| 37 | `getAllChatIdsForUser` header declaration | ⚠️ | `FileManager.cpp` only | Method is defined in `.cpp` but **not declared in `FileManager.h`** — ODR violation risk |

---

## 🔍 2. Detailed Concept Explanation

### 2.1 Basic C++ Concepts

#### Tokens
Every source file correctly uses C++ tokens in all four categories:
- **Keywords:** `class`, `public`, `private`, `protected`, `virtual`, `override`, `new`, `delete`, `template`, `typename`, `const`, `static`
- **Identifiers:** `username`, `sendMessage`, `FileManager`, `loadPrivateChat`
- **Literals:** `3` (default Caesar shift in `EncryptedMessage.h`), `"data/users.txt"`, `"1"`, `"0"` (read-status flags in files)
- **Operators:** `<<`, `>>`, `->`, `::`, `=`, `==`, `!=`, `&&`, `||`, `%`, `-`, `+`

**Verdict:** ✅ Correct and complete.

#### Expressions
- **Relational:** `password == p` in `User::login()`
- **Logical:** `msg->getSender() == sender && msg->getContent().find(keyword) != std::string::npos` in `SearchEngine.cpp`
- **Arithmetic:** `(c - base + shift) % 26 + base` — Caesar cipher in `EncryptedMessage.cpp`

**Verdict:** ✅ Correct and sufficiently varied.

#### Control Structures
- **Branching:** Multi-level `if/else` in `main.cpp` handles menu routing, user type checking (`canModerate()`), and login verification.
- **Iteration:** `while(true)` drives the main application loop. Range-based `for (auto u : users)` is used for iteration over all STL containers.
- **Break:** Used in `main.cpp` (line 274) to exit inner private chat loop.

**Verdict:** ✅ Correct. All three categories (selection, iteration, jump) are represented.

#### Functions
- **Free Functions:** `clearInput()`, `displayMainMenu()`, `displayDashboard()`, `displayPrivateChatMenu()`, `displayAdminMenu()` in `main.cpp`.
- **Member Functions:** Every class has well-defined methods.
- **Parameters:** Pass-by-value for small types, pass-by-`const` reference for `vector` and `ostream` parameters (correctly applied in `FileManager::saveUsers` and operator overloads).

**Verdict:** ✅ Correct.

---

### 2.2 OOP Concepts

#### Classes and Objects
Nine classes are defined: `User`, `Admin`, `Member`, `Message`, `TextMessage`, `EncryptedMessage`, `PrivateChat`, `FileManager`, `SearchEngine`, `EncryptionManager`, and the template class `Logger`.

Objects are instantiated both statically (e.g., `FileManager fm;`, `SearchEngine se;`) and dynamically (e.g., `new Admin(username, password)`).

**Verdict:** ✅ Correct.

#### Encapsulation
- `User`: `username`, `password`, `isOnline`, `blockedUsers`, `loginAttempts` are all `private`/`protected`.
- `Message`: `sender`, `content`, `timestamp`, `isRead` are `protected`.
- `PrivateChat`: `id`, `user1`, `user2`, `messages` are `private`.
- All access is through defined getter methods (`getUsername()`, `getContent()`, etc.).

**Verdict:** ✅ Fully correct. No unguarded public data members.

#### Constructors / Destructors
- **Parameterized Constructors:** All classes use member-initializer lists. Example: `User::User(std::string u, std::string p) : username(u), password(p), isOnline(false), loginAttempts(0) {}`.
- **Constructor Chaining:** `Admin::Admin(std::string u, std::string p) : User(u, p) {}` — delegates to the parent.
- **Destructors:** `User::~User()` is a pure virtual destructor, correctly providing a body in `User.cpp`. `~PrivateChat()` explicitly deletes all heap-allocated `Message*` objects, preventing memory leaks.

**Verdict:** ✅ Correct and demonstrates best practices.

#### Inheritance
Two distinct inheritance hierarchies:
1. `User` ← `Admin`, `Member`
2. `Message` ← `TextMessage`, `EncryptedMessage`

Both use `public` inheritance and correctly call parent constructors.

**Verdict:** ✅ Correct.

#### Function Overriding
- `Admin` and `Member` both override `displayProfile()` and `canModerate()` using the `override` keyword.
- `TextMessage` and `EncryptedMessage` both override `display()` and `getType()`.
- `EncryptedMessage` additionally overrides `getContent()` to return the *decrypted* content transparently.

**Verdict:** ✅ Correct. The `override` keyword is present, making this compiler-verified.

#### Runtime Polymorphism
```cpp
// main.cpp, line 187-189
for (auto u : users) {
    cout << *u << endl; // calls operator<< which internally triggers displayProfile() logic
}

// main.cpp, line 323
currentUser->displayProfile(); // resolves to Admin::displayProfile() or Member::displayProfile() at runtime

// PrivateChat.cpp, line 28
msg->display(); // resolves to TextMessage::display() or EncryptedMessage::display() at runtime
```
The vtable resolves these calls at runtime based on the actual object type.

**Verdict:** ✅ Correct and clearly demonstrated.

#### Compile-Time Polymorphism
```cpp
// SearchEngine.h
vector<Message*> search(const vector<Message*>& messages, string keyword);           // Overload 1
vector<Message*> search(const vector<Message*>& messages, string keyword, string sender); // Overload 2
```
Both overloads are called from `main.cpp` (lines 310–313) based on whether `searchSender` is empty. Resolved at compile time by the compiler choosing the correct signature.

**Verdict:** ✅ Correct.

---

### 2.3 Advanced C++ Concepts

#### Operator Overloading
```cpp
// User.cpp — friend function
ostream& operator<<(ostream& os, const User& u) {
    os << "Username: " << u.username << ", Online: " << (u.isOnline ? "Yes" : "No");
    return os;
}

// Message.cpp — friend function
ostream& operator<<(ostream& os, const Message& m) {
    os << "[" << m.timestamp << "] " << m.sender << ": " << m.content;
    return os;
}
```
`operator<<` is overloaded as a `friend` function for both `User` and `Message`, allowing `cout << *userPointer` to work naturally.

**Verdict:** ✅ Correct and properly implemented.

#### Type Conversion Operator
```cpp
// User.h, line 46
operator std::string() const { return username; }
```
This enables implicit conversion: `string(*currentUser)` in `main.cpp` (line 126) extracts the username string, allowing it to be directly concatenated and passed to `logger.log()`.

**Verdict:** ✅ Correct and explicitly demonstrated in `main.cpp`.

#### Pointers
- `User* currentUser = nullptr;` — null-initialized session pointer.
- `vector<User*> users` — collection of polymorphic objects.
- `map<string, PrivateChat*> privateChats` — keyed pointer cache.
- `Message* msg = new EncryptedMessage(...)` — base pointer to derived type.
- All pointers are cleaned up in explicit `delete` loops at program exit.

**Verdict:** ✅ Correct. Manual memory management is handled.

#### Virtual Functions & Dynamic Binding
The vtable mechanism is exploited across both hierarchies:
- `virtual void displayProfile() = 0` in `User` → resolved to `Admin::displayProfile()` or `Member::displayProfile()`
- `virtual void display() = 0` in `Message` → resolved to `TextMessage::display()` or `EncryptedMessage::display()`
- `virtual std::string getContent() const` in `Message` → overridden in `EncryptedMessage` to return decrypted content.

Dynamic binding is operational because pointers are to the base type. The runtime chooses the correct function via vtable lookup.

**Verdict:** ✅ Correct.

#### Base Pointer to Derived Object
```cpp
// main.cpp, lines 104-108
User* newUser = nullptr;
if (type == "admin") {
    newUser = new Admin(username, password);  // Base pointer holds Admin
} else {
    newUser = new Member(username, password); // Base pointer holds Member
}

// FileManager.cpp, lines 173-174
if (dynamic_cast<Admin*>(u)) return "Admin";
if (dynamic_cast<Member*>(u)) return "Member";
```
`dynamic_cast` is correctly used to query the actual type at runtime.

**Verdict:** ✅ Correct.

---

### 2.4 Templates

```cpp
// Logger.h
template <typename T>
class Logger {
private:
    std::string logFile;
public:
    Logger(std::string file) : logFile("data/logs/" + file + ".log") {}
    void log(T message) {
        std::ofstream file(logFile, std::ios::app);
        // ... timestamp logic ...
        file << "[" << timestamp << "] " << message << std::endl;
    }
};
```
Instantiated in `main.cpp` as `Logger<string> logger("app")`. Used to log strings throughout the session. The template parameter `T` is constrained by the `<<` operator requirement — any type that supports `operator<<` to an `ostream` is valid.

**Verdict:** ✅ Correct. The template is functional, generic, and practically used.

---

### 2.5 STL Usage

#### `std::vector`
- `vector<User*> users` — runtime-sized user registry.
- `vector<Message*> messages` in `PrivateChat` — ordered chat history.
- `vector<Message*> results` in `SearchEngine` — collected search output.

Chosen for O(1) amortized `push_back()` and sequential iteration support.

#### `std::map`
- `map<string, PrivateChat*> privateChats` in `main.cpp`.
- Provides O(log n) key-based lookup. Chats are identified by sorted username concatenation ("alice_bob"), guaranteeing uniqueness.

#### `std::set`
- `set<string> blockedUsers` in `User`.
- Provides O(log n) lookup via `find()`, and automatically prevents duplicate entries on `insert()`.

**Verdict:** ✅ All three container types demonstrated with appropriate justification.

---

### 2.6 File Handling

#### `ofstream` (Write)
```cpp
// FileManager.cpp, line 21
std::ofstream file(usersFile);
file << getUserType(u) << "," << u->getUsername() << "," << u->getPassword() << endl;
```

#### `ifstream` (Read)
```cpp
// FileManager.cpp, line 38
std::ifstream file(usersFile);
while (std::getline(file, line)) { ... }
```

#### Persistence
Data is read at startup (`fm.loadUsers()`) and written after every mutation (registration, sending a message, deleting a user). Chat files are named by Chat ID and stored in `data/private_chats/`. This constitutes a complete read-write persistence cycle.

**Verdict:** ✅ Correct and complete. Only `fstream` (read+write simultaneously) is absent — a minor gap.

---

### 2.7 Console I/O

#### Menu System
A hierarchical three-level menu:
1. **Main Menu** → Register / Login / Exit
2. **Dashboard** (Member) → Private Chat / Search / Profile / Logout
3. **Admin Menu** → Remove User / View All Users / Logout
4. **Private Chat Submenu** → Send Message / View History / Back

#### Input Handling
```cpp
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
```
Input is read with `cin >> choice` for integers. On failure, `clearInput()` resets the stream. String inputs use `getline()` to handle spaces. Empty-string validation (`if (username.empty() || password.empty())`) guards registration.

**Verdict:** ✅ Correct and robust.

---

## 🐞 3. Missing or Weak Areas

### ❌ Missing Concepts

| Concept | Status | Impact |
|---------|--------|--------|
| `std::unordered_map` | ❌ Not used | `std::map` is used; `unordered_map` (O(1) avg lookup) is not demonstrated |
| `std::queue` | ❌ Not used | No queue-based structure exists in the project |
| `fstream` (simultaneous R/W) | ⚠️ Absent | Only `ifstream`/`ofstream` are used separately |

### ⚠️ Weak Implementations

1. **`getAllChatIdsForUser()` not declared in `FileManager.h`**
   - This method is fully implemented in `FileManager.cpp` (lines 150–169) but is **missing from the header**. This means it cannot be called from any translation unit other than `FileManager.cpp` itself. It is effectively a private function with no declaration. This is a **design inconsistency**.

2. **Search does not work across file-persisted chats on fresh load**
   - The Search feature pre-loads chats by iterating over all known users (lines 283–298 in `main.cpp`). However, it only loads chats for the current user paired with each **registered user in memory**. If a user was registered in a previous session and their object is loaded from file, this works — but it is brittle. The `getAllChatIdsForUser()` function in `FileManager` was clearly intended to fix this but is never called.

3. **`Admin::removeUserFromRoom()` and `Admin::muteUser()` are stub implementations**
   - Both methods only print a message to `stdout`. They perform no actual state mutation. This is acceptable for a prototype but would be flagged as incomplete in a production evaluation.

4. **No `fstream` usage**
   - The curriculum requirement for `fstream` (simultaneous read and write) is not met. Separate `ifstream` and `ofstream` are used.

5. **`std::queue` / `std::unordered_map` absent**
   - The checklist requires at least a `set` **or** a `queue`. A `set` is present. However, `unordered_map` is listed as a required concept and is not used.

6. **Login attempt lockout state is not persisted**
   - `loginAttempts` resets to `0` every time `users.txt` is re-loaded from disk, as it is not serialized. A user who fails 2 attempts and closes the app can immediately retry after reopening.

---

## 🎯 4. Academic Evaluation

### Coverage Summary

| Category | Concepts Required | Concepts Implemented | Coverage |
|---|---|---|---|
| Basic C++ | 4 | 4 | 100% |
| OOP Concepts | 7 | 7 | 100% |
| Advanced C++ | 6 | 6 | 100% |
| Templates | 1 | 1 | 100% |
| STL | 3 (vector, map/unordered_map, set/queue) | 3 (vector, map, set) | ~83% ⚠️ |
| File Handling | 3 (ifstream, ofstream, fstream) | 2 (ifstream, ofstream) | ~67% ⚠️ |
| Console I/O | 2 | 2 | 100% |
| **TOTAL** | **26** | **23** | **~88%** |

### Strength Level: **HIGH**

The project demonstrates a clear, intentional application of OOP principles. The class hierarchies are well-reasoned, runtime polymorphism is observable and functional, and the template Logger is practically used — not just declared. The main weaknesses are in STL breadth (`unordered_map`, `queue` missing) and the `fstream` gap.

### Is This Sufficient for Grading? **YES**

The project surpasses the threshold for a passing and commendable final-year project grade. The critical OOP and Advanced C++ concepts are all implemented, verifiable, and functionally tested. The missing concepts (`unordered_map`, `queue`, `fstream`) are minor gaps that can be addressed as quick additions.

---

## 🧠 5. Viva Support Section

### Q: "Where is polymorphism used in your project?"

**Answer:**
> "I have used both types of polymorphism. For **runtime polymorphism**, I have two hierarchies: `User` → `Admin`/`Member`, and `Message` → `TextMessage`/`EncryptedMessage`. Both use pure virtual functions. When I call `currentUser->displayProfile()` in `main.cpp`, the correct version — either `Admin::displayProfile()` or `Member::displayProfile()` — is selected at runtime via the vtable. Similarly, calling `msg->display()` on a `Message*` pointer calls the correct display method depending on whether the object is a `TextMessage` or `EncryptedMessage`. For **compile-time polymorphism**, I have two overloaded `search()` methods in my `SearchEngine` class — one takes a keyword only, the other takes a keyword plus a sender filter. The compiler picks the correct one at compile time based on the number of arguments."

---

### Q: "Where is a template used?"

**Answer:**
> "I have a `Logger` template class defined in `Logger.h`. It is declared as `template<typename T> class Logger`. Its `log()` method accepts any type `T` that supports the stream insertion operator `<<`. In `main.cpp`, I instantiate it as `Logger<string> logger("app")`. This means I can log any string message by calling `logger.log("User logged in: " + string(*currentUser))`. The type conversion operator on `User` — `operator std::string() const` — converts the `User` object to its username string, which is then passed to the template `log()` method. This is a clean demonstration of templates and type conversion working together."

---

### Q: "How is file handling implemented?"

**Answer:**
> "All file I/O is centralized in the `FileManager` class. I use `std::ofstream` to write and `std::ifstream` to read. User data is stored in `data/users.txt` in CSV format: `Type,Username,Password`. Each private chat is stored in its own file under `data/private_chats/<chat_id>.txt`. The first line of a chat file contains the two usernames. Every subsequent line stores one message in the format: `Type,Sender,EncryptedContent,Timestamp,IsRead`. On application startup, `loadUsers()` reads `users.txt` and reconstructs `Admin` or `Member` objects. Chat files are loaded lazily — only when a user opens a specific chat. On any state change, such as sending a message or registering a user, the corresponding file is immediately overwritten with the current state. I also wrap all file operations in `try/catch` blocks to handle `std::runtime_error` exceptions if a file cannot be opened."

---

### Q: "How does encryption work?"

**Answer:**
> "I use a Caesar Cipher with a default shift of 3. The `EncryptedMessage` class stores content in its encrypted form. When the constructor is called with plaintext, it immediately calls `encrypt(content)` and stores the result. The `display()` method calls `decrypt(content)` before printing, so the user always sees readable text on screen. However, the raw data stored in memory is the ciphertext. When `FileManager::savePrivateChat()` writes messages to disk, it calls `em.encrypt()` on the plaintext content obtained through `getContent()` (which decrypts) — ensuring the file always contains ciphertext. When loading, `FileManager::loadPrivateChat()` calls `em.decrypt()` on the file content before passing it to the `EncryptedMessage` constructor, which will re-encrypt it into memory. This maintains a consistent encrypt-in-memory, encrypt-on-disk policy."

---

*End of Concept Verification Checklist — Generated for academic submission purposes.*
