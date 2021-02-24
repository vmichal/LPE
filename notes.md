# Poznámky z pøedmìtu LPE
Usmoleno **Vojtìchem Michalem** (vojta.michall@email.cz) v prùbìhu letního semestru 2021 (B202). </br>
Oficiální materiály jsou na Moodle na stránce https://moodle.fel.cvut.cz/course/view.php?id=5814
a na Embedded serveru https://embedded.fel.cvut.cz/kurzy/lpe/LPE2021.

## Tıden 1 - Zapojení a základní test obvodu
Instrukce pro tento tıden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283733/mod_resource/content/3/LPE_1_tyden_poznamky_2021_v2.pdf,
hlavní úkol bylo osazení breadboardu souèástkami, oivení lineárního regulátoru a MCU. Základní schéma zapojení MCU a napájení (inpirováno)
doporuèenım schématem v pøiloeném PDF.</br>
![Schéma zapojení MCU](week_1/napajeni.png)
Následuje vlastní schéma zapojení pro zadané samostatné úlohy. Pro zjednodušení vynechávám kompletní zapojení napájení a soustøedím se jenom na signály
a pøípadnì popis, jaká periferie danı signál zpracovává. Piny jsem volil s ohledem na kompatibilitu jednotlivıch úloh, lze tedy zapojit všechny tøi úlohy najednou.
![Schéma zapojení úloh 1.2 a 1.4](week_1/schema.png)

Vısledné zapojení (vidìt jsou jen úlohy 3 a 4): Úplnì vpravo je LED øízená z PWM, uprostøed jsou vidìt 3 rezistory
v dìlièi pro úlohu 1.3

![Reálné zapojení úloh 1.3 a 1.4](week_1/zapojeni.jpg)
#### Úkol 1.1
> Sestavení zapojení s STM32F042 na nepájivém poli

Bez poznámek
#### Úkol 1.2
>Rozblikejte LED pomocí generátoru, dvì úrovnì svitu (prùbìhy napìtí na LED zobrazit na osciloskopu a poznamenat do sešitu...)

Pøejeme si mìøit napìtí na LED, proto je nejsnazší její katodu uzemnit, abychom mohli pouít single-ended meøení místo diferenciálního.
Pøes ochranı R se na anodu pøivede PWM promìnlivé støídy. LED svítí podle stejnosmìrné støední hodnoty (tedy `3V3 * duty_cycle` generované PWM)
rozdìlené mezi LED a rezistor. Pøi dostateèné frekvenci PWM (u mne asi od 60 Hz) u nejsou vùbec vidìt probliky. </br>
Zkoušel jsem hledat projevy parazitní difuzní kapacity PN pøechodu uvnitø LED, ale ani s vyšší vzorkovací frekvencí nebyly hrany PWM vıraznì
deformované; zùstaly strmé a nebyla pozorovatelné exponenciála. </br> Záznam mìøení napìtí na diodì (je vykresleno deset period signálu):
![Záznam osciloskopu](week_1/1.2.png)
Vısledek odpovídá døíve zmìøené hodnotì dopøedného napìtí pomocí *diode testeru* na multimetru, která byla 1620 mV.

#### Úkol 1.3
> Napište vlastní program v mbedu, rozblikat jednu extra pøipojenou LED tak, aby mìla více úrovní svítivosti, napøíklad
0-1-2-3-2-1-0... (0=nesvítí, 3=svítí nejvíce) pomocí dvou rezistorù na dvou rùznıch pinech MCU

Zapojení: anoda LED na 3V3 a "pod ni" do serie tøi rezistory 470R. Poslední rezistor je zapojen na zem. MCU mùe piny PA3, PA4 (pøipojenımi mezi kadé dva sousední 
rezistory) urèovat, jakı uzel se dostane na zemní potenciál nebo na napájení. Kdy oba piny plavou, pozoruje LED v sérii `3 * 470R`. Paklie je PA4 pøizemnìn,
pozoruje LED jen `2 * 470R` a paklie je pøizemnìn PA3, pozoruje LED v sérii jen jeden rezistor. Paklie nìjakı z pinù dává vysokou úroveò, je pøed LED nulové napìtí. </br>
Protoe napìtí LED v propustném smìru je na znaèném rozsahu proudù skoro konstantní (tato konkrétní LED má cca 1600 mV), dává nám zapojení monost
øídit proud LED ve ètyøech krocích. Podle `I = (3V3 - Uled)/R = cca (1V7 / R)` mohou téci proudy 0mA, 3.6mA, 1.8mA a nebo 1.2mA.

