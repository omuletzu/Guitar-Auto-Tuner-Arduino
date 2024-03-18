**UTCN Facultatea de Automatică și Calculatoare**

Documentație la disciplina

Măsurători electrice

`   `și senzori

Titlul proiectului:

`   `**Acordor automat de chitară**

` `Student: Simota Mihnea-Dragoș

` `Grupa: 30229

` `An academic: 2023-2024



**Cuprins 									Pagina**					
#
**Obiectivul proiectului3**

**Ipoteza proiectului3**

**Componentele proiectului3**

` 	`**Arduino UNO4**

**Servomotor MG9955**

` 	`**Senzor piezoelectric ceramic5**

**Senzor de sunet LM3936**

` 	`**Breadboard6**

**Cum funcționează proiectul?7**

**Mod de utilizare9**

**Partea software9**

**Avantaje și dezavantaje11**

**Posibile dezvoltări ulterioare11**

**Concluzie12**






**Obiectivul proiectului**
**
`            `Principalul obiectiv al acestui proiect este să ofere ajutor și să simplifice procesul de acordare, în special începătorilor, care nu se descurcă bine la acordarea unei chitare.



**Ipoteza proiectului**

Pornind de la premisa că mulți începători în domeniul chitarei întâmpină dificultăți în procesul de acordare a instrumentului și au nevoie de asistență, am dezvoltat un acordor automat de chitară bazat pe Arduino. Astfel, prin folosirea acestui proiect, instrumentul va suna așa cum trebuie, corzile vor fi tensionate  egal, evitând deformarea gâtului chitarei în timp și uzură inegală a corzilor.

**Componentele proiectului**
**
`      `Pentru acest proiect, am ales să folosesc o plăcută Arduino UNO Rev3 SMD (ce se ocupă de procesarea tuturor comenzilor), un senzor piezoelectric ceramic (pentru vibrații), un senzor de sunet LM393 (pentru voce), un servomotor MG995 (pentru rotirea cheitelor), fire pentru a conecta componentele între ele și led-uri pentru a informa utilizatorul despre starea acordorului.





**Arduino UNO**
**
`      `Arduino este o plăcută de dezvoltare ce conține un microcontroller, porturi de intrare/ieșire, alimentare și alte componente esențiale. Se poate conecta la un computer prin intermediul unui USB-B, iar codul scris în Arduino IDE, poate fi încărcat pe placă fizică.

`                        `(Diagramă de Pinout)



`                                                                                                            `(Specificații Arduino UNO)





**Servomotor MG995**

Servomotorul MG995 a fost utilizat în cadrul proiectului datorită câtorva caracteristici specifice. Printre acestea se numără cuplul puternic (10 kg \* cm) la tensiunea de 6V, necesar rotirii cheitelor chitarei și feedback-ul precis, motorul având capacitatea de a controla și poziționa exact axul motorului, important pentru o acordare corectă. Totodată pot fi amintite durabilitatea mare și compatibilitatea cu Arduino ce fac acest motor componentă potrivită pentru rolul ei.





**Senzor piezoelectric ceramic**
**
`      `Acest senzor este foarte important pentru că este responsabil de detectarea vibrațiilor generate de corzi. El este montat pe suprafață instrumentului, iar materialul din care este făcut generează o mică tensiune electrică proporțională cu intensitatea    vibrației. Semnalul generat de acesta este mai departe prelucrat de software.











Tensiunea de operare este de 5V, iar dimensiunile lui sunt destul de reduse.



**Senzor de sunet LM393**
**
`      `Microfonul este folosit pentru a asculta vocea utilizatorului, semnalul fiind transmis mai departe la software, iar în funcție de ce litera spune, acordorul pornește sau se oprește (la litera “s” pornește și la “o” se oprește). Tensiunea lui de operare este de 5V, iar senzitivitatea este destul de mică, ceea ce-l determină pe utilizator să spună literele mai tare, pentru o recunoaștere a acestora cât mai bună.











**Breadboard**
**
`      `Am ales să folosesc un breadboard pentru că ne permite conectarea rapidă și temporară a componentelor fără a fi necesită sudură. Totodată este o unealtă bună pentru procesul de depanare în caz de erori.














**


**Cum funcționează proiectului?**

