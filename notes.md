# Poznámky z pøedmìtu LPE
Usmoleno **Vojtìchem Michalem** (vojta.michall@email.cz) v prùbìhu letního semestru 2021 (B202). </br>
Oficiální materiály jsou na Moodle na stránce https://moodle.fel.cvut.cz/course/view.php?id=5814
a na Embedded serveru https://embedded.fel.cvut.cz/kurzy/lpe/LPE2021. </br>
Seznam souèástek s pinout a schematickımi znaèkami: https://moodle.fel.cvut.cz/pluginfile.php/293919/mod_resource/content/3/Soucastky_vyvody_LPE_4.pdf

Tıdny jsou èíslovány chronologicky, poznámky k nim jsou uvedeny v obráceném poøadí.
Jako první je tedy uveden poslední tıden, scrollováním na konec stránky se èlovìk dostane na tıden první.

## Tıden 4 - Operaèní zesilovaèe
Instrukce pro tento tıden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283742/mod_resource/content/4/LPE_4_tyden_poznamky_2021_v3.pdf

Vırobní technologií lze operáky rozdìlit na bipolární (napø OPA227) a unipolární - dále dìleny podle JFETù/CMOSù na vstupu
  - Bipolární  - nízkı napìovı šum pøi zkratu vstupù (CMOS tøeba 8uV peak/peak, OPA227 zvládne tøeba 90nVp-p .. 2 øády rozdíl)
     Vstupní proud v klidu (input bias current) v øádu tøeba 2.5 nA (OPA227).
  - Unipolární: Fantastickı klidovı vstupní proud - +/-1 pikoampér pro CMOS, JFETy tøeba femtoampéry.
    - JFETy - nízkı proudovı šum
    - CMOSy (tøeba MCP6002) - Fungují i pro nízká napìtí (i tøeba 1.8V), vhodná tak k mikrokontrolerùm

V pøípadì MCP6002 je zmìøitelná "body dioda" ve smìru Vss->VDD. Pøi pøepólování napájení se otevøe a bude to hoøet.

Ideální **open-loop gain** je nekoneèno, reálnì 88-112 dB (pro MCP6003). OPA227 tøeba 160 dB (10<sup>8</sup> krát)

**Gain-bandwidth product** - souèin open-loop gain a šíøky pásma (bandwidth), odráí frekvenènì závislé vlastnosti operáku.
Na frekvenci `bandwidth` je jednotkové zesílení. Pøi stejnosmìrném vstupním napìtí je zesílení `open-loop gain`. Kdy jsme nìkde
mezi, poklesá s rostoucí frekvencí zesílení, kterého umí operák dosáhnout (rychlé hrany vyadují rychlé pøebìhy a OZ má koneènı slew rate).
Souèin frekvence a zesílení bude omezen parametrem `Gain-bandwidth product`.

#### Úkol 4.1
> Zapojte OZ jako sledovaè napìtí (impedanèní oddìlovaè), na vstupu napìtí na LED (ILED=5-20mA), zmìøte vıstupní
odpor tohoto zapojení pro IOUT = 0 a 4 mA (zatíení OZ)

<img align="right" src="week_4/ubytek_s_proudem.png">
Ideální vlastnosti sledovaèe: R<sub>in</sub> = nekoneèno, R<sub>out</sub>= 0.
Reálnì má vıstupní stupeò operáku nenulovı vnitøní odpor,
pro vyšší proudy zaène vıstupní napìtí OZ poklesat kvùli úbytku. "Vnitøní odpor" mùe bıt pro MCP6002 øádovì 100 ohm.

Na grafu od Ing. Petruchy je osa x vıstupní proud v mA, osa y je ádané napìtí ve voltech.

Mìøím v bodì Voltmetr1 (vıstup operáku) pøi zátìích 0mA a pøiblinì 4mA.
Zmìøená napìtí: bez zatíení 1811.97mV, pøi zátìi 4.17mA napìtí 1815.13mV. Z toho lze vypoèíst
vıstupní odpor pro nízké proudy R<sub>out</sub> = 0.76 ohm.
![Napìovı sledovaè](week_4/Rout.jpg)

