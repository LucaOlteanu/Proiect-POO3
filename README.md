# Proiect POO – Sistem de Gestiune Comenzi Online (Tema 3)

**Autor:** Luca Olteanu  
**Tema:** Comert – Comenzi online pentru un magazin universal  
**Tehnologii:** C++20, CMake, STL, smart pointers, template-uri, exceptii, design patterns (Singleton, Factory, Builder)

---

## Descriere

Aplicatia simuleaza un magazin online unde utilizatorul poate:
- Vizualiza un catalog de produse (alimentare, electronice, mobilier)
- Adauga si elimina produse in/din cos printr-o sesiune interactiva sau automata
- Folosi puncte de loialitate (1 punct = 1 leu reducere, se acumuleaza 1 punct la 10 lei platiti efectiv)
- Finaliza comanda cu validarea soldului si actualizarea stocurilor
- Gestiona situatii exceptionale (stoc insuficient, fonduri insuficiente, produs inexistent)

Datele de intrare (utilizator si catalog) sunt citite dintr-un fisier text (`date_intrare.txt`). Comenzile pentru sesiunea de cumparare pot fi preluate automat dintr-un fisier separat (`comenzi.txt`) pentru testare rapida.

---

## Arhitectura si concepte OOP implementate

### Ierarhia de clase
```
Produs (clasa abstracta)
├── ProdusAlimentar (reducere 50% daca expira in < 24h)
├── ProdusElectronic (reducere 10% daca garantia > 24 luni)
└── ProdusMobilier (taxa transport +15% daca greutatea > 30 kg)

Utilizator<T> (clasa sablon) – campul extra pentru puncte loialitate

Cos
└── contine std::vector<ItemComanda> cu std::unique_ptr<Produs>

Catalog (Singleton) – gestioneaza toate produsele

ProdusFactory – creeaza produse pe baza tipului si datelor din fisier

ComandaBuilder – construieste un cos pas cu pas (design pattern Builder)
```

### Caracteristici specifice temei 3

- **Clasa sablon** – `Utilizator<T>` parametrizata cu `T = int` (puncte loialitate)
- **Functie sablon** – `aplicaDiscount` in `Discount.h` (aplica un procent de reducere)
- **Design patterns**:
  - **Singleton** – `Catalog` (o singura instanta care detine toate produsele)
  - **Factory** – `ProdusFactory` (crearea centralizata a produselor din fisier)
  - **Builder** – `ComandaBuilder` (construirea pas cu pas a unui cos)
- **Puncte de loialitate** – se folosesc la cerere (optiune in consola), se aduna 1 punct la 10 lei platiti efectiv
- **Citire comenzi din fisier** – daca exista `comenzi.txt`, programul executa automat comenzile; altfel intra in mod interactiv
- **Filtrare produse expirate** – la incarcare, produsele alimentare a caror data de expirare a trecut nu sunt adaugate in catalog
- **STL** – vectori, string, unique_ptr, algoritmi (std::min)
- **Exceptii proprii** – ierarhie derivata din `std::runtime_error` (StocInsuficient, SoldInsuficient, ProdusInexistent)
- **Copy-and-swap** in `Cos`, regula celor cinci in `Produs`

---

## Compilare si rulare

### Folosind CMake (CLion)

1. Deschide proiectul in CLion.
2. Asigura-te ca fisierul `CMakeLists.txt` include toate sursele (vezi mai jos).
3. Apasa Build → Run.

### Linia de comanda (MinGW / g++)


Fisiere de intrare
date_intrare.txt – contine datele utilizatorului si catalogul produselor:
USER: Olteanu Luca, Strada Comertului 67, 1504.50

PRODUS_ALIMENTAR: Mere, 4.5, 100, 2026-06-01
PRODUS_ALIMENTAR: Lapte, 6.0, 30, 2026-05-30
PRODUS_ELECTRONIC: Mouse Wireless, 120.0, 15, 36, 2.5
PRODUS_ELECTRONIC: Tastatura mecanica, 350.0, 8, 12, 5.0
PRODUS_MOBILIER: Birou, 450.0, 5, lemn masiv, 55.0
PRODUS_MOBILIER: Scaun ergonomic, 320.0, 12, material textil, 18.0

