#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "Smart_Meter"                         //change this
 
const char WIFI_SSID[] = "OPPO F19 Pro";               //change this
const char WIFI_PASSWORD[] = "capedBaldy";           //change this
const char AWS_IOT_ENDPOINT[] = "a287vt8dam4p1m-ats.iot.ap-south-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUIQKjJugNcxliNrHSVTJ2AUwVb2UwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDQwNDA1NDk1
M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALYkXOeZuWEDb0vwmLmK
/StUS4xbMcv3GIf2wpCOPtOdggyhKRfwqNQhmylcbFRAeMWu+YbLKDLMkat+mvAZ
oHiKAhi0ednJyqh8jmWd1vzzMb4H+mV1EGzkqW3CZi1+XO6judITkIuK1/TB+lED
DvmYPBUHEOGr02ibVlHIkLcSwOFCSW5cHdk6PXTWFuQg0WuWv1BbjJYufWCqtdYR
Sf+Bo5CRzgJsq5JVtvfkm52+ZgCJ7vCMY9EBEOaCEQgQsfQ8px8TlBmNMVBAhjzT
5Ae/OMTT9NE3lSKFXtpxdwMl1HZHGl8I5CxlM4b1B0mWiuZgFOiTpDjft2cb64Vx
L9ECAwEAAaNgMF4wHwYDVR0jBBgwFoAUiHxskN4Br16R6aR8YHfYwjV5wbEwHQYD
VR0OBBYEFIkxFF9CmQjE9vgUgr9EnWoBDph3MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDfmHXRovWoyseQ16jcBP9ogjRU
yMxCadKrSW2QVasu+hQswS7OSJlbo9mT03tWP3iE9zWkUevCVEQv/ZLdh2uqz8Ww
hv4H3E8agpfVk/Ors1SOnrwLk7m/YN4R7ESvX82vMaWM2b3iGvzJhVsifvIceDSy
im5sY9+g5ZdBHP88y3sXN1vYjTDaZjOnsE/pT2dGUNU2Ngl2QXHtvoLfd6p+PVXP
Bei3yrJwdgjwsChYUqCSb2Q6nupjMzIi9paAon37n5h2qmMxv4sWkS3aBysBOcRl
dDPat/YwFuvzhrpjSmAhDjc3XYEIMo+FNtSe0Fin0FWB+NCgVsvPIG5xDV4/
-----END CERTIFICATE-----
 )KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAtiRc55m5YQNvS/CYuYr9K1RLjFsxy/cYh/bCkI4+052CDKEp
F/Co1CGbKVxsVEB4xa75hssoMsyRq36a8BmgeIoCGLR52cnKqHyOZZ3W/PMxvgf6
ZXUQbOSpbcJmLX5c7qO50hOQi4rX9MH6UQMO+Zg8FQcQ4avTaJtWUciQtxLA4UJJ
blwd2To9dNYW5CDRa5a/UFuMli59YKq11hFJ/4GjkJHOAmyrklW29+Sbnb5mAInu
8Ixj0QEQ5oIRCBCx9DynHxOUGY0xUECGPNPkB784xNP00TeVIoVe2nF3AyXUdkca
XwjkLGUzhvUHSZaK5mAU6JOkON+3ZxvrhXEv0QIDAQABAoIBABEF0vz+O/oaJRO2
1783gzPCfBERENVcMZm7cTGraanDZb0ibsHDBzRUM7ko3yL8p4zqLn3vjME6pz6c
5YQdEQdS9qEydNTq7BrVEUXj+4zGedalzjwfNbrHoCIW8g+8aJkRCjPdCjxQbKB+
ZJOfso2XMb5RW72LnoV/RxD7qrLBUGntlhdylXtxf4S6wlbL7JD/50nN3UwewlAZ
wFyiBLq1xPc7L8qbkXejtof/p8iM04A2+ligtJdatQ8HVo4ejbmeIzsv7VPPGXgc
4qtvyrubt2MUzNo3NS3JLY4QiHUT5eZVilni9u3fiUf7OmaB9rSiC/GtiJIW0XxU
TgO38TECgYEA6/ehCBNgfZHQpcKXuQvGTTbvQOi9Y2EmTt7p4RcOI1JlfFgFLGbB
tr3Ayfk0TfAYefqJPnoWPraxs6kNXkrZddE5Hw7LPz5FU6292ahFodio+XjBn2Gw
6IzigLGqGwVA3IJdGOmLGC0ZQiiDpDzXtgBt3+HVcSHJ7XXJchYsxZUCgYEAxZrt
nZj61bwbhPZRTBm2Hi9eTA2Kje+bSQLmYuDEe94doS5tqNjs8vDeuu93mHFPpy8R
bQ/5yvz/pGNDuxRFqTeKlJa7wBL6EmoHgrqnfwWl+84h99qazaU2Dwzlrm356MVr
KxHg5xZ5U6a6g4lINLYZo2u+Ze4Gd66f6GbeOk0CgYBMPMdkSo5kQ5Y71/EZMjqx
e8w1Fn0J/LtZxB+gP8irlNWBJRcWz2RK3GfLWZ6Sh74AuvdYni1Nuc0UFMxi6J/1
ttFTvX3hQwc3D+1Ew18r+Uouv9se2XtExy/vEHe7HyljlSLrB5mPCBMfEuPlTlsL
THwzV02UrawF8oZRO+TfOQKBgFNicBiLwHVGvnoaEu5A/0e3h1wibrA8RtPFZICf
BmqarPgiBmY0u7A8klBh0p7CWfFbfEgAcNEGd73foWolQMwKQvE2th10JJB2q5qv
txRzxrn+HvlfBun2aFxrfdRgVg+ylumCztvU8PeqqJPu70hG+4SpZ5vNmG8Sgino
lqgVAoGBAIgNF5sIPvySY3WpzpCWjF2LHs0tZlTovLV9xHKmF1O+Zfofp9CSiUCz
bv7uDPJ2YxXXX/eW4l4rqk5Y+HIXgwSrVcr8MnEsST2xQM+TZia63DlVhXc21JaE
Glr+r6bmUsDzW9d0AEg+4baA93vMhzoW4CjMWwr/eDqNGnxg0e3W
-----END RSA PRIVATE KEY-----
)KEY";
