# Pozn�mky z p�edm�tu LPE
Usmoleno **Vojt�chem Michalem** (vojta.michall@email.cz) v pr�b�hu letn�ho semestru 2021 (B202). </br>
Ofici�ln� materi�ly jsou na Moodle na str�nce https://moodle.fel.cvut.cz/course/view.php?id=5814
a na Embedded serveru https://embedded.fel.cvut.cz/kurzy/lpe/LPE2021. </br>
Seznam sou��stek s pinout a schematick�mi zna�kami: https://moodle.fel.cvut.cz/pluginfile.php/293919/mod_resource/content/3/Soucastky_vyvody_LPE_4.pdf

T�dny jsou ��slov�ny chronologicky, pozn�mky k nim jsou uvedeny v obr�cen�m po�ad�.
Jako prvn� je tedy uveden posledn� t�den, scrollov�n�m na konec str�nky se �lov�k dostane na t�den prvn�.

## T�dek 5 - Pokro�ilej�� opera�n� zesilova�e
Instrukce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/295565/mod_resource/content/2/LPE_5_tyden_poznamky_2021_partII_v2.pdf

#### �kol 4.6
> Zapojte OZ jako kompar�tor bez a s hysterez�

Kompar�tor U1A mus� saturovat na nap�jen� �i na zem, proto nem� ��dnou nebo jen kladnou zp�tnou vazbu 
(v�stup je p�iveden na neinvertuj�c� vstupn� svorku).
Hysterezi zaji��uje rezistor R1 p�ipojen� mezi neinvertuj�c� svorku a v�stup U1A. D�le je k neinv. svorce
p�ipojen v�stup sledova�e U1B udr�uj�c�ho konstantn� �rov�� nastavenou trimmerem RV1. Na invertuj�c� svorce je p�ipojen 
kondenz�tor C1 z RC �l�nku vyhlazuj�c�ho obd�ln�ky generovan� PWMkou na exponenci�lu. </br>
**Sch�ma:**
![Sch�ma 4.6](week_5/schema4.6.jpg)

"S�la" hystereze (jak daleko jsou od sebe p�ekl�p�c� �rovn�) bude z�visl� na hodnot� rezistor� R1, R2 kolem kompar�toru. 
Pakli�e ozna��m v�stup U1A jako Uo, nap�t� na v�stupu sledova�e U<sub>ref</sub> a rozhodovac� �rove� hystereze jako U<sub>H</sub>,
pomoc� uzlov�ch nap�t� lze odvodit vztah

![Odvozen� hystereze](week_5/hystereze_eq.gif).

Pro z�sk�n� obou �rovn� U<sub>H+</sub> a U<sub>H-</sub> je pot�eba dosadit Uo = 3V3 a Uo = 0V. Speci�ln� p��pady:
  - pro R1 = nekone�no (��dn� zp�tn� vazba) se druh� s��tanec redukuje na 0 a plat� U<sub>H</sub> = U<sub>ref</sub>.
  kompar�tor se p�ekl�p� bez jak�koli hystereze
  - pro R1 = 0 (jednotkov� ZV) je zlomek roven jedni�ce, referen�n� nap�t� se ode�te a zb�v� U<sub>H</sub> = U<sub>o</sub>
  vzd�lenost rozhodovac�ch �rovn� je cel� rozsah nap�jen� (3V3).
  - pro R1 = R2 ("polovi�n�" ZV) je zlomek roven 1/2 a rozhodovac� �rovn� jsou v polovin� vzd�lenosti U<sub>ref</sub>
  a Uo; vzd�lenost rozhodovac�ch �rovn� je 50% rozsahu nap�jen� (3V3).
  - **Obecn�:** Po �prav�ch lze odvodit (pom�rn� o�ek�vateln�) v�sledek,
  �e "���ka" hystereze je p��mo �m�rn� d�lic�mu pom�ru d�li�e R1, R2. Viz n�sleduj�c� rovnice

![Odvozen� hystereze](week_5/hystereze_rozdil.gif)

**P�r nam��en�ch pr�b�h�:**</br>
Kan�ly osciloskopu:
  - CH1 = v�stup kompar�toru (label `OSC1`)
  - CH2 = p�ekl�p�c� �rove� (label `OSC2b`)
  - CH3 = p�echodov� d�j na C1 (nen� zakresleno ve schematu)


a) Siln� hystereze (R1 = 10k),v�stup trimmeru U<sub>ref</sub> = 1.667V. </br>
Podle p�edchoz�ho odvozen� bych o�ek�val rozhodovac� �rovn� 
U<sub>H</sub> = `1.667 +/- (3.3-1.667) * 10k/(10k+10k) = 1.667 +/- 0.8165` = 2.4835V a 0.85V
(na obr�zku jsou rozhodovac� �rovn� zm��eny pomoc� horizont�ln�ch kurzor�).
![](week_5/komparator.png)

b) ��dn� hystereze (R1 = inf), v�stup trimmeru 1.815V:
![](week_5/komparator_bez_hystereze_1830_mV_stred.png)

**Vliv rozhodovac�ch �rovn� na st��du obd�ln�ku**

Na n�sleduj�c�ch pr�b�h�ch lze pozorovat, jak nastaven� rozhodovac� �rovn� trimmerem ovlivn� st��du generovan�ho obd�ln�ku.
N�zk� rozhodovac� �rove� znamen�, �e nap�t� kondenz�toru bude v�t�inu doby nad rozhodovac�mi �rovn�mi a v�stup tak bude v�t�inu u doby na zemi.
Naopak vy��� rozhodovac� �rove� povede na vy��� st��du (relativn� del�� dobu, kdy je v�stup U1A na nap�jen�).
Pro p��li� vysok�/n�zk� rozhodovac� �rovn� se nebude kompar�tor p�ekl�p�t v�bec a na v�stupu bude st�le vysok� �i n�zk� �rove�.

a) Slab� hystereze (R1 = 120k), v�stup trimmeru 2.749V:
![](week_5/komparator_mensi_hystereze_2749_mV_stred.png)

b) Slab� hystereze (R1 = 120k), v�stup trimmeru 1.093V:
![](week_5/komparator_mensi_hystereze_1093_mV_stred.png)

**Odolnost proti ru�en�**
Hystereze kompar�toru je nezbytn� v aplikac�ch, kde je na vstupn� sign�l superponovan� vysokofrekven�n� ru�en�.
Jeho vlivem by se mohl kompar�tor p�ekl�p�t �ast�ji, ne� je skute�n� ��douc�. P�id�n�m hystereze vznik� ur�it�
p�s uprost�ed nap�ov�ho rozsahu, kde kompar�tor nereaguje a �ek� a� na dosa�en� definovan� �rovn�.
Pro kvalitn� potla�en� �umu bychom si p��li maxim�ln� hysterezi. Siln�j�� hystereze ale s sebou nese inherentn� probl�m,
�e by mohla potla�it i vlastn� vstupn� sign�l, kter� si p�ejeme detekovat (ilustrov�no n�e).

K PWM z minul�ch experiment� je na n�sleduj�c�m obr�zku p�id�na dal�� PWM na frekvenci asi sedmkr�t vy���.
Spojeny jsou p�es rezistory r�zn� velikosti (rychlej�� PWM simuluj�c� �um proto m� ni��� amplitudu). 

Na n�sleduj�c�ch pr�b�h�ch je ilustrov�na �patn� rozhodovac� �rove� a pot� �rove� "na hran�" p��pustnosti.
Jednou se kompar�tor v�bec podle vstupn�ho sign�lu nep�ekl�p�, jindy se p�ekl�p� jen v ��sti p��pad� a nen� tak spolehliv�.
![](week_5/spatna_rozhod_lvl.png)
![](week_5/mediocre_rozhod_lvl.png)

