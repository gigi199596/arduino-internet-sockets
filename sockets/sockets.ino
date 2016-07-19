// Arduino simple web server by gigi199596

#include <EtherCard.h>

#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;
boolean r1 = true;
boolean r2 = true;
boolean r3 = true;
boolean r4 = true;
const char string_0[] PROGMEM = "<H1>Arduino 4 Relay</H1> \r \n";
const char string_1[] PROGMEM = "<A HREF='1'><font color=\"red\">relay 1</font></A></br> \r \n";
const char string_2[] PROGMEM = "<A HREF='1'><font color=\"green\">relay 1</font></A></br> \r \n";
const char string_3[] PROGMEM = "<A HREF='2'><font color=\"red\">relay 2</font></A></br> \r \n";
const char string_4[] PROGMEM = "<A HREF='2'><font color=\"green\">relay 2</font></A></br> \r \n";
const char string_5[] PROGMEM = "<A HREF='3'><font color=\"red\">relay 3</font></A></br> \r \n";
const char string_6[] PROGMEM = "<A HREF='3'><font color=\"green\">relay 3</font></A></br> \r \n";
const char string_7[] PROGMEM = "<A HREF='4'><font color=\"red\">relay 4</font></A></br> \r \n";
const char string_8[] PROGMEM = "<A HREF='4'><font color=\"green\">relay 4</font></A></br> \r \n";
const char string_9[] PROGMEM = "<A HREF='i'><font color=\"black\">INVERT ALL</font></A></br> \r \n";
const char string_10[] PROGMEM = "<A HREF='o'><font color=\"black\">ALL OFF</font></A>";

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700]; // tcp/ip send and receive buffer
BufferFiller bfill;

void setup(){
  Serial.begin(57600);
  Serial.println("\n[Arduino Ethernet sockets]");

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, r1);
  digitalWrite(relay2, r2);
  digitalWrite(relay3, r3);
  digitalWrite(relay4, r4);
}

static word homePage() {
  long t = millis() / 1000;
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<meta content='1'/>"
    "<title>Sockets server</title>"
    "<h1> Arduino remoted sockets server :)</h1>"));
  if (r1 == true){
    bfill.emit_p(string_1);
  }else{
    bfill.emit_p(string_2);
  }
  if (r2 == true){
    bfill.emit_p(string_3);
  }else{
    bfill.emit_p(string_4);
  }
  if (r3 == true){
    bfill.emit_p(string_5);
  }else{
    bfill.emit_p(string_6);
  }
  if (r4 == true){
    bfill.emit_p(string_7);
  }else{
    bfill.emit_p(string_8);
  }
  bfill.emit_p(string_9);
  bfill.emit_p(string_10);
  bfill.emit_p(PSTR("<h3>Uptime: $D$D:$D$D:$D$D</h3>"), h/10, h%10, m/10, m%10, s/10, s%10);
  return bfill.position();
}
void loop(){
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  // wait for an incoming TCP packet, but ignore its contents  
  if (pos) {
    char* data = (char *) Ethernet::buffer + pos;
    if (strncmp("GET /1", data, 6) == 0){
      r1 = !r1;
      digitalWrite(relay1, r1);
    }else if (strncmp("GET /2", data, 6) == 0){
      r2 = !r2;
      digitalWrite(relay2, r2);
    }else if (strncmp("GET /3", data, 6) == 0){
      r3 = !r3;
      digitalWrite(relay3, r3);
    }else if(strncmp("GET /4", data, 6) == 0){
      r4 = !r4;
      digitalWrite(relay4, r4);
    }else if(strncmp("GET /i", data, 6) == 0){
      r1 = !r1;
      r2 = !r2;
      r3 = !r3;
      r4 = !r4;
      digitalWrite(relay1, r1);
      digitalWrite(relay2, r2);
      digitalWrite(relay3, r3);
      digitalWrite(relay4, r4);
    }else if(strncmp("GET /o", data, 6) == 0){
      r1 = true;
      r2 = true;
      r3 = true;
      r4 = true;
      digitalWrite(relay1, r1);
      digitalWrite(relay2, r2);
      digitalWrite(relay3, r3);
      digitalWrite(relay4, r4);
    }
    ether.httpServerReply(homePage());
  }
}
