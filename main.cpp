#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <cmath>

using namespace std;

//****************************** Global variables and tables *************************************

struct OPTAB{
    string name[60]={ "ADD","ADDF","ADDR","AND","CLEAR","COMP","COMPF","COMPR","DIV","DIVF","DIVR","FIX","FLOAT","HIO","J","JEQ",
"JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS","MUL","MULF","MULR","NORM","OR","RD","RMO","RSUB",
"SHIFTL","SHIFTR","SIO","SSK","STA","STB","STCH","STF","STI","STL","STS","STSW","STT","STX","SUB","SUBF","SUBR","SVC","TD",
"TIO","TIX","TIXR","WD" };
    string opcode[60]={ "18","58","90","40","B4","28","88","A0","24","64","9C","C4","C0","F4","3C","30","34","38","48","00","68","50","70","08",
"6C","74","04","D0","20","60","98","C8","44","D8","AC","4C","A4","A8","F0","EC","0C","78","54","80","D4","14","7C","E8",
"84","10","1C","5C","94","B0","E0","F8","2C","B8","DC" };
};

class SYMTAB{
    public:
    string label;
    int targetAddress;
    static int isEmpty;

    void insertLabel(string key, int locationCounter)
    {
        isEmpty=0;
        label= key;
        targetAddress= locationCounter;
    }
};


int SYMTAB::isEmpty=-1;
int program_size=0;
int no_of_symbols=0;
int startingAddress=0;
OPTAB optab;
SYMTAB symtab[20];



//***************************************** Function declarations *************************************************

void pass1();
void pass2();

int search_symtab_pass1(SYMTAB, string, int);
int search_optab_pass1(string);

int search_symtab_pass2(SYMTAB, string, int);
string search_optab_pass2(string);

string convertToObject(string, string, int*);
void insertLabel(string ,int );
int stringToInt(string);
int hexToDec(string);
string decToHex(string);
string object(string, int);


//********************************************* MAIN ***************************************************************

int main()
{
    pass1();
    cout<< "Pass 1 : All done!!"<<endl<<endl;

    pass2();
    cout<< "Pass 2 : All done!!"<<endl<<endl;
    cout<< "Check out the output file. :-)"<<endl;
    return 0;
}



//*************************************** Function Definations **********************************************************

int search_symtab_pass1(SYMTAB sym[],string key, int n)
{
    int f=0,i;
    if(SYMTAB::isEmpty==-1)
        return 0;
    else
    {
        for(i=0; i<n; i++)
        {
            if(key==sym[i].label)
            {
                f=1;
                break;
            }
        }
    }

    if(f==1)
        return 1;
    else
        return 0;
}


int search_optab_pass1(string key)
{
    OPTAB optab;
    int f=0;
    for(int i=0; i<60; i++)
    {

        if(key==optab.name[i])
        {
            f=1;
            break;
        }
    }

    if(f==1)
        return 1;
    else
        return 0;
}


int search_symtab_pass2(SYMTAB sym[],string key, int n)
{
    int f=-1,i;
    if(SYMTAB::isEmpty==-1)
        return 0;
    else
    {
        for(i=0; i<n; i++)
        {
            if(key==sym[i].label)
            {
                f=i;
                break;
            }
        }
    }

    if(f==-1)
        return f;
    else
        return f;
}


string search_optab_pass2(string key)
{
    OPTAB optab;
    string f="n";
    for(int i=0; i<60; i++)
    {

        if(key==optab.name[i])
        {
            f=optab.opcode[i];
            break;
        }
    }

    if(f=="n")
        return "n";
    else
        return f;
}


int stringToInt(string key)
{
    char intVal[key.length()];
    int value;

    for(int i=0; i<key.length(); i++)
        intVal[i] = key[i];

    value = atoi(intVal);

    return value;
}


string convertToObject(string opcode, string operand, int *len)
{
    string value,z;
    char hexVal[6];
    int ival;

    ival = stringToInt(operand);    //Returns the integer value to corresponding string passed.

    if(opcode=="WORD")
    {
        itoa(ival,hexVal,16);   //To convert decimal to hexadecimal

        int i,x= strlen(hexVal);

        for(i=0; i<6-x; i++)
        {
            for(int j=x-1+i; j>=0; j--)
                hexVal[j+1] = hexVal[j];
            hexVal[0]='0';
        }

        string y(hexVal);
        value = y.substr(0,6);
        *len = 3;

    }
    else if(opcode=="BYTE")
    {
        if(operand[0]=='X')
        {
            value= operand.substr(2,operand.length()-3);
            *len = 1;
        }
        else if(operand[0]=='C')
        {
            int temp,i;
            char buf[2], hexVal1[(operand.length()-3)*2];
            string val;

            for(int i=2; i<operand.length()-1; i++)
                hexVal1[i]=operand[i];

            for(i=2; i<operand.length()-1; i++)
            {
                temp= hexVal1[i];   //cout<< "ascii value :"<< temp<<endl;

                itoa(temp,buf,16);  //cout<< "Hexadecimal value :"<< buf<< endl;

                val=buf;
                value = value + val;
            }
            *len = operand.length()-3;
        }
        else
            value = "n";
    }
    else
        value = "n";

    return value;
}


