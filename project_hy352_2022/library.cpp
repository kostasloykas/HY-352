#include "library.h"



// ================== DEFINITION OF JSON VARIABLE =====================

ARRAY::ARRAY(){

}

ARRAY ARRAY:: operator[](vector<VALUE> list){
    for(auto i : list){
        this->list.push_back(new VALUE(i));
    }
    return *this;
}
ARRAY ARRAY:: operator[](VALUE value){
    list.push_back(new VALUE(value));
    return *this;
}

void ARRAY:: print(){
    bool print_something = false;

    // print VALUES
    for (auto i :list){
        if(i->str_type == NULL) continue;
        
        i->print();
        print_something = true;
        cout<<",";
    }

    if(!print_something){
        cout<< "Empty Array";
    }else{
        cout<<"\b \b";
    }
}


NUMBER::NUMBER(int num){
    str_type = "int";
    _type.inum = num;
}

NUMBER::NUMBER(double num){
    str_type = "double";
    _type.dnum = num;
}



VALUE::VALUE(){
    this->str_type = NULL;
    this->_array = NULL;
    this->_dnumber = NULL;
    this->_inumber = NULL;
    this->_object = NULL;
    this->_string = NULL;
}

VALUE::VALUE(const VALUE& _value){
    this->str_type = _value.str_type;
    this->_array = _value._array;
    this->_bool = _value._bool;
    this->_dnumber = _value._dnumber;
    this->_inumber = _value._inumber;
    this->_object = _value._object;
    this->_string = _value._string;
}


VALUE::VALUE(ARRAY array){
    this->_array = new ARRAY(array);             
    str_type = new string("array");
}

VALUE::VALUE(OBJECT object){
    this->_object = new OBJECT(object);             
    str_type = new string("object");
}

VALUE::VALUE(string str){
    this->_string = new string(str);             
    str_type = new string("string");
}

VALUE::VALUE(NUMBER number){
    if(number.str_type == "int"){
        this->_inumber = new int(number._type.inum);             
        str_type = new string("int");
    }else{
        this->_dnumber = new double(number._type.dnum);             
        str_type = new string("double");
    }
}


VALUE::VALUE(bool flag){
    this->_bool = flag;             
    str_type = new string("bool");
}

VALUE::VALUE(CLASSNULL x){
    str_type = new string("null");
}

VALUE VALUE:: operator<<(ARRAY array){
    return VALUE(array);
}


VALUE VALUE::operator<<(OBJECT object){
    return VALUE(object);
}



void VALUE:: print(){
    if(this->str_type == NULL) return;
    PRINT::PrintValue(this);
}


 // friend function of class VALUE
 vector<VALUE> operator,(vector<VALUE> list, VALUE value)
 {
    list.push_back(value);
    return list;
}


vector<VALUE> VALUE:: operator,(VALUE value){
    auto list = vector<VALUE>();
    list.push_back(*this);
    list.push_back(value);
    return list;
 }




JSON:: JSON(){
    this->value = NULL;
}

JSON JSON:: operator=(VALUE value){
    this->value = new VALUE(value);
    return *this;
}


 void JSON:: print(){
    if (this->value == NULL){
        cout<<"Empty Json";
    }else this->value->print();
}




OBJECT::OBJECT(){}



KEY::KEY(string _name){
    this->name = _name;
}


void PrintKey(KEY key){
    cout<<key.name<<":";
}

void OBJECT:: print(){
    bool print_something = false;
    for(auto i : this->list){
        // in case some key doesn't have value
        if(i.second->str_type == NULL)
            continue;
        print_something = true;
        PrintKey(i.first);
        cout << " ";
        if(*i.second->str_type == "string") cout<<"\""<<*i.second->_string<<"\" ";
        else PRINT::PrintValue(i.second);
        cout<<",";
    }
    
    if(!print_something)
        cout<< "Empty Object";
    else{
        // replace last character with space 
        // last character is ","
        cout<<"\b \b";
    }
}



