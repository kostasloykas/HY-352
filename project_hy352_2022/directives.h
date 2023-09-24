#undef NULL
#define NULL VALUE(CLASSNULL())
#define ARRAY VALUE()<<ARRAY()
#define OBJECT VALUE()<<OBJECT
#define KEY(title) KEY(string(#title)) = false ? VALUE()
#define NUMBER(num) VALUE(NUMBER(num))
#define STRING(str) VALUE(string(str))
#define TRUE VALUE(true)
#define FALSE VALUE(false)
#define JSON(var_name)  ;JSON var_name = JSON() // for the public definition else error for non type


// ============= DEFINITION FOR PROCCESSING JSON VARIABLE AND VALUES =================
#define SET ;
#define ASSIGN *=
#define APPEND +APPEND(),
#define ERASE ;ERASE()+ 


// ============== FUNCTIONS ================
#define SIZE_OF(var) SizeOf(var)
#define IS_EMPTY(var) IsEmpty(var)
#define TYPE_OF(var) TypeOf(var)
#define HAS_KEY(var,key) HasKey(var,key)


//=============== PRINT JSON VARIABLES AND VALUES ===============
#define PRINT ;PRINT(),



#define PROGRAM_BEGIN ;int main(){
#define PROGRAM_END ;return 0;}