# Pozn�mky z p�edm�tu LPE
Usmoleno **Vojt�chem Michalem** (vojta.michall@email.cz) v pr�b�hu letn�ho semestru 2021 (B202). </br>
Ofici�ln� materi�ly jsou na Moodle na str�nce https://moodle.fel.cvut.cz/course/view.php?id=5814
a na Embedded serveru https://embedded.fel.cvut.cz/kurzy/lpe/LPE2021.

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

## T�den 2 - RC �l�nky, charakteristika LED
Instrukce pro tento t�den jsou na https://moodle.fel.cvut.cz/pluginfile.php/283737/mod_resource/content/3/LPE_2_tyden_poznamky2.pdf

  - *Doln� propust* (integra�n� �l�nek) je realizovateln� pomoc� RC i RL, RC je typi�t�j��, proto�e C je typicky "ide�ln�j��" ne� L.
Feromagnetick� j�dro induktoru m��e saturovat a nejsp� bude m�t hysterezi. Pro velmi vysokou frekvenci za�ne m�t vliv parazitn�
induk�nost p��vod� a samotn� ESL kondenz�toru, tak�e impedance nebude klesat do nekone�na.
  - *Horn� propust* (deriva�n� �l�nek) potla�uje DC a posiluje zm�ny - eliminuje DC, detekuje hrany.
  - *Transient voltage suppressor* (*TVS*) - br�n� chvilkov�m nap�ov�m �pi�k�m, t�eba zenerky.
  - Rezistory maj� teplotn� z�vislost, re�ln� nap� 50 ppm/K
  - diody lze pou��t k jednoduch� stabilizaci nap�t�, proto�e maj� malou z�vislost nap�t� na tekouc� proudu.
  Vnit�n� odpor v takov�m p��pad� bude diferenci�ln� odpor diody samotn�. Zapojen� d�li�e s diodou "dole" bude m�t skoro
  o ��d men�� ztr�tov� v�kon ne� pou�it� norm�ln�ho odporov�ho d�li�e. Soub�n� bude mal� pokles nap�t� pod z�t��.
  V sofistikovan�j��m p��pad� se pou�ije zenerka pro stabilizaci nap�t� na dan� �rovni. P�i zat�en� zdroje poklesne
  z�v�rn� nap�t� na diod� a tud� se je�t� v�c zmen�� ztr�tov� proud zp�soben� Zenerov�m pr�razem.

![Mo�nosti pro realizaci jednoduch�ho zdroje](week_2/jednoduchy-zdroj.png)
Mo�nosti realizace jednoduch�ho zdroje. Obr�zek vykraden� z p�ilo�en�ho zad�n�.


#### �kol 2.1
>  RC �l�nek, zapojen�, pozorov�n� chov�n� pro r�zn� frekvence vstupn�ho sign�lu

Kan�l CH1 m��� vstupn� generovan� sign�l. Kan�l CH2 m��� v�stupn� sign�l. </br>
Vstupn� sign�l je generov�n jako sinus s amplitudou 1500 mV a offsetem 1500mV pomoc� LEO.
D�ky tomuto nastaven� lze rozumn� od oka ode��tat p�enosy pro jednotliv� frekvence.

Zapojen� je inspirovan� zad�n�m, d�le�it� je �prava deriva�n�ho �l�nku, nebo� ten by obecn� na v�stupu generoval z�porn� nap�t�,
kter� by nebylo zdrav� pro clampovac� diody na pinu MCU.
 ![Integra�n� �l�nek, zlomov� frekvence](week_2/RC-clanky.png)

##### Integra�n� �l�nek

TODO zkontrolovat v�po�et zlomov� frekvence
Postaven s R = 10k, C = 100n, proto je �asov� konstanta tau = 1ms a zlomov� frekvence f<sub>k</sub> = 160 Hz.
  - Frekvence **zlomov�** (160Hz)</br>
    O�ek�v�m pokles o 3dB, co� je asi 70%. Zm��en� pokles je cca 500 mV, co� jsou ��dov� dv� t�etiny amplitudy.
    To je o trochu v�t�� zatlumen� jak 3dB, ale je st�le v toleranci kv�li toleranci rezistoru a kondenz�toru.
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
Postaven s rezistory RR<sub>2,3,4</sub> = 10k, C = 100n, jedn� se o tro�ku sofistikovan�j�� zapojen�, kde rezistory R<sub>3</sub>, RR<sub>4</sub>
zaji��uj� stejnosm�rn� pracovn� bod uprost�ed rozsahu nap�jen�. </br>
Odvozen� p�enosu: Uv��me superpozici, stejnosm�rn� zdroj korektn� nahrad�me. T�m se R<sub>3</sub>, RR<sub>4</sub> staly paraleln�mi.
Pro snaz�� odvozen� ozna�me R = R<sub>3</sub>||R<sub>4</sub> = 5k a pomoc� n�j vyj�d��me v�echny odpory v p�enosu.
![Odvozen� tau](week_2/rovnice.gif)
![Odvozen� tau](week_2/frekvence.gif)
Po numerick�m dosazen� vyjde, �e p�enos deriva�n� slo�ky dos�hne jedni�ky pro f<sub>0</sub> = 318 Hz,
ale d�ky integra�n� slo�ce se na zlomov� frekvenci f<sub>1</sub> = 106 Hz p�enos zalom� a jde d�l vodorovn�.
Pro nekone�nou frekvenci je p�enos jedna t�etina, statick� zes�len� 0 (DC kompletn� utlumeno).
**Z�v�r**: �asov� konstanta bude 1/f<sub>1</sub>


  - Frekvence **zlomov�** (160Hz)</br>
    O�ek�v�m pokles o 3dB, co� je asi 70%. Zm��en� pokles je cca 500 mV, co� jsou ��dov� dv� t�etiny amplitudy.
    To je o trochu v�t�� zatlumen� jak 3dB, ale je st�le v toleranci kv�li toleranci rezistoru a kondenz�toru.
  ![Integra�n� �l�nek, zlomov� frekvence](week_2/integracni-zlom.png)
  - Frekvence **o dek�du ni���** (16Hz)</br>
    O�ek�v�m pokles o 0dB, proto�e kondenz�tor by m�l b�t rozpojen�m pro DC. Zm��en� �bytek je asi 30mV
 a to je v porovn�n� s 1500mV amplitudy skoro nic.
  ![Integra�n� �l�nek, zlomov� frekvence](week_2/integracni-mensi.png)
  - Frekvence **o dek�du vy���** (1600Hz) </br>
    O�ek�v�m pokles o 20dB, proto�e jsme dek�du za zlomovkou. �tlum o 20dB znamen� p�enos jen jedn� desetiny amplitudy,
    co� perfektn� sed� se zm��enou amplitudou 150mV.
  ![Integra�n� �l�nek, zlomov� frekvence](week_2/integracni-vyssi.png)




#### �kol 2.2
> Zm��en� diferenci�ln�ho odporu LED
