// YOU MUST ::

// rename this file arduino_secrets.h
// then
// change variable below

#define SECRET_SSID "networkName"
#define SECRET_PASS "networkPassword"


// if using the shiftr try instance -- both of following should be "public"
char SHFTR_INSTANCE[] = "public" ; // your SHIFTR instance name --> this = userName in arduino docs
char SHFTR_TOKEN[] =    "public" ; // your SHIFTR secret key --> this = password in arduino docs
    // if you leave these as PUBLIC -- view @ this: https://www.shiftr.io/try

char SHIFTR_ID[] = "yourTag"; // this is your tag on the shftr graph