Pozn: Napìovı sledovaè je ze svého principu zpìtnovazební soustava, která v principu nemusí bıt vùbec stabilní.
U nìkterıch zesilovaèù se toto explicitnì uvádí jako **unity gain stability**. Pokud vzniklé zapojení neí stabilní,
OZ bude mít tendenci oscilovat. Dùsledkem potom je, e multimetr mìøící RMS tøeba bude zdánlivì mìøit rozumná èísla,
ale osciloskop ukáe rychlé smyèky. Toté se mùe stát napøíklad u low drop-out regulátorù.

Nevyuitım operákùm je potøeba definovat úroveò vstupù, napøíklad zapojením sledovaèe zemì:
![Napìovı sledovaè](week_4/definovane_vstupy.jpg)
#### Úkol 4.2
> Sestavte neinvertující zesilovaè napìtí 11x a zmìøte pomocí nìj saturaèní napìtí NPN tranzistoru.

Zapojení je na obrázku, odpor R<sub>b</sub> bude nabıvat vícero hodnot pro dosaení rùzného stupnì saturace.
![Napìovı sledovaè](week_4/saturace.jpg)

Napìtí na kolektoru NPN tranzistoru je pøímo rovné napìtí U<sub>+</sub> na neinvertující svorce OZ.
Napìtí U<sub>o</sub> je na vıstupu operaèního zešilovaèe (bod *Voltmetr1*).

a) Zmìøená napìtí pro bázovı odpor 10k: U<sub>+</sub> = 33 mV, U<sub>o</sub> = 363 mV.
Dává vısledek smysl? OZ je zapojen s dìlièem 1k a 10k, jeho zesílení je `A = 1 + 10/1 = 11`.
Na vıstupu OZ tak oèekávám 33mV * 11 = 363 mV, co se a podezøele rovná zmìøenému napìtí.
Sešla se nízká zátì vıstupu OZ `< 0.3 mA` a zøejmì velmi dobré hodnoty rezistorù v dìlièi.

b) Zmìøená napìtí pro 5k v bázi: U<sub>+</sub> = 24 mV, U<sub>o</sub> = 252 mV.
c) Zmìøená napìtí pro 470 ohmù v bázi: U<sub>+</sub> = 14 mV, U<sub>o</sub> = 150 mV.
Závìry jsou stejné jako v podúloze a). Hodnoty jsou oèekávatelné a srovnatelné s mìøeními z tıdne 3.

Praktickı vıznam je napøíklad kvùli pøesnìjšímu mìøení multimetry. Digitální multimetr má nejistotu mìøení
závislou na aktuálním mìøicím rozsahu. Paklie by nejniší rozsah byl tøeba 200 mV a nejistota tøeba 0.5% rozsahu,
vnášelo by to implicitnì chybu vnìøení 1 mV. Kdybychom pak chtìli mìøit napìtí tøeba 10 mV, rovnou máme 10% relativní chybu.
Pouitím zesilovaèe se zvıší mìøená hodnota a tím poklesne vliv chyby z rozsahu.

#### Úkol 4.4
> Zmìøte vstupní napìovı offset pouitého operaèního zesilovaèe (MCP6002).

![Napìovı sledovaè](week_4/offsety.jpg)

Schéma zapojení:

Mìøení s pouitím R4 = 120k nedávalo ádné mìøitelné vısledky.
Pro R4 = 1 megaohm (zesílení operáku `A = 1+1'000'000/470 = 2128`) jsem namìøil:
  - U<sub>o</sub> = 1.4 mV pro OZ pod piny 1,2,3
  - U<sub>o</sub> = 5.6 mV pro OZ pod piny 5,6,7

S ohledem na zesílení to odpovídá vstupním offsetùm 0.66uV pro OZ na pinech 1,2,3 a 2.63uV pro OZ na pinech 5,6,7.
Datasheet garantuje maximální offset 4.5 mV, take namìøené offsety jsou velice velice velice dobré
(a v rámci paralelky na cvika asi celkem vıjimeèné).


