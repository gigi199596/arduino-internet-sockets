// pins

#include "etherShield.h"
#include "ETHER_28J60.h"
#include <avr/pgmspace.h>    //bibliothèque nécessaire au stockage d'informations dans la mémoire du circuit
#include <math.h>
#include <Bounce2.h>
#include <Time.h>

int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;
boolean r1 = true;
boolean r2 = true;
boolean r3 = true;
boolean r4 = true;

int thermalSensor = 0;      // variable qui garde la valeur du capteur thermique incorporé dans la multiprise

const int button1 = 6;       // connexions des différents boutons de la multiprise
const int button2 = 7;
const int button3 = 8;
const int button4 = 9;

Bounce bouncer1 = Bounce();       // on démarre la méthode debounce associée à chaque bouton
Bounce bouncer2 = Bounce();
Bounce bouncer3 = Bounce();
Bounce bouncer4 = Bounce();

int toggle1 = 0;                  // on déclare ici le toggle qui va permettre de détecter si un bouton vient d'être enfoncé
int toggle2 = 0;
int toggle3 = 0;
int toggle4 = 0;
// On définit ici nos chaines de caractères afin de pouvoir les enregistrer dans la mémoire
prog_char string_0[] PROGMEM = "<H1>Arduino 4 Relay</H1> \r \n";
prog_char string_1[] PROGMEM = "<A HREF='?cmd1'><font color=\"red\">relay 1</font></A></br> \r \n";
prog_char string_2[] PROGMEM = "<A HREF='?cmd1'><font color=\"green\">relay 1</font></A></br> \r \n";
prog_char string_3[] PROGMEM = "<A HREF='?cmd2'><font color=\"red\">relay 2</font></A></br> \r \n";
prog_char string_4[] PROGMEM = "<A HREF='?cmd2'><font color=\"green\">relay 2</font></A></br> \r \n";
prog_char string_5[] PROGMEM = "<A HREF='?cmd3'><font color=\"red\">relay 3</font></A></br> \r \n";
prog_char string_6[] PROGMEM = "<A HREF='?cmd3'><font color=\"green\">relay 3</font></A></br> \r \n";
prog_char string_7[] PROGMEM = "<A HREF='?cmd4'><font color=\"red\">relay 4</font></A></br> \r \n";
prog_char string_8[] PROGMEM = "<A HREF='?cmd4'><font color=\"green\">relay 4</font></A></br> \r \n";
prog_char string_9[] PROGMEM = "<A HREF='?invert'><font color=\"black\">INVERT ALL</font></A></br> \r \n";
prog_char string_10[] PROGMEM = "<A HREF='?allOff'><font color=\"black\">ALL OFF</font></A>";

// A présent, définir un tableau pour accéder aux chaînes
PROGMEM const char *string_table[] ={      //création d'un tableau appelé string_table

    string_0, string_1, string_2, string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10};

char buffer[100]; // On définit un buffer qui fait la taille de la plus grande chaine de caractères arrondie à la dixaine supérieure afin de ne pas déborder

//TCP/IP SETTINGS ---------------------------------------------------------------------------------------------------------

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x3A};   // this just needs to be unique for your network, 
                                                                // so unless you have more than one of these boards
                                                                // connected, you should be fine with this value.
                                                           
static uint8_t ip[4] = {192, 168, 1, 15};                       // the IP address for your board. Check your home hub
                                                                // to find an IP address not in use and pick that
                                                                // this or 10.0.0.15 are likely formats for an address
                                                                // that will work.

static uint16_t port = 80;                                      // Use port 80 - the standard for HTTP

//-------------------------------------------------------------------------------------------------------------------------
ETHER_28J60 e;
//-------------------------------------------------------------------------------------------------------
/*
 *  the select mode allow you to choose btw celsius or fahrenheit. Select mode:
 *  0 for celcius
 *  1 for fahrenheit
 */
void Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 //=log(10000.0/(1024.0/RawADC-1)); // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
   Temp = Temp - 273.15;            // Convert Kelvin to Celcius
   e.print(Temp);
   e.print(" C // ");
   Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   e.print(Temp);
   e.print(" F.</br> \r \n");
}
//-------------------------------------------------------------------------------------------------------FLASH LED


