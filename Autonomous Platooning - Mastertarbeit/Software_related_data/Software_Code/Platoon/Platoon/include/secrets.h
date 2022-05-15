/**
 *
 * secrets.h - WiFi and AWS secrets
 * 
 * Copyright (C) 2021  Institute of Communication Networks (ComNets), 
 *                     Hamburg University of Technology (TUHH)
 *           (C) 2021  Ahmed Shaheen
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/* ****************** Includes ****************** */ 
#include <pgmspace.h>
/* ****************** Defines ****************** */
#define THINGNAME "Esp32"
/* ****************** Secret global variables ****************** */ 
const char WIFI_SSID[] = "TP-Link_9BA6";
const char WIFI_PASSWORD[] = "14672668";
const char AWS_IOT_ENDPOINT[] = "a1zidheuopaxeb-ats.iot.us-west-2.amazonaws.com";

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

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUVDrbdFNc08FjqOMyEcNVpwWBFt8wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDQwODAxMTgw
N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALkFPydXkgzNddxFjJpY
UgNcNwn6NpdLw2YfTFhuJisAUZGZ1opavQI3NoFqIWoZeRPFT3l7tiG3dNu8b/HN
PG21v/cOvGMv5Tfh9MAcCtILVkoI0CO2X8KpzV3Zq3DYW/+MoqHFXsGR/g64H1d+
sbp6ob6SI7bWWUbbo7uipmB2nDWV+mcsvV/2BCuyYJEg5jDGQCz6AMBaoj72ruSz
PGdEhS5RiFWKdXH1VlyMgeQXKyEnxYG3VA60qaRJGQq5fCoENY5YMLWO20oZKHf5
1K4T29ad0wmJ+GHXsWRM21Z4aBFdnY+XjNgjzq1YG03pS6Ix95xMwyIwTflT/VPU
1xECAwEAAaNgMF4wHwYDVR0jBBgwFoAUBTa+SGd93TmoR4C9YGx+GycGd3YwHQYD
VR0OBBYEFA9DVJj8binbbdG2wc7hXefx/SWhMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCKGOnyx9n1IAxbsWruyVlLso3+
PfRJ7O2fUOlQ18ncIK0J9xeaM5SxcN7VmbJSXpnMV0RG/RH+Gew9iuR6U3xmoUJU
/p7SDbLL/ZbiF2uafpsHfa5z2DFT4fCgBRdj9eHl8FcKpBtOPZ1LQFlloSYRFK7C
8klZLo1R+L7y9yREk/batGH6PlLbwkmHSAZB6RdDZQsCwrbywDUN8czbvvaWBsGK
otSnCviNoyK0E0QSF7U+epm7K6H62wM9A/KRfwog8j0uHCa7NxUjLBF2n4gBP5It
LinHjuw5Yf76z53bT4GWYYS1mktEf7mgE3WLyM8hRK+CZHn+qq+de4Yn8ti7
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAuQU/J1eSDM113EWMmlhSA1w3Cfo2l0vDZh9MWG4mKwBRkZnW
ilq9Ajc2gWohahl5E8VPeXu2Ibd027xv8c08bbW/9w68Yy/lN+H0wBwK0gtWSgjQ
I7ZfwqnNXdmrcNhb/4yiocVewZH+DrgfV36xunqhvpIjttZZRtuju6KmYHacNZX6
Zyy9X/YEK7JgkSDmMMZALPoAwFqiPvau5LM8Z0SFLlGIVYp1cfVWXIyB5BcrISfF
gbdUDrSppEkZCrl8KgQ1jlgwtY7bShkod/nUrhPb1p3TCYn4YdexZEzbVnhoEV2d
j5eM2CPOrVgbTelLojH3nEzDIjBN+VP9U9TXEQIDAQABAoIBAAnWspYH/Rc7McJF
3IU0nx/YnoCkUpTXDYv3rBqjuNneiXfho1v2GUjt4LMfDqnSsvKPMnu2TWgbllY8
/gLws/7thEjB+tiXamv/UwGIPDcRLUSAlXjgsNTsLKSJ96jniHTdaKSLl09Z0RW9
SsVfUlolPUaiBM4rNdIjyeAndQt6C+GerVRuhxNeidYkzbPv4Ga/6naWPCNwPSbK
racusD4gc6d6kQUHfnp+5YMHJuDNOIMXelrh8nClA+qhnScE5KJFdzzc/HkKn9E/
26sPL9Vo7JDLtW6/fe+E+wfvLqTOMeyibV3WBQmpxKvWn1fgGGx5kpskuVSjpTXb
z6FnmAECgYEA9Z0pN/XByEFBNLRs1y21X+X5D1iZiftM/bpeFT0qXtD7c/9yW3QF
udlXA24SQaZf8lRnlO4OpFJpw4oSwpFZmFM/D8mDyB0WEuUhUGR8YQUeI1SHypMJ
wm5MTZDph7vJMgX1LgouDF5b31tFxir/OfeZ/KhwpGC04PVznZvmK5ECgYEAwNgl
JFqoCXms3KNfZ7C6d3sv1CmcIbrQoSL7vENjAO8Lc8S1j8jfV577UiEKh1n9WdUy
+KYl6HmPPyi3yT3xp8/blpNgUh2R6moiTwKa/VlsSIF6btRP00v+YlzilhWXSKRS
LYlshdyFuZQWpzm6OeEZeu/LoXvYlMrMW4P7M4ECgYAEpayZ+nRoLZPmQ2OrzpmX
7un/eFWvXqneQyB0lmuuz5VyZGrtgAx7r7kNv49o3pUCKMas8rQkN8r4gCxKsiVX
1Htk+RMdPi+ku+EdfEk+LLKdSIQpOQ7+NsgKz6sbfloYMDSrYlXstfxXBYsUbMvX
dO/c7/LxqULC3uIJIWIBgQKBgGRNR+xDttjOz4km9E1zT1kr2nGofsvQZgkZsAN4
rTrkGnnJW4IAwaHKT/+krdw+gxbBXDSV/muPJmF8ZTMno9RbuWP1HYk4VhetwlCE
E2copriDl9GjXi2RfitdEoFrk3c1+IQ00RxC2c7vZmTuEp1eJimaJbjFOJ4TaP1E
hViBAoGAFVFxb6UMbX3gI7QMfWmaKrMA291cphyHjXGI2GYNqZfLh6Kv/SnP2fhK
fgtJQbNCkDUtaiKwYq5kCSw/qWFQz/03V/Vir9IqtMmUQv3Hw1qa9+m/Ke5qZBko
NKZMjyvu/zaQdSFidCWGIbh8BOroYMmcLtjHT/2ik8UKYzOrW0o=
-----END RSA PRIVATE KEY-----
)KEY";