#### Úkol 4.3
> Sestavte zapojení I/U pøevodníku s OZ a pouijte jej pro zpracování signálu z fotodiody (náhrada èirou LED). Na
fotodiodu blikejte pomocí LED (frekvence 1 Hz-1 kHz, støída 2-50 %). Uspoøádejte dané prvky jako reflexní senzor.

Zapojení na obrázku:
![Napìovı sledovaè](week_4/ledky.jpg)

*generátor* generuje obdélníkovı signál, kterım se spíná zelená vysílací LED v kolektoru NPN tranzistoru.
Ta je optickou vazbou spojena s pøijímající èervenou LED, kterou kvùli dopadajícímu svìtlu teèe proud, 
jen je prvním operaèním zesilovaèem pøeveden na napìtí; to je zesíleno druhım operákem 
(s pouitím R2 = 188k, R4 = 10k je zesílení `A = 1+188/10 ~ 20`) a mìøeno kanálem 2 osciloskopu.



## Tıden 3 - Tranzistory
Instrukce pro tento tıden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283739/mod_resource/content/4/LPE_3_tyden_poznamky_2021_v4.pdf

#### Úkol 3.1
> Zmìøit proudovı zesilovací èinitel NPN tranzistoru h<sub>21E</sub>

<img align="right" src="week_3/common-emitor.png">

Základní zapojení se spoleènım emitorem.
Na bázi je zapojen 1 megaohm proti 3V3, úbytek na nìm zmìøen jako 2.660 V (na PN pøechod B->E zbıvá 636 mV).
V kolektoru je èervená LED a rezistor 470R s serii proti 3V3, na R<sub>k</sub> úbytek 528 mV.

Z toho plyne proud bází I<sub>b</sub>` = 2'660/1'000'000 = 2.6 uA` a proud kolektorem I<sub>c</sub>` = 528/470 = 1.12 mA`
a zesilovací èinitel h<sub>21E</sub>` = Ic / Ib = 432`, co je oèekávatelná hodnota u signálového BJT.
Podle datasheetu jsou zesílení BJT s pøíponou "C" v rozsahu 400-800, take danı tranzistor je v garantovaném rozsahu.

S tímto zesílením lze nahradit 1M v bázi i odporem kùe - ten je ale v øádu desítek kOhm a více pouze pro nízká napìtí.
**Se síovım napìtím (230 V RMS) se kùe prorazí a odpor vıraznì poklesne**.

#### Úkol 3.2
> Rozsvítit LED pomocí NPN tranzistoru (zmìøit UBE, UCE, orientaèní vıpoèet Rb, Rc)

NPN bude pouit jako spínaè pro seriové zapojení èervené LED a rezistoru proti 5V,
take v saturaci budu pøedpokládat nulovı úbytek napìtí mezi kolektorem a emitorem.
Pøi pouití rezistoru 470 ohm v sérii s LED s dopøednım napìtím cca 1.8V by mìl v plnì sepnutém stavu LEDkou téci proud 
`Ic = (5-1.8)/470 = 6.8mA`. Pøi proudovém zesilovacím èiniteli h<sub>21e</sub> = 432 je potøeba dodat do báze
proud alespoò `Ib = Ic/h21e = 15 uA`. Budu-li pøedpokládat, e napìovı úbytek pøechodu
BE se nebude pøíliš mìnit od úlohy 3.1, a zùstane tedy cca 650mV, poté do báze potøebuji rezistor nejvıše
`Rb_max = (3V3 - 0.65)/15uA = 176 kOhm`. Pouití napøíklad 22kOhm nám dá "šestinásobnou jistotu",
e spínání bude fungovat bez ohledu na neideality souèástek a pøípadné šumy.

Zmìøené saturaèní napìtí U<sub>ce</sub> tranzistoru v daném zapojení je 57mV, co ve srovnání s úbytkem 5V na celé vìtvi vèetnì
LED a rezistoru je skuteènì zanedbatelné. Zmìøenı úbytek na pøechodu báze-emitor je 680 mV, take odpovídá oèekávanému úbytku.

