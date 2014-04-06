#include <iostream>
#include "stdlib.h"

//BITS14 = the first 14 bits of an int all set to 1 (i.e. 00000000000000000011111111111111), this is the smallest number of bits to ensure storage of the number 9999
#define BITS14 16383

using namespace std;

//link
class Link
{
public:
    Link *next;
    Link *prev;
    int vals;
};

//list
class DoublyLinkedList
{
public:
    Link *first;
    Link *last;
};


//define ListADT variables and functions
class ListADT
{
    DoublyLinkedList myList;
public:
    int nodeCount;
    ListADT();
    Link *GET_LAST();
    Link *GET_FIRST();
    Link *NEXT_RIGHT(Link *);
    Link *NEXT_LEFT(Link *);
    void INSERT_RIGHT(int);
    void INSERT_LEFT(int);
    bool IS_FIRST(Link *);
    bool IS_LAST(Link *);
    
};

//define LongInteger ADT variables and functions
class LongInteger
{
    //signbit 0 = no sign, 1 = positive, 2 = negative;
    ListADT myList;
    int signbit;
public:
    LongInteger();
    LongInteger(string);
    void INITIALIZE(string);
    char GETSIGN();
    void SETSIGN(char);
    int GETDIGITCOUNT();
    void PRINT();
    bool GREATERTHAN(LongInteger);
    bool LESSTHAN(LongInteger);
    bool EQUALTO(LongInteger);
    /*
     LongInteger ADD(LongInteger);
     LongInteger SUBTRACT(LongInteger);
     LongInteger MULTIPLY(LongInteger);
     LongInteger POWER(LongInteger);
     LongInteger DIVIDE(LongInteger);
     //*/
    
};

ListADT::ListADT()
{
    //default constructor with intial value assignments
    nodeCount = 0;
    myList.first = NULL;
    myList.last = NULL;
}

Link *ListADT::GET_LAST()
{
    //if the node isnt empty, returns the lists "last" link
    if(nodeCount == 0)
    {
        return NULL;
    }
    else
    {
        return myList.last;
    }
}

Link *ListADT::GET_FIRST()
{
    //if the node isnt empty, returns the lists "first" link
    if(nodeCount == 0)
    {
        return NULL;
    }
    else
    {
        return myList.first;
    }
}
Link *ListADT::NEXT_RIGHT(Link *tmp)
{
    //if the node exists, it returns the value stored at its "next" value
    if(tmp!=NULL)
    {
        return tmp->next;
    }
    return NULL;
}
Link *ListADT::NEXT_LEFT(Link *tmp)
{
    //if the node exists, it returns the value stored at its "prev" value
    if(tmp!=NULL)
    {
        return tmp->prev;
    }
    return NULL;
}
void ListADT::INSERT_RIGHT(int val)
{
    
    //Simple check to see if the string is empty, if so adds the first link, else adds to the end of the list
    Link *tmp = new Link;
    tmp->vals = val;
    if(myList.first == NULL)
    {
        myList.first = tmp;
        myList.last = myList.first;
        nodeCount++;
        return;
    }
    myList.last->next = tmp;
    tmp->prev = myList.last;
    myList.last = tmp;
    nodeCount++;
    
}
void ListADT::INSERT_LEFT(int val)
{
    //Simple check to see if the string is empty, if so adds the first link, else adds to the front of the list
    Link *tmp = new Link;
    tmp->vals = val;
    if(myList.first == NULL)
    {
        myList.first = tmp;
        myList.last = myList.first;
        nodeCount++;
        return;
    }
    myList.first->prev = tmp;
    tmp->next = myList.first;
    myList.first = tmp;
    nodeCount++;
}
bool ListADT::IS_FIRST(Link *tmp)
{
    //compares the address of the "first" link to the address of the passed "tmp" link to find out of its first
    if(myList.first == tmp)
    {
        return true;
    }
    return false;
}
bool ListADT::IS_LAST(Link *tmp)
{
    //compares the address of the "last" link to the address of the passed "tmp" link to find out of its last
    if(myList.last == tmp)
    {
        return true;
    }
    return false;
}