vector<pair<KEY,VALUE>> KEY:: operator=(VALUE value){
    vector<pair<KEY,VALUE>> list = vector<pair<KEY,VALUE>>();
    list.push_back(pair<KEY,VALUE>(*this,value)); 
    return list;
}


OBJECT::OBJECT(initializer_list<vector<pair<KEY,VALUE>>> _list){

    this->list = vector<pair<KEY,VALUE*>>();

    // insert all pairs<key-value> in objects list
    for(auto i : _list)
        for(auto j : i){
            auto tmp_pair = pair<KEY,VALUE*>(j.first,new VALUE(j.second));
            this->list.push_back(tmp_pair);
        }

}








// ============= PROCCESSING OF JSON VARIABLE AND VALUES =================


void operator*=(VALUE& val1 ,VALUE val2){

    // assign value to value
    string value_type = *val2.str_type;
    if( value_type == "null"){
        val1.str_type = new string("null");
    }else if(value_type == "int"){
        val1._inumber = val2._inumber;
        val1.str_type = new string("int");
    }else if(value_type == "double"){
        val1._dnumber = val2._dnumber;
        val1.str_type = new string("double");
    }else if(value_type == "bool"){
        val1._bool = val2._bool;
        val1.str_type = new string("bool");
    }else if(value_type == "string"){
        val1._string = val2._string;
        val1.str_type = new string("string");
    }else if(value_type == "object"){
        val1._object = val2._object;
        val1.str_type = new string("object");
    }else if(value_type == "array"){
        val1._array = val2._array;
        val1.str_type = new string("array");
    }

}





void JSON:: operator*=(VALUE _value){
    this->operator=(_value);
}

VALUE& JSON::operator[](int index){
    string str_type = *this->value->str_type;
    if(str_type != "array"){
        cout<<"ERROR , indexing in some value which type isn't array"<<endl;
        exit(0);
    }
    auto list = this->value->_array->list;
    return *list.at(index);
}

VALUE& VALUE::operator[](int index){
    if(*this->str_type != "array"){
        cout<<"ERROR , indexing in some value which type isn't array"<<endl;
        exit(0);
    }
    auto list = this->_array->list;
    return *list.at(index);

}


VALUE& VALUE::operator[](const char* key_name){
    if(this->str_type == NULL){
        this->str_type = new string("object");
        this->_object = new OBJECT();
    }

    if(*this->str_type != "object"){
        cout<<"ERROR , indexing in some value which type isn't object"<<endl;
        exit(0);
    }

    auto list = this->_object->list;
    for(auto i : list){
        if(i.first.name == key_name && i.second->str_type!=NULL) return *i.second;
    }

    // if pass from here then add key because doesn't exist in object
    auto new_val = new VALUE();
    this->_object->list.push_back(pair<KEY,VALUE*>(KEY(string(key_name)),new_val));
    return *new_val;

}

VALUE& JSON::operator[](const char* key_name){
    if(this->value == NULL) this->value = new VALUE(OBJECT());

    string str_type = *this->value->str_type;
    if(str_type != "object"){
        cout<<"ERROR , indexing in some value which type isn't object"<<endl;
        exit(0);
    }
    

    auto list = this->value->_object->list;
    for(auto i : list){
        if(i.first.name == key_name && i.second!=NULL && i.second->str_type!=NULL)
            return *i.second;
    }
    auto new_val = new VALUE();
    this->value->_object->list.push_back(pair<KEY,VALUE*>(KEY(string(key_name)),new_val));
    return *new_val;
}





JSON operator,(JSON json ,VALUE _value){
    if(*json.value->str_type != "array"){
        cout<<"ERROR , APPEND works only for array"<<endl;
        exit(0);
    }

    json.value->_array->list.push_back(new VALUE(_value));

    return json;
}


APPEND::APPEND(){}

APPEND::APPEND(VALUE &_value){
    val = &_value;
}

JSON& operator+(JSON &json,APPEND ap){
    if(json.value == NULL || json.value->str_type == NULL ||*json.value->str_type != "array"){
        ERROR("JSON value isn't type array")
        exit(0);
    }

    return json;
}