Protoe NPN tranzistor v sepnutém stavu pøizemòuje svùj kolektor, lze z nìj sestrojit nejhloupìjší invertor. Vysoká úroveò 
na bázi zpùsobí nízkou úroveò na kolektoru a naopak. Viz následující obrázek. Kanál 1 je U<sub>be</sub>, kanál 2 je U<sub>ce</sub>.
Zajímavé je prohnutí U<sub>ce</sub> v oblasti, kde má signál na bázi maximum. Saturace BJT neprobìhne najednou, s rostoucím
proudem stoupá míra saturace. Kvùli tomu není ani saturaèní napìtí ve smìru C->E konstantní, nıbr klesá s rostoucí mírou saturace.

![Negace signálu pomocí NPN tranzistoru](week_3/invertor.png)
#### Úkol 3.3
> Rozsvítit LED pomocí PNP tranzistoru (zmìøit UBE, UCE)

Princip zapojení úplnì identickı jako u NPN, jen "zrcadlovì obráceno". PNP je v zapojení se spoleènım emitorem (emitor na napájení, vstup na bázi, zátì v kolektoru).
Na bázi je pøes odpor 10k pøipojen generátor, dalších 10k je zapojeno mezi bázi a emitor jako pullup pro rychlejší zavírání
(vzniká vodivá cesta mezi bází a emitorem, která urychluje vynulování napìtí U<sub>be</sub> a rekombinaci nosièù v PN pøechodu).
V kolektoru je v sérii èervená LED a 470R proti zemi. Pouité zapojení je vlevo na schématu zapùjèeném ze zadání, na port STM32_Px.x
je pøipojen generátor. Zapojení vpravo je základní zapojení pro spínání napájení vyššího, ne dosahují logické úrovnì øídicí logiky
(v takovém pøípadì by prosté zapojení PNP nestaèilo, protoe logika by neumìla bázi PNP dostat dostateènì vysoko. Alternativou
by bylo pouít øízení open collector a PNP zavírat "samospádem" pomocí pullupu, øídicí pin by ale musel tolerovat vysoké napìtí.)

![Zapojení PNP v obvodu](week_3/pnp_zapojeni.png)

Pøi saturaci PNP tranzistoru lze zmìøit hodnoty U<sub>eb</sub> = 630 mV, U<sub>ec_sat</sub> = 53 mV

Zajímavé jsou dva èasové prùbìhy se zapojení s PNP tranzistorem se sinusem a obdélníkem na vstupu.

Sinusovı vstup: kanál 1 je báze, kanál 2 je kolektor, kanál 3 je napìtí na rezistoru v kolektoru. Je vidìt, e
obvod opìt má invertující charakter, zajímavı je nábìh napìtí na rezistoru (nábìná hrana kanálu 3), kde 
se projevuje exponenciální závislost proudu bází na napìtí, je se lineární závislostí Ic na Ib pøevádí na exp závislost proudu kolektorem
na napìtí U<sub>eb</sub>. Jinımi slovy: paklie `Ib ~ exp(Ueb)` a `Ic = Ib * h21e`, poté `Ic ~ exp(Ueb)`.
Z tohoto dùvodu lze na rezistoru pozorovat exponenciální nábìh proudu kolektorem.

![Prùbìh napìtí na PNP spínaèi](week_3/pnp_prubeh.png)

Další mìøení je pro obdélníkovı vstup: kanál 1 je báze, kanál 2 je kolektor, kanál 3 je napìtí na rezistoru v kolektoru, které je úmìrné tekoucímu proudu.
Je zajímavé, e i pøes nulovı proud kolektorem je spádná hrana napìtí U<sub>c</sub> pomalá. To je projev saturace LEDky, u které se 
pøechodovım dìjem vybíjí parazitní difuzní kapacita PN pøechodu.

![Prùbìh napìtí na PNP spínaèi](week_3/pnp_obdelnik.png)

#### Úkol 3.4
> Rozsvítit LED pomocí N-MOSFET tranzistoru (zmìøit UGS, UDS, RDSON)

![Prùbìh napìtí ](week_3/nmos-zapojeni.png)

