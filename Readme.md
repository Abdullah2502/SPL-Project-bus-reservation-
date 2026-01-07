# 🚌 Bus Ticket Reservation System in C

A console-based application written in C for managing bus seat reservations. This system handles booking, searching, and canceling tickets while storing data persistently using text files.

## 📋 Features

-   **Seat Booking:** Reserve seats for 9 different buses with specific routes and timings.
-   **Real-time Validation:** Prevents booking buses that have already departed based on the current system time and date.
-   **Data Persistence:** Saves reservation details in text files generated dynamically based on the travel date and bus number (e.g., `01_07_2026bus1.txt`).
-   **Search Functionality:**
    -   Search reservations by **Passenger Name**.
    -   Search reservations by **Contact Number**.
-   **Cancellation:** Cancel specific reservations, automatically updating the records.
-   **Readable Receipts:** Generates a `read_...txt` file formatted as a ticket/receipt.
-   **Capacity Management:** Tracks seat availability (Max 40 seats per bus).

## 🛠 Tech Stack

-   **Language:** C
-   **Libraries:** `stdio.h`, `string.h`, `stdlib.h`, `time.h`, `stdbool.h`
-   **Database:** File System (Text files)

## 🚀 How to Run

### Prerequisites
You need a C compiler (like GCC) installed on your system.

### Compilation
Open your terminal/command prompt and run:

```bash
gcc main.c -o bus_system