APPEND operator+(VALUE &value,APPEND ap){
    if(value.str_type == NULL || *value.str_type != "array"){
        ERROR("Value isn't type array")
        exit(0);
    }
    return APPEND(value);
}

APPEND& APPEND::operator,(VALUE _value){
    if(*this->val->str_type != "array"){
        cout<<"ERROR , APPEND works only for array"<<endl;
        exit(0);
    }
    this->val->_array->list.push_back(new VALUE(_value));
    return *this;
}




//================= (+, -, *, /, %) and (>, >=, <, <=) operators ================


// if values are not numbers print error and exit()
void CheckIfValuesAreNumbers(string type1 , string type2){
    if(type1 != "int" && type1 != "double"){
        ERROR("Value1 must be a number")
        exit(0);
    }
    
    if(type2 != "int" && type2 != "double"){
        ERROR("Value2 must be a number")
        exit(0);
    }
}

bool IsNumber(string type){
    if(type == "int" || type == "double") return true;
    else return false;
};


VALUE& VALUE::operator+(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    string str_type1 = *this->str_type;
    string str_type2 = *_value.str_type;

    VALUE *ret_val = new VALUE();
   

    if(str_type1 == "string" && str_type2 == "string"){
        // concatenate stirngs
        ret_val->_string = new string(*this->_string + *_value._string);
        ret_val->str_type = new string("string");

    }else if(str_type1 == "array" && str_type2 == "array"){
        // adding elements of an array to the other
        ret_val->_array = new ARRAY();

        for(auto i : this->_array->list){
            ret_val->_array->list.push_back(i);
        }

        for(auto i : _value._array->list){
            ret_val->_array->list.push_back(i);
        }
        ret_val->str_type = new string("array");


    }else if(str_type1 == "object" && str_type2 == "object"){
        // adding elements of pair<key,value> one array to the other
        ret_val->_object = new OBJECT();

        for(auto i : this->_object->list){
            ret_val->_object->list.push_back(i);
        }

        for(auto i : _value._object->list){
            ret_val->_object->list.push_back(i);
        }

        ret_val->str_type = new string("object");

    }else if(IsNumber(str_type1) && IsNumber(str_type2)){

        if(*this->str_type == "int"){
            if(*_value.str_type == "int"){
                ret_val->_inumber = new int(*this->_inumber + *_value._inumber);
                ret_val->str_type = new string("int");
            }else{
                ret_val->_dnumber = new double(*this->_inumber + *_value._dnumber);
                ret_val->str_type = new string("double");
            }
        }else if(*this->str_type == "double"){
            if(*_value.str_type == "double"){
                ret_val->_dnumber = new double(*this->_dnumber + *_value._dnumber);
                ret_val->str_type = new string("double");
            }else{
                ret_val->_dnumber = new double(*this->_dnumber + *_value._inumber);
                ret_val->str_type = new string("double");
            }
        }

    }else{
        DEBUG(*this->str_type)
        DEBUG(*_value.str_type)

        ERROR("Values are not the same type operator+")
        exit(0);
    }

    assert(ret_val->str_type != NULL);
    return *ret_val;
}


VALUE& VALUE::operator-(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);

    VALUE *ret_val = new VALUE();
    
    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int"){
            ret_val->_inumber = new int(*this->_inumber - *_value._inumber);
            ret_val->str_type = new string("int");
        }else{
            ret_val->_dnumber = new double(*this->_inumber - *_value._dnumber);
            ret_val->str_type = new string("double");
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double"){
            ret_val->_dnumber = new double(*this->_dnumber - *_value._dnumber);
            ret_val->str_type = new string("double");
        }
        else{
            ret_val->_dnumber = new double(*this->_dnumber - *_value._inumber);
            ret_val->str_type = new string("double");
        }

    }

    assert(ret_val->str_type != NULL);
    return *ret_val;
}
VALUE& VALUE::operator*(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);
    VALUE *ret_val = new VALUE();

    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int"){
            ret_val->_inumber = new int(*this->_inumber * *_value._inumber);
            ret_val->str_type = new string("int");
        }else{
            ret_val->_dnumber = new double(*this->_inumber * *_value._dnumber);
            ret_val->str_type = new string("double");
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double"){
            ret_val->_dnumber = new double(*this->_dnumber * *_value._dnumber);
            ret_val->str_type = new string("double");
        }else{
            ret_val->_dnumber = new double(*this->_dnumber * *_value._inumber);
            ret_val->str_type = new string("double");
        }
    }
    
    assert(ret_val->str_type != NULL);
    return *ret_val;
}