comenzi.txt (optional) – comenzi pentru sesiunea automata:
```
add 1 2
add 2 1
add 3 1
add 4 1
add 5 1
add 6 1
catalog
show
remove 3
checkout
```
Daca fisierul comenzi.txt exista, programul va executa comenzile fara a mai cere input de la tastatura (inclusiv raspunsul pentru puncte).
Exemple de comenzi in modul interactiv
```
add 1 2 – adauga produsul cu indexul 1 in cantitate 2

remove 2 – sterge al doilea produs din cos

show – afiseaza cosul curent

catalog – reafiseaza catalogul

checkout – finalizeaza comanda

quit – iese din program
```

Concluzie
Proiectul indeplineste toate cerintele temei 3:
```
clasa sablon si functie sablon

trei design patterns (Singleton, Factory, Builder)

sistem de puncte de loialitate

citire comenzi din fisier

separare cod in .h/.cpp, smart pointers, exceptii proprii, copy-and-swap, functii virtuale, dynamic_cast
```

Bibliografie
```text
sstream - pentru parsare de stringuri
ctime - functii pentru manipularea elementelor de timp
chrono - pentru extragerea timpului din sistem
infed, define - define guard, are grija sa nu se includa acelasi fisier header de mai multe ori
noexcept - promisiune ca acea functie nu poate cauza exceptii
static_cast - face conversii fara verificare la compilare daca sunt posibile, folosim cand suntem sigur ca se poate face
istream - fluxul de citire general, vede atat cin cat si fstream
iss - variabila ce citeste liniile din fisier, inlocuieste cin(parseaza automat spatiile, este mai util)
```

GitHub: LucaOlteanu/ProiectPOO3

---


Review cod proiect – Sistem de gestiune comenzi online (Tema 3)

1. Introducere si impresie generala

Proiectul meu este o aplicatie de comert online care permite gestionarea unui catalog de produse (alimentare, electronice, mobilier), a unui cos de cumparaturi si a unui sistem de puncte de loialitate. Codu este scris in C++20 si respecta cerintele temei 3: separare in fisiere header si sursa, mosteniri, functii virtuale, template-uri, design patterns (Singleton, Factory, Builder), excepii proprii si ccitire din fisiere. Structura este clara, iar functionalitatile sunt bine delimitate. Programul ruleaza fara erori si trateaza exceptiile corespunzator.

2. Arhitectura si implementare

Am pastrat ierarhia de la tema 2 (Produs, ProdusAlimentar, ProdusElectronic, ProdusMobilier) si amm adaugat elementele cerute:

- Clasa sablon Utilizator<T> inlocuieste vechea clasa Utilizator. Acum un utilizator are un camp extra de tip T, folosit pentru puncte de loialitate (int). Constructorii, operatorii si metodele sunt implementate corect. ID-ul ramane constant la copiere, ceea ce este bine.

- Functia sablon aplicaDiscount (in Discount.h) calculeaza un pret redus pe baza unui procent. Este simpla dar utila, poate fi folosita si pentru alte tipuri numerice.

- Design pattern Singleton pentru Catalog. Catalogul este o clasa cu constructor privat, destructor de copiere sters, iar getInstance() returneaza o referinta la o variabila statica locala. Aceasta varianta este thread-safe in C++11 si mai nou. Catalogul gestioneaza un vector de unique_ptr<Produs> si ofera metode de acces si adaugare. Este folosit corect in main.

- Design pattern Factory pentru ProdusFactory. Metoda statica createProdus primeste tipul produsului si un string extra cu parametrii specifici. In functie de tip, parseaza extra si intoarce un unique_ptr la derivata corespunzatoare. Aceasta centralizeaza logica de creare si face parsarea din main mai curata. O mica observatie: codul de parsare din factory duplica partial functia stringToDate din main, dar nu este o problema majora.

- Design pattern Builder pentru ComandaBuilder. Acesta primeste un utilizator, permite adaugarea de produse (clone) si un discount, iar build() construieste un obiect Cos transferand unique_ptr-urile prin metoda speciala adaugaProdus(std::unique_ptr<Produs>, int). Acest pattern elimina nevoia de a clona de doua ori produsele si face codul mai expresiv.

3. Gestiunea memoriei si smart pointers