void setup()
{ 
  e.setup(mac, ip, port);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  digitalWrite(relay1, r1);
  digitalWrite(relay2, r2);
  digitalWrite(relay3, r3);
  digitalWrite(relay4, r4);
  bouncer1.attach(button1);
  bouncer1.interval(5);
  bouncer2.attach(button2);
  bouncer2.interval(5);
  bouncer3.attach(button3);
  bouncer3.interval(5);
  bouncer4.attach(button4);
  bouncer4.interval(5);
  Serial.begin(9600);
  Serial.println("Communication etablie arduinoRelay v1");
}

void loop()
{
  //---------------------------------------------------------------------------- SECTION COMMANDE MANUELLE
  bouncer1.update();
  int state1 = bouncer1.read();
  if ( state1 == HIGH) {
    if (toggle1 == 1){
    r1 = !r1;
    toggle1 = 0;
    Serial.print("Relais 1 etat:");
    Serial.println(!r1);
    digitalWrite(relay1, r1 );
    }
  }else {
    toggle1 = 1;
  }
 bouncer2.update();
  int state2 = bouncer2.read();
  if ( state2 == HIGH) {
   if (toggle2 == 1){
    r2 = !r2;
    toggle2 = 0;
    Serial.print("Relais 2 etat:");
    Serial.println(!r2);
    digitalWrite(relay2, r2 );
    }
  }else {
    toggle2 = 1;
  }
 bouncer3.update();
  int state3 = bouncer3.read();
  if ( state3 == HIGH) {
   if (toggle3 == 1){
    r3 = !r3;
    toggle3 = 0;
    Serial.print("Relais 3 etat:");
    Serial.println(!r3);
    digitalWrite(relay3, r3 );
    }
  }else {
    toggle3 = 1;
  }
 bouncer4.update();
  int state4 = bouncer4.read();
  if ( state4 == HIGH) {
   if (toggle4 == 1){
    r4 = !r4;
    toggle4 = 0;
    Serial.print("Relais 4 etat:");
    Serial.println(!r4);
    digitalWrite(relay4, r4 );
    }
  }else {
    toggle4 = 1;
  }
  //-----------------------------------------------------------------FIN DE LA SECTION COMMANDE MANUELLE
  char* params;
  if (params = e.serviceRequest())
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[0])));
    e.print(buffer);
    if ( r1 == true){
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[1])));
    }else{
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[2])));
    }
    e.print(buffer);
    if ( r2 == true){
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[3])));
    }else{
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[4])));
    }
    e.print(buffer);
    if ( r3 == true){
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[5])));
    }else{
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[6])));
    }
    e.print(buffer);
    if ( r4 == true){
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[7])));
    }else{
      strcpy_P(buffer, (char*)pgm_read_word(&(string_table[8])));
    }
    e.print(buffer);
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[9])));
    e.print(buffer);
    Thermistor(analogRead(A0));
    e.print("</br> \r \n UT: ");
    e.print(hour() );
    e.print(":");
    e.print(minute() );
    e.print(":");
    e.print(second() );
    e.print(". \r \n");
    if (strcmp(params, "?cmd1") == 0)
    {
      r1 = !r1;
      digitalWrite(relay1, r1);
    }
    else if (strcmp(params, "?cmd2") == 0)
    {
      r2 = !r2;
      digitalWrite(relay2, r2);
    }
    else if (strcmp(params, "?cmd3") == 0)
    {
      r3 = !r3;
      digitalWrite(relay3, r3);
    }
    else if (strcmp(params, "?cmd4") == 0)
    {
      r4 = !r4;
      digitalWrite(relay4, r4);
    }
    else if (strcmp(params, "?invert") == 0){
      r1 = !r1; r2 = !r2; r3 = !r3; r4 = !r4;
      digitalWrite(relay1, r1);
      digitalWrite(relay2, r2);
      digitalWrite(relay3, r3);
      digitalWrite(relay4, r4);
    }
    if (strcmp(params, "?allOff") == 0){
      if ( r1 == false){ r1 = !r1;}
      if ( r2 == false){ r2 = !r2;}
      if ( r3 == false){ r3 = !r3;}
      if ( r4 == false){ r4 = !r4;}
      digitalWrite(relay1, r1);
      digitalWrite(relay2, r2);
      digitalWrite(relay3, r3);
      digitalWrite(relay4, r4);
    }
    e.respond();
  }
}
