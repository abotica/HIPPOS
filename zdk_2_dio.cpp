

                                                                         /*ZDK-- >> 20_2*/ 

//{1.} ZADATAK:
//
//
// Deklarirana je klasa Razlomak, kojom se definira objekt razlomka odredjen cjelobrojnim 
// brojnikom i nazivnikom. Napisite:
// - operator = 
// - operator > 
// - operator za citanje, koji neka sa ulaznog toka cita brojnik i nazivnik
// Napisite primjer funkcije main() u kojem cete upotrijebiti klasu Razlomak i njene operatore.
// U funkciji main() objekte klase Razlomak alocirajte/dealocirajte dinamicki.
//
// NAPOMENA : Nazivnik ne smije biti nula!
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
using namespace std;

class Razlomak {
    int m_nazivnik;  //privatna varijabla nazivnik koja se stiti jer ne smije biti nula
public:
    int m_brojnik;
    Razlomak() { m_brojnik = 0; m_nazivnik = 1; }       //default konstruktor
    int GetNazivnik() { return m_nazivnik; }
    void SetNazivnik(int naz) { 
        m_nazivnik = (naz != 0 ? naz : m_nazivnik);
    }

    //operator = mora biti istog tipa kao i klasa za koju pisemo
    //operator = mora vratiti referencu za tu klasu 
    Razlomak& operator=(Razlomak& other);
};

//operator > optereæujemo kao vanjsku funkciju
//možemo ga preopteretiti kao vanjsku ali i kao èlansku funkciju
bool operator>(Razlomak& left, Razlomak& right) {
    double l, r;
    l = left.m_brojnik / left.GetNazivnik();
    r = right.m_brojnik / right.GetNazivnik();

    if (l > r)
        return true;
    else
        return false;
}

//operator za èitanje sa toka
//prima jedan tok za ulazni tok i refernecu na objekt, a vraca ulazni tok
istream& operator>>(istream& istr, Razlomak& me) {

    int b, n;

    //èitanje brojnik i nazivnik
    istr >> b >> n;
    if (istr) {
        me.m_brojnik = b;
        //provjera nazivnika je veæ napisana u SetNazivnik() pa je zato samo pozivamo
        me.SetNazivnik(n);  //ovaj n je prosljeðen u f-ju kao 'naz' te se provjerava je li nazivnik nula 
    }

    return istr;
}

Razlomak& Razlomak::operator=(Razlomak& other) {
    //operator this kao kopirni konstruktor
    //on iz ovoga što šaljemo preuzima i upisuje u sebe
    //on još mora vratiti (de)referencirani pokazivaè na samog sebe tako da se može nadovezivati na operator =
    m_brojnik = other.m_brojnik;
    m_nazivnik = other.m_nazivnik;

    //operator = nam je èlan klase stoga možemo dirati privatne varijable, a da nije motali bi koristiti set i get funkcije

    return *this;
}