void CheckValue2IfIsZero(VALUE _value){
    if(*_value.str_type == "double"){
        if(*_value._dnumber == 0){
            ERROR("divide with zero not allowed")
            exit(0);
        }
    }else if(*_value.str_type == "int"){
        if(*_value._inumber == 0){
            ERROR("divide with zero not allowed")
            exit(0);
        }
    }else
        assert(0);
}

VALUE& VALUE::operator/(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);

    // check if number is zero
    CheckValue2IfIsZero(_value);

    VALUE *ret_val = new VALUE();

    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int"){
            ret_val->_inumber = new int(*this->_inumber / *_value._inumber);
            ret_val->str_type = new string("int");
        }else{
            ret_val->_dnumber = new double(*this->_inumber / *_value._dnumber);
            ret_val->str_type = new string("double");
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double"){
            ret_val->_dnumber = new double(*this->_dnumber / *_value._dnumber);
            ret_val->str_type = new string("double");
        }else{
            ret_val->_dnumber = new double(*this->_dnumber / *_value._inumber);
            ret_val->str_type = new string("double");
        }

    }

    assert(ret_val->str_type != NULL);
    return *ret_val;

}
VALUE& VALUE::operator%(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    if(*this->str_type != "int"){
        ERROR("Value1 is not integer operator%")
        exit(0);
    }
    if(*_value.str_type != "int"){
        ERROR("Value2 is not integer operator%")
        exit(0);
    }

    // check if number is zero
    if(*_value._inumber == 0){
        ERROR("modulo with zero not allowed")
        exit(0);
    }

    VALUE *ret_val = new VALUE();

    // do the calculation
    this->_inumber = new int(*this->_inumber % *_value._inumber);
    ret_val->str_type = new string("int");

    assert(ret_val->str_type != NULL);
    return *this;

}

VALUE VALUE::operator>(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);
    VALUE bool_val = VALUE();
    bool_val.str_type = new string("bool"); 

    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int")
            bool_val._bool = *this->_inumber > *_value._inumber;
        else{
            bool_val._bool = *this->_inumber > *_value._dnumber;
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double")
            bool_val._bool = *this->_dnumber > *_value._dnumber;
        else
            bool_val._bool = *this->_dnumber > *_value._inumber;
    }

    return bool_val;

}
VALUE VALUE::operator>=(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);
    VALUE bool_val = VALUE();
    bool_val.str_type = new string("bool"); 

    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int")
            bool_val._bool = *this->_inumber >= *_value._inumber;
        else{
            bool_val._bool = *this->_inumber >= *_value._dnumber;
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double")
            bool_val._bool = *this->_dnumber >= *_value._dnumber;
        else
            bool_val._bool = *this->_dnumber >= *_value._inumber;
    }

    return bool_val;
}
VALUE VALUE::operator<(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);
    VALUE bool_val = VALUE();
    bool_val.str_type = new string("bool"); 

    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int")
            bool_val._bool = *this->_inumber < *_value._inumber;
        else{
            bool_val._bool = *this->_inumber < *_value._dnumber;
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double")
            bool_val._bool = *this->_dnumber < *_value._dnumber;
        else
            bool_val._bool = *this->_dnumber < *_value._inumber;
    }

    return bool_val;

}
VALUE VALUE::operator<=(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreNumbers(*this->str_type,*_value.str_type);
    VALUE bool_val = VALUE();
    bool_val.str_type = new string("bool"); 

    // do the calculation
    if(*this->str_type == "int"){
        if(*_value.str_type == "int")
            bool_val._bool = *this->_inumber <= *_value._inumber;
        else{
            bool_val._bool = *this->_inumber <= *_value._dnumber;
        }
    }else if(*this->str_type == "double"){
        if(*_value.str_type == "double")
            bool_val._bool = *this->_dnumber <= *_value._dnumber;
        else
            bool_val._bool = *this->_dnumber <= *_value._inumber;
    }

    return bool_val;
}


