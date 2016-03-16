#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>


using namespace std;

struct dict
{
    float floatdict;
    string strdict;
};

struct stak
{
    string value;
    struct stak *next; // указатель на следующий элемент списка (стека)
};

struct stakNum
{
    float value;
    struct stakNum *next; // указатель на следующий элемент списка (стека)
};

struct stackVar {
    string value; // непосредственно значение элемента
    int priority; // приоритет операции, необходим для правильного расставления  скобок
    struct stackVar *next;
};

void trim(string s);
string loopAndAdd(string s, stak* p, stakNum* n, float Volume, int& Err, dict dictionary[], int& sizeOfDict);
bool isItGoodChar(string s);
int itsPriority(string str);
float toFloat(string prefix, stak* p, stakNum* n, dict dictionary[], int& sizeOfDict, int& Err);
void push(stak* &NEXT, const string VALUE);
string pop(stak* &NEXT);
void pushNum(stakNum* &NEXT, const float VALUE);
float popNum(stakNum* &NEXT);
void pushVar(stackVar* &NEXT, const string VALUE, const int priority);
string popVar(stackVar* &NEXT, int* priority);
int checkIt(string str );
int addToDict(string a, dict dictionary[], int& sizeOfDict); // добавить букву в словарь, если необходимо
void getAllVars(dict dictionary[], int& sizeOfDict); // получить все переменные
float varToFloat( dict dictionary[], string a, int sizeOfDict);
bool isItNumber(string s); // 1, если s - число. 0, если s - переменная
bool returnErr(string s, int* Err); //
bool IsFloat(string &line);  // float проверка
bool IsVar(string &line); //var проверка
string toInfix(string postfix, stackVar* v ); 


int main()
{
    dict dictionary[100]; // создаем словарь
    int sizeOfDict = 0; // размерность словаря
    stak *p=0;
    stakNum *n=0;
    stackVar *v = 0;

    float Volume = 0;//результат вычисления

    ifstream input("C:/Users/musta/Dropbox/ClionProjects/uselessBrackets/input.txt"); //создание класса input
    ofstream fout("C:/Users/musta/Dropbox/ClionProjects/uselessBrackets/output.txt");
    string inp;

    if (!input.is_open())
    {
        cout << "File not found.";
        input.close(); //закрытие файла
    }else
    {
        while(true){
            getline(input,inp);
            if(input.eof()) break;
        }

        trim(inp);
        cout << "Infix = " << inp << endl;
        inp = inp + ' ';
        int Err = 0;
        bool checkGo = returnErr(inp,&Err);
        // cout << "Err = " << Err << endl;
        if (Err == 0)
        {
            // cout << "Err = " << Err << endl;
            string buff = loopAndAdd(inp, p, n, Volume, Err, dictionary, sizeOfDict);
            trim(buff);
            // buff = buff + ' ';
            cout << " postfix = " << buff << endl;
            cout << " newInfix = " << toInfix(buff, v) << endl;

            // if (sizeOfDict != 0)
            // {
            //     getAllVars(dictionary, sizeOfDict); // просим ввести все переменные
            // }
            
            setlocale(LC_ALL, "rus");

        } else
        {
            // cout << "err = " << Err << endl;
            switch(Err)
            {
                case 1: cout << "ERROR: wrong brackets" << endl;
                    break;
                case 2: cout << "ERROR: wrong sequence" << endl;
                    break;
                case 3: cout << "ERROR: wrong float number" << endl;
                    break;
                case 4: cout << "ERROR: wrong sequence of brackets" << endl;
                    break;
                case 5: cout << "ERROR: wrong var. Variable must belong to the English alphabet" << endl;
                    break;
            }
        }
    }


    return 0;
}

float varToFloat( dict dictionary[], string a, int sizeOfDict) // поменять переменную на ее значение
{
    for(int i=0; i < sizeOfDict; ++i)
    {
        if(dictionary[i].strdict == a)
        {
            return dictionary[i].floatdict;
        }
    }
}