int hexToDec(string key)
{
    int sum=0;
    for(int i=key.length()-1; i>=0; i--)
    {
        if(key[i]>'9')
        {
            int var;
            switch(key[i])
            {
            case 'A':
                var=10;
                break;
            case 'B':
                var=11;
                break;
            case 'C':
                var=12;
                break;
            case 'D':
                var=13;
                break;
            case 'E':
                var=14;
                break;
            case 'F':
                var=15;
                break;
            }
            sum += var*pow(16,key.length()-i-1);
        }
        else
            sum += (key[i]-'0')*pow(16,key.length()-i-1);
    }

    return sum;

}


string decToHex(string key)
{
    int val;
    char buff[6], copY[key.length()];

    for(int i=0; i<key.length(); i++)
        copY[i] = key[i];

    val = atoi(copY);

    itoa(val,buff,16);

    string res(buff);

    return res;
}


string object(string m, int add)
{
    char buff[4];
    string val;
    itoa(add,buff,16);
    val=buff;
    //cout<<m<<endl;
    return(m+val);
}



void pass1()
{
    ifstream fin;
    ofstream fout;
    int LOCCTR,c=0,lines=1;
    char ch;
    string opcode[15], op;

    fin.open("input.txt");
    fout.open("intermediate_file.txt");

    fin>> opcode[0] >> opcode[1]>> opcode[2];   // Reading the first line.

    if(opcode[1]=="START")
    {
        lines++;
        startingAddress= hexToDec(opcode[2]);
        LOCCTR= hexToDec(opcode[2]);
        fout<< opcode[0]<< "\t"<< opcode[1]<< "\t" << opcode[2]<<endl;

        ch=fin.get();
        ch=fin.get();

        for(int i=0; ch!='\n'; i++)
        {
            fin>> opcode[i];
            c++;
            ch=fin.get();
        }
    }
    else
        LOCCTR=0;

    if(c==2)
        op=opcode[0];
    else
        op=opcode[1];

    int k;
    while(op!="END")
    {
        k=0;
        if(opcode[k]!=".")
        {
            if(c==3)
            {
                k=1;
                int f=search_symtab_pass1(symtab,opcode[0],no_of_symbols);
                if(f==1)
                    cout<< "Duplicate Symbol found at line "<< lines<<endl;
                else
                {
                    symtab[no_of_symbols].insertLabel(opcode[0],LOCCTR);
                    no_of_symbols++;
                }
            }

            fout<<" "<<LOCCTR;
            int f=search_optab_pass1(opcode[k]);
            if(f==1)
                LOCCTR += 3;
            else if(opcode[k]=="WORD")
                LOCCTR += 3;
            else if(opcode[k]=="RESW")
                LOCCTR += 3*stringToInt(opcode[k+1]);
            else if(opcode[k]=="RESB")
                LOCCTR += stringToInt(opcode[k+1]);
            else if(opcode[k]=="BYTE")
            {
                int len;
                if(opcode[k+1][0]=='X')
                    len = (opcode[k+1].length()-3)/2;
                else
                    len = opcode[k+1].length()-3;

                LOCCTR += len;
            }
            else
            {
                cout<< "Invalid opcode at line "<< lines << "is : "<<opcode[k]<<endl;
            }
        }


        //Writing line to intermediate file
        for(int i=0; i<c; i++)
            fout<< " "<< opcode[i];
        fout<<endl;


        //Read the next line
        ch=fin.get();
        c=0;
        for(int i=0; ch!='\n'; i++)
        {
            fin>> opcode[i];
            c++;
            ch=fin.get();
        }
        if(c==2 || c==1)
            op=opcode[0];
        else
            op=opcode[1];

        lines++;

    }

    //Writing last line to intermediate file
    fout<< " " <<LOCCTR<< " " ;
    for(int i=0; i<c; i++)
        fout<< opcode[i]<< "\n";

    program_size= LOCCTR - startingAddress + 3 ;
    fin.close();
    fout.close();

}


