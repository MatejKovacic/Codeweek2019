/*  Codeweek delavnica, februar 2019
*   Program za demonstracijo merjenja razdalje z ultrazvočnim senzorjem ter delovanje magnetnega stikala.
*   (CC): Matej Kovačič
*   
*   Vezava
*   ======
*   1. Ultrazvočni senzor:
*   Ultrazvočni senzor - Arduino Nano:
*   VCC --- 5V
*   Trig --- D10
*   Echo --- D9
*   GND --- GND
*   
*   2. Magnetno stikalo:
*   - 10k Ohm upor je priključen na GND in D2
*   - magnetno stikalo je priključeno na D2 and 5V
*   GND <--- 10k Ohm ---> D2
*                    |
*                    ---magnetno stikalo --- > 5V
*   (10k Ohm = rjava - črna - oranžna - zlata)
*   
*   3. LED dioda (npr. zelena):
*   GND <--- (-) LED dioda (+) -- 220 Ohm --> D8
*   
*   4. Piskač:
*   D8 --- 220 Ohm --- piskač --- GND
*   (220 Ohm = rdeča - rdeča - rjava - zlata)
*/ 

const int pin_sprozilca = 10;   // TRG pin (trigger = sprožilec) na ultrazvočnem senzorju je povezan na D10.
const int pin_odmeva = 9;       // ECHO pin (echo = odmev) na ultrazvočnem senzorju je povezan na D9.

const int pin_stikala = 2;      // Magnetno stikalo je povezano na D2.
int stanje_stikala = 0;         // Stanje magnetnega stikala nastavimo na nič (odprto).

const int led_dioda = 8 ;       // Zelena LED dioda je povezana na D8.

const int pin_piskaca = 3;      // Piskač je povezan D3.

// Definiramo spremenljivke za trajanje (čas potovanja ultrazvoka) in razdaljo (od senzorja do predmeta):
long trajanje;
int razdalja;

void setup() {
  pinMode(pin_sprozilca, OUTPUT);     // pin_sprozilca nastavimo kot izhod (output).
  pinMode(pin_odmeva, INPUT);         // pin_odmeva nastavimo kot vhod (input).

  pinMode(pin_stikala, INPUT);        // pin_stikala nastavimo kot vhod (input).

  pinMode(LED_BUILTIN, OUTPUT);       // Pin Arduino Nano vgrajene LED diode nastavimo kot izhod (output).
  pinMode(led_dioda, OUTPUT);         // Pin LED diode nastavimo kot izhod (output).

  pinMode(pin_piskaca, OUTPUT);       // pin_piskaca nastavimo kot izhod (output).
  
  Serial.begin(9600);                 // Zaženemo serijsko komunikacijo preko USB vrat.

  Serial.println("Codeweek delavnica, februar 2019");  // Na serijski vmesnik izpišemo besedilo (in skočimo v novo vrstico).
}

void loop() {
  digitalWrite(pin_sprozilca, LOW);   // pin_sprozilca "ugasnemo" (stanje 0 oz. stanje LOW) - če je bil pred tem slučajno prižgan.
  delayMicroseconds(2);               // Počakamo 2 mikrosekundi...
  
  // pin_sprozilca "prižgemo" (stanje 1 oz. stanje HIGH) za 10 mikrosekund:
  digitalWrite(pin_sprozilca, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_sprozilca, LOW);
  
  // Počakamo, da pin_odmeva na ultrazvočnem senzorju zazna odbite ultrazvočne valove. Čas potovanja ultrazvočnih valov merimo v mikrosekundah:
  trajanje = pulseIn(pin_odmeva, HIGH);
  // Izračunamo razdaljo od ultrazvočnega senzorja do predmeta:
  razdalja = trajanje*0.034/2;

/* RAZLAGA:
 * Ultrazvočni senzor odda ultrazvočni pulz (na frekvenci 40.000 Hz). Ko ultrazvok naleti na oviro, se odbije 
 * nazaj. Ultrazvok potuje s hitrostjo zvoka, to je 340 metrov na sekundo oziroma 0.034 cm na mikrosekundo.
 * Če je objekt odaljen 10 cm, bo zvočni val do njega potoval 294 mikrosekund.
 * (čas_potovanja_zvoka = razdalja_do_objekta / hitrost_zvoka = 10 cm / 0.034 cm/µs = 294,11 mikrosekund).
 * 
 * Ker zaznamo odboj zvočnega vala (ko se odbije, mora zvočni val pripotovati še nazaj do senzorja), je razdaljo treba deliti z 2. Torej:
 * razdalja = trajanje_potovanja_zvocnega_impulza * 0.034 / 2
*/


  // V serijsko konzolo (na računalnik, prek USB kabla) izpišemo izmerjeno razdaljo:
  Serial.print("Oddaljenost predmeta: ");
  Serial.print(razdalja);
  Serial.print(" cm");
  
  
  /* Ker piskač piska glede na izmerjeno razdaljo, izračunamo s kakšnim tonom naj piskač zapiska.
     Vendar pa piskamo samo do razdalje največ 50 cm. Uporabimo funkcijo preslikave izmerjene razdalje
     na frekvenco piskanja (funkcija map). Frekvenca piskanja je od 3000 Hz do 20 Hz.
     Preslikamo torej vrednosti razdalje od 0 do 50 cm na frevenco zvoka od 3000 do 20 Hz.
     To pomeni, da bližje kot je predmet, višji bo ton piskanja in obratno - ko se predmet oddalji od 
     ultrazvočnega senzorja, bo piskanje nižje, po 50 cm oddaljenosti pa bo utihnilo.
  */
  
  if (razdalja > 50) // Zapiskamo samo če je razdalja manj kot pol metra (50 cm).
  {
    noTone(pin_piskaca);  // Če je razdalja več kot pol metra piskanje utišamo...
  }
  else
  {
    int frekvenca_piskanja = map(razdalja, 0, 50, 3000, 20);
    tone(pin_piskaca, frekvenca_piskanja);  // ...če pa ne, pa zapiskamo s prej izračunano frekvenco.
    Serial.print(" (frekvenca piskanja: ");
    Serial.println(frekvenca_piskanja);         // V tem primeru izpišemo še frekvenco piskanja.
    Serial.print(" Hz)");
  }

  // Preberemo stanje magnetnega stikala (1 = HIGH, 0 = LOW):
  stanje_stikala = digitalRead(pin_stikala);

  // Stanje stikala izpišemo na serijski vmesnik (0 = odprto, 1 = zaprto):
  Serial.print(", stanje stikala: ");
  Serial.println(stanje_stikala);         // izpišemo stanje stikala (0 ali 1)
    
  // Preverimo ali je stikalo zaprto (torej, če je stanje_stikala enako 1 oz. HIGH):
  if (stanje_stikala == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);   // Prižgemo vgrajeno LED diodo,...
    digitalWrite(led_dioda, LOW);      // ...ter ugasnemo dodatno LED diodo.
  }
  // Če pa je stikalo odprto (torej, če je stanje_stikala enako 0 oz. LOW):
  else
  {
    digitalWrite(LED_BUILTIN, LOW);    // Ugasnemo vgrajeno LED diodo,...
    digitalWrite(led_dioda, HIGH);     // ...ter prižgemo dodatno LED diodo.
  }


  delay(100);  // Počakamo 100 milisekund (desetinko sekunde), in se vrnemo na začetek programa.
}