Zapojení zapùjèené ze zadání, nMOS je unipolární alternativa NPN bipoláru.

Nastavováním napìtí na gate pomocí trimmeru šlo namìøit následující data:
Threshold voltage U<sub>TO</sub> je cca 1.9 V, kdy je U<sub>gs</sub> niší, není MOSFET otevøen vùbec a mìøitelnı proud drainem neteèe.
Od pøiblinì 2.5V dál je proud MOSFETem omezen vnìjším obvodem a pøi dalším navyšování U<sub>gs</sub> ji proud neroste.
Pøi maximálním napìtí U<sub>gs</sub> = 3V3 má tranzistor odpor R<sub>ds_on</sub> = 1.5 ohmu. </br>
Pro ilustraci pøikládám dva screenshoty z prùbìhù napìtí v obvodu.
Kanál 1 je napìtí U<sub>gs</sub>, kanál 2 je U<sub>ds</sub>,
kanál 3 je U<sub>ds</sub> + U<sub>LED</sub>. Proto platí, e úbytek napìtí na rezistoru je `3V3 - kanál 3`.

Prùbìh s U<sub>gs</sub> tìsnì za U<sub>TO</sub>. Je vidìt, e úbytek na R (=doplnìk kanálu 3 do plného napìtí) je minimální,
obvodem tedy ještì skoro nic neteèe. Napìtí 3v3 se dìlí mezi PN pøechod LED a napìtí ve smìru D->S MOSFETu.

![Prùbìh napìtí ](week_3/nmos-prubeh2.png)

Prùbìh s U<sub>gs</sub> = cca 2.32V (kdesi v intervalu [U<sub>TO</sub>, 3V3]). Úbytek D->S klesá (klesá tedy odpor MOSFETu
a roste proud). Pokles napìtí na kanálu 3 odráí nárùst poklesu napìtí na rezistoru.

![Prùbìh napìtí ](week_3/nmos-prubeh.png)

Ani pøi dalším navyšování napìtí na gate se odpor MOSFETu vıraznì nemìní. Experiment (pod dozorem
ostøíleného HW návrháøe): Pøivést 5V na gate, 3v3 na drain, gnd na source. Vše jen pulsnì, aby nedošlo k poškození
lineárního regulátoru. Mìøení z multimetru: `Id = 320 mA`, `Uds = 750 mV`, na lineárním regulátoru pokles o 2V,
na spojích nepájivého pole úbytek 600 mV. Radìji zastaveno, aby nepovolila pojistka v USB. Závìr: Chce to tvrdší zdroj.

**POZOR** na zajištìní definované úrovnì gate MOSFETu! Bìhem resetu èi pøi utrení vodièe bude vstup na gate
v Hi-Z, a tranzistor bude dìlat nepøedvídatelné kraviny - bude otevøen, uzavøen, nebo nìco mezi.
U BJT toto není takovı problém, protoe tam musí pøes bázi téci proud a ten otevøenım obvodem nepoteèe.


## Tıden 2 - RC èlánky, charakteristika LED
Instrukce pro tento tıden jsou na https://moodle.fel.cvut.cz/pluginfile.php/283737/mod_resource/content/3/LPE_2_tyden_poznamky2.pdf

  - *Dolní propust* (integraèní èlánek) je realizovatelná pomocí RC i RL. RC je typiètìjší, protoe C je typicky "ideálnìjší" ne L.
