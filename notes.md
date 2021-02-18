# Poznámky z pøedmìtu LPE
Usmoleno Vojtou Michalem (vojta.michall@email.cz) v prùbìhu semestru. </br>
Oficiální materiály jsou na Moodle na stránce https://moodle.fel.cvut.cz/course/view.php?id=5814.

## Týden 1
Instrukce pro tento týden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283733/mod_resource/content/3/LPE_1_tyden_poznamky_2021_v2.pdf,
základní úkol bylo osazení breadboardu souèástkami a oživení lineárního regulátoru a MCU. Základní schéma zapojení MCU a napájení je v pøiloženém PDF.</br>
Následuje vlastní schéma zapojení pro zadané samostatné úlohy. Pro zjednodušení vynechávám kompletní zapojení napájení a soustøedím se jenom na signály
a pøípadnì popis, jaká periferie daný signál zpracovává. Piny jsem volil s ohledem na kompatibilitu jednotlivých úloh, lze tedy zapojit všechny tøi úlohy najednou.
![Schéma zapojení úloh 1.2 až 1.4](week_1/schema.png)
#### Úkol 1.1
> Sestavení zapojení s STM32F042 na nepájivém poli

Bez poznámek
#### Úkol 1.2
>Rozblikejte LED pomocí generátoru, dvì úrovnì svitu (prùbìhy napìtí na LED zobrazit na osciloskopu a poznamenat do sešitu...)

Pøejeme si mìøit napìtí na LED, proto je nejsnazší její katodu uzemnit. Pøes ochraný R se pøivede PWM promìnlivé støídy.
LED svítí podle stejnosmìrné støední hodnoty (tedy `3V3 * duty_cycle` generované PWM); pøi dostateèné frekvenci PWM
(u mne asi od 60 Hz už nejsou vùbec vidìt probliky). Ani pøi vyšší spínací (a tudíž nutnì i vzorkovací) frekvenci
se mi nepodaøilo nalézt dùkaz pøítomnosti difuzní kapacity PN pøechodu. Hrany PWM byly strmé a nebyla pozorovatelné exponenciála. </br>
Záznam mìøení napìtí na diodì (je vykresleno deset period signálu):
![Záznam osciloskopu](week_1/1.2.png)

#### Úkol 1.3
> Napište vlastní program v mbedu, rozblikat jednu extra pøipojenou LED tak, aby mìla více úrovní svítivosti, napøíklad
0-1-2-3-2-1-0... (0=nesvítí, 3=svítí nejvíce) pomocí dvou rezistorù na dvou rùzných pinech MCU

Zapojení: anoda LED na 3V3 a "pod ni" do serie tøi rezistory 470R. Poslední rezistor je zapojen na zem. MCU mùže piny PA3, PA4 (pøipojenými mezi každé dva sousední 
rezistory) urèovat, jaký uzel se dostane na zemní potenciál nebo na napájení. Když oba piny plavou, pozoruje LED v sérii `3 * 470R`. Pakliže je PA4 pøizemnìn,
pozoruje LED jen `2 * 470R` a pakliže je pøizemnìn PA3, pozoruje LED v sérii jen jeden rezistor. Pakliže nìjaký z pinù dává vysokou úroveò, je pøed LED nulové napìtí. </br>
Protože napìtí LED v propustném smìru je na znaèném rozsahu proudù skoro konstantní (tato konkrétní LED má cca 1600 mV), dává nám zapojení možnost
øídit proud LED ve ètyøech krocích. Podle `I = (3V3 - Uled)/R = cca (1V7 / R)` mohou téci proudy 0mA, 3.6mA, 1.8mA a nebo 1.2mA.

#### Úkol 1.4
> Napište vlastní program v mbedu, který bude plynule rozsvìcet a zhasínat LED (buï pomocí wait a cyklù nebo pwm a
zmìny støídy)

Pøíhodný se ukázal timer 14 generující PWM s promìnlivou støídou na pinu PA7.

