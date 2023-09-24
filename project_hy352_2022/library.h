#include <iostream>
#include <string.h>
#include <cassert>
#include <vector>

using namespace std;
// #define DEBUG(x) ;cout << x << endl;   
#define ERROR(x) ;cout <<"ERROR, "<< x << endl;    
#define DEBUG(x) ;  



class VALUE;
class KEY;

class OBJECT
{
public:
    vector<pair<KEY,VALUE*>> list;
    OBJECT();
    OBJECT(initializer_list<vector<pair<KEY,VALUE>>> _list);


    void print();


    // in order to prevent call constructor for other classes
    template<class T> OBJECT(T) = delete;
};


class ARRAY
{
public:
    vector<VALUE*> list;
    ARRAY();


    ARRAY operator[](vector<VALUE> list);
    ARRAY operator[](VALUE value);

    void print();

    friend class JSON;    
};



class KEY
{
public:
    string name;
    KEY(string _name);


    vector<pair<KEY,VALUE>> operator=(VALUE value);

    friend void PrintKey(KEY key);
    template<class T> KEY(T) = delete;
};



class CLASSNULL{};



class NUMBER{

public:
    string str_type;
    union type{
        int inum;
        double dnum;
    }_type;
    NUMBER(int);
    NUMBER(double);
    template<class T> NUMBER(T) = delete;

    friend class VALUE;
};


class VALUE
{
public:
    string* str_type;
    ARRAY* _array;
    OBJECT* _object;
    string* _string;
    int* _inumber;
    double* _dnumber;
    bool _bool;

    VALUE();
    VALUE(const VALUE& _value);
    VALUE(ARRAY array);
    VALUE(OBJECT object);
    VALUE(string str);
    VALUE(NUMBER number);
    VALUE(bool flag);
    VALUE(CLASSNULL x);

    VALUE operator<<(ARRAY array);
    VALUE operator<<(OBJECT object);
    //  overload it as friend function
    friend vector<VALUE> operator,(vector<VALUE> list, VALUE value);
    vector<VALUE> operator,(VALUE value);
    VALUE& operator[](int index);
    VALUE& operator[](const char*);
    friend void operator*=(VALUE& val1 ,VALUE val2);




    //  (+, -, *, /, %) and (>, >=, <, <=) operators


    VALUE& operator+(VALUE _value);
    VALUE& operator-(VALUE _value);
    VALUE& operator*(VALUE _value);
    VALUE& operator/(VALUE _value);
    VALUE& operator%(VALUE _value);
    VALUE operator>(VALUE _value);
    VALUE operator>=(VALUE _value);
    VALUE operator<(VALUE _value);
    VALUE operator<=(VALUE _value);


    // (&&, ||, !) and (==, !=) operators
    VALUE operator&&(VALUE _value);
    VALUE operator||(VALUE _value);
    VALUE operator!();
    VALUE operator==(VALUE _value);
    VALUE operator!=(VALUE _value);









    void print();

    template<class T> VALUE(T) = delete;
};




class JSON
{
public:
    VALUE *value;

    JSON();

    JSON operator=(VALUE _value);
    void operator*=(VALUE _value);

    VALUE& operator[](int index);
    VALUE& operator[](const char* key_name);

    friend JSON operator,(JSON json ,VALUE _value);

    void print();


    //  in order to implement syntax and the compiler throw errors 
    template<class T> void operator=(T) = delete;
    friend class SET;
};




// this class made beacause value "operator," value was previsously declared
class APPEND{
public:

    VALUE *val;
    APPEND();
    APPEND(VALUE &_value);


    friend JSON& operator+(JSON &json,APPEND ap);
    friend APPEND operator+(VALUE &value,APPEND ap);
    APPEND& operator,(VALUE _value);

};







class ERASE{
public:
    JSON json;
    ERASE(){}

    friend void operator+(ERASE er , JSON &json){
        json.value = NULL;
    }

    friend void operator+(ERASE er , VALUE &value){
        value.str_type = NULL;
    }


};





//=============== PRINT JSON VARIABLES AND VALUES ===============


class PRINT{

public:

    PRINT();

    static void PrintValue(VALUE *value);

    PRINT operator,(VALUE _value);
    PRINT operator,(JSON json);
    PRINT operator,(bool _bool);
    PRINT operator,(string str);
    PRINT operator,(int size);    

};





// =========== FUNCTIONS ============

int SizeOf(JSON json);
int SizeOf(VALUE value);
bool IsEmpty(JSON json);
bool IsEmpty(VALUE value);
string TypeOf(JSON json);
string TypeOf(VALUE value);
bool HasKey(JSON json, string key);
bool HasKey(VALUE value, string key);