void getAllVars(dict dictionary[], int& sizeOfDict) // получить все переменные
{
    string tempStr;
    for(int i=0; i < sizeOfDict; ++i)
    {
        do
        {
            cout << "Please input float number " << dictionary[i].strdict << " ";
            cin >> tempStr;
        }while(isItNumber(tempStr) == 0); // повторять, пока пользователь не введет число

        const char* tempChar = tempStr.c_str();
        dictionary[i].floatdict = atof(tempChar);
    }
}

int addToDict(string a, dict dictionary[], int& sizeOfDict) //добавить переменную в словарь, если она новая
{
    bool check = 1; // по умолчанию это не новая буква


    for (int i = 0; i < sizeOfDict; ++i)
    {
        if (dictionary[i].strdict == a)
        {
            check = 0; // отменяем добавление буквы в словарь
            return 0;
        }
    }
    if (check == 1)
    {
        dictionary[sizeOfDict].strdict = a;
        sizeOfDict++;
    }
}

int checkIt(string str ){
    int i=0;//счетчик
    bool check = 1;//по умолчанию включен
    // while(i <= strlen(str) || check == 1)
    // {

    // }
}

bool isItEmpty(stak* &NEXT){
    cout <<  "Print Top of Stak = " << NEXT->next ;
    return 1;
}

bool isItNumber(string s)
{
    for (int k = 0; k < s.length() ; ++k)
    {
        if(((s[k]<46) || (s[k]>57)) && (s[k]!=48))
        {
            return 0; //если встречена не цифра - то s - переменная
        }
    }
    return 1; //иначе - цифра

}

bool IsFloat(string &line) {
    int comma=0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (!(((line[i] >= '0') && (line[i] <= '9')) || line[i]=='.')) {
            return false;
        }
        if (line[i] == '.'){
            comma++;
        }
        if (comma>1)
            return false;
    }
    return true;
}