`            `Pentru început utilizatorul trebuie să pornească acordorul spunând în microfon litera ‘s’ și îl poate închide zicând litera ‘o’. După ce acesta este pornit, trebuie selectat dacă se dorește acordare standard (E A D G B E) sau celălalt tip disponibil (D A D F# B D ), apoi va trebui să selecteze coarda pe care dorește să o acordeze și să o ciupească. Cu ajutorul senzorului piezoelectric ceramic, știm care este amplitudinea vibrației, iar cu ajutorul acestei informații se poate află frecvența acelei corzi, folosind algoritmul Fast Fourier Transform. La final în funcție de frecvența pe care o are acea coarda, servomotorul va roți de cheița chitarei, fiind nevoie că acest proces să se repete de mai multe ori pentru o acordare bună. Astfel la final, întregul instrument va fi acordat.

`            `Frecventele standard pentru fiecare coarda sunt:      

\-        E 82 Hz (coarda cea mai groasă)

\-        A 110 Hz

\-        D 146 Hz

\-        G 196 Hz

\-        B 247 Hz

\-        E 330 Hz (coarda cea mai subțire)





Frecventele standard pentru fiecare coarda sunt:      

\-        D 73 Hz (coarda cea mai groasă)

\-        A 110 Hz

\-        D 146 Hz

\-        F# 185 Hz

\-        G 246 Hz

\-        D 293 Hz (coarda cea mai subțire)

`             `Utilizatorul va fi informat când coarda este aproape acordată, atunci când eroarea de frecvența este maxim de 3 Hz (și după asta acordorul tot va încerca să ajungă la o frecvența mai bună).









**Mod de utilizare**
**
`	`Se spune in microfon litera ‘s’ (trebuie sa se aprinde un led verde), după care se apasă pe buton pentru a selecta coarda ce se dorește acordată (sunt 6 led-uri roșii corespunzătoare fiecarei corzi). Se pune capătul servomotorului pe cheiță și se ciupește coarda. La fiecare ciupire motorașul va fi acționat până când se aprinde alt led verde ceea ce înseamnă coarda ar trebui să fie acordată, dar daca utilizatorul vrea, mai poate acorda și mai precis, repetând încă de câteva ori procesul. Din cauza faptului că servomotorul se poate roti doar 180 de grade, de fiecare dată când ajunge la 0 sau 180 de grade, motorul se resetează la 90 de grade, utilizatorul fiind informat de aceasta prin clipirea unui led albastru. La final, în microfon poate fi spusă litera ‘o’ pentru a opri aparatul.


**Partea de software**
**
`      `Partea de software necesară acestui limbaj a fost scrisă în editorul Arduino IDE, ce folosește un limbaj foarte asemănător cu C++.  Această este destul de consistentă, ea fiind cea care se ocupă de prelucrarea vibrațiilor, în scopul obținerii frecvenței, folosind Fast Fourier Transform (cu ajutorul librăriei “ArduinoFFT”), prelucrarea semnalului de la microfon pentru a ști ce litera a spus utilizatorul (cu ajutorul librăriei “uSpeech”), comenzile servomotorului (cu ajutorul librăriei “Servo.h”) și toată logică pentru led-uri ce au rolul de a informa utilizatorul.







`                                    `(Așa arată un semnal detectat de senzorul piezoelectric)











(Rezultatul algoritmului Fast Fourier Transform (frecvența în Hz), ce primește ca date de intrare amplitudinele vibrației (că în exemplul de sus))



` `(Exemplu de cod pentru citirea amplitudinilor vibrației și logică pentru   led-ul de vibrație)













`  `(Exemplu de cod pentru aflarea frecvenței folosind FFT)










` `(Exemplu de cod pentru acționarea servomotorului în funcție de eroarea frecvenței și resetarea acestui la poziția 90 de grade în caz-ul în care a ajuns la extremități)


**Avantaje și dezavantaje**

Printre avantajele acestui proiect se numără, automatizarea procesului de acordare ceea ce determină o acordare corectă, iar printre dezavantaje se numără, senzitivitatea slabă a microfonului ce captează literele din jur și unghiul de rotație limitat al servomotorului.

**Posibile dezvoltări ulterioare**

În locul folosirii led-urilor pentru a informa utilizatorului de starea actuală a procesului, se poate folosi un display digital, ce ar facilita mult feedback-ul. Totodată atașarea senzorului piezoelectric ceramic ar putea fi facută cu ajutorul un dispozitiv care să se atașeze ușor de corpul chitarei și folosirea unui servomotor cu grad de rotație mai mare sau nelimitat, ar fi mai bună.


**Concluzie**

Un auto tuner cu recunoaștere vocală poate simplifica procesul de acordare a chitarei, eliminând necesitatea de a ajusta manual cheile de acordaj. Acest lucru face acordarea mai rapidă și mai ușoară pentru utilizatori.









`									`(Imagine de ansamblu)

12