int main() {

    //dinamièka alokacija ovako...  ili kao niz od dva elementa
    Razlomak* a = new Razlomak;
    Razlomak* b = new Razlomak;

    b->m_brojnik = 3;
    cout << (*b > *a) << endl;
    *a = *b;
    cout << (*b > *a) << endl;

    cin >> *a;
    
    //dealokacija
    delete a;
    delete b;

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {2.} ZADATAK:
//
//
// Tekstualna datoteka "ulaz.num" sadrži cijele brojeve. Napisite program 
// kojim se citaju svi brojevi iz ulazne datoteke, te se u drugu tekstualnu
// datoteku imena "poz.num" ispisuju svi pozitivni brojevi iz prve datoteke.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljucite potrebne biblioteke...


//MORAMO SAMI NAPRAVIT ULAZNU DATOTEKU IMENA "ulaz.num"

#include <iostream>
#include <fstream> //jer koristimo datoteke 
using namespace std;

int main() {

    //otvaramo
    ifstream ifs("ulaz.num");
    //ono što æemo pisati
    //ako je zadano da se dodaje ukljuèujemo append!
    ofstream ofs("poz.num", ios::app);

    double d;

    //proèitamo iz ulaznog toka varijablu i onda nam na tom mjestu ostaje ifs - ulazni tok; ako je true sve ok, a ako je false dosli smo do kraja datoteke
    while (ifs >> d) {
        if (d >= 0) {           //može i samo >
            ofs << d << endl;
        }
    }

    ofs.close();
    ifs.close();


    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {3.} ZADATAK:
//
// Deklarirana je klasa Point2D kojom se opisuje polozaj tocke 
// u 2D prostoru (x,y). Koristeci klasu i pravila nasljedjivanja 
// definirajte klasu Point4D, pomocu koje se opisuje polozaj 
// tocke u trodimenzionalnom prostoru sa vremenom (x, y, z, t).
// Vrijeme ne smije biti negativan broj.
// Dodatne varijable neka budu tipa double.
// Definirajte:
//  a)	konstruktor, kojim se dodatne varijable inicijaliziraju na nulu
//  b)	operator !=
//  c)	operator >>
// U main funkciji napišite primjer korištenja klase Point4D.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...


#include <iostream>
using namespace std;

class Point2D {
public:
    Point2D() { m_x = m_y = 0.0; }
    double m_x, m_y;
};

class Point4D : public Point2D {
    double m_t;       //private i za nju je potrebno napraviti set i get funkcije

    public:
        double m_z;
        double Get_t() { return m_t; }
        void Set_t(double temp) { if (temp >= 0) m_t = temp; }

        //konstruktori se izvode po liniji nasljeðivanja -> prvo konstruktor temeljne, a onda konstruktor nasljeðene
        //U konstruktoru nasljeðene klase treba napisati samo dodatne varijable
        Point4D() { m_z = m_t = 0.0; }
};


//operator nije jednako radimo kao vanjsku funkciju i vraæa bool
bool operator!=(Point4D & left, Point4D & right) {

    //ako nije jednako treba vratiti true, a nije jednako ako bilo koji od clanskih varijabli nije jednak
    if (left.m_x != right.m_x)
        return true;
    if (left.m_y != right.m_y)
        return true;
    if (left.m_z != right.m_z)
        return true;
    if (left.Get_t() != right.Get_t())   //ne možemo direktno stavit m_t jer samo u vanjskoj funkciji (nije èlanska)
        return true;
    return false;
}

//operator za èitanje -> prima dvije referencu 
istream& operator >>(istream& istr, Point4D& me) {
    double a, b, c, d;   //privremene varijable koje èitamo

    if (istr >> a >> b >> c >> d) {
        me.m_x = a;
        me.m_y = b;
        me.m_z = c;
        me.Set_t(d);
    }
    return istr;  //nadovezivanje
}

int main() {
    Point4D a, b;

    cout << (a != b) << endl;  //oboje su na poèetku nula, što znaèi da su jednaki (false) ispisuje se nula
    cin >> a;
    cout << (a != b) << endl;

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {4.} ZADATAK:
//
//
// Napisite genericku funkciju Vece() koja neka 
// prima listu elemenata i prag. Funkcija treba iz liste
// izbaciti sve elemente manje od praga i to vratiti kao 
// povratnu vrijednost.
// U main funkciji napravite primjer koristenja
// funkcije Vece() na listi varijabli tipa int.
// Elementi liste i prag su proizvoljni.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

//NOVI TEKST ZADATKA:
// Napisite genericku funkciju Vece() koja neka 
// prima listu elemenata i prag. Funkcija treba iz liste
// izbaciti sve elemente manje od praga.
// U main funkciji napravite primjer koristenja
// funkcije Vece() na listi varijabli tipa int.
// Elementi liste i prag su proizvoljni.

#include <iostream>
#include <list>         //ako radimo sa listama
using namespace std;

//template <class T> void Vece(list<T>& L, T prag)
//neæe više zadavat ovako nego:
template <class T> list<T> Vece(list<T>, T prag) {

    list<T> ret;  //nova lista

    for (auto it : L) {     //šetamo sa 'it' kroz listu 'L'
        if (it >= prag) {   //ako vrijedi to trebamo dodati u neku novu listu
            ret.push_back(it);
        }
    }
    return ret;
}


int main() {

    list<double> lst{ 1.0, 3.2, 5.4, 7.8 };
    list<double> r;                             //povratna lista koja je prazna na poèetku

    r = Vece(lst, 4.0);

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {5.} ZADATAK:
//
//
// Napisite funkciju FindInt() kojom se pretrazuje lista integera.
// Funkcija treba u listi L pronaci integer i.
// Ukoliko ga pronadje neka vrati istinu, inace laz.
// Trazenje napravite funkcijom find() iz biblioteke <algorithm>.
// Napisite main() funkciju sa primjerom koristenja funkcije 
// FindInt().
//
// NAPOMENA: STL funkcija find() vraca iterator end() ukoliko
// je potraga neuspjesna.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...


#include <iostream>
#include <list>
#include <algorithm> //kad se radi o algoritmima
using namespace std;

bool FindInt(const list<int>& L, int i) {

    //agloritmi funkcioniraju tako da damo neki raspon unutar kojeg radimo i jos neke dodatne argumente koji su potrebni za taj algoritam
    //sort() -> samo raspon ; find() -> raspon i argumenti(ono što se traži)
    
    if (find(L.begin(), L.end(), i) == L.end())      //ako je ono što nades(vratis) L.end(); ako se ne nade vraca end(); a ako nade vraca ono što nade
        return false;                               //jer nije nista nasa odnosno vraca end()
    else
        return true;                                    
}

int main() {

    list<int> L = { 1,2,3,4,5,6,7,8,9,0 };

    cout << FindInt(L, 5) << endl;          //true -> 1
    cout << FindInt(L, 15) << endl;        //false -> 0

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

           


                                                                                         /*Proba ispit 2022/3*/


// {1.} ZADATAK:
//
//
// U ulaznoj tekstualnoj datoteci imena "ulaz.txt" zapisani su cijeli brojevi.
// U izlaznu tekstualnu datoteku imena "kor.txt" datoteku zapisite
// vrijednosti drugog korijena svih pozitivnih brojeva iz ulazne datoteke.
// 
// NAPOMENA: Funkcija za vaðenje drugog korijena sqrt je dio biblioteke <cmath>
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {

    ifstream ulaz("ulaz.txt");
    ofstream izlaz("kor.txt");

    int i;

    while (ulaz>>i){
        if (i > 0) {
            izlaz << sqrt(i) << endl;
        }
    }

    ulaz.close();
    izlaz.close();

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {2.} ZADATAK:                                                                                   
//                                                                                                                                 
// Zadana je klasa CUcenik. Napisite:
// - konstruktor koji m_ime postavlja na prazan string, a m_ocjena na 0
// - set/get funkcije za ocjenu (u rasponu od 1 do 5)
// - operator == koji vraca istinu ako dva ucenika imaju isto ime o oste ocjene 
//   (operator neka bude vanjska friend funkcija tipa bool, sa dva argumenta tipa klase CUcenik)
// - operator >> koji sa toka èita najprije ime, a potom ocjenu 
//   (operator neka bude vanjska friend funkcija tipa ulaznog toka,
//    sa prvim argumentom objektom ulaznog toka sa kojeg se èita,
//    te drugim argumentom objektom klase CUcenik u koju se èita)
// 
// U main() funkciji dinamièki deklarirajte dva objekta klase CUcenik, 
// ucitajte njihove podatke sa tipkovnice pomoæu operatora >>,
// te provjerite jesu li jednaki!
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...


#include <iostream>
using namespace std;

class CUcenik {
    int m_ocjena;       //ocjena
public:
    string m_ime;       //ime i prezime
    CUcenik();
    int GetOcjena();
    void SetOcjena(int ocjena);
    friend bool operator ==(const CUcenik& a, const CUcenik& b);
    friend istream& operator >>(istream& in, CUcenik& me);
};

bool operator ==(const CUcenik& a, const CUcenik& b) {

    if (a.m_ocjena == b.m_ocjena && a.m_ime == b.m_ime)
        return true;
    else
        return false;
}

istream& operator >>(istream& in, CUcenik& me) {
    string str;
    int i;

    if (in >> str >> i) {
        me.m_ime = str;

        if (i >= 1 && i <= 5) {
            me.m_ocjena = i;            //??
        }
    }
    return in;
}

CUcenik::CUcenik() {
    m_ime = "";
    m_ocjena = 0;
}


int main() {
    
    CUcenik* prvi;
    CUcenik* drugi;

    prvi = new CUcenik;
    drugi = new CUcenik;

    cin >> *prvi;
    cin >> *drugi;

    if (prvi == drugi) {
        cout << "Isti su!!!" << endl;
    }

    delete prvi;
    delete drugi;

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {3.} ZADATAK:
//
// Zadana je klasa Biljka, koja biljezi podatke o biljci.
// Napravite klasu GMOBIljka, koja nasljeðuje od klase Biljka,
// a ima dodatnu èlansku varijablu imena GMO, tipa bool.
// 
// Za klasu GMOBiljka definirajte:
//  a) default konstruktor, koji postavlja GMO na false
//  b) kopirni konstruktor
//  c) operator << koji neka bude vanjska funkcija tipa izlaznog toka,
//     sa prvim argumentom objektom izlaznog toka na koji se piše,
//     te drugim argumentom objektom klase GMOBiljka koji se zapisuje
//  d) operator == koji neka bude èlanska funkcija koja prima
//     jedan argument klase GMOBiljka i tipa je bool
// 
// U main() funkciji iskoristite klasu GMOBiljka i isprobajte svu njenu funkcionalnost.
// 
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
using namespace std;

class Biljka {
protected:
    string ime_biljke;
    string vrsta_biljke;
    int starost;

public:
    Biljka();
    Biljka(const Biljka& temp);
    
    void postavi_sve(string var1, string var2, int var3) {
        ime_biljke = var1;
        vrsta_biljke = var2;
        if (var3 >= 0) {
            starost = var3;
        }
    }

    string dohvati_ime() { return ime_biljke; }
    string dohvati_vrstu() { return vrsta_biljke; }
    int dohvati_starost() { return starost; }
};

Biljka::Biljka() {
    ime_biljke = vrsta_biljke = "";
    starost = 0;
}

Biljka::Biljka(const Biljka& temp) {
    ime_biljke = temp.ime_biljke;
    vrsta_biljke = temp.vrsta_biljke;
    starost = temp.starost;
}

class GMOBiljka : public Biljka {

public:
    bool GMO;

    GMOBiljka();
    GMOBiljka(GMOBiljka& other);

    bool operator ==(const GMOBiljka& a);
    friend ostream& operator <<(ostream& in, GMOBiljka& me);
};

GMOBiljka::GMOBiljka() {
    GMO = false;
}

GMOBiljka::GMOBiljka(GMOBiljka& other) {
    ime_biljke = other.ime_biljke;
    vrsta_biljke = other.vrsta_biljke;
    starost = other.starost;
    GMO = other.GMO;
}

bool GMOBiljka::operator ==(const GMOBiljka& a) {
    if (GMO == a.GMO)
        return true;
    else
        return false;
}

ostream& operator <<(ostream& out, GMOBiljka& me) {
    out << me.ime_biljke << endl;
    out << me.vrsta_biljke << endl;
    out << me.starost << endl;
    out << me.GMO << endl;

    return out;
}

int main() {

    GMOBiljka b1;
    b1.postavi_sve("a", "b", 1);
    b1.GMO = true;
    GMOBiljka b2(b1);
    b2.GMO = false;

    if (b1 == b2)
        cout << "Isti su!!!" << endl;

    cout << b1 << b2 << endl;

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {4.} ZADATAK:
//
// Napisite funkciju MiljeUKilometre(), koja prima jedan argument
// i to referencu varijeable imena udaljenosti tipa float.
// On pri pozivu funkcije sadrzi vrijednost u Miljama, a nakon
// zavrsetka funkcije sadrzi vrijednost u kilometrima.
// 
// Racunajte da 1 milja ima 1.6 kilometara
// 
// U glavnom programu sa tipkovnice ucitajte jednu vrijednost u miljama,
// te pomocu funkcije ispisite vrijednost u kilometrima.
// 
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
using namespace std;

void MiljeUKilometre(float& udaljenost) {
    udaljenost = udaljenost * 1.6;
}

int main() {

    float udalj;

    cin >> udalj;
    MiljeUKilometre(udalj);
    cout << udalj << endl;

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {5.} ZADATAK:
//
// Napisite funkciju koja prima vektor cijelih brojeva, te
// vraca minimalni i maksimalni element zapisan u vektoru.
// 
// Za trazenje min i maks elementa koristite funkcije 
// biblioteke <algorithm>
// 
// Napisite main() funkciju sa primjerom koristenja funkcije
// Range().  
// 
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...


#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;


void Range(vector<int>& vec, int& minNum, int& maxNum) {
    minNum = *min_element(vec.begin(), vec.end());
    maxNum = *max_element(vec.begin(), vec.end());
}

int main() {

    vector<int> v = { 1, 34, 3, 65, -1, 2 };
    int mn, mx;

    Range(v, mn, mx);

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {6.} ZADATAK:
//
// Napisite genericku funkciju za zamijenu vrijenosti imena Zamijeni.
// Funkcije neka bdue napisana u obliku predloska, tako da se moze
// specijalizirati za razne tipove varijabli.
// Funkcija neka prima dva argumenta putem reference cije 
// vrijednosti medusobno mijenja.
// 
// U main() funkciji upotrijebite funkciju Zmaijeni dva puta,
// jedanput za varijeble tipa double, a drugi put za int.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
using namespace std;

template <class T> void Zamijeni(T& prva, T& druga) {
    T treca;

    treca = prva;
    prva = druga;
    druga = treca;
}

int main() {
    //dodajte naredbe glavne funkcije

    double d1, d2;
    int i1, i2;

    d1 = -5.1;
    d2 = 5.1;
    Zamijeni(d1, d2);

    i1 = -5;
    i2 = 5;
    Zamijeni(i1, i2);

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {7.} ZADATAK:
//
// Napisati specifikacijui implementaciju klase Kvadar
// koja biljezi duljinu, sirinu i visinu kvadra.
// Sve clanske varijable trebaju biti deklarirane kao privatne i ne smiju biti negativne.
// 
// Napisati:
// - podrazumijevani konstruktor koji neka clanske varijable postavlja na nulu
// - set i get funkcije za clanske varijable
// - operator za citanje sa toka (operator neka bude 
//   vanjska friend funkcija tipa ulaznog toka,
//   sa prvim argumentom objektom ulaznog toka sa kojeg se cita, 
//   te drugim argumentom objektom klase Kvadar u koji se cita)
// - funkcija koja racuna volumen (duljin*sirina*visina)
// 
// U main() funkciji isprobati kompletnu funkcionalnost klase.
// 
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...


#include <iostream>
using namespace std;

class Kvadar {
    double duljina;
    double sirina;
    double visina;

public:
    double GetDuljina();
    void SetDuljina(double temp);
    double GetSirina();
    void SetSirina(double temp);
    double GetVisina();
    void SetVisina(double temp);

    Kvadar();
    double Volumen();

    friend istream& operator >>(istream& in, Kvadar& me);
};

Kvadar::Kvadar() {
    duljina = sirina = visina = 0.0;
}

double Kvadar::GetDuljina() {
    return duljina;
}

void Kvadar::SetDuljina(double temp) {
    if (temp >= 0.0) {
        duljina = temp;
    }
}

double Kvadar::GetSirina() {
    return sirina;
}

void Kvadar:: SetSirina(double temp) {
    if (temp >= 0.0) {
        sirina = temp;
    }
}

double Kvadar::GetVisina() {
    return visina;
}

void Kvadar::SetVisina(double temp) {
    if (temp >= 0.0) {
        visina = temp;
    }
}

double Kvadar::Volumen() {
    return duljina * sirina * visina;
}

istream& operator >>(istream& in, Kvadar& me) {
    double d1, d2, d3;

    if (in >> d1 >> d2 >> d3) {
        me.SetDuljina(d1);
        me.SetSirina(d2);
        me.SetVisina(d3);
    }

    return in;
}

int main() {

    Kvadar k;

    k.SetDuljina(1.1);
    k.SetSirina(2.2);
    k.SetVisina(3.3);

    cin >> k;

    cout << k.GetDuljina() << endl;
    cout << k.GetSirina() << endl;
    cout << k.GetVisina() << endl;
    cout << k.Volumen() << endl;

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


                                                           /*2.dio_18-2*/
// {1.} ZADATAK:             
//
//
// Deklarirana je klasa Niz, kojom se deklarira dinamicki niz cijelih brojeva.
// Koristeci ovu deklaraciju :
//		a)	napisite konstruktor, kojim se ujedno alocira dinamicki niz m_array 
//			i svi elementi postavljaju na nulu.
//		b)  napišite destruktor koji dealocira niz
//		c)	definirajte funkcije SetAt() i GetAt().
//		d)	definirajte operator= za klasu Niz.
//		e)  definirajte operator==
//
// U funkciji main() upotrebite klasu i sve njene funkcije i operatore.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
using namespace std;

class Niz {
public:
    Niz(int size = 5);
    ~Niz();
    void SetAt(int index, int val);
    int GetAt(int index);
    Niz& operator=(Niz& n1);
    friend bool operator==(Niz&, Niz&);

private:
    int* m_array;
    int m_size;
};

Niz::Niz(int size) {
    this->m_array = new int[size];
    m_size = size;

    for (int i = 0; i < size; i++) {
        m_array[i] = 0;
    }
}

Niz::~Niz() {
    delete[]m_array;
}

void Niz::SetAt(int index, int val) {
    m_array[index] = val;
}

int Niz::GetAt(int index) {
    return m_array[index];
}

Niz& Niz:: operator =(Niz& n1) {
    this->m_size = n1.m_size;
    this->m_array = new int[m_size];

    for (int i = 0; i < m_size; i++)
        m_array[i] = n1.m_array[i];

    return *this;
}

bool operator==(Niz& n1, Niz& n2) {

    if (n1.m_size != n2.m_size)
        return false;

    for (int i = 0; i < n1.m_size; i++)
        if (n1.m_array[i] != n2.m_array[i])
            return false;

    return true;
}

int main() {

    Niz A;
    Niz B;

    for (int i = 0; i < 5; i++)
        A.SetAt(i, i * i);

    for (int i = 0; i < 5; i++)
        cout << A.GetAt(i) << endl;

    B = A;

    if (B == A)
        cout << "Istina je!" << endl;

    for (int i = 0; i < 5; i++)
        cout << B.GetAt(i) << endl;

    return 0;
}





/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//
// {2.} ZADATAK:
//
//
// Napišite program kojim se sadržaj jedne tekstualne datoteke 
// kopira u drugu, na nacin da se sva pocetna slova rijeci kopiraju kao 
// velika slova. Ostali znakovi se ne mijenjaju. 
// Evo primjera originalne datoteke (lijevo) i kopirane datoteke (desno)

// Danas je petak 1.2.2019.						Danas Je Petak 1.2.2019. 
// Dolazi DRUGI kolokvij.						Dolazi DRUGI Kolokvij.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

int main() {

    ifstream ulaz("ulaz.txt");
    ofstream izlaz("izlaz.txt");

    char c;

    ulaz.get(c);

    while (!ulaz.eof()) {
        if (c == ' ' || c == '\n') {
            izlaz << c;
            ulaz.get(c);

            c = toupper(c);

            izlaz << c;
            ulaz.get(c);
        }
        else {
            izlaz << c;
            ulaz.get(c);
        }
    }

    ulaz.close();
    izlaz.close();

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {3.} ZADATAK:
//
//
// Deklarirana je klasa Circle, kojom se bilježi radijus kružnice.
// Napišite klasu ExtendedCircle koja pored radijusa kružnice 
// sadrži podatak o boji kružnice m_color tipa int i 
// debljini m_thickness tipa int. Ove varijable neka budu
// privatne, a njihova vrijednost od 0 do 255.
// U definiranju klase ExtendedCircle obvezno koristite mehanizam 
// nasljedjivanja, tako da klasa ExtendedCircle nasljedjuje klasu Circle.
// Za klasu ExtendedCircle definirajte:
//  a) default konstruktor, koji postavlja clanove na nulu
//  b) operator = 
//  c) pristupne funkcije za nove clanove.
//
// U main funkciji deklarirajte jedan objekt klase ExtendedCircle i 
// sa tipkovnice ucitajte vrijednosti clanskih varijabli.
// Potom deklarirajte još jedan objekt klase ExtendedCircle
// i iskoristite operator = za postaviti ga na vrijednost prethodnog objekta.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...

#include <iostream>
using namespace std;


class Circle {
public:
    Circle() { m_radius = 0; }
    void SetRadius(int r) { if (r >= 0) m_radius = r; };
    int GetRadius() { return m_radius; };

protected:
    int m_radius;
};

class ExtendedCircle : public Circle {
private:
    int m_colour;
    int m_thickness;

public:
    ExtendedCircle();
    ExtendedCircle& operator =(const ExtendedCircle&);
    void SetColour(int temp);
    int GetColour();
    void SetThickness(int temp);
    int GetThickness();
};

ExtendedCircle::ExtendedCircle() {
    m_colour = 0;
    m_thickness = 0;
}

ExtendedCircle& ExtendedCircle:: operator =(const ExtendedCircle& temp) {
    m_radius = temp.m_radius;
    m_colour = temp.m_colour;
    m_thickness = temp.m_thickness;

    return *this;
}

void ExtendedCircle::SetColour(int temp) {
    if ((temp >= 0) && (temp <= 255)) {
        m_colour = temp;
    }
}

int ExtendedCircle::GetColour() {
    return m_colour;
}

void ExtendedCircle::SetThickness(int temp) {
    if ((temp >= 0) && (temp <= 255)) {
        m_thickness = temp;
    }
}

int ExtendedCircle::GetThickness() {
    return m_thickness;
}

int main()
{
    ExtendedCircle A;
    ExtendedCircle B;
    int r, c, t;

    cout << "Unesite vrijednost radijusa, boje, debljine:" << endl;
    cin >> r;
    A.SetRadius(r);
    cin >> c;
    A.SetColour(c);
    cin >> t;
    A.SetThickness(t);

    cout << "Vrijednosti: " << A.GetRadius() << "\t" << A.GetColour() << "\t" << A.GetThickness() << endl;

    B = A;
    cout << "Vrijednosti: " << B.GetRadius() << "\t" << B.GetColour() << "\t" << B.GetThickness() << endl;

    return 0;
}






/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


//
// {4.} ZADATAK:
//
//
// Napišite genericku funkciju za odreðivanje maksimalne vrijednosti 
// imena max(). Funkcija neka bude napisana u obliku predloška, tako 
// da se može specijalizirati za razne tipove varijabli. 
// Funkcija neka prima tri argumenta, a neka vraæa najveæi 
// od njih. 
// U main funkciji upotrebite funkciju max() dva puta, jedan put za 
// varijable tipa double, drug put za int.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...

#include <iostream>
using namespace std;

template <class T> T max(T a, T b, T c) {
    T m;

    m = a > b ? a : b;
    m = c > m ? c : m;

    return m;
}

int main() {

    double d;
    int i;

    i = max(4, 2, 7);
    d = max(12.5, 1.3, 0.5);

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

//
// {5.} ZADATAK:
//
//
// Napišite funkciju, kojom se iz jednog vektora V formiraju dva vektora: 
// V1 treba sadržavati neparne, a vektor V2 parne elemente vektora.
// U funkciji vektore V1 i V2 sortirajte pomocu STL funkcije sort().
// Napišite main() funkciju sa primjerom korištenja funkcije Razdijeli_vektor().
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Vec;

void Razdijeli_vektor(Vec& V, Vec& V1, Vec& V2) {
    vector<int>::iterator iter;
    for (iter = V.begin(); iter != V.end(); iter++)
    {
        if (*iter % 2 == 0)
        {
            V2.push_back(*iter);
        }

        else
            V1.push_back(*iter);
    }

    sort(V1.begin(), V1.end());
    sort(V2.begin(), V2.end());
}

int main() {

    Vec V;
    Vec V1;
    Vec V2;

    for (int i = 0; i < 6; i++)
    {
        V.push_back((i + 1) * (i + 1));
    }

    Razdijeli_vektor(V, V1, V2);

    for (int i = 0; i < V1.size(); i++)
    {
        cout << V1[i] << endl;
    }

    cout << "Drugi vektor:" << endl;

    for (int i = 0; i < V2.size(); i++)
    {
        cout << V2[i] << endl;
    }

    return 0;
}

//#include <vector>
//#include <algorithm>
//using namespace std;
//typedef vector<int> Vec;
//
//void Razdijeli_vektor(Vec& V, Vec& V1, Vec& V2) {
//	vector<int>::iterator iter;
//	for (iter = V.begin(); iter != V.end(); ++iter) {
//		if (*iter % 2 == 1)
//			V1.push_back(*iter);
//		else
//			V2.push_back(*iter);
//	}
//	sort(V1.begin(), V1.end());
//	sort(V2.begin(), V2.end());
//}
//
//int main() {
//	Vec a = { 1,5,3,44,5,6,7,4,3,5,66,7 };
//	Vec b, c;
//	Razdijeli_vektor(a, b, c);
//
//	return 0;
//}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

                    /*17-2*/                                    /*17-2*/
                        /*17-2*/                            /*17-2*/
                            /*17-2*/                    /*17-2*/
                                /*17-2*/            /*17-2*/
                                    /*17-2*/    /*17-2*/
                                         /*17-2*/


// {1.}ZADATAK:
//
//
// Preradite funkciju kvadrat tako da rezultat kvadriranja argumenta vraæa pomoæu reference. 
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...


#include<iostream>
using namespace std;

void kvadrat(double& argument) {
    argument = argument * argument;
}

int main() {
    double x;

    cin >> x;
    kvadrat(x);
    cout << x << endl;

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {2.}ZADATAK:
//
//
// Deklarirana je klasa Razlomak, kojom se definira objekt razlomka odreðen cjelobrojnim brojnikom i nazivnikom:
// Napišite:
// - podrazumijevani konstruktor koji postavlja brojnik na 0, a nazivnik na 1
// - kopirni konstruktor
// - pristupne funkcije za nazivnik
// - postfix operator ++ koji neka poveæa brojnik za iznos nazivnika
// - operator za ispisivanje, koji neka ispisuje dva cijela broja - brojnik i nazivnik odjeljena znakom '/'
// Napišite primjer funkcije main u kojem æete upotrijebiti klasu Razlomak i njene funkcije.
//
// NAPOMENA : Nazivnik ne smije biti nula!
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...

#include<iostream>
using namespace std;

class Razlomak {
    int m_nazivnik;
public:
    int m_brojnik;
    Razlomak();
    Razlomak(const Razlomak& temp);
    int GetNazivnik();
    void SetNazivnik(int naz);
    Razlomak operator++(int);
};

Razlomak::Razlomak() {
    m_brojnik = 0;
    m_nazivnik = 1;
}

Razlomak::Razlomak(const Razlomak& temp) {
    m_brojnik = temp.m_brojnik;
    m_nazivnik = temp.m_nazivnik;
}

void Razlomak::SetNazivnik(int naz) {
    if (naz != 0) {
        m_nazivnik = naz;
    }
    else {
        cout << "Nedozvoljena vrijednost nazivnika --> nazivnik razlièit od nule!" << endl;
    }
}

int Razlomak::GetNazivnik(){
    return m_nazivnik;
}

Razlomak Razlomak::operator++(int unused) {
    Razlomak temp(*this);
    m_brojnik += m_nazivnik;
    return temp;
}

ostream& operator << (ostream& out, Razlomak& s) {
    out << s.m_brojnik << "/" << s.GetNazivnik() << endl;
    return out;
}

int main() {
    
    Razlomak R;
    int x;

    cin >> x;

    R.SetNazivnik(x);

    R++;

    cout << R;

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {3.}ZADATAK:
//
//
// Napisati funkciju, kojom se iz dva vektora cijelih brojeva V1 i V2 
// formira jedan vector V, koja treba sadržavati sve parne brojeve iz vectora V1 i V2.
// U vectoru V brojevi trebaju biti sortirani. Za vector koristite STL biblioteku;
// Za sortiranje koristite funkciju iz STL biblioteke algoritama. 
// U main funkciji sami napravite primjer upotrebe funkcije.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> formiraj_vector(vector<int>& v1, vector<int>& v2) {
    vector<int> v;
    vector<int>::iterator iter;

    for (iter = v1.begin(); iter != v1.end(); iter++) {
        if (*iter % 2 == 0) {
            v.push_back(*iter);
        }
    }

    for (iter = v2.begin(); iter != v2.end(); iter++) {
        if (*iter % 2 == 0) {
            v.push_back(*iter);
        }
    }

    sort(v.begin(), v.end());

    return v;
}

int main() {

    vector<int> v1, v2, v;
    int v1_size, v2_size, el;

    cout << "Unesi velicinu 1. vektora: ";
    cin >> v1_size;

    cout << "Unesi velicinu 2. vektora: ";
    cin >> v2_size;

    cout << "Unesi sadrzaj vektora v1: ";
    for (int i = 0; i < v1_size; i++) {

        cin >> el;
        v1.push_back(el);
    }

    cout << "Unesi sadrzaj vektora v2: ";
    for (int i = 0; i < v1_size; i++) {

        cin >> el;
        v1.push_back(el);
    }

    v = formiraj_vector(v1, v2);

    for (auto iter : v) {
        cout << iter << ' ';
    }
    cout << endl;

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {4.}ZADATAK:
//
//
// Napišite generièku funkciju za zamijenu vrijednosti imena swap. 
// Funkcija neka bude napisana u obliku predloška, tako da se može 
// specijalizirati za razne tipove varijabli. 
// Funkcija neka prima dva argumenta putem reference èije vrijednosti 
// meðusobno mijenja. 
// U main funkciji upotrebite funkciju swap dva puta, jedan put za 
// varijable tipa double, drug put za int.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...

#include<iostream>
using namespace std;

template <class T> T sswap(T& a, T& b){
    T x;

    x = a;
    a = b;
    b = x;

    return x;
}

int main() {
    
    int x, y;

    int a = 5;
    int b = 2;
    cout << "1.var: " << a << endl;
    cout << "2.var: " << b << endl;
    x = sswap<int>(a, b);
    cout << "1.var: " << a << endl;
    cout << "2.var: " << b << endl;

    cout << endl;

    double c = 5.5;
    double d = 2.2;
    cout << "1.var: " << c << endl;
    cout << "2.var: " << d << endl;
    y = sswap<double>(c, d);
    cout << "1.var: " << c << endl;
    cout << "2.var: " << d << endl;


    return 0;
}

//ILI

#include <iostream>
using namespace std;

template<class T> T swap_1(T& arg1, T& arg2) {

    T temp;

    temp = arg1;
    arg1 = arg2;
    arg2 = temp;

    return temp;
}

int main() {
    double var1, var2;
    int v1, v2;

    int x;
    double y;

    cout << "Varijabla 1 tipa double: ";
    cin >> var1;
    cout << "Varijabla 2 tipa double: ";
    cin >> var2;

    x = swap_1(var1, var2);
    cout << "Varijabla 1 tipa double: " << var1 << endl;
    cout << "Varijabla 2 tipa double: " << var2 << endl;

    cout << "Varijabla 1 tipa int: ";
    cin >> v1;
    cout << "Varijabla 2 tipa int: ";
    cin >> v2;

    y = swap_1(v1, v2);
    cout << "Varijabla 1 tipa int: " << v1 << endl;
    cout << "Varijabla 2 tipa int: " << v2 << endl;

    return 0;
}

//ILI

#include <iostream>
using namespace std;


template<class T> void swap_1(T& arg1, T& arg2) {
    T temp;

    temp = arg1;
    arg1 = arg2;
    arg2 = temp;
}

int main() {
    double var1, var2;
    int v1, v2;

    cout << "Varijabla 1 tipa double: ";
    cin >> var1;
    cout << "Varijabla 2 tipa double: ";
    cin >> var2;

    swap_1(var1, var2);
    cout << "Varijabla 1 tipa double: " << var1 << endl;
    cout << "Varijabla 2 tipa double: " << var2 << endl;

    cout << "Varijabla 1 tipa int: ";
    cin >> v1;
    cout << "Varijabla 2 tipa int: ";
    cin >> v2;

    swap_1(v1, v2);
    cout << "Varijabla 1 tipa int: " << v1 << endl;
    cout << "Varijabla 2 tipa int: " << v2 << endl;

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {5.}ZADATAK:
//
//
// Napišite program kojim se analizira sadržaj neke tekstualne datoteke. Program izvještava: 
// a)	koliko je znakova
// b)	koliko je rijeèi
// c)	koliko je redaka teksta
//
// zapisano u toj datoteci.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljuèite potrebne biblioteke...

#include<iostream>
#include<fstream>
using namespace std;

int main() {
    ifstream ulaz;

    ulaz.open("zaadaak.txt");
    if (!ulaz) {
        cout << "fail!" << endl;
    }

    int br_znakova = 0;
    int br_rijeci = 0;
    int br_redaka = 0;
    char c;

    while (ulaz.get(c)) {
        br_znakova++;

        if (c == ' ' || c == '\n' || c == '\t') {
            br_rijeci++;
        }

        if (c == '\n') {
            br_redaka++;
        }
    }

    ulaz.close();

    cout << "Znakova: " << br_znakova << endl;
    cout << "Rijeci: " << br_rijeci << endl;
    cout << "Redci: " << br_redaka << endl;

    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
                    /*18-2*/                                    /*18-2*/
                        /*18-2*/                            /*18-2*/
                            /*18-2*/                    /*18-2*/
                                /*18-2*/            /*18-2*/
                                    /*18-2*/    /*18-2*/
                                         /*18-2*/

// {1.}ZADATAK:
//
//
// Deklarirana je klasa Niz, kojom se deklarira dinamicki niz cijelih brojeva.
// Koristeci ovu deklaraciju :
//		a)	napisite konstruktor, kojim se ujedno alocira dinamicki niz m_array 
//			i svi elementi postavljaju na nulu.
//		b)  napišite destruktor koji dealocira niz
//		c)	definirajte funkcije SetAt() i GetAt().
//		d)	definirajte operator= za klasu Niz.
//		e)  definirajte operator==
//
// U funkciji main() upotrebite klasu i sve njene funkcije i operatore.
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte ništa iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
using namespace std;

class Niz {
public:
    Niz(int size = 5);
    ~Niz();
    void SetAt(int index, int val);
    int GetAt(int index);

    Niz& operator=(const Niz&);
    friend bool operator==(const Niz&, const Niz&);

private:
    int* m_array;
    int m_size;
};

Niz::Niz(int size) {
    m_size = size;
    m_array = new int[size];

    for (int i = 0; i < size; i++) {
        m_array[i] = 0;
    }
}

Niz::~Niz() {
    delete[] m_array;
}

void Niz::SetAt(int index, int val) {
    m_array[index] = val;
}

int Niz::GetAt(int index) {
    return m_array[index];
}

Niz& Niz::operator=(const Niz& temp) {

    m_size = temp.m_size;

    for (int i = 0; i < m_size; i++) {
        m_array[i] = temp.m_array[i];
    }

    return *this;
}

bool operator==(const Niz& temp1, const Niz& temp2) {
    if (temp1.m_size == temp2.m_size) {
        for (int i = 0; i < temp1.m_size; i++) {
            if (temp1.m_array[i] != temp2.m_array[i])
                return false;
        }
        return true;
    }
    else {
        return false;
    }
}

int main() {

    Niz A;
    Niz B;

    int velicina;
    int el;

    cout << "Unesite velicinu niz: " << endl;
    cin >> velicina;

    for (int i = 0; i < velicina; i++) {
        cin >> el;
        A.SetAt(i, el);
    }

    cout << "Prvi niz: " << endl;
    for (int i = 0; i < velicina; i++) {
        cout << A.GetAt(i) << endl;
    }

    B = A;
    cout << "Drugi niz: " << endl;
    for (int i = 0; i < velicina; i++) {
        cout << B.GetAt(i) << endl;
    }

    if (A == B) {
        cout << "GG" << endl;
    }

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {2.}ZADATAK:
//
//
// Napisite program kojim se sadrzaj jedne tekstualne datoteke 
// kopira u drugu, na nacin da se sva pocetna slova rijeci kopiraju kao 
// velika slova. Ostali znakovi se ne mijenjaju. 
// Evo primjera originalne datoteke (lijevo) i kopirane datoteke (desno)

// Danas je petak 1.2.2019.						Danas Je Petak 1.2.2019. 
// Dolazi DRUGI kolokvij.						Dolazi DRUGI Kolokvij.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include<fstream>
using namespace std;


int main() {

    ifstream ulaz;
    ofstream izlaz;

    ulaz.open("ulaz.txt");
    if (!ulaz) {
        cout << "Fail!" << endl;
        return 1;
    }

    izlaz.open("promjenjeni.txt");
    if(!izlaz){
        cout << "Fail!" << endl;
        return 1;
    }

    char c;
    ulaz.get(c);

    while (ulaz) {
        if (c == ' ' || c == '\n') {
            izlaz << c;
            ulaz.get(c);
            c = toupper(c);
            izlaz << c;
            ulaz.get(c);
        }
        else {
            izlaz << c;
            ulaz.get(c);
        }
    }

    ulaz.close();
    izlaz.close();

    return 0;
}


//ILI

#include<iostream>
#include<fstream>
using namespace std;


int main() {

    ifstream ulaz;
    ofstream izlaz;

    ulaz.open("ulaz.txt");
    if (!ulaz) {
        cout << "Fail!" << endl;
        return 1;
    }

    izlaz.open("promjenjeni.txt");
    if (!izlaz) {
        cout << "Fail!" << endl;
        return 1;
    }

    char c;
    ulaz.get(c);

    while (ulaz) {
        if (c == ' ' || c == '\n') {
            izlaz.put(c);
            ulaz.get(c);
            c = toupper(c);
            izlaz.put(c);
            ulaz.get(c);
        }
        else {
            izlaz.put(c);
            ulaz.get(c);
        }
    }

    ulaz.close();
    izlaz.close();

    return 0;
}




/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {3.}ZADATAK:
//
//
// Deklarirana je klasa Circle, kojom se biljezi radijus kruznice.
// Napisite klasu ExtendedCircle koja pored radijusa kruznice 
// sadrzi podatak o boji kruznice m_color tipa int i 
// debljini m_thickness tipa int. Ove varijable neka budu
// privatne, a njihova vrijednost od 0 do 255.
// U definiranju klase ExtendedCircle obvezno koristite mehanizam 
// nasljedjivanja, tako da klasa ExtendedCircle nasljedjuje klasu Circle.
// Za klasu ExtendedCircle definirajte:
//  a) default konstruktor, koji postavlja clanove na nulu
//  b) operator = 
//  c) pristupne funkcije za nove clanove.
//
// U main funkciji deklarirajte jedan objekt klase ExtendedCircle i 
// sa tipkovnice ucitajte vrijednosti clanskih varijabli.
// Potom deklarirajte jos jedan objekt klase ExtendedCircle
// i iskoristite operator = za postaviti ga na vrijednost prethodnog objekta.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
using namespace std;

class Circle {
public:
    Circle() { m_radius = 0; }
    void SetRadius(int r) { if (r >= 0) m_radius = r; };
    int GetRadius() { return m_radius; };

protected:
    int m_radius;
};

class ExtendedCircle : public Circle {
    int m_color;
    int m_thickness;
public:
    ExtendedCircle();
    void SetColor(int);
    int GetColor();
    void SetThickness(int);
    int GetThickness();

    ExtendedCircle& operator=(const ExtendedCircle&);
};

ExtendedCircle::ExtendedCircle() {
    m_color = 0;
    m_thickness = 0;
}

void ExtendedCircle::SetColor(int temp) {
    if (temp >= 0 && temp <= 255) {
        m_color = temp;
    }
}

int ExtendedCircle::GetColor() {
    return m_color;
}

void ExtendedCircle::SetThickness(int temp) {
    if (temp >= 0 && temp <= 255) {
        m_thickness = temp;
    }
}

int ExtendedCircle::GetThickness() {
    return m_thickness;
}

ExtendedCircle& ExtendedCircle:: operator=(const ExtendedCircle& temp) {
    m_radius = temp.m_radius;
    m_color = temp.m_color;
    m_thickness = temp.m_thickness;

    return *this;
}

int main() {
    ExtendedCircle ec;
    int col, thic, rad;

    cout << "Unesi boju, debljinu i radijus: " << endl;
    cin >> col >> thic >> rad;

    ec.SetColor(col);
    ec.SetThickness(thic);
    ec.SetRadius(rad);

    cout << "Boja: " << ec.GetColor() << "\nDebljina: " << ec.GetThickness() << "\nRadijus: " << ec.GetRadius() << endl;
    cout << endl;

    ExtendedCircle ec1;
    ec1 = ec;

    cout << "Boja: " << ec1.GetColor() << "\nDebljina: " << ec1.GetThickness() << "\nRadijus: " << ec1.GetRadius() << endl;

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {4.}ZADATAK:
//
//
// Napisite genericku funkciju za odredivanje maksimalne vrijednosti 
// imena max(). Funkcija neka bude napisana u obliku predloska, tako 
// da se moze specijalizirati za razne tipove varijabli. 
// Funkcija neka prima tri argumenta, a neka vraca najveci 
// od njih. 
// U main funkciji upotrebite funkciju max() dva puta, jedan put za 
// varijable tipa double, drug put za int.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...


#include<iostream>
using namespace std;

template <class T> T max(T a, T b, T c) {
    T x;

    x = a > b ? a : b;
    x = x > c ? x : c;

    return x;
}



int main() {

    int i, j, k;
    double p, r, s;

    cout << "Unesi tri int vrijenosti: " << endl;
    cin >> i >> j >> k;
    cout << "Max je: " << max(i, j, k) << endl;

    cout << "Unesi tri double vrijenosti: " << endl;
    cin >> p >> r >> s;
    cout << "Max je: " << max(p, r, s) << endl;

    return 0;
}




/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {5.}ZADATAK:
//
//
// Napisite funkciju, kojom se iz jednog vektora V formiraju dva vektora: 
// V1 treba sadrzavati neparne, a vektor V2 parne elemente vektora.
// U funkciji vektore V1 i V2 sortirajte pomocu STL funkcije sort().
// Napisite main() funkciju sa primjerom koristenja funkcije Razdijeli_vektor().
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include <vector>
#include<algorithm>
using namespace std;

typedef vector<int> Vec;

void Razdijeli_vektor(Vec& V, Vec& V1, Vec& V2) {
    vector<int>::iterator iter;
    for (iter = V.begin(); iter != V.end(); iter++) {
        if (*iter % 2 == 0) {
            V1.push_back(*iter);
        }
        else {
            V2.push_back(*iter);
        }

        sort(V1.begin(), V1.end());
        sort(V2.begin(), V2.end());
    }
}

int main() {

    Vec a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 2, 31, 48, 848, 222,  22,  2, 46, 768, 78, 42, 2121, 1, 355 };
    Vec b, c;

    Razdijeli_vektor(a, b, c);

    cout << "Prvi vektor: " << endl;
    for (int i = 0; i < b.size(); i++)
    {
        cout << b[i] << " ";
    }

    cout << endl;
    cout << "Drugi vektor:" << endl;

    for (int i = 0; i < c.size(); i++)
    {
        cout << c[i] << " ";
    }

    cout << endl;

    return 0;
}




/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

                    /*19-2*/                                    /*19-2*/
                        /*19-2*/                            /*19-2*/
                            /*19-2*/                    /*19-2*/
                                /*19-2*/            /*19-2*/
                                    /*19-2*/    /*19-2*/
                                         /*19-2*/



                                        /*ISTI KAO 17-2*/

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

                    /*20-1*/                                    /*20-1*/
                        /*20-1*/                             /*20-1*/
                            /*20-1*/                     /*20-1*/
                                /*20-1*/             /*20-1*/
                                    /*20-1*/     /*20-1*/
                                          /*20-1*/


// {1.}ZADATAK:
//
//
// Deklarirana je klasa Adresa koja sadrzi ime i adresu osobe.
// Nasljedjivanjem od klase Adresa napravite klasu Tekuci koja
// sadrzi podatke o tekucem racunu osobe.
// Klasa Tekuci neka sadrzi jos jednu dodatnu varijablu imena
// IBAN tipa string. Varijabla IBAN neka bude privatna varijabla,
// koja mora biti duzine 21 znaka, a prva dva znaka trebaju biti "HR".
// Za klasu Tekuci definirajte:
// Definirajte:
//  a)	konstruktor, kojim se IBAN inicijalizira na prazan string
//	b)  set i get funkcije za varijablu IBAN.
//  b)	kopirni konstruktor
// U main funkciji napisite primjer koristenja klase Tekuci i
// svih njenih funkcija.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include<string>
using namespace std;

class Adresa {
public:
    string ime;
    string ulica;
    string grad;

    Adresa() { ime = ulica = grad = ""; }
    Adresa(const Adresa& temp) {
        ime = temp.ime;
        ulica = temp.ulica;
        grad = temp.grad;
    }
};

class Tekuci :public Adresa {
    string IBAN;
public:
    Tekuci();
    Tekuci(const Tekuci&);
    void SetIban(string);
    string GetIban();
};

Tekuci::Tekuci() {
    string IBAN = " ";
}

Tekuci::Tekuci(const Tekuci& temp) {
    IBAN = temp.IBAN;
    ime = temp.ime;
    ulica = temp.ulica;
    grad = temp.grad;
}

void Tekuci::SetIban(string a) {
    if ((a[0] == 'H') && (a[1] == 'R') && (a.size() == 21)) {
        IBAN = a;
    }
}

string Tekuci::GetIban() {
    return IBAN;
}


int main() {

    Tekuci Karlo;
    string ime;
    string ulica;
    string grad;
    string IBAN;

    cout << "Upisite: " << endl;
    cout << "Ime: " << endl;
    cout << "Ulica :" << endl;
    cout << "Grad:" << endl;

    cout << "IBAN: " << endl;
    cin >> IBAN;
    Karlo.SetIban(IBAN);
    cout << Karlo.GetIban() << endl;


    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {2.}ZADATAK:
//
//
// Definirana je klasa Prekidac. Izradite:
// - konstruktor klase, kojim se prekidac postavlja u 
//   ukljuceno stanje
// - funkcije Ukljuci() i Iskljuci()
// - funkciju Ukljucen() koja vraca true ako je prekidac 
//   ukljucen, inace vraca false
// - operator != 
// - operator >> koji neka postavlja prekidac u stanje
//   ukljucen ako sa toka procita string "on", u stanje 
//   iskljucen ako sa toka procita string "off", a inace
//   ostavlja stanje nepromijenjeno
//
// Napisite funkciju main(), te u njoj iskoristite kompletnu
// funkcionalnost klase Prekidac.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include <iostream>
#include <string>
using namespace std;

class  Prekidac {
    bool m_ukljucen;
public:
    Prekidac();
    void Ukljuci();
    void Iskljuci();
    bool Ukljucen();

    bool operator!=(const Prekidac&);
};

Prekidac::Prekidac() { 
    m_ukljucen = true; 
}

void Prekidac::Ukljuci() { 
    m_ukljucen = true; 
}

void Prekidac::Iskljuci() { 
    m_ukljucen = false; 
}

bool Prekidac::Ukljucen() {

    if (m_ukljucen == true) {
        return true;
    }
    else {
        return false;
    }
}

bool Prekidac::operator!=(const Prekidac& obj) {
    if (m_ukljucen != obj.m_ukljucen) {
        return true;
    }
    else {
        return false;
    }
}

istream& operator>>(istream& in, Prekidac& temp) {
    string stanje;

    in >> stanje;

    if (stanje == "on" || stanje == "1" || stanje == "true") {
        temp.Ukljuci();
    }
    else if (stanje == "off" || stanje == "0" || stanje == "false") {
        temp.Iskljuci();
    }

    return in;
}

int main() {
    Prekidac obj1, obj2;

    cin >> obj1;
    cin >> obj2;

    cout << endl;

    if (obj1 != obj2) {

        cout << "Razlicita stanja";
    }
    else {
        cout << "Ista stanja";
    }

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {3.}ZADATAK:
//
//
// Napisite funkciju, kojom se iz jednog vektora V formiraju dva vektora: 
// V1 treba sadrzavati neparne, a vektor V2 parne elemente vektora.
// U funkciji vektore V1 i V2 sortirajte pomocu STL funkcije sort().
// Napisite main() funkciju sa primjerom koristenja funkcije Razdijeli_vektor().
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


typedef vector<int> Vec;

void Razdijeli_vektor(Vec& V, Vec& V1, Vec& V2) {
    vector<int>::iterator iter;

    for (iter = V.begin(); iter != V.end(); iter++) {
        if (*iter % 2 == 0) {
            V1.push_back(*iter);
        }
        else {
            V2.push_back(*iter);
        }
    }

    sort(V1.begin(), V1.end());
    sort(V2.begin(), V2.end());
}

int main() {

    Vec V = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
    Vec A, B;

    Razdijeli_vektor(V, A, B);

    cout << "1. Vektor: " << endl;
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }

    cout << endl;

    cout << "2. Vektor: " << endl;
    for (int i = 0; i < B.size(); i++) {
        cout << B[i] << " ";
    }

    cout << endl;

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {4.}ZADATAK:
//
//
// Napisite program kojim se sadrzaj jedne tekstualne datoteke 
// kopira u drugu, na nacin da se u ciljanu datoteku kopiraju samo
// parni redovi.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main() {

    ifstream ulaz;
    ofstream izlaz;

    ulaz.open("ulaz.txt");
    izlaz.open("copy2.txt");

    if (!ulaz)
        cout << "fail" << endl;
    if (!izlaz)
        cout << "fail" << endl;

    char c;


    while (ulaz.get(c)) {
        izlaz.put(c);
    }

    ulaz.close();
    izlaz.close();

    return 0;
}



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


                    /*21-2*/                                    /*21-2*/
                        /*21-2*/                            /*21-2*/
                            /*21-2*/                     /*21-2*/
                                /*21-2*/             /*21-2*/
                                    /*21-2*/     /*21-2*/
                                          /*21-2*/


// {2.}ZADATAK:
//
//
// Napisite program kojim se analizira sadrzaj neke tekstualne datoteke. Program izvjestava: 
// a)	koliko je malih slova (a-z)
// b)	koliko je velikih slova (A-Z)
// c)	koliko je znamenki (0-9)
//
// zapisano u toj datoteci.
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include<fstream>
using namespace std;

int main() {

    ifstream ulaz;

    ulaz.open("ulaz.txt");
    if (!ulaz) {
        cout << "Fail!" << endl;
        return 1;
    }

    char c;
    int m_slova = 0;
    int v_slova = 0;
    int znam = 0;

    while (ulaz.get(c)) {
        if (c >= 'a' && c <= 'z') {
            m_slova++;
        }
        else if (c >= 'A' && c <= 'Z') {
            v_slova++;
        }
        else if (c >= '0' && c <= '9') {
            znam++;
        }
    }

    cout << "Broj malih slova: " << m_slova << endl;
    cout << "Broj velikih slova: " << v_slova << endl;
    cout << "Broj znamenki: " << znam << endl;


    return 0;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


// {3.}ZADATAK:
//
// Preradite postojeci program na nacin da:
//   - temeljna klasa bude cista apstraktna klasa
//   - objekti u glavnom programu budu ubaceni u jedan vektor
// 
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...
#include <iostream>
#include<vector>
using namespace std;

class A {
public:
    virtual void disp() = 0;
};

class B : public A {
public:
    void disp() {
        cout << "Sub Class B Function" << endl;
    }
};
class C : public A {
public:
    void disp() {
        cout << "Sub Class C Function" << endl;
    }
};
class D : public A {
public:
    void disp() {
        cout << "Sub Class D Function" << endl;
    }
};
int main() {

    vector<A*>Vec;

    Vec.push_back(new B());
    Vec.push_back(new C());
    Vec.push_back(new D());
    Vec.push_back(new B());

    for (int i = 0; i < Vec.size(); i++) {
        Vec[i]->disp();
    }

    return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

// {4.}ZADATAK:
//
//
// Napisite genericku funkciju za odredjivanje maksimalne vrijednosti 
// imena max(). Funkcija neka bude napisana u obliku predloska, tako 
// da se moze specijalizirati za razne tipove varijabli. 
// Funkcija neka prima tri argumenta, a neka vraca najveci 
// od njih. 
// U main funkciji upotrebite funkciju max() dva puta, jedan put za 
// varijable tipa double, drug put za int.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
using namespace std;

template <class T> T max(T a, T b, T c) {
    int x;

    x = a > b ? a : b;
    x = x > c ? x : c;

    return x;
}

int main() {

    int i, j, k;
    double p, r, s;

    cout << "Unesi tri int vrijenosti: " << endl;
    cin >> i >> j >> k;
    cout << "Max je: " << max(i, j, k) << endl;

    cout << "Unesi tri double vrijenosti: " << endl;
    cin >> p >> r >> s;
    cout << "Max je: " << max(p, r, s) << endl;

    return 0;
}






/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/



// {5.}ZADATAK:
//
//
// Napisite funkciju Min2Vector koja vraca najmanji element iz
// vektora V1 i V2, koje su argumenti funkcije. 
// Trazenje minimalnog elementa u pojedinom vektoru napravite
// korsiteci funkciju STL biblioteke algoritama.
// U glavnom programu isprobajte funkciju.
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Ne mijenjajte nista iznad ove linije!

// ukljucite potrebne biblioteke...

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int Min2Vector(vector<int>& V1, vector<int>& V2) {
    vector<int>::iterator iter;
    int min;

    iter = min_element(V1.begin(), V1.end());
    int A = *iter;

    iter = min_element(V2.begin(), V2.end());
    int B = *iter;

    min = A < B ? A : B;
    return min;    
}

int main() {
    
    vector<int> vec1, vec2;
   
    int vec1_size, vec2_size, el, min;

    cout << "Unesi velicinu 1. vektora: ";
    cin >> vec1_size;

    cout << "Unesi velicinu 2. vektora: ";
    cin >> vec2_size;

    cout << "Unesi sadrzaj vektora v1: ";
    for (int i = 0; i < vec1_size; i++) {

        cin >> el;
        vec1.push_back(el);
    }

    cout << "Unesi sadrzaj vektora v2: ";
    for (int i = 0; i < vec2_size; i++) {

        cin >> el;
        vec2.push_back(el);
    }

    min = Min2Vector(vec1, vec2);

    cout << "Minimalni element: " << min << endl;

    return 0;
}