Software je triviální: V RCC zapnout hodiny pro GPIOA, dále pøepínat dva zvolené piny mezi módem `input floating` (stav po resetu)
a `push-pull general purpose output` v registrech GPIOx_MODER, GPIOx_PUPDR. V mezidobí jádro èeká v busy wait cyklu po urèitı poèet milisekund
(odmìøováno `SysTick`em).

**TODO** Setkal jsem se s podivnım chováním GPIO. Po pøepnutí pinu z GP PP vysoké úrovnì do input floating (MODER = 0, PUPDR = 0) byla na vıstupu stále jednièka,
aèkoli by mìl plavat. Fixnulo se to clearnutím pøíslušného bitu v ODR, poté zaèal pin plavat. Jednalo se o PA3 (pin 9), zeptat se na cviku.

#### Úkol 1.4
> Napište vlastní program v mbedu, kterı bude plynule rozsvìcet a zhasínat LED (buï pomocí wait a cyklù nebo pwm a zmìny støídy)

Pøíhodnı se ukázal timer 14 generující PWM s promìnlivou støídou na pinu PA7. Mikrokontroler bìí z 8MHz HSI násobeného šestkrát interní PLL.
Prozatím nechme i PCLK na 48MHz. Timer 14 je širokı 16 bitù. Pøi pouití prescaleru 48 - 1 bude na vstupu timeru frekvence 1 MHz.
Nastavením TIMx_ARR = 1000 dostaneme PWM na frekvenci 1kHz se støídou nastavovatelnou po promile zápisem do TIMx_CCR1.
Pro plynulejší pøechody se zápisy do TIMx_CCR1 provádí v SysTick interruptu bìícího na 1 kHz, zapise je v reimu napodobujícícm
center-aligned mód timeru. Jas LED tedy plynule nabíhá od nuly do 100% a následnì klesá v nule.

**TODO** Zeptat se, proè mohly plovoucí piny 17,18 (D+, D-) zpùsobit nestabilní koumikaci STlinku s mikrokontrolerem. Staèilo se prstem dotknout
odhalenıch pinù MCU a ji to vedlo na stabilní komunikaci.

## Tıden 2 - RC èlánky, charakteristika LED
Instrukce pro tento tıden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283737/mod_resource/content/3/LPE_2_tyden_poznamky2.pdf

  - *Dolní propust* (integraèní èlánek) je realizovatelná pomocí RC i RL, RC je typiètìjší, protoe C je typicky "ideálnìjší" ne L.
Feromagnetické jádro induktoru mùe saturovat a nejspíš bude mít hysterezi. Pro velmi vysokou frekvenci zaène mít vliv parazitní
indukènost pøívodù a samotné ESL kondenzátoru, take impedance nebude klesat do nekoneèna.
  - *Horní propust* (derivaèní èlánek) potlaèuje DC a posiluje zmìny - eliminuje DC, detekuje hrany.
  - *Transient voltage suppressor* (*TVS*) - brání chvilkovım napìovım špièkám, tøeba zenerky.
  - Rezistory mají teplotní závislost, reálnì napø 50 ppm/K
  - diody lze pouít k jednoduché stabilizaci napìtí, protoe mají malou závislost napìtí na tekoucí proudu.
  Vnitøní odpor v takovém pøípadì bude diferenciální odpor diody samotné. Zapojení dìlièe s diodou "dole" bude mít skoro
  o øád menší ztrátovı vıkon ne pouití normálního odporového dìlièe. Soubìnì bude malı pokles napìtí pod zátìí.
  V sofistikovanìjším pøípadì se pouije zenerka pro stabilizaci napìtí na dané úrovni. Pøi zatíení zdroje poklesne
  závìrné napìtí na diodì a tudí se ještì víc zmenší ztrátovı proud zpùsobenı Zenerovım prùrazem.

![Monosti pro realizaci jednoduchého zdroje](week_2/jednoduchy-zdroj.png)
Monosti realizace jednoduchého zdroje. Obrázek vykradenı z pøiloeného zadání.


#### Úkol 2.1
>  RC èlánek, zapojení, pozorování chování pro rùzné frekvence vstupního signálu

Kanál CH1 mìøí vstupní generovanı signál. Kanál CH2 mìøí vıstupní signál. </br>
Vstupní signál je generován jako sinus s amplitudou 1500 mV a offsetem 1500mV pomocí LEO.
Díky tomuto nastavení lze rozumnì od oka odeèítat pøenosy pro jednotlivé frekvence.

