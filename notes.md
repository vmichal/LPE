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