void pass2()
{
    ifstream fin;
    ofstream fout;
    string opcode[10], op;
    char ch;
    int c=0,sizeCount=0, pointerPos=0,y=0,z=1;

    fin.open("intermediate_file.txt");
    fout.open("output.txt");

    fin>> opcode[0] >> opcode[1]>> opcode[2];   // Reading the first line.

    if(opcode[1]=="START")
    {
        fout<< "OBJECT PROGRAM"<<endl<<endl;
        char buff[6];
        itoa(program_size-3,buff,16);
        fout<< "H^"<<setw(6)<<setfill('_')<<opcode[0] << "^"<<setw(6)<<setfill('0')<< opcode[2]<< "^"<< setw(6)<<setfill('0')<<buff<<endl<<endl;

        ch=fin.get();
        ch=fin.get();

        for(int i=0; ch!='\n'; i++)
        {
            fin>> opcode[i];
            c++;
            ch=fin.get();
        }
        if(opcode[0]==".")
            op=opcode[0];
        else if(c==3)
            op=opcode[1];
        else
            op=opcode[2];
    }

    fout<< "T^"<< setw(6)<<setfill('0')<<decToHex(opcode[0])<< "^  ";
    pointerPos = fout.tellp();
    while(op!="END")
    {
        if(op!=".")
        {
            int x=0;
            string value;
            string m=search_optab_pass2(op);
            if(m!="n")
            {
                if(c>=3)
                {
                    int k=0;
                    if(opcode[c-1].substr(opcode[c-1].length()-2,2)==",X")
                    {
                        k = 1;
                        opcode[c-1] = opcode[c-1].substr(0,opcode[c-1].length()-2);
                    }

                    int f=search_symtab_pass2(symtab,opcode[c-1],no_of_symbols);
                    if(f!=-1)
                    {
                        int val;
                        if(k==1)
                            val = symtab[f].targetAddress + 32768;
                        else
                            val = symtab[f].targetAddress;

                        value = object(m,val);
                    }
                    else
                    {
                        opcode[3]= "0000";
                        value = m + opcode[3];
                        cout<< "Undefined Symbol!! "<< opcode[2]<<endl;
                    }
                }
                else
                {
                    opcode[3]= "0000";
                    value = m + opcode[3];
                }
                sizeCount += 3;
            }
            else if(op=="BYTE" || op=="WORD")   //Finding the object code of byte and word.
            {
                int byteLen=0;
                if(c==3)
                    value = convertToObject(op,opcode[2],&byteLen);
                else
                    value = convertToObject(op,opcode[3],&byteLen);

                if(value=="n")
                    cout<< "Invalid opcode!!!";

                if(op=="WORD")
                    sizeCount += byteLen;
                else
                    sizeCount += byteLen;

            }
            else    //To check the break point of text record.
            {
                x=1;
                z=0;
            }

            if(sizeCount>30 || x==1)   //Checking the text record size availability.
            {
                if(y!=1)    //This condition prevents the change in the file pointer every time.
                {
                    if(sizeCount>30)
                        sizeCount -= 3;
                    char buff[6];
                    itoa(sizeCount,buff,16);
                    pointerPos = fout.tellp() - pointerPos;
                    fout.seekp(-pointerPos-2,ios_base::cur);   //Writing the text record size to output file.
                    fout<<setw(2)<<setfill('0')<< buff;
                    fout.seekp(0,ios_base::end);
                }
                y=1;
            }

            if(x!=1 && y==1)
            {
                y=0;
                z=1;
                sizeCount=3;
                fout<< "\nT^"<<setw(6)<<setfill('0')<< decToHex(opcode[0])<< "^  ";    //Creating the new text record.
                pointerPos = fout.tellp();
            }

            //Writing text record to output file
            if(x!=1)
            {
                fout<< "^"<< value;
            }
            //cout<< sizeCount<<endl;
        }

        //Read the next line
        ch=fin.get();
        c=0;
        for(int i=0; ch!='\n'; i++)
        {
            fin>> opcode[i];
            c++;
            ch=fin.get();
        }
        if(c==2 || c==3)
            op=opcode[1];
        else
            op=opcode[2];

    }

    if(z==1)    // This condition checks if there are no resw or resb instructions at end of program then it sets the text record size.
    {
        char buff[6];
        itoa(sizeCount,buff,16);
        pointerPos = fout.tellp() - pointerPos;
        fout.seekp(-pointerPos-2,ios_base::cur);   //Writing the text record size to output file.
        fout<<setw(2)<<setfill('0')<< buff;
        fout.seekp(0,ios_base::end);
    }

    //Writing last text record to output file
    char buf[6];
    itoa(startingAddress,buf,16);
    fout<< "\n\nE^"<<setw(6)<<setfill('0')<<buf;

    fin.close();
    fout.close();
}