LongInteger::LongInteger()
{
    //default constructor
    signbit = 0;
}
LongInteger::LongInteger(string s)
{
    //constructor allowing for fast initialization -- LongInteger x("123456"); == LongInteger x; x.INITIALIZE("123456");
    signbit = 0;
    INITIALIZE(s);
}
//*
void LongInteger::INITIALIZE(string s)
{
    int sLen = s.length();
    int count = 0;
    //signbit 0 = no sign, 1 = positive, 2 = negative;
    //finds the sign if there is one and if so makes an exception for the next check
    if(s[0] == '+' || s[0] == '-')
    {
        count = 1;
        signbit = ((((int)s[0]) - 41)>>1);
    }
    //check to make sure that no character is outside of the bounds of 0-9
    while(count < sLen)
    {
        if(!((int)s[count]>=48 && (int)s[count]<=58))
        {
            cout << "incorrect format" << endl;
            return;
        }
        count++;
    }
    //defines 4 digit chunks to be stored in pushVal which will later be pushed to the LongInteger. accounts for variations in signbit possibilities and variable string lengths.
    int pushVal = 0;
    count=1;
    sLen--;
    while(sLen!=-1)
    {
        if(s[sLen] < 48 )
        {
            break;
        }
        if(count==10000)
        {
      //      cout << "pushing left: " << pushVal << endl;
            myList.INSERT_LEFT(pushVal);
            count=1;
            pushVal = 0;
        }
        //cout << "s[" << sLen << "]:" << (s[sLen] - 48) << endl;
        pushVal += (s[sLen--]-48)*count;
        count*=10;
    }
    //cout << "pushing left: " << pushVal << endl;
    myList.INSERT_LEFT(pushVal);
    
}
//*/
/*
void LongInteger::INITIALIZE(string s)
{
    int sLen = s.length();
    int count = 0;
    //signbit 0 = no sign, 1 = positive, 2 = negative;
    //finds the sign if there is one and if so makes an exception for the next check
    if(s[0] == '+' || s[0] == '-')
    {
        count = 1;
        signbit = ((((int)s[0]) - 41)>>1);
    }
    //check to make sure that no character is outside of the bounds of 0-9
    while(count < sLen)
    {
        if(!((int)s[count]>=48 && (int)s[count]<=58))
        {
            cout << "incorrect format" << endl;
            return;
        }
        count++;
    }
    //defines 4 digit chunks to be stored in pushVal which will later be pushed to the LongInteger. accounts for variations in signbit possibilities and variable string lengths.
    int pushVal;
    int highend = sLen;
    count = 0;
    //compensates for the signbit
    if(signbit != 0)
    {
        highend--;
        count++;
    }
    //finds out the number of digits that will be in the first node, independant of whether sign is set.
    highend = highend&3;
    //if the first node isnt 4 digits like the others, run this special procedure to add them here.
    if(highend!=0)
    {
        pushVal = 0;
        highend+=count;
        while (count<highend)
        {
            pushVal*=10;
            pushVal+=(((int)s[count])-48);
            count++;
        }
        myList.INSERT_RIGHT(pushVal);
    }
    else
    {
        //either from the previous function or from this one highend, which is ((strlen - (possible 1 for signbit))%4),
        //which results in the true first node digits count, now adds count(which at the time is either 0 or 1, depending on the signbit being present
        //which leaves highend being (signbitlength + firstnodecount) and results in showing the starting point for the rest of the nodes in the string
        highend+=count;
    }
    while(count < sLen)
    {
        // essentially this statement says "if(count-highend%4 == 0)" therefore performing this operation after every 4 digits (one node)
        if(!((count-highend)&3))
        {
            //skips the first iteration, as it'll be a result of the "first node" or just empty data
            if((count-highend)!=0)
            {
                //adds the number to the list
                myList.INSERT_RIGHT(pushVal);
            }
            //resets the number
            pushVal = 0;
        }
        //essentially a base 10 LSL 1 to the previous total, then add the new number to the total resulting in the new total
        pushVal*=10;
        pushVal+=(((int)s[count])-48);
        count++;
    }
    //inserts the last node
    myList.INSERT_RIGHT(pushVal);
    
}
//*/
char LongInteger::GETSIGN()
{
    //returns the character value of the sign based on the stored signbit. the else is for if the signbit is stored as 0 (none was found)
    if(signbit!=0)
    {
        return (signbit<<1)+41;
    }
    else return '+';
}
void LongInteger::SETSIGN(char c)
{
    //sets the signbit to 1 or 2 depending on the value, 1 for positive, 2 for negative
    if(c == '+' || c == '-')
    {
        signbit = ((((int)c) - 41)>>1);
    }
}
int LongInteger::GETDIGITCOUNT()
{
    int count=0;
    Link *tmp = myList.GET_FIRST();
    // counts the digits in the first node
    if(tmp->vals>0)
    {
        count++;
        if(tmp->vals>9)
        {
            count++;
            if(tmp->vals>99)
            {
                count++;
                if(tmp->vals>999)
                {
                    count++;
                    
                }
            }
        }
    }
    // knowing that all other nodes must have a full 4, counts the number of remaining nodes and adds 4 for each
    while(!myList.IS_LAST(tmp))
    {
        count+=4;
        tmp = myList.NEXT_RIGHT(tmp);
    }
    return count;
}
void LongInteger::PRINT()
{
    //prints signbit
    if(signbit!=0)
    {
        cout << GETSIGN();
    }
    // prints all of the numbers in every node, including leading zeros if the number is smaller than 4 digits.
    Link *tmp = myList.GET_FIRST();
    while(!myList.IS_LAST(tmp))
    {
        if(tmp->vals<1000)
        {
            //skips leading digits for the first number
            if(!myList.IS_FIRST(tmp))
            {
                cout << '0';
                if(tmp->vals<100)
                {
                    cout << '0';
                    if(tmp->vals<10)
                    {
                        cout << '0';
                        if(tmp->vals==0)
                        {
                            cout << '0';
                        }
                    }
                }
            }
        }
        cout << tmp->vals;
        tmp = myList.NEXT_RIGHT(tmp);
    }
    //prints the last node
    if(tmp->vals<1000)
    {
        cout << '0';
        if(tmp->vals<100)
        {
            cout << '0';
            if(tmp->vals<10)
            {
                cout << '0';
                if(tmp->vals==0)
                {
                    cout << '0';
                }
            }
        }
    }
    cout << tmp->vals;
}
bool LongInteger::GREATERTHAN(LongInteger myLong)
{
    // if the first LongInt has the sign character '+' (which is of value 43) and the second has '-' (45), this will evaluate to true and therefore greaterthan
    if(GETSIGN() < myLong.GETSIGN())
    {
        return true;
    }
    // if the 2 long ints have equal signs
    if(GETSIGN()==myLong.GETSIGN())
    {
        // and theyre both negative
        if(GETSIGN() == '-')
        {
            int ct1 = GETDIGITCOUNT();
            int ct2 = myLong.GETDIGITCOUNT();
            // then the smaller negative number is greater than the other, and less digits results in a smaller number
            if(ct1<ct2)
            {
                return true;
            }
            else if(ct1>ct2)
            {
                return false;
            }
            else
            {
                // if they have the same number of digits, compare every node's value
                Link *tmp1 = myList.GET_FIRST();
                Link *tmp2 = myLong.myList.GET_FIRST();
                if(tmp1->vals < tmp2->vals)
                {
                    return true;
                }
                if(tmp1->vals > tmp2->vals)
                {
                    return false;
                }
                while(!myList.IS_LAST(tmp1))
                {
                    tmp1 = myList.NEXT_RIGHT(tmp1);
                    tmp2 = myList.NEXT_RIGHT(tmp2);
                    if(tmp1->vals < tmp2->vals)
                    {
                        return true;
                    }
                    if(tmp1->vals > tmp2->vals)
                    {
                        return false;
                    }
                    
                }
                return false;
            }
        }
        //if(GETSIGN() == '+') this isnt neccesary but serves as a reminder
        {
            // same as above but with inverted signs for positive comparison instead of negative
            int ct1 = GETDIGITCOUNT();
            int ct2 = myLong.GETDIGITCOUNT();
            if(ct1>ct2)
            {
                return true;
            }
            else if(ct1<ct2)
            {
                return false;
            }
            else
            {
                Link *tmp1 = myList.GET_FIRST();
                Link *tmp2 = myLong.myList.GET_FIRST();
                if(tmp1->vals > tmp2->vals)
                {
                    return true;
                }
                if(tmp1->vals < tmp2->vals)
                {
                    return false;
                }
                while(!myList.IS_LAST(tmp1))
                {
                    tmp1 = myList.NEXT_RIGHT(tmp1);
                    tmp2 = myList.NEXT_RIGHT(tmp2);
                    if(tmp1->vals > tmp2->vals)
                    {
                        return true;
                    }
                    if(tmp1->vals < tmp2->vals)
                    {
                        return false;
                    }
                    
                }
                return false;
            }
        }
        
    }
    return false;
}
bool LongInteger::LESSTHAN(LongInteger myLong)
{
    // if the first LongInt has the sign character '-' (which is of value 45) and the second has '+' (43), this will evaluate to true and therefore lessthan
    if(GETSIGN() > myLong.GETSIGN())
    {
        return true;
    }
    // if the 2 long ints have equal signs
    if(GETSIGN()==myLong.GETSIGN())
    {
        // and theyre both negative
        if(GETSIGN() == '-')
        {
            int ct1 = GETDIGITCOUNT();
            int ct2 = myLong.GETDIGITCOUNT();
            // then the greater negative number is less than the other, and more digits results in a greater number
            if(ct1>ct2)
            {
                return true;
            }
            else if(ct1<ct2)
            {
                return false;
            }
            else
            {
                // if they have the same number of digits, compare every node's value
                Link *tmp1 = myList.GET_FIRST();
                Link *tmp2 = myLong.myList.GET_FIRST();
                if(tmp1->vals > tmp2->vals)
                {
                    return true;
                }
                if(tmp1->vals < tmp2->vals)
                {
                    return false;
                }
                while(!myList.IS_LAST(tmp1))
                {
                    tmp1 = myList.NEXT_RIGHT(tmp1);
                    tmp2 = myList.NEXT_RIGHT(tmp2);
                    if(tmp1->vals > tmp2->vals)
                    {
                        return true;
                    }
                    if(tmp1->vals < tmp2->vals)
                    {
                        return false;
                    }
                    
                }
                return false;
            }
        }
        //if(GETSIGN() == '+') this isnt neccesary but serves as a reminder
        {
            // same as above but with inverted signs for positive comparison instead of negative
            int ct1 = GETDIGITCOUNT();
            int ct2 = myLong.GETDIGITCOUNT();
            if(ct1<ct2)
            {
                return true;
            }
            else if(ct1>ct2)
            {
                return false;
            }
            else
            {
                Link *tmp1 = myList.GET_FIRST();
                Link *tmp2 = myLong.myList.GET_FIRST();
                if(tmp1->vals < tmp2->vals)
                {
                    return true;
                }
                if(tmp1->vals > tmp2->vals)
                {
                    return false;
                }
                while(!myList.IS_LAST(tmp1))
                {
                    tmp1 = myList.NEXT_RIGHT(tmp1);
                    tmp2 = myList.NEXT_RIGHT(tmp2);
                    if(tmp1->vals < tmp2->vals)
                    {
                        return true;
                    }
                    if(tmp1->vals > tmp2->vals)
                    {
                        return false;
                    }
                    
                }
                return false;
            }
        }
        
    }
    return false;
}
bool LongInteger::EQUALTO(LongInteger myLong)
{
    // if not greater than and not less than it must be equal, otherwise not equal
    if(!GREATERTHAN(myLong)&&!LESSTHAN(myLong))
    {
        return true;
    }
    return false;
}
/*
 LongInteger LongInteger::ADD(LongInteger myLong);
 LongInteger LongInteger::SUBTRACT(LongInteger myLong);
 LongInteger LongInteger::MULTIPLY(LongInteger myLong);
 LongInteger LongInteger::POWER(LongInteger myLong);
 LongInteger LongInteger::DIVIDE(LongInteger myLong);
 //*/

