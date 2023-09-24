#include "JSONlang.h"



PROGRAM_BEGIN

    JSON(emptyArray) = ARRAY

    JSON(week_temperatures) = ARRAY [
        NUMBER(20),NUMBER(19.5),NUMBER(19),NUMBER(20),
        NUMBER(19),NUMBER(18.5),NUMBER(19), NULL ,TRUE , FALSE , STRING("okkk")]


    JSON(emptyObj) = OBJECT{}

    JSON(book) = OBJECT {
        KEY(title) : STRING("Gone Girl"),
        KEY(published) : NUMBER(2012),
        KEY(type) : STRING("Thriller"),
        KEY(author) : OBJECT{
            KEY(firstname) : STRING("GILLIAN"),
            KEY(surname) : STRING("FLYNN"),
            KEY(age) : NUMBER(45)
        }
    }


    JSON(students) = ARRAY [
        OBJECT {
            KEY(name) : STRING("Kevin Malone"),
            KEY(id) : NUMBER(4444),
            KEY(grades) : ARRAY[
                OBJECT { KEY(hy100) : NUMBER(9.5) },
                OBJECT { KEY(hy150) : NUMBER(9) }
                ]
        }
    ]

    // SET emptyObj ASSIGN OBJECT{ KEY(a) : STRING("alpha") }

    SET students[0]["email"] ASSIGN STRING("csd404@csd.uoc.gr")

    SET emptyArray APPEND NUMBER(23), NUMBER(22), NUMBER(20)

    SET week_temperatures APPEND NUMBER(23), NUMBER(22), NUMBER(20)

    SET students[0]["grades"] APPEND OBJECT { KEY(hy255) : NUMBER(9) } ,STRING("kostas")

    // ERASE book["author"]["age"] //removes age from author object of book
    // ERASE book["author"] //removes age from author object of book
    // ERASE book["type"] //removes type of book
    // ERASE book



    JSON(hy352_ang) = OBJECT{ KEY(exam) : NUMBER(7) , KEY(project) : NUMBER(8) }

    // JSON(test) = (ARRAY [
    //     NUMBER(20),NUMBER(19.5),NUMBER(19),NUMBER(20),
    //     NUMBER(19),NUMBER(18.5),NUMBER(19), NULL ,TRUE , FALSE , STRING("okkk")]) + (ARRAY[NUMBER(3980)])
    //     + (ARRAY[STRING("kostas loukas")]) 

    // SET test APPEND NUMBER(210000), NUMBER(22), NUMBER(20)

    // JSON(graduate) = ARRAY[
    //     OBJECT {
    //         KEY(name) : STRING("Angela ") + STRING("Martin"),
    //         KEY(id) : NUMBER(4444),
    //         KEY(grades) : ARRAY[
    //             OBJECT {KEY(hy352): hy352_ang["exam"] * NUMBER(0.75) + hy352_ang["project"] * NUMBER(0.25)}
    //         ]
    //     }
    // ]

    // SET graduate[0]["grades"][0]["hy352"] APPEND NUMBER(210000), NUMBER(22), NUMBER(20)

    // ERASE graduate[0]["grades"][0]["hy352"]
    // ERASE graduate[0]["grades"]

    // SET graduate[0]["grades"] ASSIGN ARRAY[NUMBER(23) , STRING("csd3980")]

    // JSON(test2) = (graduate[0]["grades"]) + (ARRAY[
    //     OBJECT {KEY(hy352): hy352_ang["exam"] * NUMBER(0.75) + hy352_ang["project"] * NUMBER(0.25)}])
    

    // JSON(test3) = ARRAY[NUMBER(0)]
    // ERASE test3[0]
    // ERASE test3

    // JSON(CSD3980) = (OBJECT{KEY(3980) : STRING("konstantinos")}) + (OBJECT{KEY(3980) : STRING("loukas")})
    // PRINT CSD3980["3980"]

    // PRINT TYPE_OF(book["author"]["age"])
    // PRINT TYPE_OF(test3["author"]["age"])
    // PRINT TYPE_OF(book["author"]["age"]["as"])
    // PRINT TYPE_OF(graduate[0]["id"])
    // PRINT HAS_KEY(book["author"], "age")
    // PRINT HAS_KEY(book, "author")



    // PRINT (ARRAY[NUMBER(4)]) + (ARRAY[NUMBER(2)])
    // PRINT test2
    // PRINT graduate
    // PRINT test
    // PRINT test3
    // PRINT hy352_ang
    // PRINT emptyObj
    // PRINT emptyArray
    // PRINT students
    // PRINT book
    // PRINT week_temperatures


    // PRINT book["title"]
    // //prints:Gone Girl
    // PRINT book["author"] //prints:{firstname:”Gillian”,surname:“Flynn”,age:45}
    // PRINT book
    // //prints: the whole json for book
    // PRINT HAS_KEY(book, "author")//prints: true
    // //prints: Book has key author? True
    // PRINT STRING("Book has key author? "), HAS_KEY(book, "author")




PROGRAM_END


