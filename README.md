# C++ P2P Chat Application

![Language](https://img.shields.io/badge/language-C++17-blue.svg)
![Framework](https://img.shields.io/badge/framework-Qt-green.svg)
![Library](https://img.shields.io/badge/library-Boost.Asio-orange.svg)
![Build](https://img.shields.io/badge/build-CMake-red.svg)

A multithreaded TCP chat application featuring Protobuf and boost::asio based communication and a Qt graphical user interface.

**Currently NAT is not taken into account, therefore the app only works in LAN networks. In the future a STUN server could be implemented to solve this.**

**Note:** I've made this as an educational project developed to explore C++ concepts such as networking, multithreading, memory management. While fully functional, the app is simple and a bit limited and certain parts require a bit more polish, therefore it is not intended for production use as a secure messaging platform.

---

## Screenshots

| Main Menu | Chat Window |
|:---:|:---:|
| *[<img width="499" height="426" alt="Screenshot from 2025-12-30 16-34-38" src="https://github.com/user-attachments/assets/c7cba487-bccc-49f3-85c2-33fb95f9904f" />
]* | *<img width="405" height="260" alt="Screenshot from 2025-12-30 16-36-02" src="https://github.com/user-attachments/assets/e9ecc4e1-d36c-4f33-9736-46119729ae15" />
<img width="499" height="426" alt="Screenshot from 2025-12-30 16-34-54" src="https://github.com/user-attachments/assets/f41538f1-6525-4487-9a44-285f25658911" />
<img width="499" height="426" alt="Screenshot from 2025-12-30 16-35-35" src="https://github.com/user-attachments/assets/e17167d6-42b4-4aff-aaa2-650f1bae2f5b" />

* |
| *Manage hosts and connections* | *Real-time messaging interface* |

---

## Learning Outcomes

I've built the project from scratch with a focus on understanding these concepts:

* **Networking & Asynchronous IO**: Non-blocking (mostly) TCP server/client architecture using **Boost.Asio**. I've handled socket lifecycles, async read/write operations, and TCP stream management.
* **Multithreading & Concurrency**: I've separated the **GUI (Main Thread)** from the **Network Logic (IO Thread)**. I also did my best to make it thread-safe by utilizing `std::mutex` for data protection and `Qt Signals/Slots` for cross-thread communication.
* **Memory Management**: Used smart-pointers to ensure leak-free resource management and `std::enable_shared_from_this` for safer object lifecycles across threads.
* **Data Serialization**: I've defined a custom message format using **Google Protocol Buffers (Protobuf)** for efficient structured data exchange.
* **GUI Development in C++**: While I already knew signal/slots since I've used Qt previously in Python, I also had the chance to learn it at a bit more advanced level here.
* **Testing code**
* **Build Systems**: Used pure **CMake** to glue all the dependencies together (Qt, Boost, Protobuf, OpenSSL).

---

## Features

* Instant text communication between clients.
* P2P - Acts as both a client and a server; any instance can host or connect.
* You can save and manage a list of known IP addresses.
* **Connection Handling**: Graceful handling of disconnects, timeouts, and unavailable hosts.
* **Responsive UI**: Qt-based interface that remains fluid during network operations thanks to the background IO thread.

---

## Architecture Overview

The application is formed of two 

### 1. The Core (`ChatController` & `SessionManager`)

### 2. The Network Library (`chat_lib`)


---

## Getting Started

### Prerequisites
Ensure you have the following installed on your system:

* **C++ Compiler** (supporting C++17 or later)
* **CMake** (3.14+)
* **Qt 5 or 6** (Core, Widgets)
* **Boost Libraries** (System, Thread, Asio)
* **Protocol Buffers** (Protobuf)
* **OpenSSL** (Required for SSL sockets)

### Installation & Build

1.  **Clone the repository**
    ```bash
    git clone https://github.com/DeloranV/p2p_chat.git
    cd p2p_chat
    ```

2.  **Create a build directory**
    ```bash
    mkdir build && cd build
    ```

3.  **Configure with CMake**
    ```bash
    cmake .. 
    ```

4.  **Build**
    ```bash
    cmake --build . --parallel $(nproc)
    ```

5.  **Run**
    ```bash
    ./chat_exec
    ```

---

## Protocol Buffers

The application uses a custom Protocol Buffer definition for messages:

```protobuf
message ChatMessage {
  string timestamp = 1;
  string sender_ip = 2;
  string msg_contents = 3;
}
