
#include <TinyGPS.h>

#include <LiquidCrystal.h>








LiquidCrystallcd(48, 46, 28, 26, 24, 22);



#define DEFAULT_SPEED_LIMIT 55

#define NSPEEDZONES 8



booleandebugMode = true;



boolean speeding = false;



class Vertex {

public:

Vertex(float llat, float llng) {

lat = llat;

lng = llng;

}

floatlat;

floatlng;

42
};



classSpeedZone {

public:

SpeedZone(int s) {

speedLimit = s;

}

voidsetVertices(int n, Vertex *v) {

nVertices = n;

vertices = v;

}

intnVertices;

Vertex *vertices;

intspeedLimit;

};



SpeedZone *speedZones[NSPEEDZONES];

TinyGPSgps;



void setup() {

Serial.begin(9600);

Serial1.begin(9600);	//to be used by gsm module

Serial1.print("\r");

delay(1000);	//Wait for a second while the modem sends an "OK"

Serial1.print("AT+CMGF=1\r");	//Because we want to send the SMS in text mode



43
delay(1000);



Serial1.print("AT+CSCA=\"+254733000810\"\r"); //Setting for the SMS Message center number, delay(1000);


lcd.begin(16, 2);



//Print a message to the LCD.

lcd.print("gps search....");



setupSpeedZones();






Allow Eb-365 to power up delay(2000);


}

voidsetupSpeedZones() {

// jkuat avenue

speedZones[0] = &SpeedZone(40);

speedZones[0]->setVertices(4, (Vertex[4]){

Vertex(-1.10007761, 37.01458699),

Vertex(-1.09518616, 37.01458699),

Vertex(-1.09518616, 37.01486594),

Vertex(-1.10012052, 37.01490885)});



44





// main gate

speedZones[1] = &SpeedZone(15);

speedZones[1]->setVertices(8, (Vertex[8]){

Vertex(-1.10228734, 37.01444751),

Vertex(-1.10152573, 37.01392180),

Vertex(-1.10104302, 37.01395399),

Vertex(-1.10009906, 37.01459772),

Vertex(-1.10012052, 37.01490885),

Vertex(-1.10113957, 37.01425439),

Vertex(-1.10143992, 37.01425439),

Vertex(-1.10206208, 37.01472646)});



// jkuat exit road

speedZones[2] = &SpeedZone(50);

speedZones[2]->setVertices(4, (Vertex[4]){

Vertex(-1.10553757, 37.01688296),

Vertex(-1.10230879, 37.01446897),

Vertex(-1.10208353, 37.01473719),

Vertex(-1.10529086, 37.01714045)});








// science street/ NSC bypass



45
speedZones[3] = &SpeedZone(30);

speedZones[3]->setVertices(6, (Vertex[6]){

Vertex(-1.09829695, 37.01456553),

Vertex(-1.09845785, 37.01325661),

Vertex(-1.09623739, 37.01308495),

Vertex(-1.09621594, 37.01335317),

Vertex(-1.09818968, 37.01351410),

Vertex(-1.09812532, 37.01456553)});






//hospital ave

speedZones[4] = &SpeedZone(20);

speedZones[4]->setVertices(4, (Vertex[4]){

Vertex(-1.09619448, 37.01160437),

Vertex(-1.09600140, 37.01161510),

Vertex(-1.09603358, 37.01455480),

Vertex(-1.09623739, 37.01454407)});








// Thikard1

speedZones[5] = &SpeedZone(60);

speedZones[5]->setVertices(8, (Vertex[8]){

Vertex(-1.10645301, 37.01634485),

Vertex(-1.10595958, 37.01598007),



46
Vertex(-1.10184047, 37.02031452),

Vertex(-1.09733519, 37.02522832),

Vertex(-1.09527563, 37.02825386),

Vertex(-1.09561889, 37.02868301),

Vertex(-1.09823625, 37.02557165),

Vertex(-1.10402875, 37.01913435)});



Thikard2 speedZones[6] = &SpeedZone(65); speedZones[6]->setVertices(6, (Vertex[6]){


Vertex(-1.09538290, 37.02829677),

Vertex(-1.08853914, 37.03593570),

Vertex(-1.08879659, 37.03627903),

Vertex(-1.09210047, 37.03318912),

Vertex(-1.09403131, 37.03063566),

Vertex(-1.09557598, 37.02861864)});



// Thikard3

speedZones[7] = &SpeedZone(70);

speedZones[7]->setVertices(7, (Vertex[7]){

Vertex(-1.08878586, 37.03638631),

Vertex(-1.08835679, 37.03591425),

Vertex(-1.07853093, 37.04393941),

Vertex(-1.06827596, 37.05011922),



47
Vertex(-1.06870504, 37.05093462),

Vertex(-1.07896001, 37.04466898),

Vertex(-1.08569651, 37.03908998)});






// Thikard1

speedZones[8] = &SpeedZone(67);

speedZones[8]->setVertices(9, (Vertex[9]){

Vertex(-1.06868359, 37.05104190),

Vertex(-1.06825451, 37.05018360),

Vertex(-1.06220449, 37.05348808),

Vertex(-1.05152039, 37.05730754),

Vertex(-1.04341074, 37.06082660),

Vertex(-1.04409728, 37.06185657),

Vertex(-1.04607105, 37.06031162),

Vertex(-1.05177784, 37.05773670),

Vertex(-1.06276230, 37.05404598)});

if (debugMode) {

printSpeedZones();

}



}



