# ðŸ“˜ C++ File-Based Chat Application â€” Version 2.0
# Complete Project Documentation (Detailed)

---

## ðŸ“„ 1. Project Overview

### Title
**File-Based Chat Application (v2.0)** â€” A console-based, persistent messaging system built in modern C++.

### Objective
Design and implement a fully functional command-line chat application that demonstrates mastery of Object-Oriented Programming (OOP), Standard Template Library (STL), file I/O, encryption, templates, operator overloading, and exception handling â€” all in a single cohesive project.

### Problem Statement
Modern messaging relies on databases and servers. In constrained academic or embedded environments, a lightweight, server-less alternative is needed. The challenge is to build a persistent, multi-user chat system using only flat files for storage, while maintaining data security through encryption and clean OOP architecture.

### Solution Approach
- **Flat-file persistence**: All user data, chat histories, and logs are stored in plain text files under the `data/` directory.
- **Caesar cipher encryption**: Passwords and messages are encrypted before writing to disk.
- **Polymorphic class hierarchy**: Abstract base classes (`User`, `Message`) with concrete derived classes (`Admin`, `Member`, `TextMessage`, `EncryptedMessage`).
- **Template-based logging**: A generic `Logger<T>` template class for audit trails.
- **Modular architecture**: Separate classes for file management (`FileManager`), search (`SearchEngine`), encryption (`EncryptionManager`), and chat sessions (`PrivateChat`).

---

## ðŸ§  2. System Architecture

### Overall Design

The application follows a **layered modular architecture**:

```
â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
â”‚                  main.cpp                    â”‚
â”‚          (CLI Menu + Application Loop)       â”‚
â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
â”‚  User    â”‚ Message  â”‚ Private   â”‚  Search    â”‚
â”‚ Hierarchyâ”‚ Hierarchyâ”‚  Chat     â”‚  Engine    â”‚
â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
â”‚          â”‚          FileManager              â”‚
â”‚          â”‚    (Persistence Layer)             â”‚
â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
â”‚           EncryptionManager                  â”‚
â”‚         (Security / Cipher Layer)            â”‚
â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
â”‚             Logger<T>                        â”‚
â”‚         (Audit / Logging Layer)              â”‚
â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
â”‚          File System (data/)                 â”‚
â”‚   users.txt | private_chats/ | logs/         â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
```

### Module Interaction
1. `main.cpp` orchestrates the entire CLI flow and holds the application state (`vector<User*>`, `map<string, PrivateChat*>`).
2. `FileManager` handles all reading/writing to disk â€” it depends on `EncryptionManager` to encrypt/decrypt data during save/load.
3. `SearchEngine` operates on in-memory `Message*` vectors; it uses the virtual `getContent()` method, which transparently decrypts `EncryptedMessage` content.
4. `Logger<T>` is instantiated as `Logger<string>` and appends timestamped entries to `data/logs/app.log`.

### Data Flow

```
User Input â†’ main.cpp menu â†’ Create/Modify objects in memory
    â†’ FileManager.saveUsers() / savePrivateChat()
    â†’ EncryptionManager.encrypt() â†’ Write to .txt file

File on disk â†’ FileManager.loadUsers() / loadPrivateChat()
    â†’ EncryptionManager.decrypt() â†’ Reconstruct objects in memory
    â†’ Display to user via display() / operator<<
```

---

## ðŸ§± 3. File Structure Overview

| File | Role |
|---|---|
| `main.cpp` | Entry point: CLI menus, application loop, orchestration |
| `User.h` / `User.cpp` | Abstract base class for all users |
| `Admin.h` / `Admin.cpp` | Derived class: admin users with moderation privileges |
| `Member.h` / `Member.cpp` | Derived class: regular users |
| `Message.h` / `Message.cpp` | Abstract base class for all messages |
| `TextMessage.h` / `TextMessage.cpp` | Derived class: plain text messages |
| `EncryptedMessage.h` / `EncryptedMessage.cpp` | Derived class: Caesar-cipher encrypted messages |
| `EncryptionManager.h` / `EncryptionManager.cpp` | Standalone encryption/decryption utility |
| `FileManager.h` / `FileManager.cpp` | All file I/O: save/load users, chats |
| `SearchEngine.h` / `SearchEngine.cpp` | Keyword search with function overloading |
| `PrivateChat.h` / `PrivateChat.cpp` | Chat session: holds messages between two users |
| `Logger.h` | Template class for timestamped logging |
| `data/users.txt` | Persistent user records (encrypted passwords) |
| `data/private_chats/*.txt` | Persistent chat histories (encrypted messages) |
| `data/logs/app.log` | Timestamped application log |

---

## ðŸ“‚ 4. FILE-BY-FILE DETAILED EXPLANATION

---

### ðŸ“„ File: User.h

#### ðŸ”¹ Purpose
Defines the **abstract base class** `User`. Every user in the system (whether Admin or Member) inherits from this class. It establishes the common interface and shared data members.

#### ðŸ”¹ Code Breakdown

```cpp
#ifndef USER_H
#define USER_H
```
**Include guards** prevent multiple inclusion of this header. If `USER_H` is already defined, the preprocessor skips the entire file. This is essential in C++ to avoid "redefinition" compilation errors.

```cpp
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <ctime>
```
Standard library headers: `string` for text, `set` for the blocked-users collection (guarantees uniqueness + O(log n) lookup), `iostream` for console output, `ctime` for timestamps.

```cpp
class User {
protected:
    std::string username;
    std::string password;
    std::string securityQuestion;
    std::string securityAnswer;
    bool isOnline;
    std::set<std::string> blockedUsers;
    int loginAttempts;
    static const int MAX_LOGIN_ATTEMPTS = 3;
```
- **`protected`**: Derived classes (`Admin`, `Member`) can access these directly, but external code cannot. This is **encapsulation**.
- **`std::set<std::string> blockedUsers`**: Uses STL `set` â€” automatically sorts and prevents duplicate entries. Checking if a user is blocked is O(log n).
- **`static const int MAX_LOGIN_ATTEMPTS = 3`**: A class-level constant shared by all instances. Limits brute-force login attempts.

```cpp
public:
    User(std::string u, std::string p);
    virtual ~User() = 0;  // Pure virtual destructor
```
- The constructor takes username and password.
- **Pure virtual destructor (`= 0`)**: Makes `User` an abstract class â€” you **cannot** instantiate `User` directly. However, it still needs a body (provided in `User.cpp`) because destructors are called during derived-class destruction.

```cpp
    virtual void displayProfile() = 0;
    virtual bool canModerate() = 0;
```
**Pure virtual methods**: Every derived class **must** override these. `displayProfile()` shows user info; `canModerate()` returns `true` for Admin, `false` for Member. This is **runtime polymorphism** â€” the correct version is called via virtual dispatch.

