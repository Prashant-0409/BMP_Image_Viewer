# 🖼️ BMP Image Viewer

A simple **BMP image viewer** written in **C** using **SDL2**.  
This project demonstrates how BMP files are structured and how pixel data can be read and displayed without relying on external image libraries.  

👉 The main goal is **educational** – to help beginners understand the **BMP file format** and the process of rendering images pixel by pixel.

---

## 🚀 Features
- Reads and displays **24-bit BMP images**.
- Supports uncompressed BMP files (**biCompression = 0**).
- Command-line based – just provide the image file path as an argument.
- Uses **SDL2** for rendering pixels on the screen.
- Helps in learning **file I/O, BMP headers, and image rendering basics**.

---

## 📂 Project Structure
```
BMP_Image_Viewer/
│── src/            # Source code
│    └── bmp_viewer.c
│── pictures/       # Sample BMP images for testing
│── README.md       # Project documentation
```

---

## ⚙️ Requirements
To build and run this project, you need:
- **GCC** (or any C compiler)
- **SDL2 library**

Install SDL2 (Linux example):
```bash
sudo apt update
sudo apt install libsdl2-dev
```

---

## 🛠️ Build & Run
Compile the project:
```bash
gcc src/bmp_viewer.c -o src/bmp_viewer -lSDL2
```

Run the program with a BMP image:
```bash
src/bmp_viewer pictures/test_image.bmp
```

---

## 🖼️ Example
Sample BMP images are provided inside the `pictures/` folder.  
Try:
```bash
src/bmp_viewer pictures/sample1.bmp
```

---

## 📑 BMP File Structure (Simplified)

```
+----------------------+-----------------------------+
| Offset (Bytes)       | Field                       |
+----------------------+-----------------------------+
| 0 - 1                | Signature ("BM")            |
| 2 - 5                | File size                   |
| 6 - 9                | Reserved                    |
| 10 - 13              | Pixel data offset           |
+----------------------+-----------------------------+
| 14 - 17              | DIB header size             |
| 18 - 21              | Image width                 |
| 22 - 25              | Image height                |
| 26 - 27              | Color planes (always 1)     |
| 28 - 29              | Bits per pixel (24 in this) |
| 30 - 33              | Compression (0 = none)      |
| 34 - 37              | Image size (may be 0)       |
| ...                  | More header fields          |
+----------------------+-----------------------------+
| Pixel Array          | Actual pixel data (BGR)     |
+----------------------+-----------------------------+
```

👉 In this project, we only handle:
- **24-bit images** (`Bits per pixel = 24`)
- **Uncompressed data** (`Compression = 0`)

---

## ⚠️ Current Limitations
- Supports only **24-bit BMP images**.
- Works only with **uncompressed BMP files (biCompression = 0)**.
- No GUI features – runs from command line.

---

## 🔮 Future Improvements
Planned features:
- Support for **32-bit BMP images**.
- Support for **different compression methods**.
- Add image operations: **rotate, crop, zoom**.
- Cross-platform build scripts (Windows & Linux).

---

## 📚 Learning Outcome
By studying this project, you will learn:
- How BMP headers are structured.
- How raw pixel data is stored in a file.
- How to use **SDL2** for rendering images pixel by pixel.
- Basics of graphics programming in C.

---

## 🤝 Contributing
Contributions are welcome!  
You can:
- Fix bugs
- Add support for new BMP formats
- Improve documentation
- Suggest new features

---

## 📜 License
This project is licensed under the **MIT License** – feel free to use and modify it.

---
