#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "A100570";
// Số test kiểm tra
const int NTEST = 1000;

// Viết lại hàm random để sử dụng cho thuận tiện. Hàm random này sinh ngẫu nhiên số trong phạm vi long long, số sinh ra >= l và <= h.
long long Rand(long long l, long long h) {
    return l + rand() * 1LL * rand() % (h - l + 1);
}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".inp").c_str());
        int n = Rand(10, 30);
        int m = Rand(10, 20); 
        inp << n << " "<< m << '\n';
        for(int i = 0; i < n; ++i) {
            inp << Rand(1, 60) << " ";
        }
        inp << '\n';
        for(int i=0; i<m; ++i){
            inp << Rand(1,n) << '\n'; 
        }
        inp.close();
        // Nếu dùng Linux thì "./" + Tên chương trình
        system((NAME + ".exe").c_str());
        system((NAME + "_trau.exe").c_str());
        // Nếu dùng linux thì thay fc bằng diff
        if (system(("fc " + NAME + ".out" + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}