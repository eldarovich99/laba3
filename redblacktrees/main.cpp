#include <iostream>
#include <auditory_map.h>
#include <cassert>
using namespace std;

int main()
{
    AuditoryMap <int, char>map;
    assert(map.size()==0);      //default constructor
    map.insert(401, 'a');
    assert(map.size()==1);
    map.insert(401, 'a');       //adding existing key
    assert(map.size()==1);
    assert(map.contains(401) && map[401]=='a');      //inserting

    map.insert(402, 'b');
    assert(map.contains(402));
    Iterator<int,char> i = map.begin();         //iterator
    assert(i.value()==map[401]);
    assert(i.next().value()==map[402]);
    assert(!map.contains(808));     //unexisted key

    map.insert(403, 'c');
    map.insert(404, 'd');
    map.insert(405, 'e');
    map.insert(412, 'a');

    AuditoryMap<int, char> map3 = AuditoryMap<int,char>(map);
    assert(map==map3);      // copying constructor
    map3.insert(802, 'g');
    assert(!(map==map3));

    int prevSize = map.size();
    map.deleteKey(900);     //deleting unexisted key
    assert(prevSize == map.size());

    map.clear();    //clear function
    assert(!map.contains(404));     // check deleted key
    AuditoryMap<int, char> map4;
    assert(map==map4);

    cin >> map3;
    cout << map3;


    /*assert(map.size()==0);
    map.insert(403, 'c');
    map.insert(404, 'd');
    map.insert(405, 'e');
    assert(map.contains(405));
    map.deleteKey(404);
    AuditoryMap<int, char> map2 = AuditoryMap<int,char>(map);
    Iterator<int,char> i2 = map.end();
    assert(i2.value()==map[405]);
    //cin >> map;
    cout << map;
    cout << map2;*/
    return 0;
}