#### �kol 4.7
> Zapojte OZ jako gener�tor obd�ln�kov�ho sign�lu (Astabiln� Klopn� Obvod)

Sch�ma je na obr�zku. Prakticky je to stejn� kompar�tor jako v �loze v��e, jen se m�sto extern� PWMky nech�
kondenz�tor p�eb�jet p��mo z v�stupu U1A. Pro snaz�� nastavov�n� referen�n� �rovn� pomoc� trimmeru RV1 jsem
zapojil nevyu�it� OZ jako nap�ov� sledova� U1B.
![Sch�ma 4.7](week_5/schema4.7.jpg)

**Pozn.** Bez hystereze (R1 = inf) se v obvodu d�je kdov� jak� �patnost.
Na n�sleduj�c�m obr�zku je jak�si sign�l z v�stupu OZ, nejsp�e je ale st�le podvzorkovan�.
Rozhodn� takov� rychl� smy�ka nebude zdrav� ani pro OZ, ani pro EMC.
![](week_5/AKO_bez_hystereze.png)

Na referen�n�m nap�t� nastavovan�m trimmerem je z�visl� frekvence i st��da generovan�ho obd�ln�ku, jak
se lze p�esv�d�it z n�sleduj�c�ch pr�b�h�. Mal� hystereze (R1 = 120k) a r�zn� polohy trimmeru: </br>
a) Trimmer U<sub>ref</sub> = 57mV:
![](week_5/AKO_mala_hystereze_trimmer_57mV.png)
b) Trimmer U<sub>ref</sub> = 683mV:
![](week_5/AKO_mala_hystereze_trimmer_683mV.png)
c) Trimmer U<sub>ref</sub> = 1659mV:
![](week_5/AKO_mala_hystereze_trimmer_1659mV.png)
d) Trimmer U<sub>ref</sub> = 3106mV:
![](week_5/AKO_mala_hystereze_trimmer_3106mV.png)

Korektn�j�� je ��ci, �e na poloze trimmeru z�vis� doby T1 (nap�t� na kondenz�toru stoup�) a T2, kdy se kond�k vyb�j�.
B�hem t�chto dob se nap�t� po exponenci�le p�esouv� mezi jednou a druhou p�ekl�p�c� �rovn�. Z jejich pom�ru a p�evr�cen�
hodnoty sou�tu lze potom vypo��st frekvenci a st��du generovan�ho obd�ln�ka. </br>
**Odvozen�**

![](week_5/odvozeni1.jpg)

D�v� tento v�sledek smysl? Proto�e u(t) je v�dy mezi u<sub>0</sub> a u<sub>inf</sub>, mus� b�t zlomek men�� jak 1,
proto bude logaritmus z�porn� a dohromady bude t kladn� (co� pot�ebujeme. Z povahy probl�mu je trivi�ln� vid�t,
�e T1 i T2 mus� b�t nez�porn�. Dokonce mus� b�t i kladn� kv�li spojitosti nap�t� na kondenz�toru a nenulov� hysterezi).
Odtud d�le

![](week_5/odvozeni2.jpg)

Poda�ilo se vyj�d�it �asy T1 a T2 jako funkce referen�n�ho nap�t� na trimmeru. S�lu hystereze nastavovanou rezistorem R1
neberu jako prom�nnou, po��t�m jen s hodnotou 120k, pro kterou jsem si nam��il data. St�ejn� ot�zka: D�v� to furt smysl?
Logaritmy mus� b�t z�porn�. U T2 to je vid�t trivi�ln� (ve jmenovateli je n�co kladn�ho nav�c, co nen� v �itateli).
Pro T1 to nen� tak z�ejm�. Proto�e v�ak 12/13 3V3 > 12/13 U<sub>ref</sub>, bude �itatel i jmenovatel zlomku z�porn�,
jmenovatel bude v�t�� v absolutn� hodnot�. Tak�e asi OK.

�asov� konstanta d�je je `tau = 12 ms`. Dosazen�m do rovnice (2) z�sk�me
  - pro U<sub>ref</sub> = 1.659V ... `T1 = 1.859 ms`, `T2 = 1.840 ms`, `f = 270 Hz`
  - pro U<sub>ref</sub> = 0.683V ... `T1 = 1.199 ms`, `T2 = 4.060 ms`, `f = 190 Hz`
  - pro U<sub>ref</sub> = 0.057V ... `T1 = 0.976 ms`, `T2 = 21.15 ms`, `f = 45 Hz`

Pro U<sub>ref</sub> = 1659 mV jsme p�ibli�n� uprost�ed rozsahu nap�jen�, tak�e by m�la vyj�t st��da 50%.
Frekvence nejsou �pln� stejn� jako ty m��en� osciloskopem (302, 205 a 47 hertz�).
Mo�n� chyby mohl do v�po�tu vn�st fakt, �e OZ nen� dokonale rail to rail. Dal�� chyby p�irozen� vn��
nejistoty hodnot sou��stek, kvantiza�n� chyba p�i m��en� nap�t� atd.</br> 
V�eobecn� ale v�sledky nejsou v rozporu s realitou, v�po�et souhlas�.

#### �kol 4.8
> p�evodn�k obd�ln�kov�ho sign�lu na troj�heln�kov� (integr�tor)

Druh� OZ U1B akor�t p�ed�l�me z nap�ov�ho sledova�e na integr�tor, kter� se p�ipoj� na v�stup AKO.
P�ipojen� dal��ho tvarova�e s diodami na v�stup U1B by umo�nilo generovat sinusov� sign�l (star�� metody
analogov�ho generov�n� funkc�. Dnes �asto vytla�ov�ny digit�ln�m ��zen�m a DAC).
![Sch�ma 4.8](week_5/schema4.8.jpg)
Zaj�mav� je posunut� nula pro U1B pomoc� kombinace rezistor� R5, R6.

Generovan� sign�ly jsou na n�sleduj�c�m pr�b�hu (v�znam kan�l� osciloskopu je podle sch�matu):
  - CH1 = v�stup U1A (obd�ln�k)
  - CH2 = v�stup U1B (troj�heln�k)
  - CH3 = C1 (p�echodov� jev na RC �l�nku)
![Sch�ma 4.8](week_5/trojuhelnik.png)

#### �kol 4.9
> Sestavte zapojen� s OZ � regul�tory teploty

Na sch�matu jsou dv� alternativy
  - Neosazen� R4a => U1B m� jen z�pornou zp�tnou vazbu a chov� se line�rn�.
  - Neosazen� R4b => U1B m� jen kladnou zp�tnou vazbu a je to on/off sp�na�.

Na v�stup OZ je p�ipojena LED indikuj�c� "spu�t�n� topen�" (v p��pad� line�rn�ho m�du ukazuje aktu�ln� intenzitu topen�).
D�le je v�stupem OZ ��zena b�ze NPN tranzistoru Q1, kter� reguluje proud tekouc� skrz R1. Joulovo teplo na n�m sp�len�
oh��v� NTC (rostouc� teplota ... klesaj�c� odpor) TH1, kter� uzav�r� z�pornou zp�tnou vazbu kolem cel�ho obvodu.
Dvojice sou��stek R3, RV1 nastavuje posunutou nulu pro U1B, kolem t�to �rovn� kol�s� i nap�t� na d�li�i R2,TH1.
S rostouc� teplotou TH1 kles� jeho odpor, tak�e kles� i v�stup d�li�e. V d�sledku toho pokles� nap�t� na neinvertuj�c�
svorce. Kdy� poklesne pod �rove� invertuj�c� svorky, OZ vypne topen� a TH1 se chlad�.
![Sch�ma 4.9](week_5/schema4.9.jpg).