Feromagnetické jádro induktoru mùe saturovat a nejspíš bude mít hysterezi. RC taky není ideální:
pro velmi vysokou frekvenci zaène mít vliv parazitní
indukènost pøívodù a samotné ESL kondenzátoru, take impedance nebude klesat do nekoneèna.
  - *Horní propust* (derivaèní èlánek) potlaèuje DC a posiluje zmìny. Pouití pro detekci hran (strmou hranu
   derivace extrémnì zesílí) a nebo oddìlení èástí obvodu na rùznıch stejnosmìrnıch potenciálech (komunikace
BMS na jednotlivıch segmentech akumulátoru).
  - *Transient voltage suppressor* (*TVS*) - brání chvilkovım napìovım špièkám, tøeba zenerky.
  - Rezistory mají teplotní závislost, reálnì napø 50 ppm/K
  - Diody lze pouít k jednoduché stabilizaci napìtí, protoe mají malou závislost napìtí na tekoucí proudu.
  Vnitøní odpor v takovém pøípadì bude diferenciální odpor diody samotné. Zapojení dìlièe s diodou "dole" bude mít skoro
  o øád menší ztrátovı vıkon ne pouití normálního odporového dìlièe. Soubìnì bude malı pokles napìtí pod zátìí.
  V sofistikovanìjším pøípadì se pouije zenerka pro stabilizaci napìtí na dané úrovni. Pøi zatíení zdroje poklesne
  závìrné napìtí na diodì a tudí se ještì víc zmenší ztrátovı proud zpùsobenı Zenerovım prùrazem.
Ztrátovı vıkon klesá s rostoucí zátìí na zdroji.

**Monosti realizace jednoduchého zdroje** (obrázek vykradenı z pøiloeného zadání): </br>

![Monosti pro realizaci jednoduchého zdroje](week_2/jednoduchy-zdroj.png)

(a) = odporovı dìliè (b) = dìliè s LED dole (c) = dìliè se zenerkou dole


#### Úkol 2.1
>  RC èlánek, zapojení, pozorování chování pro rùzné frekvence vstupního signálu

Zapojení osciloskopu: Kanál CH1 mìøí vstupní generovanı signál. Kanál CH2 mìøí vıstupní signál. </br>
Vstupní signál je generován jako sinus s amplitudou 1500 mV a offsetem 1500mV pomocí LEO.
Díky tomuto nastavení lze rozumnì od oka odeèítat pøenosy pro jednotlivé frekvence.

Zapojení je inspirované zadáním, dùleitá je úprava derivaèního èlánku, nebo ten by obecnì na vıstupu generoval záporné napìtí,
které by nebylo zdravé pro clampovací diody na pinu MCU. Rezistory R3 a R4 nastavují stejnosmìrnı pracovní bod,
vıstup tak osciluje kolem støedu napìového rozsahu <0, 3V3>.
 ![Integraèní èlánek, zlomová frekvence](week_2/RC-clanky.png)

##### Integraèní èlánek

Postaven s R = 10k, C = 100n, proto je èasová konstanta tau = 1ms a zlomová frekvence f<sub>k</sub> = 160 Hz.
Odeèítání èasové konstanty není v tomto pøípadì pøíliš zajímavé pro svou pøímoèarost.
Experimentálnì je provedeno a u druhé konfigurace - derivaèního èlánku.

Frekvnenèí závislost odezvy na harmonickı signál:

  - Frekvence **zlomová** (160Hz)</br>
    Oèekávám pokles o 3dB, take asi 70% amplitudy. Zmìøenı pokles je cca 500 mV, co jsou øádovì dvì tøetiny amplitudy.
    To je o trochu vìtší zatlumení jak 3dB, ale je stále øádovì sedí s tolerancí rezistoru a kondenzátoru.
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
Postaven s rezistory R<sub>2,3,4</sub> = 10k, C = 100n, jedná se o trošku sofistikovanìjší zapojení, kde rezistory R<sub>3</sub>, R<sub>4</sub>
zajišují stejnosmìrnı pracovní bod uprostøed rozsahu napájení. </br>

**Analıza:** Uváíme superpozici, stejnosmìrnı zdroj korektnì nahradíme zdrojem 0V (zkrat). Tím se R<sub>3</sub>, RR<sub>4</sub> staly paralelními.
Pro snazší odvození oznaème R = R<sub>3</sub>||R<sub>4</sub> = 5k a pomocí nìj vyjádøíme všechny odpory v pøenosu.
Vznikl impedanèní dìliè. Mìøí se na R = R<sub>3</sub>||R<sub>4</sub>, "nahoøe" jsou v sérii kondenzátor a odpor R<sub>2</sub> = 2R.

![Odvození tau](week_2/rovnice.gif)

![Odvození tau](week_2/frekvence.gif)