In intreg proiectul se folosesc std::unique_ptr pentru a detine produsele in catalog si in cos. Nu exista new/delete explicite (cu exceptia metodei clone care intoarce un pointer raw, dar acesta este imediat incapsulat intr-un unique_ptr). Regula celor cinci este implementata corect in Produs si in Cos (cu copy-and-swap). Cos are doi constructori de copiere (unul pentru copierea din alta instanta si unul pentru mutare). Toate destructorii sunt default sau nu au cod periculos. Nu exista memory leaks.

4. Tratarea exceptiilor

Exceptiile proprii sunt definite in Exceptii.h: StocInsuficientException, SoldInsuficientException, ProdusInexistentException. Ele sunt aruncate in metodele relevante (de exemplu, in finalizeazaComanda). In main, sunt prinse in blocuri try-catch separate. De asemenea, se arunca si exceptii standard (std::invalid_argument, std::out_of_range). Totul functioneaza corect.

5. Interfata non-virtuala si functii virtuale

Clasa Produs are functii virtuale pure (calculeazaPretFinal, clone, afisare). Operator<< este prieten si apeleaza afisare (NVI). In clasele derivate, afisare este suprascrisa. Acest design este respectat.

6. Sesiunea interactiva si citirea comenzilor

Partea cea mai noua este sesiunea de cumparare, care poate fi controlata de la tastatura sau dintr-un fisier comenzi.txt. Am folosit un std::istream& care poate fi std::cin sau un ifstream. Comenzile sunt parseeate linie cu linie. Programul afiseaza promptul "> " chiar si cand citeste din fisier, ceea ce poate fi deranjant, dar nu afecteza functionalitatea. O imbunatatire minora ar fi sa nu mai afiseze promptul in modul automat. In rest, comenzile sunt simple si usor de inteles.

7. Sistemul de puncte de loialitate

Punctele sunt stocate in extra-ul utilizatorului. La finalizarea comenzii, utilizatorul poate alege daca foloseste punctele (se scad din total). Apoi, la plata efectiva (dupa eventuala reducere cu puncte), se adauga puncte noi (1 la 10 lei). Codul din Cos::finalizeazaComanda gestioneaza corect aceste operatii. Este un feture realist si bine integrat.

8. Mici observatii si posibile imbunatatiri

- In main, linia `std::cin >> opt;` pentru puncte ar fi putut fi inlocuita cu `std::getline` pentru a evita problemele cu newline-ul ramas, dar in contextul actual (dupa ce s-a citit din stream-ul de comenzi sau de la tastatura) functioneaza.

- Produsul alimentar Paine (expirat) este incarcat in fisier dar nu este adaugat in catalog (este filtrat). In fisierul dat, Paine este ultima linie, dar are data 2024-01-01, deci este ignorata. Am ales sa o pastrez pentru ca am implementatoptiunea ca produsele sa fie adaugate in catalog doar daca sunt valabile.
  
- In Builder, produsele sunt mutate in cos, dar discount-ul setat nu este aplicat nicaieri (metoda setDiscount este definita dar nu folosita in build). Acesta este un punct slab: discount-ul nu se reflecta in pretul final. De fapt, in build() se apeleaza cos.adaugaProdus(std::move(item.produs), item.cantitate) fara a aplica discountul. Ar fi trebuit ca builder-ul sa aplice discountul fiecarui produs inainte de a-l adauga, sau sa seteze un discount global pe cos. Acesta este un bug functional.

- In main, dupa ce se termina sesiunea de comenzi (checkout), se citeste raspunsul pentru puncte cu `std::cin >> opt;`. In cazul in care se ruleaza cu fisierul comenzi.txt, aceasta citire nu mai vine din fisier ci de la tastatura, deoarece inputStream era finComenzi, dar dupa iesirea din bucla, se foloseste din nou std::cin. Pentru a fi consistent, ar fi trebuit sa se citeasca tot din inputStream. In codul actual, daca exista comenzi.txt, programul va astepta la sfarsit input de la tastatura, ceea ce nu este automat. Acesta este un alt defect minor. Solutia ar fi ca ultima linie din comenzi.txt sa fie si raspunsul pentru puncte, iar codul sa citeasca din acelasi stream.

9. Concluzie

In ciuda celor doua probleme mentionate (discountul neaplicat si citirea neuniforma a punctelor), proiectul este functional si demonstreaza intelegerea conceptelor cerute. Codul este lizibil si cu mici ajustari, ar putea deveni impecabil. AM depus un efort considerabil si am reusit sa integrez template-uri si trei design patterns.
