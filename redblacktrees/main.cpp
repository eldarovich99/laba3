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
    Iterator<int, char> i1 = map.begin();
    Iterator<int, char> i2 = map.end();
    //bool flag = (*i1).value;
    cout << i1.value();
    cout << i1.next().getKey() << endl;
    cout << i1.next().getKey()<< endl;
    cout << i1.next().getKey() << endl;
    cout << i1.next().getKey() << endl;
    cout << i2.getKey() << endl;
    cout << map.size();
    return 0;
}