```cpp
    std::string getUsername() const { return username; }
    bool getIsOnline() const { return isOnline; }
    std::string getPassword() const { return password; }
    std::string getSecurityQuestion() const { return securityQuestion; }
    std::string getSecurityAnswer() const { return securityAnswer; }
```
**Getter methods** â€” all marked `const` (they don't modify the object). These provide read-only access to private data. This is the **encapsulation** pattern: data is `protected`, access is through public methods.

```cpp
    void setPassword(std::string p) { password = p; }
    void setSecurityQuestion(std::string q) { securityQuestion = q; }
    void setSecurityAnswer(std::string a) { securityAnswer = a; }
```
**Setter methods** â€” allow controlled modification of specific fields.

```cpp
    bool checkSecurityAnswer(const std::string& a) const { return securityAnswer == a; }
```
Used in the "Forgot Password" flow. Takes the answer by `const` reference (avoids copying) and compares it.

```cpp
    bool login(std::string p);
    void logout();
    void blockUser(std::string u);
    void unblockUser(std::string u);
    bool isBlocked(std::string u) const;
```
Method declarations â€” implementations are in `User.cpp`.

```cpp
    operator std::string() const { return username; }
```
**Type conversion operator**: Allows a `User` object to be implicitly or explicitly converted to `std::string`. Used in `main.cpp` as `string(*currentUser)` to get the username for logging. This demonstrates **user-defined type conversion**.

```cpp
    friend std::ostream& operator<<(std::ostream& os, const User& u);
```
**Operator overloading**: Declares `operator<<` as a **friend function** so it can access `User`'s protected members. Enables `cout << *u` syntax.

---

### ðŸ“„ File: User.cpp

#### ðŸ”¹ Purpose
Implements the `User` base class methods declared in `User.h`.

#### ðŸ”¹ Code Breakdown

```cpp
User::User(std::string u, std::string p)
    : username(u), password(p), isOnline(false), loginAttempts(0) {}
```
**Member initializer list**: Initializes all fields before the constructor body executes. `isOnline` starts as `false`, `loginAttempts` starts at `0`. This is more efficient than assignment inside the body.

```cpp
User::~User() {}
```
**Pure virtual destructor body**: Even though the destructor is declared `= 0`, C++ requires a body. This is called when any derived-class object is destroyed (destructor chaining).

```cpp
bool User::login(std::string p) {
    if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
        std::cout << "Too many failed attempts. Account locked." << std::endl;
        return false;
    }
    if (password == p) {
        isOnline = true;
        loginAttempts = 0;  // Reset on success
        return true;
    } else {
        loginAttempts++;
        return false;
    }
}
```
**Login logic with brute-force protection**:
1. If attempts >= 3, the account is locked â€” returns `false` immediately.
2. If password matches, set `isOnline = true`, reset the counter, return `true`.
3. If password is wrong, increment `loginAttempts`, return `false`.

```cpp
void User::logout() {
    isOnline = false;
}
```
Simply sets the online flag to `false`.

```cpp
void User::blockUser(std::string u) {
    blockedUsers.insert(u);
}
void User::unblockUser(std::string u) {
    blockedUsers.erase(u);
}
bool User::isBlocked(std::string u) const {
    return blockedUsers.find(u) != blockedUsers.end();
}
```
**STL `set` operations**: `insert` adds (ignores duplicates), `erase` removes, `find` checks membership. `find` returns an iterator â€” if it equals `end()`, the element wasn't found.

```cpp
std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "Username: " << u.username << ", Online: " << (u.isOnline ? "Yes" : "No");
    return os;
}
```
**Operator `<<` overload**: Prints user info. Returns `os` by reference to allow chaining (`cout << u1 << u2`). Uses the ternary operator to print "Yes"/"No" for the boolean.

---

### ðŸ“„ File: Admin.h / Admin.cpp

#### ðŸ”¹ Purpose
Defines `Admin`, a **derived class** of `User` with elevated privileges. Admins can moderate the system (remove users, view all users).

#### ðŸ”¹ Class Design
```
User (abstract)
  â””â”€â”€ Admin (concrete)
```

#### ðŸ”¹ Code Breakdown â€” Admin.h

```cpp
class Admin : public User {
public:
    Admin(std::string u, std::string p);
    ~Admin();
    void displayProfile() override;
    bool canModerate() override;
    void removeUserFromRoom(std::string username);
    void muteUser(std::string username);
};
```
- **`public User`**: Public inheritance â€” the "is-a" relationship. An `Admin` **is-a** `User`.
- **`override`**: Explicitly marks methods that override base-class virtuals. The compiler will error if the base class doesn't have a matching virtual method.

#### ðŸ”¹ Code Breakdown â€” Admin.cpp

```cpp
Admin::Admin(std::string u, std::string p) : User(u, p) {}
```
**Delegating to the base constructor**: Passes `u` and `p` up to `User::User()`. The Admin constructor has no additional initialization.

```cpp
void Admin::displayProfile() {
    std::cout << "Admin Profile: " << username << std::endl;
}
```
Overrides the pure virtual method. Accesses `username` directly (it's `protected` in `User`).

```cpp
bool Admin::canModerate() {
    return true;  // Admins CAN moderate
}
```
This is the key **polymorphic discriminator**. In `main.cpp`, the code calls `currentUser->canModerate()`. If the pointer points to an `Admin`, this returns `true` and the admin menu is shown. If it points to a `Member`, it returns `false`.

```cpp
void Admin::removeUserFromRoom(std::string username) {
    std::cout << "Admin " << this->username << " removed user " << username << " from room." << std::endl;
}
```
Uses `this->username` to disambiguate the class member from the parameter.

---

### ðŸ“„ File: Member.h / Member.cpp

#### ðŸ”¹ Purpose
Defines `Member`, a **derived class** of `User` representing regular (non-admin) users.

#### ðŸ”¹ Code Breakdown â€” Member.cpp

```cpp
Member::Member(std::string u, std::string p) : User(u, p) {}
```
Same delegation pattern as `Admin`.

```cpp
void Member::displayProfile() {
    std::cout << "Member Profile: " << username << std::endl;
}
```
Different output than `Admin::displayProfile()` â€” demonstrates **polymorphism**: same method name, different behavior based on object type.

```cpp
bool Member::canModerate() {
    return false;  // Members CANNOT moderate
}
```

```cpp
void Member::changePassword(std::string newPass) {
    password = newPass;
    std::cout << "Password changed for " << username << std::endl;
}
```
Member-specific functionality. Directly modifies the `protected` field `password`.

---

### ðŸ“„ File: Message.h

#### ðŸ”¹ Purpose
Defines the **abstract base class** `Message`. All message types (`TextMessage`, `EncryptedMessage`) inherit from this.

#### ðŸ”¹ Code Breakdown

```cpp
class Message {
protected:
    std::string sender;
    std::string content;
    std::string timestamp;
    bool isRead;
```
- `sender`: Username of who sent the message.
- `content`: The message text (may be encrypted in derived classes).
- `timestamp`: When the message was created.
- `isRead`: Tracks read/unread status.

```cpp
    Message(std::string s, std::string c);
    virtual ~Message() = 0;
```
Same abstract pattern as `User`. Pure virtual destructor makes `Message` non-instantiable.

```cpp
    virtual void display() = 0;
    virtual std::string getType() = 0;
```
- `display()`: Each message type renders differently (plain vs. encrypted tag).
- `getType()`: Returns `"Text"` or `"Encrypted"` â€” used by `FileManager` to determine the serialization format.

```cpp
    virtual std::string getContent() const { return content; }
```
**Virtual getter**: This is critical. `EncryptedMessage` overrides this to **decrypt** the content before returning it. This means `SearchEngine` can call `msg->getContent()` on any `Message*` and always get the plaintext â€” **polymorphism** makes encryption transparent to the search logic.

```cpp
    void setTimestamp(const std::string& ts) { timestamp = ts; }
```
Used when loading messages from file â€” restores the original timestamp instead of using the current time.

```cpp
    friend std::ostream& operator<<(std::ostream& os, const Message& m);
```
Same friend operator overload pattern as `User`.

---

### ðŸ“„ File: Message.cpp

#### ðŸ”¹ Code Breakdown

```cpp
Message::Message(std::string s, std::string c) : sender(s), content(c), isRead(false) {
    std::time_t now = std::time(nullptr);
    timestamp = std::ctime(&now);
    timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1);
}
```
- **Timestamp generation**: `std::time(nullptr)` gets the current UNIX time. `std::ctime()` converts it to a human-readable string like `"Fri May  1 16:22:07 2026\n"`.
- **Trimming**: `ctime` appends a newline. The `erase` call removes trailing whitespace/newlines by finding the last non-whitespace character and erasing everything after it.
- `isRead` defaults to `false` â€” newly created messages are unread.

```cpp
Message::~Message() {}
```
Pure virtual destructor body â€” required by C++.

```cpp
std::ostream& operator<<(std::ostream& os, const Message& m) {
    os << "[" << m.timestamp << "] " << m.sender << ": " << m.content;
    return os;
}
```
Formats messages as `[timestamp] sender: content`. Note: this outputs raw `content` (possibly encrypted). The `display()` virtual method is used for user-facing output.

---

### ðŸ“„ File: TextMessage.h / TextMessage.cpp

#### ðŸ”¹ Purpose
A concrete derived class of `Message` for **plain text** messages (no encryption).

#### ðŸ”¹ Code Breakdown

```cpp
TextMessage::TextMessage(std::string s, std::string c) : Message(s, c) {}
```
Delegates entirely to the base `Message` constructor. No additional processing.

```cpp
void TextMessage::display() {
    std::cout << *this << std::endl;
}
```
Uses the `operator<<` defined in `Message.cpp`. Since `TextMessage` doesn't encrypt, the raw `content` is already plaintext â€” this just prints it.

```cpp
std::string TextMessage::getType() {
    return "Text";
}
```
Returns the type identifier. `FileManager` uses this string when serializing to decide the format.

---

### ðŸ“„ File: EncryptedMessage.h / EncryptedMessage.cpp

#### ðŸ”¹ Purpose
A concrete derived class of `Message` that **encrypts content at creation** and **decrypts for display**. Uses a Caesar cipher internally.

#### ðŸ”¹ Class Design
```cpp
class EncryptedMessage : public Message {
private:
    int shift;  // Caesar cipher shift value (default = 3)
```
The `shift` value determines how many positions each character is rotated.

#### ðŸ”¹ Code Breakdown â€” Constructor

```cpp
EncryptedMessage::EncryptedMessage(std::string s, std::string c, int sh)
    : Message(s, c), shift(sh) {
    content = encrypt(c);
}
```
**Critical flow**:
1. The base `Message` constructor stores the plaintext in `content`.
2. Immediately after, `content` is **overwritten** with the encrypted version.
3. From this point on, `content` always holds ciphertext internally.

This means the object always stores encrypted data in memory.

#### ðŸ”¹ Code Breakdown â€” display()

```cpp
void EncryptedMessage::display() {
    std::string decrypted = decrypt(content);
    std::cout << "[" << timestamp << "] " << sender << ": " << decrypted << " (Encrypted)" << std::endl;
}
```
Decrypts the content for display and appends `(Encrypted)` as a visual indicator. Does NOT use `operator<<` because that would show raw ciphertext.

#### ðŸ”¹ Code Breakdown â€” getContent()

```cpp
std::string EncryptedMessage::getContent() const {
    return decrypt(content);
}
```
**Overrides the virtual `getContent()`** from `Message`. Returns **decrypted** plaintext. This is why `SearchEngine` can search through encrypted messages â€” it calls `msg->getContent()` and gets plaintext transparently.

#### ðŸ”¹ Code Breakdown â€” encrypt()

```cpp
std::string EncryptedMessage::encrypt(std::string text) const {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        } else if (isdigit(c)) {
            c = (c - '0' + shift) % 10 + '0';
        }
    }
    return result;
}
```
**Caesar cipher algorithm**:
1. **Range-based for loop** with `char&` â€” modifies characters in-place.
2. **For letters**: Subtract the base (`'A'` or `'a'`) to get 0â€“25, add `shift`, modulo 26, add base back. Example: `'h'` with shift 3 â†’ `(104-97+3)%26+97 = 10%26+97 = 107 = 'k'`.
3. **For digits**: Same logic with base `'0'` and modulo 10. Example: `'1'` with shift 3 â†’ `(1+3)%10 = 4 â†’ '4'`.
4. **Non-alphanumeric characters** (spaces, punctuation) pass through unchanged.

#### ðŸ”¹ Code Breakdown â€” decrypt()

```cpp
std::string EncryptedMessage::decrypt(std::string text) const {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base - shift + 26) % 26 + base;
        } else if (isdigit(c)) {
            c = (c - '0' - shift + 10) % 10 + '0';
        }
    }
    return result;
}
```
Reverse of encrypt: **subtracts** the shift. The `+ 26` (or `+ 10` for digits) prevents negative values before the modulo operation. Example: `'a'` with shift 3 â†’ `(0-3+26)%26 = 23 â†’ 'x'`.

---

### ðŸ“„ File: EncryptionManager.h / EncryptionManager.cpp

#### ðŸ”¹ Purpose
A **standalone utility class** for encryption/decryption. Used by `FileManager` to encrypt passwords and security answers before writing to `users.txt`, and to encrypt/decrypt message content during chat file I/O.

#### ðŸ”¹ Why it exists separately from EncryptedMessage
`EncryptedMessage` handles message-level encryption within the object. `EncryptionManager` is a **service class** used by `FileManager` for field-level encryption during file I/O (passwords, security answers, chat file content). This separation follows the **Single Responsibility Principle**.

#### ðŸ”¹ Code Breakdown

```cpp
class EncryptionManager {
private:
    int defaultShift = 3;
```
Default shift value. C++11 in-class member initializer.

```cpp
std::string EncryptionManager::encrypt(std::string text, int shift) {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        } else if (isdigit(c)) {
            c = (c - '0' + shift) % 10 + '0';
        }
    }
    return result;
}
```
Identical algorithm to `EncryptedMessage::encrypt()`. The `shift` parameter has a default value of `3` (declared in the header), so callers can omit it.

The `decrypt` method is the exact inverse (subtracts shift with wraparound), identical to `EncryptedMessage::decrypt()`.

<!-- PART1_END -->
### ðŸ“„ File: FileManager.h / FileManager.cpp

#### ðŸ”¹ Purpose
The **persistence layer** of the application. Handles all reading from and writing to disk â€” user records, private chat histories, and chat file discovery.

#### ðŸ”¹ Class Design (FileManager.h)

```cpp
class FileManager {
private:
    std::string usersFile = "data/users.txt";
    std::string privateChatsDir = "data/private_chats/";
```
- **In-class initializers** (C++11): File paths are hardcoded as defaults.
- `usersFile`: Single file storing all user records.
- `privateChatsDir`: Directory where each chat gets its own `.txt` file.

```cpp
public:
    void saveUsers(const std::vector<User*>& users);
    std::vector<User*> loadUsers();
    void savePrivateChat(PrivateChat* chat);
    PrivateChat* loadPrivateChat(std::string id);
    bool privateChatExists(std::string id);
    void deletePrivateChatFile(std::string id);
    std::vector<std::string> getAllChatIdsForUser(std::string username);
    std::string getUserType(User* u);
```
The interface exposes save/load for both users and chats, file existence checks, deletion, and a directory-scanning method.

#### ðŸ”¹ Code Breakdown â€” saveUsers()

```cpp
void FileManager::saveUsers(const std::vector<User*>& users) {
    try {
        std::ofstream file(usersFile);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open users file for writing.");
        }
        EncryptionManager em;
        for (auto u : users) {
            std::string encryptedPassword = em.encrypt(u->getPassword(), 3);
            std::string encryptedAnswer = em.encrypt(u->getSecurityAnswer(), 3);
            file << getUserType(u) << "," << u->getUsername() << "," << encryptedPassword
                 << "," << u->getSecurityQuestion() << "," << encryptedAnswer << std::endl;
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error: " << e.what() << std::endl;
    }
}
```
**Step-by-step**:
1. Opens `data/users.txt` with `ofstream` (overwrites entire file each time).
2. If file can't be opened, throws `runtime_error` â€” caught by the `catch` block.
3. Creates an `EncryptionManager` to encrypt sensitive fields.
4. For each user pointer: encrypts the password and security answer, then writes a CSV line: `Type,Username,EncryptedPassword,SecurityQuestion,EncryptedAnswer`.
5. The `getUserType()` helper uses `dynamic_cast` to determine if the user is Admin or Member.

**CSV format example** (from actual `users.txt`):
```
Member,noor,qrru123,murgi age na dim age,pxujl
```
Here `qrru123` is the encrypted password (plaintext `noor123` shifted by 3).

#### ðŸ”¹ Code Breakdown â€” loadUsers()

```cpp
std::vector<User*> FileManager::loadUsers() {
    std::vector<User*> users;
    try {
        std::ifstream file(usersFile);
        if (!file.is_open()) {
            return users;  // First run: no file yet, return empty
        }
        std::string line;
        EncryptionManager em;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string type, username, password, question, answer;
            std::getline(ss, type, ',');
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');
            std::getline(ss, question, ',');
            std::getline(ss, answer, ',');
            std::string decryptedPassword = em.decrypt(password, 3);
            std::string decryptedAnswer = answer.empty() ? "" : em.decrypt(answer, 3);
            User* u = nullptr;
            if (type == "Admin") {
                u = new Admin(username, decryptedPassword);
            } else if (type == "Member") {
                u = new Member(username, decryptedPassword);
            }
            if (u) {
                u->setSecurityQuestion(question);
                u->setSecurityAnswer(decryptedAnswer);
                users.push_back(u);
            }
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error: " << e.what() << std::endl;
    }
    return users;
}
```
**Step-by-step**:
1. Opens `data/users.txt` for reading. If it doesn't exist (first run), returns an empty vector gracefully.
2. Reads line-by-line using `std::getline`.
3. Parses each CSV line using `std::stringstream` and `std::getline` with `','` delimiter.
4. Decrypts the password and security answer using `EncryptionManager`.
5. Based on the `type` field, creates either `new Admin(...)` or `new Member(...)` â€” **polymorphic object creation**.
6. Sets the security Q&A and pushes the pointer into the vector.

#### ðŸ”¹ Code Breakdown â€” savePrivateChat()

```cpp
void FileManager::savePrivateChat(PrivateChat* chat) {
    try {
        std::string filename = privateChatsDir + chat->getId() + ".txt";
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open private chat file for writing.");
        }
        file << chat->getUser1() << "," << chat->getUser2() << std::endl;
        EncryptionManager em;
        for (auto msg : chat->getMessages()) {
            std::string contentToSave = msg->getContent();
            if (msg->getType() == "Encrypted") {
                contentToSave = em.encrypt(contentToSave, 3);
            }
            file << msg->getType() << "," << msg->getSender() << "," << contentToSave
                 << "," << msg->getTimestamp() << "," << (msg->getIsRead() ? "1" : "0") << std::endl;
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error: " << e.what() << std::endl;
    }
}
```
**Key detail**: `msg->getContent()` calls the **virtual** method. For `EncryptedMessage`, this returns **decrypted** plaintext. The code then **re-encrypts** it via `em.encrypt()` before saving. This ensures data at rest is always encrypted.

**File format** â€” Line 1: `user1,user2`. Subsequent lines: `Type,Sender,Content,Timestamp,IsRead`.

#### ðŸ”¹ Code Breakdown â€” loadPrivateChat()

```cpp
PrivateChat* FileManager::loadPrivateChat(std::string id) {
    try {
        std::string filename = privateChatsDir + id + ".txt";
        std::ifstream file(filename);
        // ... error checking ...
        std::string line;
        std::getline(file, line);  // First line: user1,user2
        std::stringstream ss(line);
        std::string u1_str, u2_str;
        std::getline(ss, u1_str, ',');
        std::getline(ss, u2_str, ',');
        PrivateChat* chat = new PrivateChat(u1_str, u2_str);

        while (std::getline(file, line)) {  // Message lines
            std::stringstream ss2(line);
            std::string type, sender, content, timestamp, isReadStr;
            std::getline(ss2, type, ',');
            std::getline(ss2, sender, ',');
            std::getline(ss2, content, ',');
            std::getline(ss2, timestamp, ',');
            std::getline(ss2, isReadStr, ',');
            Message* msg = nullptr;
            if (type == "Text") {
                msg = new TextMessage(sender, content);
            } else if (type == "Encrypted") {
                EncryptionManager em;
                std::string plaintext = em.decrypt(content, 3);
                msg = new EncryptedMessage(sender, plaintext, 3);
            }
            if (msg) {
                msg->setIsRead(isReadStr == "1");
                msg->setTimestamp(timestamp);
                chat->sendMessage(msg);
            }
        }
        return chat;
    } catch (...) { return nullptr; }
}
```
**Key detail for Encrypted messages**: The file stores ciphertext. The loader decrypts it with `em.decrypt()`, then passes the **plaintext** to the `EncryptedMessage` constructor â€” which **re-encrypts** it internally. This round-trip ensures the in-memory object behaves correctly.

`msg->setTimestamp(timestamp)` restores the original timestamp from the file instead of using the current time (which the constructor would set).

#### ðŸ”¹ Code Breakdown â€” getAllChatIdsForUser()

```cpp
std::vector<std::string> FileManager::getAllChatIdsForUser(std::string username) {
    std::vector<std::string> ids;
    DIR* dir = opendir(privateChatsDir.c_str());
    if (dir == NULL) return ids;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string filename = entry->d_name;
        if (filename.find(".txt") != std::string::npos) {
            std::string id = filename.substr(0, filename.find(".txt"));
            std::string search1 = username + "_";
            std::string search2 = "_" + username;
            if (id.find(search1) == 0 ||
                (id.length() >= search2.length() &&
                 id.compare(id.length() - search2.length(), search2.length(), search2) == 0)) {
                ids.push_back(id);
            }
        }
    }
    closedir(dir);
    return ids;
}
```
Uses POSIX `<dirent.h>` to scan the `private_chats/` directory. For each `.txt` file, it extracts the chat ID (filename without extension) and checks if the username appears as either the first or second participant (e.g., `alice_bob` matches both `alice` and `bob`). Used to pre-load all relevant chats before searching.

#### ðŸ”¹ Code Breakdown â€” getUserType()

```cpp
std::string FileManager::getUserType(User* u) {
    if (dynamic_cast<Admin*>(u)) return "Admin";
    if (dynamic_cast<Member*>(u)) return "Member";
    return "Unknown";
}
```
**`dynamic_cast`**: A **runtime type identification (RTTI)** mechanism. It attempts to cast the `User*` to `Admin*` or `Member*`. If the cast succeeds (non-null), the type is identified. This demonstrates **downcasting** in a polymorphic hierarchy.

---

### ðŸ“„ File: PrivateChat.h / PrivateChat.cpp

#### ðŸ”¹ Purpose
Represents a **one-to-one chat session** between two users. Holds the message history and provides send/view/read-tracking operations.

#### ðŸ”¹ Class Design (PrivateChat.h)

```cpp
class PrivateChat {
private:
    std::string id;
    std::string user1;
    std::string user2;
    std::vector<Message*> messages;
```
- `id`: Deterministic identifier â€” always `"smallerName_largerName"` (alphabetically sorted).
- `user1`, `user2`: Stored as **strings** (not `User*` pointers) to avoid dangling pointer issues when users are deleted.
- `messages`: STL `vector` of polymorphic `Message*` pointers.

```cpp
    const std::vector<Message*>& getMessages() const { return messages; }
```
Returns a **const reference** â€” avoids copying the entire vector. The caller can read but not modify.

#### ðŸ”¹ Code Breakdown â€” Constructor

```cpp
PrivateChat::PrivateChat(std::string u1, std::string u2) : user1(u1), user2(u2) {
    std::string name1 = u1;
    std::string name2 = u2;
    if (name1 > name2) std::swap(name1, name2);
    id = name1 + "_" + name2;
}
```
**Canonical ID generation**: Sorts the two names alphabetically so that a chat between `"irfan"` and `"noor"` always has ID `"irfan_noor"`, regardless of who initiates. `std::swap` is from `<algorithm>`.

#### ðŸ”¹ Code Breakdown â€” Destructor

```cpp
PrivateChat::~PrivateChat() {
    for (auto msg : messages) {
        delete msg;
    }
}
```
**Ownership semantics**: `PrivateChat` owns its `Message*` pointers. The destructor iterates and `delete`s each one to prevent memory leaks. This is the **composition** pattern â€” the chat "has" messages and manages their lifetime.

#### ðŸ”¹ Code Breakdown â€” viewHistory() and getUnreadCount()

```cpp
void PrivateChat::viewHistory() {
    for (auto msg : messages) {
        msg->display();      // Polymorphic call
        msg->setIsRead(true);
    }
}
```
`msg->display()` invokes the **virtual** method â€” `TextMessage::display()` or `EncryptedMessage::display()` depending on the actual type. After displaying, marks each message as read.

```cpp
int PrivateChat::getUnreadCount() const {
    int count = 0;
    for (auto msg : messages) {
        if (!msg->getIsRead()) count++;
    }
    return count;
}
```
Simple counter using a range-based for loop.

---

### ðŸ“„ File: SearchEngine.h / SearchEngine.cpp

#### ðŸ”¹ Purpose
Provides **keyword-based search** across message collections. Demonstrates **function overloading** (compile-time polymorphism).

#### ðŸ”¹ Code Breakdown â€” Overload 1: Search by keyword

```cpp
std::vector<Message*> SearchEngine::search(const std::vector<Message*>& messages, std::string keyword) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}
```
1. Takes messages by **const reference** (avoids copying the vector).
2. For each message, calls `msg->getContent()` â€” the **virtual** method that decrypts `EncryptedMessage` content transparently.
3. Uses `std::string::find()` for substring matching. `std::string::npos` is the "not found" sentinel value.
4. Matching messages are collected into `results`.

#### ðŸ”¹ Code Breakdown â€” Overload 2: Search by keyword + sender

```cpp
std::vector<Message*> SearchEngine::search(const std::vector<Message*>& messages,
                                            std::string keyword, std::string sender) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getSender() == sender &&
            msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}
```
Same as Overload 1, but adds a **sender filter** using `&&`. Both conditions must be true. This is **function overloading** â€” same function name, different parameter lists. The compiler selects the correct version at compile time.

---

### ðŸ“„ File: Logger.h

#### ðŸ”¹ Purpose
A **template class** for logging. Demonstrates **generic programming** â€” the logger can log any type that supports `operator<<`.

#### ðŸ”¹ Code Breakdown

```cpp
template <typename T>
class Logger {
private:
    std::string logFile;

public:
    Logger(std::string file) : logFile("data/logs/" + file + ".log") {}
    ~Logger() {}
```
- **`template <typename T>`**: Makes the class generic. `T` is the type of data to log.
- Constructor builds the log file path from a name (e.g., `"app"` â†’ `"data/logs/app.log"`).
- **Why header-only**: Template classes must be fully defined in the header because the compiler needs the full definition to instantiate them for each type.

```cpp
    void log(T message) {
        std::ofstream file(logFile, std::ios::app);
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::ctime(&now);
        timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1);
        file << "[" << timestamp << "] " << message << std::endl;
        file.close();
        std::cout << "Logged: " << message << std::endl;
    }
```
1. Opens the file in **append mode** (`std::ios::app`) â€” new entries are added at the end, preserving history.
2. Generates a timestamp (same trimming technique as `Message`).
3. Writes `[timestamp] message` to the file.
4. Also prints to console for immediate feedback.

**In `main.cpp`**, it's instantiated as `Logger<string> logger("app")` â€” so `T = string`. But the template could be instantiated with `int`, `double`, or any type with `operator<<`.

---

### ðŸ“„ File: main.cpp

#### ðŸ”¹ Purpose
The **entry point** and **orchestrator** of the entire application. Contains the CLI menu system, application loop, and all feature logic.

#### ðŸ”¹ Code Breakdown â€” Initialization (Lines 61â€“77)

```cpp
int main() {
    system("mkdir data\\private_chats 2>nul");
    system("mkdir data\\logs 2>nul");
```
Creates the required directories on startup. `2>nul` suppresses error messages if they already exist (Windows-specific).

```cpp
    vector<User*> users;
    map<string, PrivateChat*> privateChats;
    FileManager fm;
    SearchEngine se;
    EncryptionManager em;
    Logger<string> logger("app");
    User* currentUser = nullptr;
    users = fm.loadUsers();
    logger.log("Application started");
```
- **`vector<User*>`**: Dynamic array of polymorphic user pointers.
- **`map<string, PrivateChat*>`**: Maps chat IDs (e.g., `"irfan_noor"`) to chat objects. `std::map` provides O(log n) lookup, ordered by key.
- **`currentUser = nullptr`**: Tracks the logged-in user. `nullptr` means no one is logged in.
- `fm.loadUsers()`: Deserializes all users from disk into memory.

#### ðŸ”¹ Code Breakdown â€” Main Loop (Lines 79â€“391)

```cpp
    while (true) {
        if (!currentUser) {
            displayMainMenu();
            // Handle: Register, Login, Forgot Password, Exit
        } else {
            if (currentUser->canModerate()) {
                displayAdminMenu();
                // Handle: Remove User, View All Users, Logout
            } else {
                displayDashboard();
                // Handle: Private Chat, Search, Profile, Logout
            }
        }
    }
```
**State machine pattern**:
- **State 1**: Not logged in â†’ Main Menu (Register/Login/Forgot/Exit).
- **State 2**: Logged in as Admin â†’ Admin Menu.
- **State 3**: Logged in as Member â†’ Dashboard.

The `canModerate()` virtual method call determines which menu to show â€” **polymorphism in action**.

#### ðŸ”¹ Code Breakdown â€” Registration (Lines 90â€“137)

```cpp
if (choice == 1) {
    // Get username, password, type
    // Validate non-empty
    // Check for duplicate username
    bool duplicate = false;
    for (auto u : users) {
        if (u->getUsername() == username) { duplicate = true; break; }
    }
    if (duplicate) { cout << "Username already exists!"; continue; }

    // Security question setup
    User* newUser = nullptr;
    if (type == "admin") {
        newUser = new Admin(username, password);
    } else {
        newUser = new Member(username, password);
    }
    newUser->setSecurityQuestion(question);
    newUser->setSecurityAnswer(answer);
    users.push_back(newUser);
    fm.saveUsers(users);
}
```
**Polymorphic object creation**: Based on user input (`"admin"` or `"member"`), creates the appropriate derived class. The pointer is stored as `User*` â€” demonstrating **upcasting**.

#### ðŸ”¹ Code Breakdown â€” Login (Lines 139â€“162)

```cpp
for (auto u : users) {
    if (u->getUsername() == username) {
        found = true;
        if (u->login(password)) {
            currentUser = u;
            logger.log("User logged in: " + string(*currentUser));
        }
        break;
    }
}
```
- `string(*currentUser)`: Uses the **type conversion operator** (`operator string()`) defined in `User.h`.
- `u->login(password)`: Calls the login method with brute-force protection.

#### ðŸ”¹ Code Breakdown â€” Private Chat (Lines 272â€“342)

```cpp
string u1 = currentUser->getUsername();
string u2 = recipient;
if (u1 > u2) swap(u1, u2);
string chatId = u1 + "_" + u2;
```
Generates the canonical chat ID â€” same sorting logic as `PrivateChat` constructor.

```cpp
if (privateChats.find(chatId) == privateChats.end()) {
    if (fm.privateChatExists(chatId)) {
        PrivateChat* loadedChat = fm.loadPrivateChat(chatId);
        if (loadedChat) privateChats[chatId] = loadedChat;
        else privateChats[chatId] = new PrivateChat(...);
    } else {
        privateChats[chatId] = new PrivateChat(...);
    }
}
```
**Lazy loading**: Chats are loaded from disk only when first accessed. Checks in-memory cache first, then disk, then creates new.

```cpp
try {
    if (content.empty()) throw invalid_argument("Message content cannot be empty.");
    Message* msg = new EncryptedMessage(currentUser->getUsername(), content);
    chat->sendMessage(msg);
    fm.savePrivateChat(chat);
} catch (const exception& e) {
    cout << "Error: " << e.what() << endl;
}
```
**Exception handling**: Validates input, creates an encrypted message, adds it to the chat, and persists to disk. The `catch` block handles any exceptions gracefully.

#### ðŸ”¹ Code Breakdown â€” Search (Lines 344â€“376)

```cpp
vector<string> chatIds = fm.getAllChatIdsForUser(currentUser->getUsername());
for (const string& chatId : chatIds) {
    if (privateChats.find(chatId) == privateChats.end()) {
        PrivateChat* loadedChat = fm.loadPrivateChat(chatId);
        if (loadedChat) privateChats[chatId] = loadedChat;
    }
}
```
**Pre-loading**: Before searching, ensures all chats involving the current user are loaded into memory. This is critical â€” without it, the search would miss messages in chats not yet opened.

#### ðŸ”¹ Code Breakdown â€” Admin: Remove User (Lines 219â€“246)

```cpp
auto it = find_if(users.begin(), users.end(),
    [&](User* u){ return u->getUsername() == username; });
if (it != users.end()) {
    string targetUser = (*it)->getUsername();
    delete *it;
    users.erase(it);
    fm.saveUsers(users);
    // Clean up related chats to prevent dangling pointers
    auto chatIt = privateChats.begin();
    while (chatIt != privateChats.end()) {
        if (chatIt->second->getUser1() == targetUser || ...) {
            fm.deletePrivateChatFile(chatIt->second->getId());
            delete chatIt->second;
            chatIt = privateChats.erase(chatIt);
        } else { ++chatIt; }
    }
}
```
- **`std::find_if`** with a **lambda**: Searches the vector using a predicate.
- **Memory cleanup**: `delete *it` frees the user object, `users.erase(it)` removes the pointer from the vector.
- **Cascading cleanup**: Removes all chat files and objects associated with the deleted user to prevent dangling references.

#### ðŸ”¹ Code Breakdown â€” Cleanup (Lines 393â€“402)

```cpp
for (auto u : users) delete u;
for (auto pc : privateChats) delete pc.second;
logger.log("Application exited");
return 0;
```
Frees all dynamically allocated memory before exit. `pc.second` is the `PrivateChat*` value in the map pair.
---

## âš™ï¸ 5. Feature Implementation

### 5.1 Register
- **Flow**: Main Menu â†’ Option 1 â†’ Enter username, password, type, security Q&A.
- **Logic**: Checks for empty fields and duplicate usernames by iterating `vector<User*>`. Creates `Admin` or `Member` via polymorphic construction. Saves all users to disk immediately.
- **File impact**: Rewrites `data/users.txt` entirely (simple but safe).

### 5.2 Login
- **Flow**: Main Menu â†’ Option 2 â†’ Enter username and password.
- **Logic**: Linear search through `users` vector. Calls `u->login(password)` which checks the password and enforces the 3-attempt lockout. On success, sets `currentUser` pointer.
- **Type conversion**: `string(*currentUser)` invokes `operator string()` to log the username.

### 5.3 Forgot Password
- **Flow**: Main Menu â†’ Option 3 â†’ Enter username â†’ Answer security question â†’ Set new password.
- **Logic**: Finds the user, verifies the security answer via `checkSecurityAnswer()`, validates password confirmation, then calls `setPassword()` and re-saves all users.

### 5.4 Private Chat
- **Flow**: Dashboard â†’ Option 1 â†’ Enter recipient â†’ Send/View/Back sub-menu.
- **Logic**: Generates a canonical chat ID by sorting usernames alphabetically. Uses lazy loading â€” checks in-memory map first, then disk, then creates new. Messages are `EncryptedMessage` objects. Chat is saved to disk after each message.

### 5.5 Search Messages
- **Flow**: Dashboard â†’ Option 2 â†’ Enter keyword (and optional sender filter).
- **Logic**: Pre-loads all chats involving the current user from disk into the in-memory map. Iterates all loaded chats and calls `SearchEngine::search()` â€” the overloaded version (with or without sender). Results are displayed via polymorphic `display()`.

### 5.6 Admin: Remove User
- **Flow**: Admin Menu â†’ Option 1 â†’ Enter username to remove.
- **Logic**: Uses `std::find_if` with a lambda to locate the user. Deletes the object, removes from vector, saves users. Cascading cleanup: deletes all chat files and objects involving the removed user.

### 5.7 Admin: View All Users
- **Flow**: Admin Menu â†’ Option 2.
- **Logic**: Iterates `users` and uses `cout << *u` which invokes the overloaded `operator<<`.

---

## ðŸ§© 6. OOP Concepts â€” Detailed Implementation

### 6.1 Encapsulation
- **Where**: All class data members are `protected` or `private`. Access is through public getters/setters.
- **Example**: `User::password` is `protected`. External code uses `getPassword()` and `setPassword()`. The `login()` method controls authentication logic internally.

### 6.2 Inheritance
- **Where**: `Admin` and `Member` inherit from `User`. `TextMessage` and `EncryptedMessage` inherit from `Message`.
- **Type**: Public inheritance (`class Admin : public User`), establishing "is-a" relationships.
- **Depth**: Single-level hierarchy (one base, one derived).

### 6.3 Polymorphism

#### Runtime Polymorphism (Virtual Functions)
- `User::displayProfile()` â€” overridden in `Admin` (prints "Admin Profile") and `Member` (prints "Member Profile").
- `User::canModerate()` â€” returns `true` in `Admin`, `false` in `Member`. Used in `main.cpp` to switch between admin/member menus.
- `Message::display()` â€” overridden in `TextMessage` (plain output) and `EncryptedMessage` (decrypts then outputs).
- `Message::getContent()` â€” overridden in `EncryptedMessage` to return decrypted text. Enables transparent search.
- `Message::getType()` â€” returns `"Text"` or `"Encrypted"` for serialization.

#### Compile-time Polymorphism (Function Overloading)
- `SearchEngine::search()` has two overloads: one with `(messages, keyword)` and one with `(messages, keyword, sender)`.

### 6.4 Abstraction
- `User` and `Message` are **abstract classes** (pure virtual destructors + pure virtual methods).
- They define a contract (interface) that all derived classes must fulfill.
- External code works with `User*` and `Message*` pointers without knowing the concrete type.

### 6.5 Composition
- `PrivateChat` **has** a `vector<Message*>` â€” it owns and manages the lifetime of message objects.
- The `PrivateChat` destructor `delete`s all messages â€” demonstrating **ownership-based composition**.
- `main.cpp` composes the entire system: it owns `vector<User*>` and `map<string, PrivateChat*>`.

---

## ðŸ“š 7. STL Usage

### 7.1 `std::vector<User*>` and `std::vector<Message*>`
- **Why**: Dynamic arrays that grow as users register or messages are sent. O(1) amortized push_back.
- **Where**: `main.cpp` holds `vector<User*> users`. `PrivateChat` holds `vector<Message*> messages`. `SearchEngine` returns `vector<Message*> results`.

### 7.2 `std::map<string, PrivateChat*>`
- **Why**: Associates chat IDs with chat objects. Provides O(log n) lookup by key. Ordered by key (useful for iteration).
- **Where**: `main.cpp` holds `map<string, PrivateChat*> privateChats`.

### 7.3 `std::set<std::string>`
- **Why**: Stores blocked usernames. Guarantees no duplicates and provides O(log n) insert/find/erase.
- **Where**: `User::blockedUsers`.

### 7.4 `std::stringstream`
- **Why**: Parses CSV lines by treating a string as an input stream. `std::getline(ss, field, ',')` extracts comma-delimited fields.
- **Where**: `FileManager::loadUsers()` and `FileManager::loadPrivateChat()`.

### 7.5 `std::find_if` with Lambda
- **Why**: Searches a container using a custom predicate without writing a named function.
- **Where**: `main.cpp` admin user removal: `find_if(users.begin(), users.end(), [&](User* u){ return u->getUsername() == username; })`.

### 7.6 `std::swap`
- **Where**: `main.cpp` and `PrivateChat` constructor â€” sorts two usernames to create a canonical chat ID.

---

## ðŸ” 8. Advanced Concepts

### 8.1 Operator Overloading
1. **`operator<<` for `User`**: `friend` function, outputs `"Username: X, Online: Yes/No"`. Enables `cout << *u`.
2. **`operator<<` for `Message`**: `friend` function, outputs `"[timestamp] sender: content"`. Used by `TextMessage::display()`.
3. **`operator string()` for `User`**: Type conversion operator. Converts a `User` to `string` (returns username). Used as `string(*currentUser)`.

### 8.2 Templates
- **`Logger<T>`**: Generic class parameterized by the type of data to log. Instantiated as `Logger<string>`. The `log(T message)` method uses `operator<<` on `T`, so any streamable type works.
- **Header-only**: Templates must be fully defined in headers because the compiler generates code at instantiation.

### 8.3 Type Conversion
1. **Implicit upcasting**: `Admin*`/`Member*` â†’ `User*` throughout `main.cpp` (e.g., `users.push_back(newUser)`).
2. **Explicit `dynamic_cast`**: `FileManager::getUserType()` downcasts `User*` to `Admin*` or `Member*` for RTTI.
3. **User-defined conversion**: `operator string()` in `User` class.

### 8.4 Exception Handling
- **Where**: `FileManager` (all methods wrapped in `try/catch`), `main.cpp` (message sending).
- **Types thrown**: `std::runtime_error` (file I/O failures), `std::invalid_argument` (empty message).
- **Pattern**: Throw specific exceptions, catch by `const reference` (`const std::exception& e`), report via `e.what()`.

---

## ðŸ’¾ 9. File System Design

### 9.1 Directory Structure
```
data/
â”œâ”€â”€ users.txt              # All user records
â”œâ”€â”€ private_chats/
â”‚   â”œâ”€â”€ alice_bob.txt      # Chat between alice and bob
â”‚   â””â”€â”€ irfan_noor.txt     # Chat between irfan and noor
â””â”€â”€ logs/
    â””â”€â”€ app.log            # Application audit log
```

### 9.2 File Format â€” users.txt
```
Type,Username,EncryptedPassword,SecurityQuestion,EncryptedAnswer
```
Example: `Member,noor,qrru123,murgi age na dim age,pxujl`
- Password `noor123` encrypted with shift 3 â†’ `qrru123` (letters shifted, digits shifted).

### 9.3 File Format â€” Private Chat Files
```
Line 1: user1,user2
Line 2+: Type,Sender,EncryptedContent,Timestamp,IsRead(0/1)
```
Example: `Encrypted,noor,khoor,Fri May  1 16:22:07 2026,1`
- Content `hello` encrypted â†’ `khoor`.

### 9.4 File Format â€” app.log
```
[Timestamp] Event description
```
Example: `[Fri May  1 16:22:07 2026] User logged in: noor`

### 9.5 Persistence Logic
- **Save strategy**: Full rewrite on every save (users.txt). Full rewrite per chat file.
- **Load strategy**: Full load at startup (users). Lazy load for chats (on first access).
- **Encryption**: Passwords and security answers are encrypted via `EncryptionManager` during save/load. Messages are encrypted via `EncryptedMessage` class + `EncryptionManager` during save/load.

---

## ðŸ–¥ï¸ 10. CLI Flow

```
Application Start
    â”‚
    â”œâ”€â”€â”€ Not Logged In â”€â”€â”€â–º MAIN MENU
    â”‚                        â”œâ”€â”€ 1. Register â†’ input fields â†’ save â†’ back
    â”‚                        â”œâ”€â”€ 2. Login â†’ authenticate â†’ set currentUser
    â”‚                        â”œâ”€â”€ 3. Forgot Password â†’ security Q&A â†’ reset
    â”‚                        â””â”€â”€ 4. Exit â†’ cleanup â†’ terminate
    â”‚
    â”œâ”€â”€â”€ Logged In (Admin) â”€â”€â–º ADMIN MENU
    â”‚                           â”œâ”€â”€ 1. Remove User â†’ find â†’ delete â†’ cleanup
    â”‚                           â”œâ”€â”€ 2. View All Users â†’ iterate â†’ print
    â”‚                           â””â”€â”€ 3. Logout â†’ clear currentUser
    â”‚
    â””â”€â”€â”€ Logged In (Member) â”€â–º DASHBOARD
                                â”œâ”€â”€ 1. Private Chat â†’ recipient â†’ SUB-MENU
                                â”‚                      â”œâ”€â”€ 1. Send Message
                                â”‚                      â”œâ”€â”€ 2. View History
                                â”‚                      â””â”€â”€ 3. Back
                                â”œâ”€â”€ 2. Search Messages â†’ keyword â†’ results
                                â”œâ”€â”€ 3. Profile â†’ displayProfile()
                                â””â”€â”€ 4. Logout â†’ clear currentUser
```

### Input Handling
```cpp
void clearInput() {
    cin.clear();              // Reset error flags (e.g., after invalid input)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard remaining input
}
```
Called after every `cin >> choice` to clean the input buffer. Without this, leftover newlines would cause `getline` to read empty strings.

```cpp
if (!(cin >> choice)) {
    clearInput();
    cout << "Invalid input!" << endl;
    continue;
}
```
**Defensive input handling**: If the user enters a non-integer (e.g., "abc"), `cin >> choice` fails, sets the error flag, and the stream becomes unusable until cleared.

---

## âš ï¸ 11. Error Handling

| Error Scenario | Handling Mechanism |
|---|---|
| File cannot be opened for writing | `throw std::runtime_error()` â†’ caught in `catch` block |
| File doesn't exist on first run | `loadUsers()` returns empty vector gracefully |
| Empty username/password at registration | Validation check â†’ `continue` to re-prompt |
| Duplicate username | Linear search check â†’ error message â†’ `continue` |
| Wrong password | `login()` returns `false`, increments attempt counter |
| Too many login attempts (â‰¥3) | Account locked â€” `login()` rejects all further attempts |
| Empty message content | `throw invalid_argument()` â†’ caught, error displayed |
| Non-integer menu input | `cin` error state detected â†’ `clearInput()` â†’ re-prompt |
| User not found (login/chat/remove) | Conditional check â†’ "User not found!" message |
| Private chat file is empty/corrupt | `throw runtime_error()` â†’ returns `nullptr` |
| Security question not set | Conditional check â†’ "No security question set" message |
| Password confirmation mismatch | String comparison â†’ "Passwords do not match!" |

---

## ðŸš€ 12. Challenges & Fixes

### Fix 1: Timestamp Preservation
**Problem**: When loading messages from file, the `Message` constructor auto-generates a new timestamp. Loaded messages lost their original timestamps.
**Solution**: Added `setTimestamp()` setter. After constructing the message during load, the original timestamp from the file is restored.

### Fix 2: Dangling Pointer Prevention
**Problem**: `PrivateChat` originally stored `User*` pointers. When a user was deleted (admin removal), the chat's pointer became dangling â€” accessing it caused undefined behavior.
**Solution**: Changed `PrivateChat` to store usernames as `std::string` instead of `User*`. Also added cascading cleanup: when a user is removed, all their chat files and in-memory chat objects are deleted.

### Fix 3: Encryption Round-Trip
**Problem**: `EncryptedMessage::getContent()` returns decrypted plaintext. When `FileManager::savePrivateChat()` called `msg->getContent()`, it got plaintext and saved it unencrypted.
**Solution**: In `savePrivateChat()`, after getting plaintext via `getContent()`, re-encrypt it via `EncryptionManager::encrypt()` before writing. In `loadPrivateChat()`, decrypt the file content first, then pass plaintext to the `EncryptedMessage` constructor (which re-encrypts internally).

### Fix 4: Pass-by-Value Inefficiency
**Problem**: `SearchEngine::search()` originally took `vector<Message*>` by value, copying the entire vector on each call.
**Solution**: Changed to `const std::vector<Message*>&` (const reference) â€” zero-copy.

### Fix 5: Type Conversion
**Problem**: Needed a way to convert `User` objects to strings for logging.
**Solution**: Added `operator std::string() const` to `User`, returning the username.

### Fix 6: Compile-Time Polymorphism
**Problem**: Needed search with and without sender filtering.
**Solution**: Function overloading â€” two `search()` methods with different parameter lists.

### Fix 7: Exception Handling
**Problem**: File I/O failures and invalid inputs could crash the application.
**Solution**: Wrapped all `FileManager` methods and message creation in `try/catch` blocks. Throw specific exceptions (`runtime_error`, `invalid_argument`), catch by const reference.

### Fix 8: Numerical Password Encryption
**Problem**: Caesar cipher originally only handled alphabetic characters. Numerical passwords (e.g., `"12345"`) were stored as plaintext.
**Solution**: Added `isdigit()` branch to both `encrypt()` and `decrypt()` methods, using modulo 10 arithmetic with base `'0'`.

### Fix 9: Search on Encrypted Messages
**Problem**: `SearchEngine` searched `msg->getContent()`, but for `EncryptedMessage`, the base class returned raw ciphertext.
**Solution**: Made `getContent()` `virtual` in `Message` and overrode it in `EncryptedMessage` to return `decrypt(content)`. Pre-loading all user chats before search ensures all data is available.

---

## ðŸŽ¯ 13. Conclusion

### Final System Evaluation
The File-Based Chat Application v2.0 is a fully functional, persistent, multi-user messaging system that demonstrates professional-grade software design within academic constraints:
- **Modular architecture** with clear separation of concerns.
- **Polymorphic class hierarchies** for both users and messages.
- **Transparent encryption** via virtual method overriding.
- **Robust file I/O** with error handling and data integrity.
- **Template-based logging** for audit trails.

### Learning Outcomes
| Concept | Demonstrated By |
|---|---|
| Encapsulation | Protected data + public getters/setters in `User`, `Message` |
| Inheritance | `Admin`/`Member` from `User`; `TextMessage`/`EncryptedMessage` from `Message` |
| Polymorphism (Runtime) | Virtual `display()`, `canModerate()`, `getContent()`, `getType()` |
| Polymorphism (Compile-time) | Overloaded `SearchEngine::search()` |
| Abstraction | Pure virtual classes `User` and `Message` |
| Composition | `PrivateChat` owns `vector<Message*>` |
| Templates | `Logger<T>` generic logging class |
| STL | `vector`, `map`, `set`, `stringstream`, `find_if` |
| Operator Overloading | `operator<<` (User, Message), `operator string()` (User) |
| Exception Handling | `try/catch` with `runtime_error`, `invalid_argument` |
| File I/O | `ifstream`/`ofstream`, CSV parsing, directory scanning |
| Dynamic Memory | `new`/`delete`, ownership semantics, cleanup on exit |
| RTTI | `dynamic_cast` in `FileManager::getUserType()` |
| Lambda Expressions | `find_if` predicate in admin user removal |
| Encryption | Caesar cipher with letter + digit support |

---

*Document generated for viva preparation, submission documentation, and self-learning.*
*Project: File-Based Chat Application v2.0 â€” C++*
