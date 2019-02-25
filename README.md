# Codeweek 2019
Arduino koda za Codeweek delavnico, februarja 2019

## Strojna oprema
- 1 x Arduino Nano
- 1 x ultrazvočni senzor HC-SR04
- 1 x magnetno stikalo
- 1 x LED dioda
- 1 x piskač
- 2 x 220 Ohm upor
- 1 x 1k Ohm upor

## Programska oprema
- [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- *codeweek2019.ino* (vsebuje tudi navodila za povezave med elementi)

## Delovanje naprave
Z ultrazvočnim senzorjem merimo razdaljo. Če je razdalja manj kot pol metra, vgrajeni piskač piska. Piskanje je odvisno od oddaljnosti predmeta. Bližje kot je predmet, višji bo ton piskanja in obratno - ko se predmet oddalji od ultrazvočnega senzorja, bo piskanje nižje, po 50 cm oddaljenosti pa bo utihnilo.

Z magnetnim stikalom upravljamo prižiganje LED diod. Če je magnetno stikalo zaprto, bo svetila vgrajena LED dioda, če je odprto pa bo svetila dodatna LED dioda.

Podatke o stanju magnetnega stikala, oddaljenosti predmeta od ultrazvočnega senzorja in frekvenci piskanja (če piskamo), izpisujemo preko serijskega vmesnika na računalnik.

### Izračun oddaljenosti predmeta od ultrazvočnega senzorja
Ultrazvočni senzor odda ultrazvočni pulz (na frekvenci 40.000 Hz). Ko ultrazvok naleti na oviro, se odbije nazaj. Ultrazvok potuje s hitrostjo zvoka, to je 340 metrov na sekundo oziroma 0.034 cm na mikrosekundo.

Če je objekt odaljen 10 cm, bo zvočni val do njega potoval 294 mikrosekund. Izračun:

  čas_potovanja_zvoka = razdalja_do_objekta / hitrost_zvoka = 10 cm / 0.034 cm/µs = 294,11 mikrosekund

Ker zaznamo *odboj* zvočnega vala (ko se odbije, mora zvočni val pripotovati še nazaj do senzorja), je razdaljo treba deliti z 2. Torej:

  razdalja = trajanje_potovanja_zvocnega_impulza * 0.034 / 2

### Frekvenca piskanja glede na oddaljenost predmeta od ultrazvočnega senzorja
Ker želimo, da piskač piska glede na izmerjeno razdaljo, izračunamo s kakšnim tonom naj piskač zapiska. Pri tem je potrebno upoštevati, da piskamo samo do razdalje največ 50 cm.

Uporabimo funkcijo preslikave izmerjene razdalje na frekvenco piskanja (funkcija *map*). Frekvenca piskanja je od 3000 Hz do 20 Hz. Preslikamo torej vrednosti razdalje od 0 do 50 cm na frevenco zvoka od 3000 do 20 Hz. To pomeni, da bližje kot je predmet, višji bo ton piskanja in obratno - ko se predmet oddalji od ultrazvočnega senzorja, bo piskanje nižje, po 50 cm oddaljenosti pa bo utihnilo.

Programska koda:
  int frekvenca_piskanja = map(razdalja, 0, 50, 3000, 20);
  tone(pin_piskaca, frekvenca_piskanja); 

## Zanimivosti
Ultrazvočni senzor oddaja zvok s frekvenco 40 kHZ. Ljudje slišimo zvoke do okrog 20 kHz, živali pa bistveno več. Netopirji do 100 kHz (oziroma morda celo do 200 kHz), psi do 45 kHz, mačke pa do 64 kHz. Ultrazvočne piščalke se uporabljajo za treniranje psov - psi zvok iz takšne piščalke slišijo, za ljudi pa je neslišen.

Podoben princip, ki se uporablja za merjenje razdalje z ultrazvočnim senzorjem (tim. eholokacijo, lociranje na podlagi zvočnega odmeva), uporabljajo tudi netopirji, ki s pomočjo ultrazvoka "vidijo" okolico in zaznavajo svoj plen. Na podoben način delfini uporabljajo tim. biosonar (ultrazvočni valovi potujejo tudi pod vodo). Nekateri insekti pa se, ko zaslišijo ultrazvok z določeno frekvenco, pričnejo umikati, saj mislijo, da so v bližini plenilca.