Stejnou zp�tnou vazbu by �lo uzav��t, kdybychom TH1 p�ipojili do odporov�ho d�li�e "nahoru" a oto�ili svorky oper�ku.
Klesaj�c� odpor TH1 by zvy�oval celkov� nap�t� na v�stupu d�li�e, t�m by rostlo nap�t� na inv. svorce
a t�m by opera�n� zesilova� brzdil topen�.

�pi�kov� topic� proud byl 127 mA z 5V p�es R1=33ohm a Q1, to odpov�d� v�konu cca p�l wattu.
(To mimochodem p�i nap�t� 3v3 na v�stupu U1B odpov�d� proudu 1.35 mA do b�ze Q1. Ten by tak m�l �initel
h21e t�sn� pod stovku, co� je o�ek�van� hodnota pro v�konov� BJT. V p�edchoz�ch �loh�ch se pou��val sign�lov� BJT
se zes�len�m cca 400).

**Identifikace syst�mu:** Proces skokov�ho oh��t� NTC z odporu 11 442 ohm (cca 22�C) na ust�len�ch 4316 ohm (cca 45�C) trval 214 sekund.
P�edpokl�dejme, �e se jedn� o syst�m prvn�ho ��du. Zm��en� �as 214 s je p�tin�sobek �asov� konstanty, tak�e by mohlo platit
cca `tau ~ 43 s`. </br>
To asi nen� �pln� nere�ln�, ale model m� jist� nezanedbatenou chybu, proto�e syst�m se nen� schopen oh��vat
libovoln� rychle (Q1 omezuje oh��vac� proud tekouc� p�es R1). Proto je velikost derivace teploty na TH1 omezen�
a oh��v�n� by bylo pot�eba modelovat syst�mem ��du vy���ho.

## T�den 4 - Opera�n� zesilova�e
Instrukce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/283742/mod_resource/content/4/LPE_4_tyden_poznamky_2021_v3.pdf

V�robn� technologi� lze oper�ky rozd�lit na bipol�rn� (nap� OPA227) a unipol�rn� - d�le d�leny podle JFET�/CMOS� na vstupu
  - Bipol�rn�  - n�zk� nap�ov� �um p�i zkratu vstup� (CMOS t�eba 8uV peak/peak, OPA227 zvl�dne t�eba 90nVp-p .. 2 ��dy rozd�l)</br>
     Vstupn� proud v klidu (input bias current) v ��du t�eba 2.5 nA (OPA227).
  - Unipol�rn�: Fantastick� klidov� vstupn� proud +/-1 pikoamp�r pro CMOS, JFETy t�eba femtoamp�ry.
    - JFETy - n�zk� proudov� �um
    - CMOSy (t�eba MCP6002) - Funguj� i pro n�zk� nap�t� (i t�eba 1.8V), vhodn� t�eba k MCU (tam u� m�em zdroj 3V3).

V p��pad� MCP6002 je zm��iteln� "body dioda" ve sm�ru Vss->VDD. P�i p�ep�lov�n� nap�jen� se otev�e a bude to "ho�et".

Ide�ln� **open-loop gain** je nekone�no, re�ln� 88-112 dB (pro MCP6003). OPA227 t�eba 160 dB (10<sup>8</sup> kr�t)

Charakteristika **Gain-bandwidth product** (= sou�in open-loop gain a ���ky p�sma (bandwidth)), odr�� frekven�n� z�visl� vlastnosti oper�ku.
Na frekvenci `bandwidth` je jednotkov� zes�len�. P�i stejnosm�rn�m vstupn�m nap�t� je zes�len� `open-loop gain` (viz ARI str 49). Kdy� jsme n�kde
mezi, pokles� s rostouc� frekvenc� zes�len�, kter�ho um� oper�k dos�hnout (rychl� hrany vy�aduj� rychl� p�eb�hy a OZ m� kone�n� slew rate).
`Gain-bandwidth product` tak omezuje sou�in frekvence a zes�len� na konstantn� hodnotu.

#### �kol 4.1
> Zapojte OZ jako sledova� nap�t� (impedan�n� odd�lova�), na vstupu nap�t� na LED (ILED=5-20mA), zm��te v�stupn�
odpor tohoto zapojen� pro IOUT = 0 a 4 mA (zat�en� OZ)

<img align="right" src="week_4/ubytek_s_proudem.png">
Ide�ln� vlastnosti sledova�e: R<sub>in</sub> = nekone�no, R<sub>out</sub>= 0.
Re�ln� m� v�stupn� stupe� oper�ku nenulov� vnit�n� odpor,
pro vy��� proudy za�ne v�stupn� nap�t� OZ poklesat kv�li �bytku. "Vnit�n� odpor" m��e b�t pro MCP6002 ��dov� 100 ohm.

Na grafu od Ing. Petruchy je osa x v�stupn� proud v mA, osa y je referen�n� nap�t� ve voltech.

M���m v bod� Voltmetr1 (v�stup oper�ku) p�i z�t��ch 0mA a p�ibli�n� 4mA.
Zm��en� nap�t�: bez zat�en� 1811.97mV, p�i z�t�i 4.17mA nap�t� 1815.13mV. Z toho lze vypo��st
v�stupn� odpor pro n�zk� proudy R<sub>out</sub> = 0.76 ohm.</br>
Srovnej s vlastnostmi, kter� bychom dostali odeb�r�n�m proudu p��mo z nap�ov�ho d�li�e nap� z rezistor� 10k. Odb�r 4mA by
na horn�m rezistoru v d�li�i zp�sobil �bytek 4V. V p��pad� velk�ch d�li�� (t�eba m��en� 600V na tractive system d�li�em 68k : 1M)
impedan�n� odd�len� nezbytn�.
![Nap�ov� sledova�](week_4/Rout.jpg)

Pozn: Nap�ov� sledova� je zp�tnovazebn� soustava, kter� v principu nemus� b�t v�bec stabiln�.
U n�kter�ch zesilova�� se toto explicitn� uv�d� jako **unity gain stability**. Pokud vznikl� zapojen� nen� stabiln�,
OZ bude m�t tendenci oscilovat. D�sledkem potom je, �e multimetr m���c� RMS t�eba bude zd�nliv� m��it rozumn� ��sla,
ale osciloskop uk�e rychl� smy�ky. Tot� se m��e st�t nap��klad u low drop-out regul�tor�.

Nevyu�it�m oper�k�m je pot�eba definovat �rove� vstup�, nap��klad zapojen�m sledova�e zem�:
![Nap�ov� sledova�](week_4/definovane_vstupy.jpg)
#### �kol 4.2
> Sestavte neinvertuj�c� zesilova� nap�t� 11x a zm��te pomoc� n�j satura�n� nap�t� NPN tranzistoru.

Zapojen� je na obr�zku, odpor R<sub>b</sub> bude nab�vat v�cero hodnot pro dosa�en� r�zn�ho stupn� saturace.
![Nap�ov� sledova�](week_4/saturace.jpg)

Nap�t� na kolektoru NPN tranzistoru je p��mo rovn� nap�t� U<sub>+</sub> na neinvertuj�c� svorce OZ.
Nap�t� U<sub>o</sub> je na v�stupu opera�n�ho zesilova�e (bod *Voltmetr1*).

a) Zm��en� nap�t� pro b�zov� odpor 10k: U<sub>+</sub> = 33 mV, U<sub>o</sub> = 363 mV.
D�v� v�sledek smysl? OZ je zapojen s d�li�em 1k a 10k, jeho zes�len� je `A = 1 + 10/1 = 11`.
Na v�stupu OZ tak o�ek�v�m 33mV * 11 = 363 mV, co� se rovn� zm��en�mu nap�t�.
Se�la se n�zk� z�t� v�stupu OZ `< 0.3 mA` a z�ejm� velmi dobr� hodnoty rezistor� v d�li�i.

