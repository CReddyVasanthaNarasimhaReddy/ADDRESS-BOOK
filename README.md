# Address Book 📒

A C-based command-line **Address Book** application that lets you store, search, edit, and delete contact information. Built using file handling and structured data to demonstrate core C programming concepts.

---

## 📌 Table of Contents

- [About the Project](#-about-the-project)
- [Why This Project](#-why-this-project)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Sample Output](#-sample-output)
- [How It Works](#-how-it-works)
- [Data Structure](#-data-structure)
- [Function Reference](#-function-reference)
- [Error Handling](#-error-handling)
- [Compilation & Build Details](#-compilation--build-details)
- [Testing](#-testing)
- [Limitations](#-limitations)
- [Future Enhancements](#-future-enhancements)
- [FAQ](#-faq)
- [Author](#-author)
- [License](#-license)

---

## 🧠 About the Project

**Address Book** is a menu-driven console application written in **C** that allows a user to manage their personal contacts. Each contact stores a name, phone number, email, and address. All contacts are persisted in a CSV-style text file so the data remains available between program runs.

The application is designed with a focus on **simplicity**, **clarity**, and **modularity**. It serves as an excellent learning project for anyone getting started with systems programming in C, as it touches on nearly every foundational topic in the language.

This project is ideal for beginners learning:

- Structures (`struct`) and typedefs
- File I/O (`fopen`, `fscanf`, `fprintf`, `fclose`, `fseek`)
- String handling (`strcpy`, `strcmp`, `strtok`, `strcspn`)
- Dynamic memory management (`malloc`, `free`)
- Menu-driven program design
- Input validation and error recovery
- Modular source file organization

---

## ❓ Why This Project

Unlike simple "hello world" tutorials, a full Address Book touches **real-world programming concerns**:

1. **State management** — keeping an array of records in memory while mirroring them on disk
2. **Data integrity** — preventing duplicates and validating input
3. **User experience** — clear prompts, confirmations, and error messages
4. **Extensibility** — the module boundaries make it easy to swap the storage backend

If you're learning C, this project gives you a realistic target that is not too complex but still exercises most of the language.

---

## ✨ Features

- ✅ **Add** a new contact (name, phone, email, address)
- ✅ **Search** a contact by name or phone number
- ✅ **Edit** an existing contact's details
- ✅ **Delete** a contact
- ✅ **List** all saved contacts
- ✅ **Persistent storage** — data saved in `contacts.csv`
- ✅ **Input validation** — checks for duplicate phone numbers, empty fields
- ✅ **Modular design** — separated into logical source files
- ✅ **Auto-create** the storage file if it doesn't exist
- ✅ **Confirmation prompt** before destructive operations (delete)
- ✅ **Case-insensitive** name search

---

## 📁 Project Structure

```
address-book/
├── main.c          # Entry point, menu loop, user interaction
├── contact.c       # CRUD operations (add, search, edit, delete, list)
├── contact.h       # Contact struct and function prototypes
├── file_io.c       # File loading/saving utilities
├── file_io.h       # File I/O prototypes
├── utils.c         # Helper functions (validation, trimming)
├── utils.h         # Helper prototypes
├── contacts.csv    # Persistent storage file (auto-generated)
├── Makefile        # Build automation
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- GCC / Clang compiler
- Linux / macOS / Windows (WSL or MinGW)
- Basic terminal knowledge

### Build

```bash
gcc *.c -o addressbook
```

Or explicitly:

```bash
gcc main.c contact.c file_io.c utils.c -o addressbook
```

Or with a Makefile:

```bash
make
```

### Run

```bash
./addressbook
```

---

## 📖 Usage

When you launch the program, you'll see a menu:

```
========== ADDRESS BOOK ==========
1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Exit
==================================
Enter your choice:
```

### Example Session

**1. Add Contact**

```
Enter name    : Naveen Reddy
Enter phone   : 9876543210
Enter email   : naveen@example.com
Enter address : Hyderabad, India

[+] Contact added successfully.
```

**2. Search Contact**

```
Enter name or phone to search: Naveen

[+] Contact found:
    Name    : Naveen Reddy
    Phone   : 9876543210
    Email   : naveen@example.com
    Address : Hyderabad, India
```

**3. Edit Contact**

```
Enter name to edit: Naveen Reddy
Enter new phone   : 9123456780
Enter new email   : naveen.new@example.com
Enter new address : Bengaluru, India

[+] Contact updated successfully.
```

**4. Delete Contact**

```
Enter name to delete: Naveen Reddy

Are you sure? (y/n): y
[+] Contact deleted successfully.
```

**5. List All Contacts**

```
------ All Contacts (3) ------
1. Naveen Reddy   | 9876543210 | naveen@example.com
2. Ravi Kumar     | 9988776655 | ravi@example.com
3. Priya Sharma   | 9012345678 | priya@example.com
-------------------------------
```

---

## 📸 Sample Output

```
$ ./addressbook

========== ADDRESS BOOK ==========
1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Exit
==================================
Enter your choice: 1

--- Add New Contact ---
Enter name    : Naveen Reddy
Enter phone   : 9876543210
Enter email   : naveen@example.com
Enter address : Hyderabad, India

[+] Contact added successfully.

========== ADDRESS BOOK ==========
1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Exit
==================================
Enter your choice: 5

------ All Contacts (1) ------
1. Naveen Reddy   | 9876543210 | naveen@example.com
-------------------------------
```

---

## 🔬 How It Works

1. On startup, the program reads `contacts.csv` into an in-memory array of `Contact` structs.
2. The user selects an option from the menu.
3. The corresponding operation runs on the in-memory array.
4. After every add / edit / delete, the entire array is **rewritten** back to `contacts.csv`.
5. On exit, the file is flushed and closed cleanly.

### File Format (`contacts.csv`)

```
Naveen Reddy,9876543210,naveen@example.com,Hyderabad India
Ravi Kumar,9988776655,ravi@example.com,Chennai India
```

Each line represents one contact, with fields separated by commas. The address field is written last so that any commas inside it are naturally absorbed into the final field. (For a more robust format, see "Future Enhancements".)

### Flow Diagram

```
       +-------------+
       |   main()    |
       +------+------+
              |
              v
      +---------------+
      | load_contacts |  <-- reads contacts.csv
      +-------+-------+
              |
              v
      +---------------+
      |   menu loop   |
      +-------+-------+
              |
   +----------+----------+----------+----------+
   |          |          |          |          |
   v          v          v          v          v
 add()     search()    edit()    delete()   list()
   |          |          |          |          |
   +----------+----------+----------+----------+
              |
              v
      +---------------+
      | save_contacts |  --> writes contacts.csv
      +---------------+
```

---

## 🗂️ Data Structure

```c
typedef struct {
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
} Contact;
```

| Field   | Size  | Purpose                     |
|---------|-------|-----------------------------|
| name    | 50    | Contact's full name         |
| phone   | 15    | Phone number (with country) |
| email   | 50    | Email address               |
| address | 100   | Postal address              |

Additional globals:

```c
#define MAX_CONTACTS 1000
extern Contact contacts[MAX_CONTACTS];
extern int contact_count;
```

---

## 📚 Function Reference

### `contact.c`

| Function | Description |
|----------|-------------|
| `void add_contact(void)` | Prompts for fields and appends a new contact |
| `void search_contact(void)` | Finds a contact by name or phone |
| `void edit_contact(void)` | Edits fields of an existing contact |
| `void delete_contact(void)` | Removes a contact after confirmation |
| `void list_contacts(void)` | Prints all contacts in a table |

### `file_io.c`

| Function | Description |
|----------|-------------|
| `int load_contacts(const char *path)` | Reads CSV into memory; returns count or -1 |
| `int save_contacts(const char *path)` | Writes all contacts back to CSV |
| `int append_contact(const char *path, const Contact *c)` | Appends a single contact (optional fast path) |

### `utils.c`

| Function | Description |
|----------|-------------|
| `void trim_newline(char *s)` | Strips trailing `\n` / `\r` |
| `int is_valid_phone(const char *s)` | Validates digits, `+`, `-`, ` ` |
| `int is_valid_email(const char *s)` | Basic `user@domain.tld` check |
| `int find_by_name(const char *name)` | Returns index or -1 |
| `int find_by_phone(const char *phone)` | Returns index or -1 |

---

## 🛡️ Error Handling

| Scenario                          | Behavior                                     |
|-----------------------------------|----------------------------------------------|
| Contacts file missing             | Creates a new empty file                     |
| Duplicate phone number            | Rejects with error message                   |
| Empty field during add            | Prompts again for input                      |
| Contact not found                 | Prints `No matching contact found`           |
| File read/write failure           | `perror` reports the system error            |
| Invalid menu choice               | Prints `Invalid choice, try again`           |
| Too many contacts                 | Rejects with `Address book is full`          |
| Invalid phone format              | Rejects with `Invalid phone number`          |
| Invalid email format              | Rejects with `Invalid email address`         |

---

## 🧾 Compilation & Build Details

### Manual build

```bash
gcc -Wall -Wextra -std=c11 -o addressbook \
    main.c contact.c file_io.c utils.c
```

### Sample Makefile

```makefile
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
TARGET  = addressbook
SRCS    = main.c contact.c file_io.c utils.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
```

Then run:

```bash
make
./addressbook
```

---

## 🧪 Testing

### Manual Tests

| Test Case | Steps | Expected Result |
|-----------|-------|-----------------|
| Add valid contact | Menu → 1 → fill fields | `[+] Contact added successfully.` |
| Add duplicate phone | Add contact with same phone | `[-] Phone number already exists.` |
| Add empty name | Menu → 1 → blank name | Re-prompts for name |
| Search existing | Menu → 2 → existing name | Contact details shown |
| Search non-existent | Menu → 2 → `ZZZ` | `No matching contact found` |
| Edit contact | Menu → 3 → edit phone | Updated successfully |
| Delete with `n` | Menu → 4 → answer `n` | Contact preserved |
| Delete with `y` | Menu → 4 → answer `y` | Contact removed |
| List all | Menu → 5 | Table printed |
| Persistence | Add → exit → relaunch → list | Contact still present |

### Automated Test Harness (optional)

You can build a small test file `test_contact.c` that:

1. Creates a temporary `contacts.csv`
2. Adds a known contact
3. Calls `load_contacts()` and asserts count == 1
4. Calls `search_contact()` and compares output

Compile with:

```bash
gcc -Wall -Wextra -std=c11 -o test_contact \
    test_contact.c contact.c file_io.c utils.c
./test_contact
```

---

## ⚠️ Limitations

- Maximum number of contacts is limited by `MAX_CONTACTS` (default: 1000).
- Data is stored in **plain text** — no encryption.
- No support for multiple phone numbers or emails per contact.
- Names must be unique for edit/delete operations.
- Not thread-safe.
- Comma inside address may confuse a naive CSV parser.
- No pagination for large lists.
- No undo for deletion.

---

## 🚧 Future Enhancements

- [ ] Store data in a **binary file** or **SQLite** database
- [ ] Add **search by partial match** (substring)
- [ ] Support **multiple phone numbers** and **emails** per contact
- [ ] Add **sorting** (by name, date added)
- [ ] Import / export to **CSV and vCard (.vcf)**
- [ ] Password-protect the address book
- [ ] Simple **GUI using GTK or Qt**
- [ ] **Unit tests** with a framework like `Unity` or `Check`
- [ ] Use proper **CSV escaping** (double-quote fields containing commas)
- [ ] Add **pagination** to the list view

---

## ❓ FAQ

**Q: Where is the data stored?**
A: In `contacts.csv` in the same directory as the executable.

**Q: Can I edit `contacts.csv` by hand?**
A: Yes — just keep the comma-separated format. Close the program first to avoid overwrites.

**Q: Why does the program overwrite the whole file on every change?**
A: Simplicity. For a small number of contacts, this is fast enough. For larger datasets, use a database.

**Q: Does it work on Windows?**
A: Yes, via MinGW or WSL. The code uses only standard C library functions.

**Q: How do I increase the contact limit?**
A: Change `MAX_CONTACTS` in `contact.h` and rebuild.

---

## 👨‍💻 Author

**C REDDY VASANTHA NARASIMHA Reddy**

- 💼 **LinkedIn:** [linkedin.com/in/c reddy vasantha narasimha reddy]([https://www.linkedin.com/in/naveen-kumar-reddy-vangimalla](https://www.linkedin.com/in/reddy-vasantha-narasimha-reddy-c-690279352/?lipi=urn%3Ali%3Apage%3Ad_flagship3_profile_view_base_contact_details%3Bd3%2Bw3uVRTVCv%2FVUkOw0Xwg%3D%3D))
- 📧 **Email:** crvnreddy48@gmail.com
- 📍 **Location:** India

### 🔗 Connect with Me

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/naveen-kumar-reddy-vangimalla)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/naveenreddy-vangimalla)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:naveenreddy.vangimalla@example.com)

> 💡 *"Programs must be written for people to read, and only incidentally for machines to execute."* — Harold Abelson

---

## 📄 License

This project is released under the **MIT License**.

```
MIT License

Copyright (c) 2025 Vangimalla Naveen Kumar Reddy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 🙏 Acknowledgements

- Inspired by classic C mini-projects for beginners
- File I/O best practices from the C community
- CSV handling patterns from open-source projects
- Menu design inspired by classic UNIX utilities

---

⭐ **If you found this project helpful, please give it a star!** ⭐