Zapojení je inspirované zadáním, dùleitá je úprava derivaèního èlánku, nebo ten by obecnì na vıstupu generoval záporné napìtí,
které by nebylo zdravé pro clampovací diody na pinu MCU.
 ![Integraèní èlánek, zlomová frekvence](week_2/RC-clanky.png)

##### Integraèní èlánek

TODO zkontrolovat vıpoèet zlomové frekvence
Postaven s R = 10k, C = 100n, proto je èasová konstanta tau = 1ms a zlomová frekvence f<sub>k</sub> = 160 Hz.
  - Frekvence **zlomová** (160Hz)</br>
    Oèekávám pokles o 3dB, co je asi 70%. Zmìøenı pokles je cca 500 mV, co jsou øádovì dvì tøetiny amplitudy.
    To je o trochu vìtší zatlumení jak 3dB, ale je stále v toleranci kvùli toleranci rezistoru a kondenzátoru.
  ![Integraèní èlánek, zlomová frekvence](week_2/integracni-zlom.png)
  - Frekvence **o dekádu niší** (16Hz)</br>
    Oèekávám pokles o 0dB, protoe kondenzátor by mìl bıt rozpojením pro DC. Zmìøenı úbytek je asi 30mV
 a to je v porovnání s 1500mV amplitudy skoro nic.
  ![Integraèní èlánek, zlomová frekvence](week_2/integracni-mensi.png)
  - Frekvence **o dekádu vyšší** (1600Hz) </br>
    Oèekávám pokles o 20dB, protoe jsme dekádu za zlomovkou. Útlum o 20dB znamená pøenos jen jedné desetiny amplitudy,
    co perfektnì sedí se zmìøenou amplitudou 150mV.
  ![Integraèní èlánek, zlomová frekvence](week_2/integracni-vyssi.png)

##### Derivaèní èlánek
Postaven s rezistory RR<sub>2,3,4</sub> = 10k, C = 100n, jedná se o trošku sofistikovanìjší zapojení, kde rezistory R<sub>3</sub>, RR<sub>4</sub>
zajišují stejnosmìrnı pracovní bod uprostøed rozsahu napájení. </br>
Odvození pøenosu: Uváíme superpozici, stejnosmìrnı zdroj korektnì nahradíme. Tím se R<sub>3</sub>, RR<sub>4</sub> staly paralelními.
Pro snazší odvození oznaème R = R<sub>3</sub>||R<sub>4</sub> = 5k a pomocí nìj vyjádøíme všechny odpory v pøenosu.
![Odvození tau](week_2/rovnice.gif)
![Odvození tau](week_2/frekvence.gif)
Po numerickém dosazení vyjde, e pøenos derivaèní sloky dosáhne jednièky pro f<sub>0</sub> = 318 Hz,
ale díky integraèní sloce se na zlomové frekvenci f<sub>1</sub> = 106 Hz pøenos zalomí a jde dál vodorovnì.
Pro nekoneènou frekvenci je pøenos jedna tøetina, statické zesílení 0 (DC kompletnì utlumeno).
**Závìr**: èasová konstanta bude 1/f<sub>1</sub>


  - Frekvence **zlomová** (160Hz)</br>
    Oèekávám pokles o 3dB, co je asi 70%. Zmìøenı pokles je cca 500 mV, co jsou øádovì dvì tøetiny amplitudy.
    To je o trochu vìtší zatlumení jak 3dB, ale je stále v toleranci kvùli toleranci rezistoru a kondenzátoru.
  ![Integraèní èlánek, zlomová frekvence](week_2/integracni-zlom.png)
  - Frekvence **o dekádu niší** (16Hz)</br>
    Oèekávám pokles o 0dB, protoe kondenzátor by mìl bıt rozpojením pro DC. Zmìøenı úbytek je asi 30mV
 a to je v porovnání s 1500mV amplitudy skoro nic.
  ![Integraèní èlánek, zlomová frekvence](week_2/integracni-mensi.png)
  - Frekvence **o dekádu vyšší** (1600Hz) </br>
    Oèekávám pokles o 20dB, protoe jsme dekádu za zlomovkou. Útlum o 20dB znamená pøenos jen jedné desetiny amplitudy,
    co perfektnì sedí se zmìøenou amplitudou 150mV.
  ![Integraèní èlánek, zlomová frekvence](week_2/integracni-vyssi.png)




#### Úkol 2.2
> Zmìøení diferenciálního odporu LED