b) Zm��en� nap�t� pro 5k v b�zi: Saturace NPN naroste, o�ek�v�m ni��� satura�n� nap�t� ve sm�ru kolektor->emitor. </br>
Zm��eno U<sub>+</sub> = 24 mV, U<sub>o</sub> = 252 mV. </br>
M��en� je v po��dku. ADC m��� kv�li kvantiza�n� chyb� (ide�ln�) +/- 0.5 LSB, dal�� chybu m��e vn�st numerick� chyba p�epo�tu
LSB -> mV v mikrokontroleru (n�chyln� na ztr�tu p�enosti floatov�ch operac�, nebo na o�ez�v�n� v celo��seln�m d�len�).
Pakli�e by skute�n� nap�t� U<sub>ce</sub>bylo t�eba 23mV, pot� m��en� v�stup OZ sed� p�esn�.
c) Zm��en� nap�t� pro 470 ohm� v b�zi: U<sub>+</sub> = 14 mV, U<sub>o</sub> = 150 mV.
Z�v�ry jsou stejn� jako v pod�loze (b).

Praktick� v�znam neinvertuj�c�cho zapojen� OZ je kv�li p�esn�j��mu digit�ln�mu m��en�. Digit�ln� multimetr m� nejistotu m��en�
z�vislou na aktu�ln�m m��ic�m rozsahu. Pakli�e by nejni��� rozsah byl t�eba 200 mV a nejistota t�eba 0.5% rozsahu,
vn�elo by to implicitn� chybu vn��en� 1 mV. Kdybychom pak cht�li m��it nap�t� t�eba 10 mV, rovnou m�me 10% relativn� chybu.
Pou�it�m zesilova�e se zv��� m��en� hodnota a t�m poklesne vliv chyby z rozsahu.

Jin�mi slovy OZ zesiluje "analogov�" (d�ky ZV zapojen� m��eme dokonce p�edpkl�dat, �e zesiluje velice dokonale).
Kdy� jej p�ed�ad�me za��zen� vn�ej�c�mu kvantiza�n� chybu, pot� se relativn� chyba kvantov�n� sn��, proto�e optim�ln�
vyu��v�me cel� rozsah na m��en� sign�lu po zes�len� (viz protokol 2 ze SME: vliv nesrp�vn�ho vertik�ln�ho m���tka osciloskopu 
na vypo�ten� RMS).

#### �kol 4.4
> Zm��te vstupn� nap�ov� offset pou�it�ho opera�n�ho zesilova�e (MCP6002).

Sch�ma zapojen�:
![Nap�ov� sledova�](week_4/offsety.jpg)


M��en� s pou�it�m R4 = 120k ned�valo ��dn� m��iteln� v�sledky.
Pro R4 = 1 megaohm (zes�len� oper�ku `A = 1+1'000'000/470 = 2128`) nam��eno:
  - U<sub>o</sub> = 1.4 mV pro OZ pod piny 1,2,3
  - U<sub>o</sub> = 5.6 mV pro OZ pod piny 5,6,7

S ohledem na zes�len� to odpov�d� vstupn�m offset�m 0.66uV pro OZ na pinech 1,2,3 a 2.63uV pro OZ na pinech 5,6,7.
Datasheet garantuje maxim�ln� offset 4.5 mV, tak�e nam��en� offsety jsou velice velice velice dobr�
(a v r�mci paralelky na cvika asi celkem v�jime�n�).


#### �kol 4.3
> Sestavte zapojen� I/U p�evodn�ku s OZ a pou�ijte jej pro zpracov�n� sign�lu z fotodiody (n�hrada �irou LED). Na
fotodiodu blikejte pomoc� LED (frekvence 1 Hz a� 1 kHz, st��da 2-50 %). Uspo��dejte dan� prvky jako reflexn� senzor.

Zapojen� na obr�zku:
![Nap�ov� sledova�](week_4/ledky.jpg)

*gener�tor* generuje obd�ln�kov� sign�l, kter�m se sp�n� zelen� vys�lac� LED v kolektoru NPN tranzistoru.
Ta je optickou vazbou spojena s p�ij�maj�c� �ervenou LED, kterou kv�li dopadaj�c�mu sv�tlu te�e proud v z�v�rn�m sm�ru. 
Prvn�m opera�n�m zesilova�em je proud p�eveden na nap�t�; to je zes�leno druh�m oper�kem 
(s pou�it�m R2 = 188k, R4 = 10k je zes�len� `A = 1+188/10 ~ 20`) a m��eno kan�lem 2 osciloskopu.
Kan�l 1 osciloskopu m��� nap�t� v kolektoru tranzistoru, proto je vys�lac� LED aktivn� p�i p�izemn�n� sign�lu.

![Nap�ov� sledova�](week_4/ledky_prubeh.png)

S prom�nlivou st��dou jsou pr�b�hy v�ce m�n� stejn�, modr� kan�l (p�ij�man� sign�l) se ust�l� na hodnot� ~3V.
Dosa�en� �rove� je z�visl� na s�le optick� vazby (nap�. poloha a nato�en� LEDek).

## T�den 3 - Tranzistory
Instrukce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/283739/mod_resource/content/4/LPE_3_tyden_poznamky_2021_v4.pdf

#### �kol 3.1
> Zm��it proudov� zesilovac� �initel NPN tranzistoru h<sub>21E</sub>

<img align="right" src="week_3/common-emitor.png">

Z�kladn� zapojen� se spole�n�m emitorem.
Na b�zi je zapojen 1 megaohm proti 3V3, �bytek na n�m zm��en jako 2.660 V (na PN p�echod B->E zb�v� 636 mV).
V kolektoru je �erven� LED a rezistor 470R s serii proti 3V3, na R<sub>k</sub> �bytek 528 mV.

Z toho plyne proud b�z� I<sub>b</sub>` = 2'660/1'000'000 = 2.6 uA` a proud kolektorem I<sub>c</sub>` = 528/470 = 1.12 mA`
a zesilovac� �initel h<sub>21E</sub>` = Ic / Ib = 432`, co� je o�ek�vateln� hodnota u sign�lov�ho BJT.
Podle datasheetu jsou zes�len� BJT s p��ponou "C" v rozsahu 400-800, tak�e dan� tranzistor je v garantovan�m rozsahu.

S t�mto zes�len�m lze nahradit 1M v b�zi i odporem k��e - ten je ale v ��du des�tek kOhm a v�ce pouze pro n�zk� nap�t�.
**Se s�ov�m nap�t�m (230 V RMS) se k��e proraz� a odpor v�razn� poklesne**.

#### �kol 3.2
> Rozsv�tit LED pomoc� NPN tranzistoru (zm��it UBE, UCE, orienta�n� v�po�et Rb, Rc)

NPN bude pou�it jako sp�na� pro seriov� zapojen� �erven� LED a rezistoru proti 5V,
tak�e v saturaci budu p�edpokl�dat nulov� �bytek nap�t� mezi kolektorem a emitorem.
P�i pou�it� rezistoru 470 ohm v s�rii s LED s dop�edn�m nap�t�m cca 1.8V by m�l v pln� sepnut�m stavu LEDkou t�ci proud 
`Ic = (5-1.8)/470 = 6.8mA`. P�i proudov�m zesilovac�m �initeli h<sub>21e</sub> = 432 je pot�eba dodat do b�ze
proud alespo� `Ib = Ic/h21e = 15 uA`. Budu-li p�edpokl�dat, �e nap�ov� �bytek p�echodu
BE se nebude p��li� m�nit od �lohy 3.1, a z�stane tedy cca 650mV, pot� do b�ze pot�ebuji rezistor nejv��e
`Rb_max = (3V3 - 0.65)/15uA = 176 kOhm`. Pou�it� nap��klad 22kOhm n�m d� "�estin�sobnou jistotu",
�e sp�n�n� bude fungovat bez ohledu na neideality sou��stek a p��padn� �umy.