Po numerickém dosazení vyjde, e pøenos derivaèní sloky dosáhne jednièky pro f<sub>0</sub> = 318 Hz,
ale díky integraèní sloce se na zlomové frekvenci f<sub>1</sub> = 106 Hz pøenos zalomí a jde dál vodorovnì.
Pro nekoneènou frekvenci je pøenos jedna tøetina, statické zesílení 0 (DC kompletnì utlumeno). </br>
**Závìr**: Èasová konstanta bude ta menší z obou èasovıch konstant systému. Oèekávám tau = 1/(2\*pi\*f<sub>1</sub>) = 1.5 ms.

**Experimentální odeètení**: Pøiveïme na vstup obdélníkovı signál. Ten bude pro náš systém pøedstavovat jednotkové skoky.
Pøedpokládejme, e zvolená frekvence - v mém pøípadì 10 Hz - je dostateènì nízká, aby se èlánek zvládal ustálit.
Amplituda skokové odezvy je tìsnì pøes jeden volt, jak je vidìt na obrázku:
  ![Derivaèní èlánek, amplituda odezvy na skok](week_2/derivacni-amplituda.png)
Po uplynutí jedné èasvé konstanty by mìla bıt odezva na 36% amplitudy. Pomocí kurzorù mùeme z osciloskopu odeèíst, e èasová konstanta
je pøiblinì 1.5 ms, viz následující obrázek.
  ![Derivaèní èlánek, tau](week_2/derivacni-tau.png)
Tento vısledek potvrzuje pøedchozí vıpoèet.
Byl ale experiment korektní? Pro odeètení amplitudy odezvy je nezbytné mít na poèátku systém ustálenı. Já pøedpokládal, e
frekvence 10 Hz je dostateèná pro ustálení odezvy. Kadou pùlperiodu vstupního signálu zapoène novı pøechodovı dìj dlouhı 50 ms.
Jestli jsme zmìøili èasovou konstantu 1.5ms, poté má systém mezi dvìma po sobì následujícími jednotkovımi skoky víc ne 33 èasovıch konstant.
Ji 4.6 tau znamená chybu menší ne jedno procento, pøi 33 tau je relativní chyba cca 4e-15. Experiment je tedy proveden korektnì, chyby zpùsobené
zanedbáváním a odhady jsou nesrovnatelnì vìtší ne chyby metodické.

**Ovìøení:**
Pro kontrolu vıše vypoètenıch frekvenèních vlastností zkusím odezvu derivaèního èlánku na harmonickı vstup.
Drme v pamìti, e amplitudová frekvenèní charakteristika má maximum pro nekoneènou frekvenci na zesílení 1/3, viz odvození pøenosu vıše.
Na vstupu èlánku je sinusovı signál s amplitudou 1500 mV, offsetem 1650 mV (støed rozsahu napájení) a promìnlivou frekvencí.
  - Frekvence skoro **nekoneèná** (50 kHz) </br>
    Oèekávám zeslabení signálu na jednu tøetinu a ménì. Zmìøená amplituda 449 mV øádovì sedí; H(s) = 1/3 toti platí a pro nekoneènou frekvenci a
další nezanedbatenou chybu vnáší nepøesné odeèítání hodnot. Na obrázku je 100 vzorkù z osciloskopu pracujícího na frekvenci 1MSps,
kadı dílek na ose èasové tak odpovodá jedné mikrosekundì.
  ![Derivaèní èlánek, nekoneèná frekvence](week_2/derivacni-vyssi.png)
  - Frekvence **zlomová** (108Hz)</br>
    Amplituda je tøikrát zeslabena (|H(s)| pro s -> nekoneèno) na cca 500mV, nad to ale bude amplituda zeslabena ještì o další 3dB na 0.7*500 = 350 mV.
Zmìøené napìtí sedí velmi pøesnì.
  ![Derivaèní èlánek, zlomová frekvence](week_2/derivacni-zlom.png)
  - Frekvence **o dekádu niší** (10Hz)</br>
  Signál je tak zatlumen, e bylo potøeba jej digitálnì zesílit na pìtinásobek, èasové prùbìhy osciloskopu tedy nejsou to scale.