/*

This is the point-in-polygon algorithm adapted from



48

http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html */



booleaninSpeedZone(intspeedZone, float lat, float lng) { SpeedZone *s = speedZones[speedZone];


int i, j;

boolean inside = false;

for (i = 0, j = s->nVertices-1; i < s->nVertices; j = i++) { if ( ((s->vertices[i].lat>lat) != (s->vertices[j].lat>lat)) &&

(lng< (s->vertices[jlng - s->vertices[i].lng) * (lat - s->verticeslat) / (s->vertices[j].lat - s->vertices[i].lat)

s->vertices[i].lng) ) inside = !inside;

}



return inside;

}

booleaninSpeedZone(intspeedZone) {

floatlat, lng;

unsigned long fix_age;



retrieves +/- lat/long in 100,000ths of a degree gps.f_get_position(&lat, &lng, &fix_age);


returninSpeedZone(speedZone, lat, lng);

}

void loop() {

49


boolnewdata = false;

//unsigned long start = millis();



Every second we print an update //while (millis() - start < 1000)

//{

if (feedgps())

newdata = true;

//}

if (newdata)

{



gpsdump(gps);



}



speeding = isSpeeding();



if (speeding )

{

sendtexts();

}








50
}

staticboolfeedgps()

{

while (Serial.available())

{

if (gps.encode(Serial.read())) {

return true;

}

}

return false;

}



intgetSpeedLimit() {

booleanisInSpeedZone;



for(int i=0;i<NSPEEDZONES;i++) {

isInSpeedZone = inSpeedZone(i);

if (isInSpeedZone) {

returnspeedZones[i]->speedLimit;

}

}

return DEFAULT_SPEED_LIMIT;

}



booleanisSpeeding() {



51
int speed = (int)(gps.f_speed_kmph() + 0.5);

intspeedLimit = getSpeedLimit();



if (speed >speedLimit) {

lcd.print("Slow down!!!");

}

delay(2000);//give the driver time to slow down



if (speed >speedLimit) {//failure to slow down msg is sent return true;

}



return false;

}



booleansendtexts()

{



Serial1.print("AT+CMGS=\"+254729169305\"\r");	//Start accepting the text for the message

//to be sent to the number specified.

//Replace this number with the target mobile number.

delay(1000);

Serial1.print("KBC	238C\r");  //The text for the message

delay(1000);

Serial1.print(26,BYTE); //Equivalent to sending Ctrl+Z



52





}

voidprintSpeedZones() {



for(int i=0;i<NSPEEDZONES;i++) {

SpeedZone *s = speedZones[i];

Serial.println(s->speedLimit);

for(int v=0;v<s->nVertices;v++) {

Serial.print("(");

Serial.print(s->vertices[v].lat);

Serial.print(", ");

Serial.print(s->vertices[v].lng);

Serial.println(")");

}

}

}



static void gpsdump(TinyGPS&gps)

{

longlat, lon;

unsigned long fix_age, time, date, speed, course;



retrieves +/- lat/long in 100000ths of a degree gps.get_position(&lat, &lon, &fix_age);


53


Serial.println(getSpeedLimit());



Serial.print("lat: ");

Serial.print(lat);

Serial.print("	lng: ");

Serial.print(lon);

Serial.print("	speed: ");

Serial.println(gps.f_speed_kmph());

lcd.clear();

lcd.print("LIMIT: ");

lcd.print(getSpeedLimit(),DEC);

lcd.setCursor(0,1);

lcd.print("SPEED: ");

lcd.print(gps.f_speed_kmph(),2);






}





















