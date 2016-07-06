#include <iostream>
#include <fstream>
#include "MyCache.h"

using namespace std;

int main()
{
    //ofstream ofstrm("t.txt", ofstream::binary);
    ifstream ifstrm("t.txt", ifstream::binary);

    MyCache t;
    t.init();
    t.setsize(524288);

    string bs;
    while (ifstrm >> bs) {
        if (t.write(bs.c_str(), bs.size()) < 0) {
            cout << "full!" << endl;
            return -1;
        }
        cout << bs;
    }
    cout << endl;

    char s[700];
    size_t cnt = t.read(s, sizeof(s));
    cout << cnt << endl;
    s[cnt] = '\0';
    cout << s << endl;

    cnt = t.read(s, sizeof(s));
    cout << cnt << endl;
    s[cnt] = '\0';
    cout << s << endl;
    return 0;
}
