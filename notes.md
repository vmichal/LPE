# Poznámky z pøedmìtu LPE
Usmoleno **Vojtìchem Michalem** (vojta.michall@email.cz) v prùbìhu letního semestru 2021 (B202). </br>
Oficiální materiály jsou na Moodle na stránce https://moodle.fel.cvut.cz/course/view.php?id=5814
a na Embedded serveru https://embedded.fel.cvut.cz/kurzy/lpe/LPE2021.

## Týden 1 - Zapojení a základní test obvodu
Instrukce pro tento týden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283733/mod_resource/content/3/LPE_1_tyden_poznamky_2021_v2.pdf,
hlavní úkol bylo osazení breadboardu souèástkami, oživení lineárního regulátoru a MCU. Základní schéma zapojení MCU a napájení (inpirováno)
doporuèeným schématem v pøiloženém PDF.</br>
![Schéma zapojení MCU](week_1/napajeni.png)
Následuje vlastní schéma zapojení pro zadané samostatné úlohy. Pro zjednodušení vynechávám kompletní zapojení napájení a soustøedím se jenom na signály
a pøípadnì popis, jaká periferie daný signál zpracovává. Piny jsem volil s ohledem na kompatibilitu jednotlivých úloh, lze tedy zapojit všechny tøi úlohy najednou.
![Schéma zapojení úloh 1.2 až 1.4](week_1/schema.png)

Výsledné zapojení (vidìt jsou jen úlohy 3 a 4): Úplnì vpravo je LED øízená z PWM, uprostøed jsou vidìt 3 rezistory
v dìlièi pro úlohu 1.3

![Reálné zapojení úloh 1.3 a 1.4](week_1/zapojeni.jpg)
#### Úkol 1.1
> Sestavení zapojení s STM32F042 na nepájivém poli

Bez poznámek
#### Úkol 1.2
>Rozblikejte LED pomocí generátoru, dvì úrovnì svitu (prùbìhy napìtí na LED zobrazit na osciloskopu a poznamenat do sešitu...)

Pøejeme si mìøit napìtí na LED, proto je nejsnazší její katodu uzemnit, abychom mohli použít single-ended meøení místo diferenciálního.
Pøes ochraný R se na anodu pøivede PWM promìnlivé støídy. LED svítí podle stejnosmìrné støední hodnoty (tedy `3V3 * duty_cycle` generované PWM)
rozdìlené mezi LED a rezistor. Pøi dostateèné frekvenci PWM (u mne asi od 60 Hz) už nejsou vùbec vidìt probliky. </br>
Zkoušel jsem hledat projevy parazitní difuzní kapacity PN pøechodu uvnitø LED, ale ani s vyšší vzorkovací frekvencí nebyly hrany PWM výraznì
deformované; zùstaly strmé a nebyla pozorovatelné exponenciála. </br> Záznam mìøení napìtí na diodì (je vykresleno deset period signálu):
![Záznam osciloskopu](week_1/1.2.png)
Výsledek odpovídá døíve zmìøené hodnotì dopøedného napìtí pomocí *diode testeru* na multimetru, která byla 1620 mV.

#### Úkol 1.3
> Napište vlastní program v mbedu, rozblikat jednu extra pøipojenou LED tak, aby mìla více úrovní svítivosti, napøíklad
0-1-2-3-2-1-0... (0=nesvítí, 3=svítí nejvíce) pomocí dvou rezistorù na dvou rùzných pinech MCU

Zapojení: anoda LED na 3V3 a "pod ni" do serie tøi rezistory 470R. Poslední rezistor je zapojen na zem. MCU mùže piny PA3, PA4 (pøipojenými mezi každé dva sousední 
rezistory) urèovat, jaký uzel se dostane na zemní potenciál nebo na napájení. Když oba piny plavou, pozoruje LED v sérii `3 * 470R`. Pakliže je PA4 pøizemnìn,
pozoruje LED jen `2 * 470R` a pakliže je pøizemnìn PA3, pozoruje LED v sérii jen jeden rezistor. Pakliže nìjaký z pinù dává vysokou úroveò, je pøed LED nulové napìtí. </br>
Protože napìtí LED v propustném smìru je na znaèném rozsahu proudù skoro konstantní (tato konkrétní LED má cca 1600 mV), dává nám zapojení možnost
øídit proud LED ve ètyøech krocích. Podle `I = (3V3 - Uled)/R = cca (1V7 / R)` mohou téci proudy 0mA, 3.6mA, 1.8mA a nebo 1.2mA.

Software je triviální: V RCC zapnout hodiny pro GPIOA, dále pøepínat dva zvolené piny mezi módem `input floating` (stav po resetu)
a `push-pull general purpose output` v registrech GPIOx_MODER, GPIOx_PUPDR. V mezidobí jádro èeká v busy wait cyklu po urèitý poèet milisekund
(odmìøováno `SysTick`em).

**TODO** Setkal jsem se s podivným chováním GPIO. Po pøepnutí pinu z GP PP vysoké úrovnì do input floating (MODER = 0, PUPDR = 0) byla na výstupu stále jednièka,
aèkoli by mìl plavat. Fixnulo se to clearnutím pøíslušného bitu v ODR, poté zaèal pin plavat. Jednalo se o PA3 (pin 9), zeptat se na cviku.

#### Úkol 1.4
> Napište vlastní program v mbedu, který bude plynule rozsvìcet a zhasínat LED (buï pomocí wait a cyklù nebo pwm a zmìny støídy)

Pøíhodný se ukázal timer 14 generující PWM s promìnlivou støídou na pinu PA7. Mikrokontroler bìží z 8MHz HSI násobeného šestkrát interní PLL.
Prozatím nechme i PCLK na 48MHz. Timer 14 je široký 16 bitù. Pøi použití prescaleru 48 - 1 bude na vstupu timeru frekvence 1 MHz.
Nastavením TIMx_ARR = 1000 dostaneme PWM na frekvenci 1kHz se støídou nastavovatelnou po promile zápisem do TIMx_CCR1.
Pro plynulejší pøechody se zápisy do TIMx_CCR1 provádí v SysTick interruptu bìžícího na 1 kHz, zapise je v režimu napodobujícícm
center-aligned mód timeru. Jas LED tedy plynule nabíhá od nuly do 100% a následnì klesá v nule.

**TODO** Zeptat se, proè mohly plovoucí piny 17,18 (D+, D-) zpùsobit nestabilní koumikaci STlinku s mikrokontrolerem. Staèilo se prstem dotknout
odhalených pinù MCU a již to vedlo na stabilní komunikaci.

## Týden 2 - RC èlánky, charakteristika LED
Instrukce pro tento týden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283737/mod_resource/content/3/LPE_2_tyden_poznamky2.pdf


