
# 💻 Cargo Manager 



Set up the latest **cURL library** in your **Dev-C++ IDE** for C/C++ projects that require web-based API calls or downloading content over HTTP.

---

## 🔗 Step-by-Step Installation

### 1️⃣ Download cURL

➡️ Download the latest Windows-compatible version of cURL from:  
👉 [https://curl.se/windows/](https://curl.se/windows/)

Choose the version that includes **`libcurl` development files (with SSL support)**.

---

### 2️⃣ Copy Header Files

🔹 Navigate to the downloaded `curl` directory.  
🔹 Inside the `include` folder, **copy all contents**.  
🔹 Paste them into your **Dev-C++ include directory**:

```
For older versions of Dev-C++:
C:\Program Files (x86)\Dev-Cpp\MinGW64\include

For Embarcadero Dev-C++:
C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\include
```

---

### 3️⃣ Copy Library Files

🔹 Copy all files from cURL’s `lib` folder.  
🔹 Paste them into the corresponding Dev-C++ `lib` folder.

---

### 4️⃣ Copy Binary Files

🔹 Copy all files from cURL’s `bin` folder.  
🔹 Paste them into the Dev-C++ `bin` folder.

---

### 5️⃣ Configure Dev-C++ Linker

Inside **Dev-C++**, go to:

```
Tools > Compiler Options > Add the following under "Commands when calling the linker":
-static -lib-gcc -lcurl
```

---

### 6️⃣ Update File Paths in Code

Update the following lines in your **C source file** to match your image folder locations:

- Line **298**: Set folder path to save the image.
- Line **471**: Set folder path for reading/displaying the image.

---

✅ You're now ready to use cURL with Dev-C++!

---


