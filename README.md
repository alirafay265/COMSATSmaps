# 🧭 COMSATS Lahore - Smart Campus Navigation System

A fully interactive and intelligent web-based navigation platform for **COMSATS Lahore Campus**. It computes the shortest or simplest walking path between campus buildings using advanced graph algorithms: **Dijkstra** and **BFS**.

---

## 📁 Project Structure

```

project-root/
│
├── index.html               # Frontend UI (interactive map and controls)
├── navigation.cpp           # C++ engine (handles pathfinding logic)
├── navigation_engine.exe    # Compiled C++ binary
├── server.js                # Express backend server
├── LICENSE                  # MIT License
└── README.md                # This file

````

---

## 🚀 How to Run This Project

### ✅ Prerequisites

- [Node.js](https://nodejs.org/en/) (v14+ recommended)
- `g++` compiler for C++ (e.g., via MinGW or GCC)

---

### 🔧 Setup Instructions

#### 1️⃣ Compile the C++ Navigation Engine
```bash
g++ -o navigation_engine navigation.cpp
````

This creates `navigation_engine.exe` which is required for the backend to function.

> 💡 If you're on Mac/Linux, you may need to make it executable with `chmod +x navigation_engine`.

---

#### 2️⃣ Install Node.js Dependencies

```bash
npm install express cors
```

---

#### 3️⃣ Run the Backend Server

```bash
node server.js
```

The server starts at: [http://localhost:3000](http://localhost:3000)

---

#### 4️⃣ Access the Frontend

Open your browser and visit:

```
http://localhost:3000
```

Use the dropdown to select **source** and **destination**, and click **Find Route**.

---

## 📷 Screenshots

![image](https://github.com/user-attachments/assets/9cb9ea31-be07-4336-8e81-741142ad84b8)

![image](https://github.com/user-attachments/assets/7a4124f2-5658-40ae-94f5-6307579e4d8f)

![image](https://github.com/user-attachments/assets/2e1a88cd-c529-47c5-8d3c-dbcc3118b7a2)


## 🌐 API Overview

| Method | Endpoint         | Description                         |
| ------ | ---------------- | ----------------------------------- |
| `GET`  | `/api/health`    | Check backend + C++ engine status   |
| `GET`  | `/api/locations` | Get all campus locations            |
| `POST` | `/api/navigate`  | Get best path between two buildings |

### 🔄 Example POST Request to `/api/navigate`

```json
{
  "source": "N Block",
  "destination": "K Block",
  "algorithm": "dijkstra"
}
```

---

## ⚙️ Algorithms Supported

* **Dijkstra's Algorithm:** Finds the **shortest distance**
* **BFS (Breadth-First Search):** Finds path with **least number of steps**

---

## 🧠 How It Works

1. User selects source, destination, and algorithm from the frontend.
2. Backend receives the request and invokes the compiled `navigation_engine.exe`.
3. The C++ program calculates the path and returns JSON.
4. The result is rendered on the interactive campus map.

---

## 👥 Contributors

* 👨‍💻 [alirafay265](https://github.com/alirafay265)
* 👨‍💻 [iambillx](https://github.com/iambillx)

---

## 📝 License

This project is for **educational and academic purposes only**.
