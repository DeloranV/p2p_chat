# C++ P2P Chat Application


![GUI](https://img.shields.io/badge/gui-Qt-green.svg)
![Networking](https://img.shields.io/badge/networking-Boost.Asio-yellow.svg)
![Serialization](https://img.shields.io/badge/serialization-protobuf-red.svg)
![Build](https://img.shields.io/badge/build-CMake-orange.svg)
![Testing](https://img.shields.io/badge/testing-GoogleTest-blue.svg)
![Code_style](https://img.shields.io/badge/code_style-Google-purple.svg)

A multithreaded TCP chat application featuring a graphical user interface.

**Currently NAT is not taken into account, therefore the app only works in LAN networks. In the future a STUN server could be implemented to solve this.**

**Note:** I've made this as an educational project developed to explore C++ concepts such as networking, multithreading, memory management. While fully functional, the app is simple and a bit limited and certain parts require a bit more polish, therefore it is not intended for production use as a secure messaging platform.

---

## Screenshots
### Some views from the application are not displayed here

|                                                                            Main Menu                                                                             |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| <img width="499" height="426" alt="Screenshot from 2025-12-30 16-34-38" src="https://github.com/user-attachments/assets/c7cba487-bccc-49f3-85c2-33fb95f9904f" /> 

|                                                                             Add Host                                                                             |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| <img width="499" height="426" alt="Screenshot from 2025-12-30 16-34-54" src="https://github.com/user-attachments/assets/f41538f1-6525-4487-9a44-285f25658911" /> 

|                                                                           Chat Window                                                                            |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| <img width="499" height="426" alt="Screenshot from 2025-12-30 16-35-35" src="https://github.com/user-attachments/assets/e17167d6-42b4-4aff-aaa2-650f1bae2f5b" /> 

|                                                                        Host Disconnected                                                                         |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| <img width="405" height="260" alt="Screenshot from 2025-12-30 16-36-02" src="https://github.com/user-attachments/assets/e9ecc4e1-d36c-4f33-9736-46119729ae15" /> 

---

## Learning Outcomes

* **Networking & Asynchronous IO**: Non-blocking (mostly) TCP server/client architecture using **Boost.Asio**. I've handled socket lifecycles, async read/write operations, and TCP stream management.
* **Multithreading & Concurrency**: I've separated the **GUI (Main Thread)** from the **Network Logic (IO Thread)**. I also did my best to make it thread-safe by utilizing `std::mutex` for data protection and `Qt Signals/Slots` for cross-thread communication.
* **Memory Management**: Used smart-pointers to ensure leak-free resource management and `std::enable_shared_from_this` for safer object lifecycles across threads.
* **Testing code**: Application was split into a GUI executable and a testable core library which provides the messaging capabilities. The tests for this portion are written using the industry standard **Google Test (GTest)** library.
* **Data Serialization**: I've defined a custom message format using **Google Protocol Buffers (Protobuf)** for efficient structured data exchange.
* **GUI Development in C++**: While I already knew signal/slots since I've used **Qt** previously in Python, I also had the chance to learn it at a bit more advanced level here.
* **Build Systems**: Used pure **CMake** to glue all the dependencies together (Qt, Boost, Protobuf, OpenSSL).

---

## Architecture Overview

The application is split into two main components in order to provide more testability and modularity.

### 1. Core Library (`core_lib`)
Core of the chat functionality, provides **Boost.Asio** server/client objects as well as **protobuf** message format and other utilies. 
Main target of unit and integration tests.

### 2. GUI Application  (`app`)
The main executable which provides a graphical interface and controlling logic. It heavily utilizes the core library along with **Qt** widgets, communicating with
the rest of the application through signals/slots.

---

## Building & Installing

### Prerequisites
* **Linux** (preferably a Debian distro - was tested only on Ubuntu 22.04)
* **C++ Compiler** (supporting C++17 or later)
* **CMake** (3.14+)
* **Qt 5 or 6** (Core, Widgets)
* **Boost.Asio**
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