Zm��en� satura�n� nap�t� U<sub>ce</sub> tranzistoru v dan�m zapojen� je 57mV, co� ve srovn�n� s �bytkem 5V na cel� v�tvi v�etn�
LED a rezistoru je skute�n� zanedbateln�. Zm��en� �bytek na p�echodu b�ze-emitor je 680 mV, tak�e odpov�d� o�ek�van�mu �bytku.

Proto�e NPN tranzistor v sepnut�m stavu p�izem�uje sv�j kolektor, lze z n�j sestrojit nejhloup�j�� invertor. Vysok� �rove� 
na b�zi zp�sob� n�zkou �rove� na kolektoru a naopak. Viz n�sleduj�c� obr�zek. Kan�l 1 je U<sub>be</sub>, kan�l 2 je U<sub>ce</sub>.
Zaj�mav� je prohnut� U<sub>ce</sub> v oblasti, kde m� sign�l na b�zi maximum. Saturace BJT neprob�hne najednou, s rostouc�m
proudem stoup� m�ra saturace. Kv�li tomu nen� ani satura�n� nap�t� ve sm�ru C->E konstantn�, n�br� kles� s rostouc� m�rou saturace.

![Negace sign�lu pomoc� NPN tranzistoru](week_3/invertor.png)
#### �kol 3.3
> Rozsv�tit LED pomoc� PNP tranzistoru (zm��it UBE, UCE)

Princip zapojen� �pln� identick� jako u NPN, jen "zrcadlov� obr�ceno". PNP je v zapojen� se spole�n�m emitorem (emitor na nap�jen�, vstup na b�zi, z�t� v kolektoru).
Na b�zi je p�es odpor 10k p�ipojen gener�tor, dal��ch 10k je zapojeno mezi b�zi a emitor jako pullup pro rychlej�� zav�r�n�
(vznik� vodiv� cesta mezi b�z� a emitorem, kter� urychluje vynulov�n� nap�t� U<sub>be</sub> a rekombinaci nosi�� v PN p�echodu).
V kolektoru je v s�rii �erven� LED a 470R proti zemi. Pou�it� zapojen� je vlevo na sch�matu zap�j�en�m ze zad�n�, na port STM32_Px.x
je p�ipojen gener�tor. Zapojen� vpravo je z�kladn� zapojen� pro sp�n�n� nap�jen� vy���ho, ne� dosahuj� logick� �rovn� ��dic� logiky
(v takov�m p��pad� by prost� zapojen� PNP nesta�ilo, proto�e logika by neum�la b�zi PNP dostat dostate�n� vysoko. Alternativou
by bylo pou��t ��zen� open collector a PNP zav�rat "samosp�dem" pomoc� pullupu, ��dic� pin by ale musel tolerovat vysok� nap�t�.)

![Zapojen� PNP v obvodu](week_3/pnp_zapojeni.png)

P�i saturaci PNP tranzistoru lze zm��it hodnoty U<sub>eb</sub> = 630 mV, U<sub>ec_sat</sub> = 53 mV

Zaj�mav� jsou dva �asov� pr�b�hy se zapojen� s PNP tranzistorem se sinusem a obd�ln�kem na vstupu.

Sinusov� vstup: kan�l 1 je b�ze, kan�l 2 je kolektor, kan�l 3 je nap�t� na rezistoru v kolektoru. Je vid�t, �e
obvod op�t m� invertuj�c� charakter, zaj�mav� je n�b�h nap�t� na rezistoru (n�b�n� hrana kan�lu 3), kde 
se projevuje exponenci�ln� z�vislost proudu b�z� na nap�t�, je� se line�rn� z�vislost� Ic na Ib p�ev�d� na exp z�vislost proudu kolektorem
na nap�t� U<sub>eb</sub>. Jin�mi slovy: pakli�e `Ib ~ exp(Ueb)` a `Ic = Ib * h21e`, pot� `Ic ~ exp(Ueb)`.
Z tohoto d�vodu lze na rezistoru pozorovat exponenci�ln� n�b�h proudu kolektorem.

![Pr�b�h nap�t� na PNP sp�na�i](week_3/pnp_prubeh.png)

Dal�� m��en� je pro obd�ln�kov� vstup: kan�l 1 je b�ze, kan�l 2 je kolektor, kan�l 3 je nap�t� na rezistoru v kolektoru, kter� je �m�rn� tekouc�mu proudu.
Je zaj�mav�, �e i p�es nulov� proud kolektorem je sp�dn� hrana nap�t� U<sub>c</sub> pomal�. To je projev saturace LEDky, u kter� se 
p�echodov�m d�jem vyb�j� parazitn� difuzn� kapacita PN p�echodu.

![Pr�b�h nap�t� na PNP sp�na�i](week_3/pnp_obdelnik.png)

#### �kol 3.4
> Rozsv�tit LED pomoc� N-MOSFET tranzistoru (zm��it UGS, UDS, RDSON)

![Pr�b�h nap�t� ](week_3/nmos-zapojeni.png)

Zapojen� zap�j�en� ze zad�n�, nMOS je unipol�rn� alternativa NPN bipol�ru.

Nastavov�n�m nap�t� na gate pomoc� trimmeru �lo nam��it n�sleduj�c� data:
Threshold voltage U<sub>TO</sub> je cca 1.9 V, kdy� je U<sub>gs</sub> ni���, nen� MOSFET otev�en v�bec a m��iteln� proud drainem nete�e.
Od p�ibli�n� 2.5V d�l je proud MOSFETem omezen vn�j��m obvodem a p�i dal��m navy�ov�n� U<sub>gs</sub> ji� proud neroste.
P�i maxim�ln�m nap�t� U<sub>gs</sub> = 3V3 m� tranzistor odpor R<sub>ds_on</sub> = 1.5 ohmu. </br>
Pro ilustraci p�ikl�d�m dva screenshoty z pr�b�h� nap�t� v obvodu.
Kan�l 1 je nap�t� U<sub>gs</sub>, kan�l 2 je U<sub>ds</sub>,
kan�l 3 je U<sub>ds</sub> + U<sub>LED</sub>. Proto plat�, �e �bytek nap�t� na rezistoru je `3V3 - kan�l 3`.

Pr�b�h s U<sub>gs</sub> t�sn� za U<sub>TO</sub>. Je vid�t, �e �bytek na R (=dopln�k kan�lu 3 do pln�ho nap�t�) je minim�ln�,
obvodem tedy je�t� skoro nic nete�e. Nap�t� 3v3 se d�l� mezi PN p�echod LED a nap�t� ve sm�ru D->S MOSFETu.

![Pr�b�h nap�t� ](week_3/nmos-prubeh2.png)

Pr�b�h s U<sub>gs</sub> = cca 2.32V (kdesi v intervalu [U<sub>TO</sub>, 3V3]). �bytek D->S kles� (kles� tedy odpor MOSFETu
a roste proud). Pokles nap�t� na kan�lu 3 odr�� n�r�st poklesu nap�t� na rezistoru.

![Pr�b�h nap�t� ](week_3/nmos-prubeh.png)

