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
- [Arduino IDE] (https://www.arduino.cc/en/Main/Software)
- *codeweek2019.ino*

## Delovanje
Z ultrazvočnim senzorjem merimo razdaljo. Če je razdalja manj kot pol metra, vgrajeni piskač piska. Piskanje je odvisno od oddaljnosti predmeta. Bližje kot je predmet, višji bo ton piskanja in obratno - ko se predmet oddalji od ultrazvočnega senzorja, bo piskanje nižje, po 50 cm oddaljenosti pa bo utihnilo.

Z magnetnik stikalom upravljamo prižiganje LED diod. Če je magnetno stikalo zaprto, bo svetila vgrajena LED dioda, če je odprto pa bo svetila dodatna LED dioda.

Podatke o stanju magnetnega stikala, oddaljenosti predmeta od ultrazvočnega senzorja in frekvenci piskanja (če piskamo), izpisujemo preko serijskega vmesnika na računalnik.
