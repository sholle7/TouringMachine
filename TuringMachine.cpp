#include <iostream>

#include <vector>

#include <string>

using namespace std;
// konstanta koja predstavlja blanko znak 
const int b = -1;
// IZVRSAVANJE SLEDBENIKA FUNKCIJE 
void ispisTrake(vector < int > & );
void ispisStanja2(vector < int > & );
// cilj funkcije je da zapis x u obliku b1^(x+1)b, prevede u b1^(x+2)b, njegovog sledbenika
void nadjiSledbenik(int x, vector < int > & TM) {
  TM.clear();
  // azbuka Tjuringove masine je S={b,1} gde je b blanko znak
  TM.push_back(b);
  do {
    TM.push_back(1);
  } while (x--);
  TM.push_back(b);
  // ispis broja
  cout << "Forma broja x u Tjuringovoj masini: " << endl;
  ispisTrake(TM);
  ispisStanja2(TM);
}
void ispisTrake(vector < int > & TM) {
  for (int i: TM) {
    if (i == -1)
      cout << "b";
    else
      cout << i;
  }
  cout << endl;
}
void ispisStanja2(vector < int > & TM) {
  string stanje = "q0";
  int br = 0;
  bool nadjena = false;
  for (int i: TM) {
    if (i == 1 && !nadjena) {
      nadjena = true;
      cout << "f(" << stanje << ", 1) = (q1, 1,+1)" << endl;;
    }
    if (i == 1 && nadjena && stanje == "q0") {
      stanje = "q1";
      cout << "f(" << stanje << ", 1) = (q1, 1, +1)" << endl;;
    }
    if (stanje == "q1" && i == b) {
      cout << "f(" << stanje << ", b) = (q+, 1, +1)" << endl;;
      TM[br] = 1;
    }
    br++;
  }
  TM.push_back(b);
  cout << "Forma sledbenika broja x:" << endl;
  ispisTrake(TM);
}
// IZVRSAVANJE NULE FUNKCIJE
void ispisStanja1(vector < int > & TM) {
  string stanje = "q0";
  int br = 0;
  bool nadjena = false;
  for (int i: TM) {
    if (i == 1 && !nadjena) {
      nadjena = true;
      cout << "f(" << stanje << ", 1) = (q1, 1,+1)" << endl;;
    }
    if (i == 1 && nadjena) {
      if (stanje == "q0") {
        stanje = "q1";
        cout << "f(" << stanje << ", 1) = (q1, b, +1)" << endl;
      } else
        TM[br] = b;
    }
    if (stanje == "q1" && i == b) {
      cout << "f(" << stanje << ", b) = (q+, b, +1)" << endl;;
    }
    br++;
  }
  cout << "Forma nule broja x:" << endl;
  ispisTrake(TM);
}
// cilj funkcije je da zapis x u obliku b1^(x+1)b, prevede u zapis b1b (nula funkcije) 
void nadjiNulu(int x, vector<int>& TM) {
TM.clear();
// azbuka Tjuringove masine je S={b,1} gde je b blanko znak
TM.push_back(b);
do {
  TM.push_back(1);
} while (x--);
TM.push_back(b);
// ispis broja 
cout << "Forma broja x u Tjuringovoj masini: " << endl; ispisTrake(TM);
ispisStanja1(TM);
}
// IZVRSAVANJE PRVE PROJEKCIJE 
void ispisStanja3(vector<int>& TM) {
string stanje = "q0";
int br = 0;
bool nadjena = false;
bool q2 = false;
for (int i: TM) {
  if (i == 1 && !nadjena) {
    nadjena = true;
    cout << "f(" << stanje << ", 1) = (q1, 1,+1)" << endl;;
  }
  if (i == 1 && nadjena) {
    if (stanje == "q0") {
      stanje = "q1";
      cout << "f(" << stanje << ", 1) = (q1, 1, +1)" << endl;
    }
  }
  if (stanje == "q1" && i == 0) {
    cout << "f(" << stanje << ", 0) = (q2, b, +1)" << endl;
    stanje = "q2";
    TM[br] = b;
  }
  if (stanje == "q2" && i == 1) {
    if (q2 == false) {
      q2 = true;
      cout << "f(" << stanje << ", 1) = (q2, b, +1)" << endl;
    }
    TM[br] = b;
  }
  if (stanje == "q2" && i == b) {
    cout << "f(" << stanje << ", b) = (q+, b, +1)" << endl;;
  }
  br++;
}
cout << "Forma rezultata:" << endl;
ispisTrake(TM);
}
// cilj funkcije je da zapis x u obliku b1^(x+1)01^(y+1)b, prevede u zapis b1^(x+1)b
void nadjiProjekciju(int x,int y,vector<int>&TM){
TM.clear();
// azbuka Tjuringove masine je S={b,0,1} gde je b blanko znak
TM.push_back(b);
do {
  TM.push_back(1);
} while (x--);
TM.push_back(0);
do {
  TM.push_back(1);
} while (y--);
TM.push_back(b); // ispis broja 
cout << "Forma uredjenog para (x,y) u Tjuringovoj masini: " << endl;
ispisTrake(TM);
ispisStanja3(TM);
}
// IZVRSAVANJE ZBIRA FUNCKIJE X+Y
void ispisStanja4(vector < int > & TM) {
  string stanje = "q0";
  int br = 0, p = 0;
  bool q2 = false;
  while (stanje != "q+") {
    if (br == 0) {
      br++;
    }
    if (TM[br] == 1 && stanje == "q0") {
      cout << "f(" << stanje << ", 1) = (q1, 1,+1)" << endl;
      stanje = "q1";
      br++;
      continue;
    }
    if (TM[br] == 1 && stanje == "q1") {
      if (p == 0) {
        cout << "f(" << stanje << ", 1) = (q1, 1, +1)" << endl;
        p++;
      }
      br++;
      continue;
    }
    if (stanje == "q1" && TM[br] == 0) {
      cout << "f(" << stanje << ", 0) = (q2, 1, +1)" << endl;
      stanje = "q2";
      TM[br] = 1;
      br++;
      continue;
    }
    if (stanje == "q2" && TM[br] == 1) {
      if (q2 == false) {
        q2 = true;
        cout << "f(" << stanje << ", 1) = (q2, 1, +1)" << endl;
      }
      br++;
      continue;
    }
    if (stanje == "q2" && TM[br] == b) {
      cout << "f(" << stanje << ", b) = (q3, b, -1)" << endl;
      stanje = "q3";
      br--;
      continue;
    }
    if (stanje == "q3" && TM[br] == 1) {
      cout << "f(" << stanje << ", 1) = (q4, b, -1)" << endl;
      stanje = "q4";
      TM[br] = b;
      br--;
      continue;
    }
    if (stanje == "q4" && TM[br] == 1) {
      cout << "f(" << stanje << ", b) = (q+, b, +1)" << endl;
      TM[br] = b;
      stanje = "q+";
      br--;
      continue;
    }
  }
  cout << "Forma rezultata:" << endl;
  ispisTrake(TM);
}
// cilj funkcije je da zapis u obliku b1^(x+1)01^(y+1)b prevede u zapis b1^(x+y+1)b 
void nadjiZbir(int x, int y, vector<int>& TM) {
TM.clear();
// azbuka Tjuringove masine je S={b,0,1} gde je b blanko znak
TM.push_back(b);
do {
  TM.push_back(1);
} while (x--);
TM.push_back(0);
do {
  TM.push_back(1);
} while (y--);
TM.push_back(b); // ispis broja 
cout << "Forma uredjenog para (x,y) u Tjuringovoj masini: " << endl;
ispisTrake(TM);
ispisStanja4(TM);
}
int main() {
  int x, y, rb;
  vector < int > TM;
  // vektor celih brojeva(integera) koji predstavlja traku za zapisivanje tjuringove masine
  while (1) {
    do {
      cout << "Unesi zeljeni broj koji cete odbradjivati u Tjuringovoj masini: " << endl;
      cin >> x;
    } while (x < 0);
    cout << "Unesite redni broj algoritma koji zelite da izvrsite:" << endl;
    cout << "1) Nula funkcije;" << endl;
    cout << "2) Sledbenik funkcije;" << endl;
    cout << "3) Racuna prvu projekciju uredjenog para(x, y);" << endl;
    cout << "4) Racuna funkciju zbira x+y;" << endl;
    cout << "5) Kraj rada;" << endl;
    cin >> rb;
    switch (rb) {
    case 1:
      nadjiNulu(x, TM);
      break;
    case 2:
      nadjiSledbenik(x, TM);
      break;
    case 3:
      do {
        cout << "Unesi y:" << endl;
        cin >> y;
      } while (y < 0);
      cout << "(x,y) = (" << x << "," << y << ") " << endl;
      nadjiProjekciju(x, y, TM);
      break;
    case 4:
      do {
        cout << "Unesi y:" << endl;
        cin >> y;
      } while (y < 0);
      cout << "(x,y) = (" << x << "," << y << ") " << endl;
      nadjiZbir(x, y, TM);
      break;
    case 5:
      exit(1);
    default:
      cout << "Ne postoji trazena opcija!!" << endl;
    }
  }
  return 0;
}
