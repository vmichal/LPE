# Pozn�mky z p�edm�tu LPE
Usmoleno **Vojt�chem Michalem** (vojta.michall@email.cz) v pr�b�hu letn�ho semestru 2021 (B202). </br>
Ofici�ln� materi�ly jsou na Moodle na str�nce https://moodle.fel.cvut.cz/course/view.php?id=5814
a na Embedded serveru https://embedded.fel.cvut.cz/kurzy/lpe/LPE2021.

T�dny jsou ��slov�ny chronologicky, pozn�mky k nim jsou uvedeny v obr�cen�m po�ad�.
Jako prvn� je tedy uveden posledn� t�den, scrollov�n�m na konec str�nky se �lov�k dostane na t�den prvn�.

## T�den 3 - Element�rn� tranzistorov� zapojen�
Insturkce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/283739/mod_resource/content/4/LPE_3_tyden_poznamky_2021_v4.pdf

#### �kol 3.1
> Zm��it proudov� zesilovac� �initel NPN tranzistoru h<sub>21E</sub>

Z�kladn� zapojen� se spole�n�m emitorem.
Na b�zi je zapojen 1 mega ohm proti 3V3, �bytek na n�m zm��en jako 2.660 V (na PN p�echod BE zb�v� 636 mV).
V kolektoru je �erven� LED a rezistor 470R s serii proti 3V3, na R �bytek 528 mV.

Z toho plyne proud b�z� `I<sub>b</sub> = 2'660/1'000'000 = 2.6 uA` a proud kolektorem `I<sub>c</sub> = 528/470 = 1.12 mA`
a zesilovac� �initel `h<sub>21E</sub> = I<sub>b</sub> / I<sub>c</sub> = 432`, co� je o�ek�vateln� hodnota u sign�lov�ho BJT.
Podle datasheetu jsou zes�len� BJT s p��ponou "C" v rozsahu 400-800, tak�e dan� tranzistor je v garantovan�m rozsahu.

S t�mto zes�len�m lze nahradit 1M v b�zi i odporem k��e - ten je ale v ��du des�tek kOhm a v�ce pouze pro n�zk� nap�t�.
Se s�ov�m nap�t�m (230 V RMS) se k��e proraz� a odpor **v�razn� poklesne**.

#### �kol 3.2
> Rozsv�tit LED pomoc� NPN tranzistoru (zm��it UBE, UCE, orienta�n� v�po�et Rb, Rc)

NPN bude pou�it jako sp�na�  pro seriov� zapojen� �erven� LED a rezistoru proti 5V,
tak�e v saturaci budu p�edpokl�dat nulov� �bytek nap�t� mezi kolektorem a emitorem.
P�i pou�it� rezistoru 470 ohm v s�rii s LED s dop�edn�m nap�t�m cca 1.8V by m�l v pln� sepnut�m stavu LEDkou t�ci proud 
`Ic = (5-1.8)/470 = 6.8mV`. P�i proudov�m zesilovac�m �initeli h<sub>21e</sub> = 432 je pot�eba dodat do b�ze
proud alespo� `Ib = Ic/h21e = 15 uA`. Budu-li p�edpokl�dat, �e nap�ov� �bytek p�echodu
BE se nebude p��li� m�nit od �lohy 3.1, a z�stane tedy cca 650mV, pot� do b�ze pot�ebuji rezistor nejv��e
`Rb_max = (3V3 - 0.65)/15uA = 176 kOhm`. Pou�it� nap��klad 22kOhm n�m d� "�estin�sobnou jistotu",
�e sp�n�n� bude fungovat bez ohledu na neideality sou��stek a p��padn� �umy.

Zm��en� satura�n� nap�t� U<sub>ce</sub> tranzistoru v dan�m zapojen� je 57mV, co� ve srovn�n� s �bytkem 5V na cel� v�tvi v�etn�
LED a rezistoru je skute�n� zanedbateln�. Zm��en� �bytek na p�echodu b�ze-emitor je 680 mV, tak�e odpov�d� o�ek�van�mu �bytku.

Proto�e NPN tranzistor v sepnut�m stavu p�izem�uje sv�j kolektor, lze z n�j sestrojit nejhloup�j�� invertor. Vysok� �rove� 
na b�zi zp�sob� n�zkou �rove� na kolektoru a naopak. Viz n�sleduj�c� obr�zek. Kan�l 1 je U<sub>be</sub>, kan�l 2 je U<sub>ce</sub>.
Zaj�mav� je prohnut� U<sub>ce</sub> v oblasti, kde m� sign�l na b�zi maximum. Saturace BJT neprob�hne najednou,
nen� satura�n� nap�t� nen� konstantn� - z�le�� na m��e saturace.

![Negace sign�lu pomoc� NPN tranzistoru](week_3/invertor.png)
#### �kol 3.3
> Rozsv�tit LED pomoc� PNP tranzistoru (zm��it UBE, UCE)

Princip zapojen� �pln� identick� jako u NPN, jen "zrcadlov� obr�ceno". PNP je p�ipojen emitorem na nap�jen�,
na b�zi je p�es 10k p�ipojen gener�tor, dal��ch 10k je zapojeno mezi b�zi a emitor jako pullup pro rychlej�� zav�r�n�.
V kolektoru je v s�rii �erven� LED a 470R do zem�.

Zaj�mav� jsou dva �asov� pr�b�hy se zapojen� s PNP tranzistorem se sinusem a obd�ln�kem na vstupu.

Sinusov� vstup: kan�l 1 je b�ze, kan�l 2 je kolektor, kan�l 3 je nap�t� na rezistoru v kolektoru. Je vid�t, �e
obvod op�t m� invertuj�c� charakter, zaj�mav� je n�b�h nap�t� na rezistoru (n�b�n� hrana kan�lu 3), kde 
se projevuje exponenci�ln� z�vislost proudu b�z� na nap�t�, je� se line�rn� z�vislost� p�ev�d� na exp z�vislost proudu kolektorem
na nap�t� U<sub>eb</sub>

![Pr�b�h nap�t� na PNP sp�na�i](week_3/pnp_prubeh.png)
![Pr�b�h nap�t� na PNP sp�na�i](week_3/pnp_obdelnik.png)

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
dal�� nezanedbatenou chybu vn�� nep�esn� ode��t�n� hodnot. Na obr�zku je 100 vzork� z osciloskopu pracuj�c�ho na frekvenci 1MSps
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