Ani p�i dal��m navy�ov�n� nap�t� na gate se odpor MOSFETu v�razn� nem�n�. Experiment (pod dozorem
ost��len�ho HW n�vrh��e): P�iv�st 5V na gate, 3v3 na drain, gnd na source. V�e jen pulsn�, aby nedo�lo k po�kozen�
line�rn�ho regul�toru. M��en� z multimetru: `Id = 320 mA`, `Uds = 750 mV`, na line�rn�m regul�toru pokles o 2V,
na spoj�ch nep�jiv�ho pole �bytek 600 mV. Rad�ji zastaveno, aby nepovolila pojistka v USB. Z�v�r: Chce to tvrd�� zdroj.

**POZOR** na zaji�t�n� definovan� �rovn� gate MOSFETu! B�hem resetu �i p�i utr�en� vodi�e bude vstup na gate
v Hi-Z, a tranzistor bude d�lat nep�edv�dateln� kraviny - bude otev�en, uzav�en, nebo n�co mezi.
U BJT toto nen� takov� probl�m, proto�e tam mus� p�es b�zi t�ci proud a ten otev�en�m obvodem nepote�e.


## T�den 2 - RC �l�nky, charakteristika LED
Instrukce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/283737/mod_resource/content/3/LPE_2_tyden_poznamky2.pdf

  - *Doln� propust* (integra�n� �l�nek) je realizovateln� pomoc� RC i RL. RC je typi�t�j��, proto�e C je typicky "ide�ln�j��" ne� L.
Feromagnetick� j�dro induktoru m��e saturovat a nejsp� bude m�t hysterezi. RC taky nen� ide�ln�:
pro velmi vysokou frekvenci za�ne m�t vliv parazitn�
induk�nost p��vod� a samotn� ESL kondenz�toru, tak�e impedance nebude klesat do nekone�na.
  - *Horn� propust* (deriva�n� �l�nek) potla�uje DC a posiluje zm�ny. Pou�it� pro detekci hran (strmou hranu
   derivace extr�mn� zes�l�) a nebo odd�len� ��st� obvodu na r�zn�ch stejnosm�rn�ch potenci�lech (komunikace
BMS na jednotliv�ch segmentech akumul�toru).
  - *Transient voltage suppressor* (*TVS*) - br�n� chvilkov�m nap�ov�m �pi�k�m, t�eba zenerky.
  - Rezistory maj� teplotn� z�vislost, re�ln� nap� 50 ppm/K
  - Diody lze pou��t k jednoduch� stabilizaci nap�t�, proto�e maj� malou z�vislost nap�t� na tekouc� proudu.
  Vnit�n� odpor v takov�m p��pad� bude diferenci�ln� odpor diody samotn�. Zapojen� d�li�e s diodou "dole" bude m�t skoro
  o ��d men�� ztr�tov� v�kon ne� pou�it� norm�ln�ho odporov�ho d�li�e. Soub�n� bude mal� pokles nap�t� pod z�t��.
  V sofistikovan�j��m p��pad� se pou�ije zenerka pro stabilizaci nap�t� na dan� �rovni. P�i zat�en� zdroje poklesne
  z�v�rn� nap�t� na diod� a tud� se je�t� v�c zmen�� ztr�tov� proud zp�soben� Zenerov�m pr�razem.
Ztr�tov� v�kon kles� s rostouc� z�t�� na zdroji.

**Mo�nosti realizace jednoduch�ho zdroje** (obr�zek vykraden� z p�ilo�en�ho zad�n�): </br>

![Mo�nosti pro realizaci jednoduch�ho zdroje](week_2/jednoduchy-zdroj.png)

(a) = odporov� d�li� (b) = d�li� s LED dole (c) = d�li� se zenerkou dole


#### �kol 2.1
>  RC �l�nek, zapojen�, pozorov�n� chov�n� pro r�zn� frekvence vstupn�ho sign�lu

Zapojen� osciloskopu: Kan�l CH1 m��� vstupn� generovan� sign�l. Kan�l CH2 m��� v�stupn� sign�l. </br>
Vstupn� sign�l je generov�n jako sinus s amplitudou 1500 mV a offsetem 1500mV pomoc� LEO.
D�ky tomuto nastaven� lze rozumn� od oka ode��tat p�enosy pro jednotliv� frekvence.

Zapojen� je inspirovan� zad�n�m, d�le�it� je �prava deriva�n�ho �l�nku, nebo� ten by obecn� na v�stupu generoval z�porn� nap�t�,
kter� by nebylo zdrav� pro clampovac� diody na pinu MCU. Rezistory R3 a R4 nastavuj� stejnosm�rn� pracovn� bod,
v�stup tak osciluje kolem st�edu nap�ov�ho rozsahu <0, 3V3>.
 ![Integra�n� �l�nek, zlomov� frekvence](week_2/RC-clanky.png)

##### Integra�n� �l�nek

Postaven s R = 10k, C = 100n, proto je �asov� konstanta tau = 1ms a zlomov� frekvence f<sub>k</sub> = 160 Hz.
Ode��t�n� �asov� konstanty nen� v tomto p��pad� p��li� zaj�mav� pro svou p��mo�arost.
Experiment�ln� je provedeno a� u druh� konfigurace - deriva�n�ho �l�nku.

Frekvnen�� z�vislost odezvy na harmonick� sign�l:

  - Frekvence **zlomov�** (160Hz)</br>
    O�ek�v�m pokles o 3dB, tak�e asi 70% amplitudy. Zm��en� pokles je cca 500 mV, co� jsou ��dov� dv� t�etiny amplitudy.
    To je o trochu v�t�� zatlumen� jak 3dB, ale je st�le ��dov� sed� s toleranc� rezistoru a kondenz�toru.
  ![Integra�n� �l�nek, zlomov� frekvence](week_2/integracni-zlom.png)
  - Frekvence **o dek�du ni���** (16Hz)</br>
    O�ek�v�m pokles o 0dB, proto�e kondenz�tor by m�l b�t rozpojen�m pro DC. Zm��en� �bytek je asi 30mV
 a to je v porovn�n� s 1500mV amplitudy skoro nic.
  ![Integra�n� �l�nek, zlomov� frekvence](week_2/integracni-mensi.png)
  - Frekvence **o dek�du vy���** (1600Hz) </br>
    O�ek�v�m pokles o 20dB, proto�e jsme dek�du za zlomovkou. �tlum o 20dB znamen� p�enos jen jedn� desetiny amplitudy,
    co� perfektn� sed� se zm��enou amplitudou 150mV.
  ![Integra�n� �l�nek, zlomov� frekvence](week_2/integracni-vyssi.png)

##### Deriva�n� �l�nek
Postaven s rezistory R<sub>2,3,4</sub> = 10k, C = 100n, jedn� se o tro�ku sofistikovan�j�� zapojen�, kde rezistory R<sub>3</sub>, R<sub>4</sub>
zaji��uj� stejnosm�rn� pracovn� bod uprost�ed rozsahu nap�jen�. </br>

**Anal�za:** Uv��me superpozici, stejnosm�rn� zdroj korektn� nahrad�me zdrojem 0V (zkrat). T�m se R<sub>3</sub>, RR<sub>4</sub> staly paraleln�mi.
Pro snaz�� odvozen� ozna�me R = R<sub>3</sub>||R<sub>4</sub> = 5k a pomoc� n�j vyj�d��me v�echny odpory v p�enosu.
Vznikl impedan�n� d�li�. M��� se na R = R<sub>3</sub>||R<sub>4</sub>, "naho�e" jsou v s�rii kondenz�tor a odpor R<sub>2</sub> = 2R.

![Odvozen� tau](week_2/rovnice.gif)

![Odvozen� tau](week_2/frekvence.gif)