void CheckIfValuesAreBool(string type1,string type2){
    if(type1 != "bool"){
        ERROR("Value1 must be type bool")
        exit(0);
    }
    
    if(type2 != "bool"){
        ERROR("Value2 must be type bool")
        exit(0);
    }
}

VALUE VALUE::operator&&(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreBool(*this->str_type , *_value.str_type);

    if(this->_bool && _value._bool) return VALUE(true);
    else return VALUE(false);

}
VALUE VALUE::operator||(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    CheckIfValuesAreBool(*this->str_type , *_value.str_type);

    if(this->_bool || _value._bool) return VALUE(true);
    else return VALUE(false);

}
VALUE VALUE::operator!(){
    if(this->str_type == NULL) this->str_type = new string("null");

    if(*this->str_type != "bool"){
        ERROR("value is not type of bool operator!")
        exit(0);
    }

    if(!this->_bool) return VALUE(true);
    else return VALUE(false);
}


VALUE VALUE::operator==(VALUE _value){
    if(_value.str_type == NULL) _value.str_type = new string("null");
    if(this->str_type == NULL) this->str_type = new string("null");

    if(IsNumber(*this->str_type) && IsNumber(*_value.str_type)){
        // gia na perasei se periptwsh pou einai to ena value int kai to allo double
    }else if(*this->str_type != *_value.str_type){
        ERROR("Values aren't the same type")
        exit(0);
    }

    VALUE ret_val = VALUE();
    ret_val.str_type = new string("bool");
    string type = *this->str_type;

    if(type == "string"){
        ret_val._bool = ( *this->_string == *_value._string);
        return ret_val;
    }else if(IsNumber(type)){
        if(*this->str_type == "int"){
            if(*_value.str_type == "int")
                ret_val._bool = *this->_inumber == *_value._inumber;
            else{
                ret_val._bool = *this->_inumber == *_value._dnumber;
            }
        }else if(*this->str_type == "double"){
            if(*_value.str_type == "double")
                ret_val._bool = *this->_dnumber == *_value._dnumber;
            else
                ret_val._bool = *this->_dnumber == *_value._inumber;
        }

    }else if(type == "object"){

        vector<pair<KEY,VALUE *>> list1;
        vector<pair<KEY,VALUE *>> list2;

        for(auto i : this->_object->list){
            if(i.second != NULL && i.second->str_type != NULL) list1.push_back(i);
        }

        for(auto i : _value._object->list){
            if(i.second != NULL && i.second->str_type != NULL) list2.push_back(i);
        }

        if(list1.size() != list2.size()){
            ret_val._bool = false;
            return ret_val;
        }

        // iterator
        auto value2 = list2.begin();
        for(auto value1 : list1){
            // an den einai idia return false
            if(value1.first.name != value2.base()->first.name){
                ret_val._bool = false;
                return ret_val;
            }

            if(!value1.second->operator==(*value2.base()->second)._bool){
                ret_val._bool = false;
                return ret_val;
            }
            value2++;
        }
        // arrays are equal
        ret_val._bool = true;

    }else if(type == "array"){

        vector<VALUE *> list1;
        vector<VALUE *> list2;

        for(auto i : this->_array->list){
            if(i != NULL && i->str_type != NULL) list1.push_back(i);
        }

        for(auto i : _value._array->list){
            if(i != NULL && i->str_type != NULL) list2.push_back(i);
        }

        if(list1.size() != list2.size()){
            ret_val._bool = false;
            return ret_val;
        }

        // iterator
        auto value2 = list2.begin();
        for(auto value1 : list1){
            // an den einai idia return false
            if(!value1->operator==(**value2)._bool){
                ret_val._bool = false;
                return ret_val;
            }
            value2++;
        }
        // arrays are equal
        ret_val._bool = true;
    }else if(type == "bool"){
        ret_val._bool = ( this->_bool == _value._bool);
        return ret_val;
    }else if(type == "null"){
        ret_val._bool = true;
        return ret_val;
    }else{
        assert(0);
    }


    return ret_val;
}

