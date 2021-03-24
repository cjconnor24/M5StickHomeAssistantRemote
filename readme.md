# M5 Stick Home Assistant Remote

This is a work in progress

## Usage

Update the following with your wifi credentials

```
const char *ssid = "sidname";
const char *password = "pwd";
```

Then pass in your webhooks for each button:

```
postRequest("http://192.168.100.105:8123/api/webhook/activate_security");
```

## Caveat

This is a work in progress and I am RUBBISH at C programming :)