Po numerick�m dosazen� vyjde, �e p�enos deriva�n� slo�ky dos�hne jedni�ky pro f<sub>0</sub> = 318 Hz,
ale d�ky integra�n� slo�ce se na zlomov� frekvenci f<sub>1</sub> = 106 Hz p�enos zalom� a jde d�l vodorovn�.
Pro nekone�nou frekvenci je p�enos jedna t�etina, statick� zes�len� 0 (DC kompletn� utlumeno). </br>
**Z�v�r**: �asov� konstanta bude ta men�� z obou �asov�ch konstant syst�mu. O�ek�v�m tau = 1/(2\*pi\*f<sub>1</sub>) = 1.5 ms.

**Experiment�ln� ode�ten�**: P�ive�me na vstup obd�ln�kov� sign�l. Ten bude pro n� syst�m p�edstavovat jednotkov� skoky.
P�edpokl�dejme, �e zvolen� frekvence - v m�m p��pad� 10 Hz - je dostate�n� n�zk�, aby se �l�nek zvl�dal ust�lit.
Amplituda skokov� odezvy je t�sn� p�es jeden volt, jak je vid�t na obr�zku:
  ![Deriva�n� �l�nek, amplituda odezvy na skok](week_2/derivacni-amplituda.png)
Po uplynut� jedn� �asv� konstanty by m�la b�t odezva na 36% amplitudy. Pomoc� kurzor� m��eme z osciloskopu ode��st, �e �asov� konstanta
je p�ibli�n� 1.5 ms, viz n�sleduj�c� obr�zek.
  ![Deriva�n� �l�nek, tau](week_2/derivacni-tau.png)
Tento v�sledek potvrzuje p�edchoz� v�po�et.
Byl ale experiment korektn�? Pro ode�ten� amplitudy odezvy je nezbytn� m�t na po��tku syst�m ust�len�. J� p�edpokl�dal, �e
frekvence 10 Hz je dostate�n� pro ust�len� odezvy. Ka�dou p�lperiodu vstupn�ho sign�lu zapo�ne nov� p�echodov� d�j dlouh� 50 ms.
Jestli jsme zm��ili �asovou konstantu 1.5ms, pot� m� syst�m mezi dv�ma po sob� n�sleduj�c�mi jednotkov�mi skoky v�c ne� 33 �asov�ch konstant.
Ji� 4.6 tau znamen� chybu men�� ne� jedno procento, p�i 33 tau je relativn� chyba cca 4e-15. Experiment je tedy proveden korektn�, chyby zp�soben�
zanedb�v�n�m a odhady jsou nesrovnateln� v�t�� ne� chyby metodick�.

**Ov��en�:**
Pro kontrolu v��e vypo�ten�ch frekven�n�ch vlastnost� zkus�m odezvu deriva�n�ho �l�nku na harmonick� vstup.
Dr�me v pam�ti, �e amplitudov� frekven�n� charakteristika m� maximum pro nekone�nou frekvenci na zes�len� 1/3, viz odvozen� p�enosu v��e.
Na vstupu �l�nku je sinusov� sign�l s amplitudou 1500 mV, offsetem 1650 mV (st�ed rozsahu nap�jen�) a prom�nlivou frekvenc�.
  - Frekvence skoro **nekone�n�** (50 kHz) </br>
    O�ek�v�m zeslaben� sign�lu na jednu t�etinu a m�n�. Zm��en� amplituda 449 mV ��dov� sed�; H(s) = 1/3 toti� plat� a� pro nekone�nou frekvenci a
dal�� nezanedbatenou chybu vn�� nep�esn� ode��t�n� hodnot. Na obr�zku je 100 vzork� z osciloskopu pracuj�c�ho na frekvenci 1MSps,
ka�d� d�lek na ose �asov� tak odpovod� jedn� mikrosekund�.
  ![Deriva�n� �l�nek, nekone�n� frekvence](week_2/derivacni-vyssi.png)
  - Frekvence **zlomov�** (108Hz)</br>
    Amplituda je t�ikr�t zeslabena (|H(s)| pro s -> nekone�no) na cca 500mV, nad to ale bude amplituda zeslabena je�t� o dal�� 3dB na 0.7*500 = 350 mV.
Zm��en� nap�t� sed� velmi p�esn�.
  ![Deriva�n� �l�nek, zlomov� frekvence](week_2/derivacni-zlom.png)
  - Frekvence **o dek�du ni���** (10Hz)</br>
  Sign�l je tak zatlumen, �e bylo pot�eba jej digit�ln� zes�lit na p�tin�sobek, �asov� pr�b�hy osciloskopu tedy nejsou to scale.
Podle anal�zy bychom m�li m��it 500mV zeslaben�ch o 20dB (jsme dek�du od zlomovky), zm��en�ch 50 mV jsem tedy o�ek�val.
  ![Deriva�n� �l�nek, ni��� frekvence](week_2/derivacni-nizsi.png)


#### �kol 2.2
> Zm��en� diferenci�ln�ho odporu LED

Na n�sleduj�c�m obr�zku (zap�j�en�m ze zad�n� p�ilo�en�ho v��e) je vid�t sch�ma zapojen� a o�ek�van� pr�b�h
voltamp�rov� charakteristiky na LED. Podle Shockleyovy rovnice ide�ln� diody m� z�vislost proudu na nap�t�
v propustn�m sm�ru exponenci�ln� charakter. Exponenici�lu zkus�me lok�ln� linearizovat pomoc� diferenci�ln�ch odpor�
R<sub>diff1</sub> na okol� proudu 3 mA a R<sub>diff2</sub> na okol� proudu 20 mA.
  ![Diferenci�ln� odpor, zad�n�](week_2/dif-odpor-zadani.png)

**Anal�za:**
Pro exponenci�ln� z�vislost proudu na nap�t� plat� d/du exp(c\*u) = c*exp(c\*u) a analogicky pro derivace vy���ch ��d�.
Proto�e konstantn� koeficient exponenci�ly v rovnici diody je jist� kladn�, budou v�dy voltamp�rov� charakteristika i v�echny jej� derivace
ryze rostouc� funkc�. Podle infinitezim�ln� definice vodivosti a odporu:

  ![Deriva�n� �l�nek, nekone�n� frekvence](week_2/dif-odpor.gif)

a v��e zm�n�n� podm�nky `c > 0` plyne, �e diferenci�ln� odpor bude klesat, nebo� je p�evr�cenou hodnotou diferenci�ln�
vodivosti g<sub>diff</sub> a ta jist� roste.

**Ov��en�:**
Dop�edn� m��en� na LED je m��eno p��mo kan�lem `VLED`. Kan�l `VR` m��� nap�t� na seriov� kombinaci LED a 47ohm odporu.
Ode�ten�m `VR - VLED` z�sk�me diferenci�ln� m��en� nap�t� na odporu, kter� je p��mo �m�rn� tekouc�mu proudu.
sloupec I se dopo�te vztahem `I = (VR-VLED)/47`. M��en� prob�hlo dvakr�t s dv�ma r�zn�mi rezistory velikosti 47 ohm.


Prvn� sada m��en�:

| VR [mV] | VLED [mV] | I [mA] | R<sub>diff</sub> [ohm] |
|--- | ---| --- | --- | 
| 1810 | 1675 | 2.87 | 17.74 |
| 1850| 1686| 3.49 |    |
| 2862 | 1897 | 20.5 | 6.09  |
| 2983 | 1911| 22.8 |   |

Druh� sada m��en�:

| VR [mV] | VLED [mV] | I [mA] | R<sub>diff</sub> [ohm] |
|--- | ---| --- | --- |
| 1833 | 1667 | 3.53 |   16.18   |
| 1790 | 1656 | 2.85 |      |
| 2806 | 1831 | 20.75 |  8.35   |
| 3045 | 1867 | 25.06 |     |

