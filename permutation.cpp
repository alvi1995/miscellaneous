#include <iostream>
#include <cstring>

using namespace std;
typedef unsigned int ui;
ui list = 0;

struct info
{
    char alphabet = ' ';
    ui repetence = 0;
};

const ui property_string_object(const char* c, struct info* l, ui n)
{
    ui index = 0;
    l[index].alphabet = c[0];
    for (ui i = 0; i < n; i++)
    {
        if (l[index].alphabet == c[i])
        {
            l[index].repetence++;
        }
        else
        {
            index++;
            l[index].alphabet = c[i];
            l[index].repetence++;
        }
        
    }
    return index;
}

void string_to_cstring(string object, char* uo, ui sz)
{
    for (ui i = 0; i < sz-1; i++)
    {
        uo[i] = object[i];
    }
    uo[sz-1] = '\0';
}

void view(struct info* w, ui n)
{
    for (ui i = 0; i < n; i++)
    {
        cout << i << ":" << w[i].alphabet << w[i].repetence << endl;
    }
}

ui index(struct info* s, char c, ui cl)
{
    ui i = 0;
    for ( ; i < cl; i++)
    {
        if (c == s[i].alphabet)
        {
            break;
        }
    }
    return i;
}

bool availibility(struct info* s, char c, ui cl)
{
    bool available = false;
    for (ui i = 0; i < cl; i++)
    {
        if (s[i].alphabet == c && s[i].repetence > 0)
        {
            available = true;
            break;
        }
    }
    return available;
}

void permutation(struct info* s, const char* c, string str, ui cl, ui cs)
{
    if (str.size() == cs)
    {
        list++;
        cout << list << ":" << str << endl;
    }
    else
    {
        for (ui i = 0; i < cl; i++)
        {
            char temp = c[i];
            ui source_index = 0;
            if (availibility(s,temp,cl))
            {
                source_index = index(s, s[i].alphabet, cl);
                str.append(1,temp);
                s[source_index].repetence--;
                permutation(s,c,str,cl,cs);
                str.pop_back();
                s[source_index].repetence++;
            }
        }
    }
}

int main(void)
{
    string example = "AAABBCCDDE";
    string object_with_unique_letters = "";

    struct info* l = new struct info[example.size()];
    const ui total = property_string_object(example.c_str(), l, example.size());
    struct info* letter = new struct info[total+1];
    for (ui i = 0; i < total+1; i++)
    {
        letter[i] = { l[i].alphabet, l[i].repetence };
        object_with_unique_letters += letter[i].alphabet;
    }
    delete []l;
    //view(letter, total+1);
    char* c_string_unique_letters = new char[example.size()+1];
    string_to_cstring(object_with_unique_letters,c_string_unique_letters,object_with_unique_letters.size()+1);
    
    string out = "";

    permutation(letter, object_with_unique_letters.c_str(), "", total+1, example.size());
    

    delete []letter;
    delete []c_string_unique_letters;

    return 0;
}