int DIGIT(int t)
{
    //finds the number of significant digits in a regular int.
    int count=0;
    int cmp=9;
    if(t>0)
    {
        count++;
        while(t>cmp && count<8)
        {
            cmp=(cmp*10)+9;
            count++;
        }
    }
    
    return count;
}

//to extract the overflow and regular number
//I made this a pointer as despite the paper declaring it as OVER_FLOW(int t) because you wanted the overflow to be returned for any
// given integer, as well as the integer to be modified. In order to do this, the needs to be some reference to the original int, or
// else we would just be modifying an instance of the value t, which would cease to exist upon the end of the function. This method
// allows for any int (i.e. a vals which is the product of an addition/multiplication) to be passed through, corrected for future
// usage, and the overflow value to be returned for tallying up to the next tier.
int OVER_FLOW(int *t)
{
    if(DIGIT(*t)>4)
    {
        int mydigit;
        int overflow;
        mydigit = *t%10000;
        overflow = (*t-mydigit)/10000;
        *t=mydigit;
        return overflow;
    }
    return 0;
}

void Test1(LongInteger X, string name)
{
    //declare local versions of the ints for testing purposes
    LongInteger A;
    LongInteger B;
    LongInteger C;
    LongInteger D;
    LongInteger AX;
    LongInteger AZ;
    A.INITIALIZE("2222");
    B.INITIALIZE("99999999");
    C.INITIALIZE("246813575732");
    D.INITIALIZE("180270361023456789");
    AX.INITIALIZE("29302390234702973402973420937420973420937420937234872349872934872893472893749287423847");
    AZ.INITIALIZE("-98534342983742987342987339234098230498203894209928374662342342342356723423423");
    
    //perform test for the specific LongInteger
    
    cout << name << ":\n\tSize - " << X.GETDIGITCOUNT() << "\n\tNumber - ";
    X.PRINT();
    cout << "\n\t" << name << ">A: " << X.GREATERTHAN(A) << " - " << name << "<A: " << X.LESSTHAN(A) << " - " << name << "=A: " << X.EQUALTO(A);
    cout << "\n\t" << name << ">B: " << X.GREATERTHAN(B) << " - " << name << "<B: " << X.LESSTHAN(B) << " - " << name << "=B: " << X.EQUALTO(B);
    cout << "\n\t" << name << ">C: " << X.GREATERTHAN(C) << " - " << name << "<C: " << X.LESSTHAN(C) << " - " << name << "=C: " << X.EQUALTO(C);
    cout << "\n\t" << name << ">D: " << X.GREATERTHAN(D) << " - " << name << "<D: " << X.LESSTHAN(D) << " - " << name << "=D: " << X.EQUALTO(D);
    cout << "\n\t" << name << ">AX: " << X.GREATERTHAN(AX) << " - " << name << "<AX: " << X.LESSTHAN(AX) << " - " << name << "=AX: " << X.EQUALTO(AX);
    cout << "\n\t" << name << ">AZ: " << X.GREATERTHAN(AZ) << " - " << name << "<AZ: " << X.LESSTHAN(AZ) << " - " << name << "=AZ: " << X.EQUALTO(AZ);
    cout << "\n\n";
}

int main()
{
    // Set up test situation
    LongInteger A;
    LongInteger B;
    LongInteger C;
    LongInteger D;
    LongInteger AX;
    LongInteger AZ;
    A.INITIALIZE("2222");
    B.INITIALIZE("99999999");
    C.INITIALIZE("246813575732");
    D.INITIALIZE("180270361023456789");
    AX.INITIALIZE("29302390234702973402973420937420973420937420937234872349872934872893472893749287423847");
    AZ.INITIALIZE("-98534342983742987342987339234098230498203894209928374662342342342356723423423");
    
    //Begin print information
    
    Test1(A, "A");
    Test1(B, "B");
    Test1(C, "C");
    Test1(D, "D");
    Test1(AX, "AX");
    Test1(AZ, "AZ");
    int myB = 99999999;
    cout << "Pre B:" << myB << " - ";
    int myOverflow = OVER_FLOW(&myB);
    cout << "Post B:" << myB << " - Overflow:" << myOverflow << endl;
    return 0;
}
