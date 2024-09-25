# Victim machine
- Run indirect command through forfiles.exe
```bash
forfiles /p C:\windows\system32 /m notepad.exe /c calc.exe
```