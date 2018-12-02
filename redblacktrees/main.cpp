#include <iostream>
#include <auditory_map.h>
using namespace std;

int main()
{
    AuditoryMap <int, char>map;
    map.insert(401, 'a');
    map.insert(402, 'b');
    map.insert(403, 'c');
    map.insert(404, 'd');
    map.insert(405, 'e');
    map.displayInfo();
    AuditoryMap<int, char>::iterator i1 = map.begin();
    AuditoryMap<int, char>::iterator i2 = map.end();
    bool flag = (*i1).value;
    cout << (*i1).value << endl;
    cout << (*i1.next()).value << endl;
    cout << (*i1.next()).value << endl;
    cout << (*i1.next()).value << endl;
    cout << (*i2).value << endl;
    return 0;
}