**Z�v�r**: Diferenci�ln� odpor LED jsou jednotky, nejv��e des�tky ohm�. M��en� je z�ejm� siln� zat�eno nep�esnost�
rezistor� - sna��me-li se m��it n�zk� diferenci�ln� odpor LED, hraje ohm sem �i tam u ochrann�ho rezistoru velkou roli.
Ka�dop�dn� se potvrdila hypot�za, �e diferenci�ln� odpor mus� s rostouc�m proudem klesat.
Fyzik�ln� je to mo�n� vysv�tlit v�t�� saturac� PN p�echodu uvnit� diody. T�m kles� odpor v *depletion layer* a
voltamp�rov� charakteristika srtm� stoup�. Strm� t�m stoup� i ztr�tov� v�kon, ten byl v p��pad� maxim�ln�ho m��en�ho proudu
roven `25mA * 1.87V = 46.7 mW`.

**TODO**: Zeptat se na pom�r v�konu vysv�cen�ho a vytopen�ho LEDkou.

## T�den 1 - Zapojen� a z�kladn� test obvodu
Instrukce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/283733/mod_resource/content/3/LPE_1_tyden_poznamky_2021_v2.pdf,
hlavn� �kol bylo osazen� breadboardu sou��stkami, o�iven� line�rn�ho regul�toru a MCU. Z�kladn� sch�ma zapojen� MCU a nap�jen� (inpirov�no)
doporu�en�m sch�matem v p�ilo�en�m PDF.</br>
![Sch�ma zapojen� MCU](week_1/napajeni.png)
N�sleduje vlastn� sch�ma zapojen� pro zadan� samostatn� �lohy. Pro zjednodu�en� vynech�v�m kompletn� zapojen� nap�jen� a soust�ed�m se jenom na sign�ly
a p��padn� popis, jak� periferie dan� sign�l zpracov�v�. Piny jsem volil s ohledem na kompatibilitu jednotliv�ch �loh, lze tedy zapojit v�echny t�i �lohy najednou.
![Sch�ma zapojen� �loh 1.2 a� 1.4](week_1/schema.png)

V�sledn� zapojen� (vid�t jsou jen �lohy 3 a 4): �pln� vpravo je LED ��zen� z PWM, uprost�ed jsou vid�t 3 rezistory
v d�li�i pro �lohu 1.3

![Re�ln� zapojen� �loh 1.3 a 1.4](week_1/zapojeni.jpg)
#### �kol 1.1
> Sestaven� zapojen� s STM32F042 na nep�jiv�m poli

Bez pozn�mek
#### �kol 1.2
>Rozblikejte LED pomoc� gener�toru, dv� �rovn� svitu (pr�b�hy nap�t� na LED zobrazit na osciloskopu a poznamenat do se�itu...)

P�ejeme si m��it nap�t� na LED, proto je nejsnaz�� jej� katodu uzemnit, abychom mohli pou��t single-ended me�en� m�sto diferenci�ln�ho.
P�es ochran� R se na anodu p�ivede PWM prom�nliv� st��dy. LED sv�t� podle stejnosm�rn� st�edn� hodnoty (tedy `3V3 * duty_cycle` generovan� PWM)
rozd�len� mezi LED a rezistor. P�i dostate�n� frekvenci PWM (u mne asi od 60 Hz) u� nejsou v�bec vid�t probliky. </br>
Zkou�el jsem hledat projevy parazitn� difuzn� kapacity PN p�echodu uvnit� LED, ale ani s vy��� vzorkovac� frekvenc� nebyly hrany PWM v�razn�
deformovan�; z�staly strm� a nebyla pozorovateln� exponenci�la. </br> Z�znam m��en� nap�t� na diod� (je vykresleno deset period sign�lu):
**TODO** ov��it, �e to byla skute�n� difuzn� kapacita. Pokusit se ji zm��it.
![Z�znam osciloskopu](week_1/1.2.png)
V�sledek odpov�d� d��ve zm��en� hodnot� dop�edn�ho nap�t� pomoc� *diode testeru* na multimetru, kter� byla 1620 mV.

#### �kol 1.3
> Napi�te vlastn� program v mbedu, rozblikat jednu extra p�ipojenou LED tak, aby m�la v�ce �rovn� sv�tivosti, nap��klad
0-1-2-3-2-1-0... (0=nesv�t�, 3=sv�t� nejv�ce) pomoc� dvou rezistor� na dvou r�zn�ch pinech MCU

Zapojen�: anoda LED na 3V3 a "pod ni" do serie t�i rezistory 470R. Posledn� rezistor je zapojen na zem. MCU m��e piny PA3, PA4 (p�ipojen�mi mezi ka�d� dva sousedn� 
rezistory) ur�ovat, jak� uzel se dostane na zemn� potenci�l nebo na nap�jen�. Kdy� oba piny plavou, pozoruje LED v s�rii `3 * 470R`. Pakli�e je PA4 p�izemn�n,
pozoruje LED jen `2 * 470R` a pakli�e je p�izemn�n PA3, pozoruje LED v s�rii jen jeden rezistor. Pakli�e n�jak� z pin� d�v� vysokou �rove�, je p�ed LED nulov� nap�t�. </br>
Proto�e nap�t� LED v propustn�m sm�ru je na zna�n�m rozsahu proud� skoro konstantn� (tato konkr�tn� LED m� cca 1600 mV), d�v� n�m zapojen� mo�nost
��dit proud LED ve �ty�ech kroc�ch. Podle `I = (3V3 - Uled)/R = cca (1V7 / R)` mohou t�ci proudy 0mA, 3.6mA, 1.8mA a nebo 1.2mA.

Software je trivi�ln�: V RCC zapnout hodiny pro GPIOA, d�le p�ep�nat dva zvolen� piny mezi m�dem `input floating` (stav po resetu)
a `push-pull general purpose output` v registrech GPIOx_MODER, GPIOx_PUPDR. V mezidob� j�dro �ek� v busy wait cyklu po ur�it� po�et milisekund
(odm��ov�no `SysTick`em).

**TODO** Setkal jsem se s podivn�m chov�n�m GPIO. Po p�epnut� pinu z GP PP vysok� �rovn� do input floating (MODER = 0, PUPDR = 0) byla na v�stupu st�le jedni�ka,
a�koli by m�l plavat. Fixnulo se to clearnut�m p��slu�n�ho bitu v ODR, pot� za�al pin plavat. Jednalo se o PA3 (pin 9), zeptat se na cviku.

#### �kol 1.4
> Napi�te vlastn� program v mbedu, kter� bude plynule rozsv�cet a zhas�nat LED (bu� pomoc� wait a cykl� nebo pwm a zm�ny st��dy)

P��hodn� se uk�zal timer 14 generuj�c� PWM s prom�nlivou st��dou na pinu PA7. Mikrokontroler b�� z 8MHz HSI n�soben�ho �estkr�t intern� PLL.
Prozat�m nechme i PCLK na 48MHz. Timer 14 je �irok� 16 bit�. P�i pou�it� prescaleru 48 - 1 bude na vstupu timeru frekvence 1 MHz.
Nastaven�m TIMx_ARR = 1000 dostaneme PWM na frekvenci 1kHz se st��dou nastavovatelnou po promile z�pisem do TIMx_CCR1.
Pro plynulej�� p�echody se z�pisy do TIMx_CCR1 prov�d� v SysTick interruptu b��c�ho na 1 kHz, zapise je v re�imu napodobuj�c�cm
center-aligned m�d timeru. Jas LED tedy plynule nab�h� od nuly do 100% a n�sledn� kles� v nule.

**TODO** Zeptat se, pro� mohly plovouc� piny 17,18 (D+, D-) zp�sobit nestabiln� koumikaci STlinku s mikrokontrolerem. Sta�ilo se prstem dotknout
odhalen�ch pin� MCU a ji� to vedlo na stabiln� komunikaci.
