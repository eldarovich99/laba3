#include <iostream>
#include <auditory_map.h>
#include <cassert>
using namespace std;

int main()
{
    AuditoryMap <int, char>map;
    map.insert(401, 'a');
    map.insert(402, 'b');
    assert(map.contains(401) && map[401]=='a');      //inserting
    assert(map.contains(402));
    assert(!map.contains(808));     //unexisted key

    map.clear();
    assert(map.size()==0);      //clear function
    map.insert(403, 'c');
    map.insert(404, 'd');
    map.insert(405, 'e');
    assert(map.contains(405));
    map.deleteKey(404);
    assert(!map.contains(404));     // deleting single key
    return 0;
}