bool IsVar(string &line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (!((line[i] >= 'a') && (line[i] <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool isItGoodChar(string s)
{
    for (int k = 0; k < s.length() ; ++k)
    {
        if ( ((s[k]<40) || (s[k] > 57)) && (s[k] != 94) && ((s[k]<97) || (s[k] > 122)) )
        {
            cout << "s[k] = " << s[k] << endl;
            return 0;
        }
    }
    return 1;
}

string toInfix(string postfix, stackVar* v )
{
    int k=0;
    bool check = 0;
    string buff = ""; // сторока для символов
    string Var1 = ""; // временные переменные
    string Var2 = ""; // временные переменные
    string tempToStack = ""; // временная для формирования нового действия
    int priority1,priority2; // для приоритета двух операторов
    while((k < postfix.length()) && (check ==0))
    {
        if (postfix[k] == ' ')
        {
            if (itsPriority(buff) == 1) //если это похоже на число
            {
                pushVar(v, buff, 5); // у всех чисел приоритет 5
            }else
            {
                if ((itsPriority(buff)==3)||(itsPriority(buff)==4)||(itsPriority(buff)==5)) // если встечен оператор
                {
                    Var1 = popVar(v, &priority1); // правый операнд
                    Var2 = popVar(v, &priority2); // левый операнд
                    
                    if (itsPriority(buff) > priority2)
                    {
                        Var2 = "( " + Var2 + " )";
                    };
                    if (itsPriority(buff) > priority1)
                    {
                        Var1 = "( " + Var1 + " )";
                    };
                    if((buff == "-") && (priority1 == 3)) // обрабатываем минус перед скобкой
                    {
                        Var1 = "( " + Var1 + " )";
                    };
                    tempToStack = Var2 + " " + buff + " " + Var1;
                    // cout << "tempToStack = " << tempToStack << endl;
                    if (itsPriority(buff) == 5) // если степень
                    {
                        pushVar(v, tempToStack, 4); // заносим сформированное выраженеи обратно в стек с заниженным приоритетом 
                    }else
                    {
                        pushVar(v, tempToStack, itsPriority(buff)); // заносим сформированное выраженеи обратно в стек 
                    }; 
                }
            }
            buff = "";
        }else
        {
            buff = buff + postfix[k];
        }
        k++;
    };
    return popVar(v, &priority1);
};

float toFloat(string prefix, stak* p, stakNum* n, dict dictionary[], int& sizeOfDict, int& Err) // prefix to float
{
    int k=0; //счетчик конца строки
    bool check=1;
    string temp=""; // временная переменная
    float tempFloat;
    while((k < prefix.length()) && (check==1))
    {
        if (prefix[k] == ' ')
        {
            // cout << "temp = " << temp << endl;
            if(itsPriority(temp)==1) // если встречено число
            {
                if(isItNumber(temp) == 0) // если перед нами переменная
                {
                    float tempFloat = varToFloat( dictionary, temp, sizeOfDict);
                    pushNum(n,tempFloat);
                    addToDict(temp, dictionary, sizeOfDict); //добавим в словарь, если она новая
                }
                else // если temp = число
                {
                    const char* tempChar = temp.c_str();
                    pushNum(n,atof(tempChar)); // добавим число в стек чисел
                }
                // pushNum(n,stof(temp)); // добавим число в стек чисел
                // vivod+=temp + ' ';
                //pushNum(n, stof(temp));
            }
            if ((itsPriority(temp)==3)||(itsPriority(temp)==4)||(itsPriority(temp)==5)) // если встечен оператор + - * /
            {

                tempFloat=popNum(n);
                if (temp == "+")
                {
                    tempFloat = popNum(n) + tempFloat;
                }
                if (temp == "-")
                {
                    tempFloat = popNum(n) - tempFloat;
                }
                if (temp == "*")
                {
                    tempFloat = popNum(n) * tempFloat;
                }
                if (temp == "/")
                {
                    if (tempFloat != 0)
                    {
                        tempFloat = popNum(n) / tempFloat;
                    } else
                    {
                        Err = 5; // деление на ноль
                        cout << "ERROR: wrong division by zero" << endl;
                        return 0;
                    }

                }
                if (temp == "^")
                {
                    tempFloat = pow(popNum(n),tempFloat);
                }

                pushNum(n, tempFloat);

            }
            temp="";
        }
        else
        {
            temp+=prefix[k];
        }
        k++;
    }
    return popNum(n);
}

bool returnErr(string s, int* Err) // нет ошибок  = 0
{
    int leftBrackets = 0;
    int rightBrackets = 0;
    bool check = 0;
    int balance = 0; //баланс переменных
    string tempStr;
    int isItFloat;
    int i =0;
    bool rightBracketsWas = 0; //только что была закрывающая скобка
    while((i < s.length()) && !(balance < 0) && !(balance > 1) )
    {
        if (s[i] == ' ')
        {
            // cout << "tempStr = " << tempStr << endl;
            if (tempStr == "(")
            {
                leftBrackets++;
                if ((balance == 1) && (i != 0) )
                {
                    *Err = 4; // перед скобками - оператор
                    return 1;
                }
            };
            if (tempStr == ")")
            {
                rightBrackets++;
                if (rightBrackets > leftBrackets)
                {
                    *Err = 1; // открывающая скобка стоит перед закрывающей
                    return 1;
                }
                rightBracketsWas = 1;
            };

            if (itsPriority(tempStr) == 1) // если число
            {
                balance++;
                // cout << "++" << endl;
                if (rightBracketsWas == 1) // перед числом не должно быть скобок
                {
                    *Err = 4; // перед скобками - оператор
                    return 1;
                }
            };
            if ((itsPriority(tempStr)==3)||(itsPriority(tempStr)==4)||(itsPriority(tempStr)==5)) // если оператор + - * / ^
            {
                balance--;
                // cout << "--" << endl;
                rightBracketsWas = 0;
            };
            if (itsPriority(tempStr) == 1) //если операнд
            {
                if(isItNumber(tempStr) != 0) // если перед нами не переменная
                {
                    if (IsFloat(tempStr) == 0)
                    {
                        *Err = 3; //недопустимые символы
                        return 1;
                    };
                }else
                {
                    if(IsVar(tempStr) == 0)
                    {
                        *Err = 5; //неправильная переменная
                        return 1;
                    }
                }
            };
            tempStr="";
        }else
        {
            tempStr+=s[i];
        }
        i++;
    };
    if (leftBrackets != rightBrackets)
    {
        *Err = 1; //скобки
        // cout << "Error Brackets" << endl;
        return 1;
    };
    if ((balance < 0) || (balance > 1))
    {
        *Err = 2; //неправильная последовательность
        return 1;
    };

    if (check == 1)
    {
        return 0;
    };
}

string loopAndAdd(string s, stak* p, stakNum* n, float Volume, int& Err, dict dictionary[], int& sizeOfDict)
{
    int k=0; //счетчик конца строки
    bool check=1;
    string temp=""; // временная переменная
    string vivod="";
    int tempPriority;
    int balance=0; // баланс символов число: +1. символ: -1.
    while((k < s.length()) && (check==1))
    {
        if (s[k] == ' ')
        {
            if (isItGoodChar(temp)==1)
            {
                if(itsPriority(temp)==1) // если встречено число
                {
                    // if(isItNumber(temp) == 0) // если перед нами переменная
                    // {
                    //     addToDict(temp, dictionary, sizeOfDict); //добавим в словарь, если она новая
                    // }
                    vivod+=temp + ' ';
                }else{
                    if (temp=="(")
                    {

                        push(p,temp);
                    }else{
                        if ((itsPriority(temp)==3)||(itsPriority(temp)==4)) // если встечен оператор + - * / ^
                        {
                            if (p != 0)
                            {
                                tempPriority=itsPriority(p->value);
                                while( itsPriority(temp) <= tempPriority)
                                {
                                    // float tempNum;
                                    // tempNum= popNum(n) + popNum(n);
                                    // pushNum(n,tempNum);


                                    // Volume+= popNum(n) + popNum(n); // применим этот оператор для последних двух чисел из стека чисел
                                    vivod+=pop(p) + ' ';

                                    if (p != 0)
                                    {
                                        tempPriority=itsPriority(p->value);
                                    } else{
                                        tempPriority = 0;
                                    }
                                }
                            }
                            // else {
                            // 	// cout << " nu zanesli" << temp << " " ;
                            // 	push(p, temp);
                            // }
                            push(p, temp);
                        }else{
                            if ((itsPriority(temp)==5))
                            {
                                push(p, temp);
                            }else{
                                if (temp==")")
                                {
                                    while(p->value != "(")
                                    {
                                        // Volume+= popNum(n) + popNum(n); // применим этот оператор для последних двух чисел из стека чисел
                                        vivod+=pop(p) + ' ';
                                    }
                                    pop(p);
                                    // do
                                    // {
                                    // 	vivod+=pop(p) + ' ';
                                    // } while (p->value == "(");
                                }
                            }
                        }
                    }
                }
            }else{
                cout << "ERROR CHARS" << endl;
                return 0;
            }
            temp="";
        }
        else
        {
            temp+=s[k];
        }
        k++;
    }
    while(p != 0)
    {
        // float tempRec;
        // tempRec = popNum(n) + popNum(n);
        // pushNum(n,tempRec);
        // Volume+= popNum(n) + popNum(n); // применим этот оператор для последних двух чисел из стека чисел
        vivod+=pop(p) + ' ';

    }
    // string tempstr = "100.4";
    // float tempvolume = 2.1;
    // tempvolume+= stof(tempstr);
    // cout << " tempvolume = " << tempvolume << endl;
    // Volume = popNum(n);

    // cout << "vivod = " << vivod << endl;
    return vivod;


}

void trim(string s)
{
    // удаляем пробелы и табы с начала строки:
    int i=0;
    while(s[0]==' ')
    {
        s.erase(0,1);//ампутация пробела
        i++;
    }
    while(s[s.length()-1]==' ')
    {
        s.erase(s.length()-1, 1);//ампутация пробела
    }
    // cout << s;
    /*if(i>0)
    {
           for(j=0;j<strlen(s);j++)
           {
               s[j]=s[j+i];
           }
         s[j]='\0';
    }

    // удаляем пробелы и табы с конца строки:
    i=strlen(s)-1;
    while((s[i]==' ')||(i==strlen(s))
    {
           i--;
    }
    if(i<(strlen(s)-1))
    {
           s[i+1]='\0';
    }*/
}


void push(stak* &NEXT, const string VALUE)
{
    stak *MyStack = new stak; // объявляем новую динамическую переменную типа stak
    MyStack->value = VALUE; // записываем значение, которое помещается в стек
    MyStack->next = NEXT; // связываем новый элемент стека с предыдущим
    NEXT = MyStack; // новый элемент стека становится его вершиной
}

string pop(stak* &NEXT)
{
    string temp = NEXT->value; // извлекаем в переменную temp значение в вершине стека
    stak *MyStack = NEXT; // запоминаем указатель на вершину стека, чтобы затем
    // освободить выделенную под него память
    NEXT = NEXT->next; // вершиной становится предшествующий top элемент
    delete MyStack; // освобождаем память, тем самым удалили вершину
    // std::cout<<temp; //Вывод текущего элемента на экран
    return temp; // возвращаем значение, которое было в вершине
}

void pushVar(stackVar* &NEXT, const string VALUE, const int priority)
{
    stackVar *MyStack = new stackVar; // объявляем новую динамическую переменную типа stak
    MyStack->value = VALUE; // записываем значение, которое помещается в стек
    MyStack->priority = priority; // записываем значение, которое помещается в стек
    MyStack->next = NEXT; // связываем новый элемент стека с предыдущим
    NEXT = MyStack; // новый элемент стека становится его вершиной
}

string popVar(stackVar* &NEXT, int* priority)
{
    string temp = NEXT->value; // извлекаем в переменную temp значение в вершине стека
    *priority = NEXT->priority ; //извлекаем из стека приоритет
    stackVar *MyStack = NEXT; // запоминаем указатель на вершину стека, чтобы затем
    // освободить выделенную под него память
    NEXT = NEXT->next; // вершиной становится предшествующий top элемент
    delete MyStack; // освобождаем память, тем самым удалили вершину
    // std::cout<<temp; //Вывод текущего элемента на экран
    return temp; // возвращаем значение, которое было в вершине
}

void pushNum(stakNum* &NEXT, const float VALUE)
{
    stakNum *MyStack = new stakNum; // объявляем новую динамическую переменную типа stakNum
    MyStack->value = VALUE; // записываем значение, которое помещается в стек
    MyStack->next = NEXT; // связываем новый элемент стека с предыдущим
    NEXT = MyStack; // новый элемент стека становится его вершиной
}

float popNum(stakNum* &NEXT)
{
    float temp = NEXT->value; // извлекаем в переменную temp значение в вершине стека
    stakNum *MyStack = NEXT; // запоминаем указатель на вершину стека, чтобы затем
    // освободить выделенную под него память
    NEXT = NEXT->next; // вершиной становится предшествующий top элемент
    delete MyStack; // освобождаем память, тем самым удалили вершину
    // std::cout<<temp; //Вывод текущего элемента на экран
    return temp; // возвращаем значение, которое было в вершине
}


int itsPriority(string str)
{
    if (str == "^")
    {
        return 5;
    }else{
        if (str == "*" || str == "/")
        {
            return 4;
        } else{
            if (str == "+" || str == "-")
            {
                return 3;
            } else{
                if (str == "(" || str == ")")
                {
                    return 2;
                } else{
                    return 1;//если число
                }
            }
        }
    }
}
