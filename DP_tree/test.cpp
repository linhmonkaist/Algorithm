#include <bits/stdc++.h>
using namespace std;
int const t= 30; 
int const lim= 50; 

int main()
{
    ofstream inp("test.inp");
    inp << t << '\n';
    for (int i=0; i<t; i++){
        int n= rand()%20 +1; 
        int k= rand()%n + 1; 
        inp << n << ' '<< k << '\n';
        for (int j=0; j<n; j++){
            inp << int(rand()%lim) << ' ';
        }
        inp << '\n'; 
    }
    system("test_trau.exe");
    system("median.exe");
    ifstream test_out("test.ans");
    ifstream medi_out("test.out"); 
    string s, w; 
    for (int i=0; i<t; i++){
        getline(test_out, s);
        getline(medi_out, w);
        if (s.compare(w) != 0) {
            cout << "false at: "<< i << " s: "<< s << " w: "<< w;
            break;  
        }
    }
    test_out.close();
    medi_out.close();
    inp.close();
    return 0;
}