Podle analızy bychom mìli mìøit 500mV zeslabenıch o 20dB (jsme dekádu od zlomovky), zmìøenıch 50 mV jsem tedy oèekával.
  ![Derivaèní èlánek, niší frekvence](week_2/derivacni-nizsi.png)


#### Úkol 2.2
> Zmìøení diferenciálního odporu LED

Na následujícím obrázku (zapùjèeném ze zadání pøiloeného vıše) je vidìt schéma zapojení a oèekávanı prùbìh
voltampérové charakteristiky na LED. Podle Shockleyovy rovnice ideální diody má závislost proudu na napìtí
v propustném smìru exponenciální charakter. Exponeniciálu zkusíme lokálnì linearizovat pomocí diferenciálních odporù
R<sub>diff1</sub> na okolí proudu 3 mA a R<sub>diff2</sub> na okolí proudu 20 mA.
  ![Diferenciální odpor, zadání](week_2/dif-odpor-zadani.png)

**Analıza:**
Pro exponenciální závislost proudu na napìtí platí d/du exp(c\*u) = c*exp(c\*u) a analogicky pro derivace vyšších øádù.
Protoe konstantní koeficient exponenciály v rovnici diody je jistì kladnı, budou vdy voltampérová charakteristika i všechny její derivace
ryze rostoucí funkcí. Podle infinitezimální definice vodivosti a odporu:

  ![Derivaèní èlánek, nekoneèná frekvence](week_2/dif-odpor.gif)

a vıše zmínìné podmínky `c > 0` plyne, e diferenciální odpor bude klesat, nebo je pøevrácenou hodnotou diferenciální
vodivosti g<sub>diff</sub> a ta jistì roste.

**Ovìøení:**
Dopøedné mìøení na LED je mìøeno pøímo kanálem `VLED`. Kanál `VR` mìøí napìtí na seriové kombinaci LED a 47ohm odporu.
Odeètením `VR - VLED` získáme diferenciální mìøení napìtí na odporu, kterı je pøímo úmìrnı tekoucímu proudu.
sloupec I se dopoète vztahem `I = (VR-VLED)/47`. Mìøení probìhlo dvakrát s dvìma rùznımi rezistory velikosti 47 ohm.


První sada mìøení:

| VR [mV] | VLED [mV] | I [mA] | R<sub>diff</sub> [ohm] |
|--- | ---| --- | --- | 
| 1810 | 1675 | 2.87 | 17.74 |
| 1850| 1686| 3.49 |    |
| 2862 | 1897 | 20.5 | 6.09  |
| 2983 | 1911| 22.8 |   |

Druhá sada mìøení:

| VR [mV] | VLED [mV] | I [mA] | R<sub>diff</sub> [ohm] |
|--- | ---| --- | --- |
| 1833 | 1667 | 3.53 |   16.18   |
| 1790 | 1656 | 2.85 |      |
| 2806 | 1831 | 20.75 |  8.35   |
| 3045 | 1867 | 25.06 |     |

**Závìr**: Diferenciální odpor LED jsou jednotky, nejvıše desítky ohmù. Mìøení je zøejmì silnì zatíeno nepøesností
rezistorù - snaíme-li se mìøit nízkı diferenciální odpor LED, hraje ohm sem èi tam u ochranného rezistoru velkou roli.
Kadopádnì se potvrdila hypotéza, e diferenciální odpor musí s rostoucím proudem klesat.
Fyzikálnì je to moné vysvìtlit vìtší saturací PN pøechodu uvnitø diody. Tím klesá odpor v *depletion layer* a
voltampérová charakteristika srtmì stoupá. Strmì tím stoupá i ztrátovı vıkon, ten byl v pøípadì maximálního mìøeného proudu
roven `25mA * 1.87V = 46.7 mW`.

**TODO**: Zeptat se na pomìr vıkonu vysvíceného a vytopeného LEDkou.

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
**TODO** ovìøit, e to byla skuteènì difuzní kapacita. Pokusit se ji zmìøit.
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