VALUE VALUE::operator!=(VALUE _value){
    // call operator ==
    VALUE ret_val = this->operator==(_value);
    assert(*ret_val.str_type == "bool");
    if(ret_val._bool == true) return VALUE(false);
    else return VALUE(true);
}



// ============ FUNCTIONS ===============

int SizeOf(JSON json){
    if(json.value == NULL) return 0;
    return SizeOf(*json.value);

}


int SizeOf(VALUE value){
    if(value.str_type == NULL) return 0;
    int size = 0;

    if(*value.str_type == "object"){
        auto list = value._object->list;
        for(auto i : list){
            if(i.second!=NULL & i.second->str_type != NULL)
                size++;
        }


    }else if(*value.str_type == "array"){
        auto list = value._array->list;
        for(auto i : list){
            if(i!=NULL & i->str_type != NULL)
                size++;
        }
    }else
        return 1;    


    return size;
}



bool IsEmpty(JSON json){
    if(json.value == NULL) return true;
    else return IsEmpty(*json.value);
}

bool IsEmpty(VALUE value){
    assert(value.str_type != NULL);
    if(*value.str_type == "object" || *value.str_type == "array")
        return !SizeOf(value);
    else
        return false;
}



string TypeOf(JSON json){
    if(json.value == NULL) return "null";
    else return TypeOf(*json.value);
}
string TypeOf(VALUE value){
    if(value.str_type == NULL) return "null";
    if(*value.str_type == "bool") return "boolean";
    else if(IsNumber(*value.str_type)) return "number";
    else return *value.str_type;
}



bool HasKey(JSON json, string key){
    if(json.value == NULL) return false;
    return HasKey(*json.value,key);
}
bool HasKey(VALUE value, string key){
    if(value.str_type == NULL) return false;
    if(*value.str_type != "object") return false;

    auto list = value._object->list;

    for(auto val : list){
        if(val.first.name == key){
            if(val.second!=NULL && val.second->str_type!=NULL)
                return true;
        }
    }

    return false;
}






// ============= PRINT JSON VARIABLE AND VALUES =================


void PRINT::PrintValue(VALUE *value){
    assert(value != NULL);
    assert(value->str_type != NULL);

    if(*value->str_type == "null") cout<<"NULL";
    else if(*value->str_type == "int") cout<<to_string(*value->_inumber);
    else if(*value->str_type == "double") cout<<to_string(*value->_dnumber);
    else if(*value->str_type == "bool")  value->_bool ? cout<< "true" : cout<<"false";     
    else if(*value->str_type == "string") cout<<*value->_string;     
    else if(*value->str_type == "object") {
        cout<<"{";
        value->_object->print();     
        cout<<"}";
        return;
    }
    else if(*value->str_type == "array") {
        cout<<"[";
        value->_array->print();
        cout<<"]";
        return;
    }
    cout<<" ";
}


PRINT::PRINT(){}


PRINT PRINT::operator,(VALUE _value){
    _value.print();    
    cout<<endl;
    return *this;
    
}
PRINT PRINT::operator,(JSON json){
    json.print();
    cout<<endl;
    return *this;
}
PRINT PRINT::operator,(bool _bool){
    _bool ? cout<<"true" : cout<<"false";
    cout<<endl; 
    return *this;
    
}
PRINT PRINT::operator,(string str){
    cout<<str<<endl; 
    return *this;
}

PRINT PRINT::operator,(int size){
    cout<<size<<endl; 
    return *this;
}

















