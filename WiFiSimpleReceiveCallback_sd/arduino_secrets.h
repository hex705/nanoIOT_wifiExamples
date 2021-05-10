// YOU MUST ::

// rename this file arduino_secrets.h
// then
// change variable below

#define SECRET_SSID "networkName"
#define SECRET_PASS "networkPassword"

//  mqtt://webtopro:69uErpSdXkZuaDDL@webtopro.cloud.shiftr.io

//mqtt://webtopro:QqAc4iyYj6SRhJVt@webtopro.cloud.shiftr.io

char SHFTR_INSTANCE[] = "instanceName" ; // your SHIFTR instance name --> this = userName in arduino docs
char SHFTR_TOKEN[] =    "tokenSecretKey" ; // your SHIFTR secret key --> this = password in arduino docs
    // if you leave these as PUBLIC -- view @ this: https://www.shiftr.io/try

char SHIFTR_ID[] = "yourTag"; // this is your tag on the shftr graph
