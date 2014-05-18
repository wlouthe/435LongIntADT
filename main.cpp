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
    //*
    LongInteger ADD(LongInteger);
    LongInteger ADD(int);
    LongInteger SUBTRACT(LongInteger);
    LongInteger SUBTRACT(int);
    LongInteger MULTIPLY(LongInteger);
    LongInteger MULTIPLY(int);
    LongInteger POWER(int);
    LongInteger DIVIDE(LongInteger);
    int DIGIT(int);
    int OVER_FLOW(int *);
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
    //pushes chunks of 4 backwards onto the new integer
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
            myList.INSERT_LEFT(pushVal);
            count=1;
            pushVal = 0;
        }
        pushVal += (s[sLen--]-48)*count;
        count*=10;
    }
    myList.INSERT_LEFT(pushVal);
    
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
    //THERE SHOULD NEVER BE A NEGATIVE NUMBER STORED IN HERE, REGARDLESS...
    int count=0;
    Link *tmp = myList.GET_FIRST();
    // counts the digits in the first node
    //THERE SHOULD NEVER BE A NEGATIVE NUMBER STORED IN HERE, REGARDLESS...
    int mynegative = 1;
    if(tmp->vals < 0)
    {
        mynegative = -1;
        tmp->vals = tmp->vals * mynegative;
    }
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
    //in the event of some freak accident where there actually is negative numbers somehow, restore tmp vals to its original value.
    tmp->vals = tmp->vals * mynegative;
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
    if(myList.IS_LAST(tmp))
    {
        cout << tmp->vals;
        return;
    }
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
                    }
                }
            }
        }
        cout << tmp->vals;// << endl;
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
            }
        }
    }
    cout << tmp->vals;// << endl;
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
//*
LongInteger LongInteger::ADD(LongInteger myLong)
{
    //declares variables
    LongInteger big;
    LongInteger small;
    LongInteger sum;
    //gets signs of the two ints
    char tmpsign1 = GETSIGN();
    char tmpsign2 = myLong.GETSIGN();
    int overflow = 0;
    // duplicates the integers into "big" and "small" as to not alter the original values
    big = *this;
    small = myLong;
    // allows for absolute value comparison
    big.SETSIGN('+');
    small.SETSIGN('+');
    //finds the absolute bigger or smaller values
    if(big.GREATERTHAN(small))
    {
        //corrects the sign back to its original form
        big.SETSIGN(tmpsign1);
        small.SETSIGN(tmpsign2);
    }
    else
    {
        //corrects the sign back to its original form and swaps positions of the variables
        big = myLong;
        small = *this;
        big.SETSIGN(tmpsign2);
        small.SETSIGN(tmpsign1);
    }
    //makes sure the original signs remained unaltered, although they shouldnt have been affected anyway
    SETSIGN(tmpsign1);
    myLong.SETSIGN(tmpsign2);
    
    //compares signs of the two numbers, if theyre not equal, then this is the equivilent of subtraction and therefore it is sent there, otherwise it sets the sign of the sum to be that of the bigger value
    if(big.GETSIGN() != small.GETSIGN())
    {
        return big.SUBTRACT(small);
    }
    else
    {
        sum.SETSIGN(big.GETSIGN());
    }
    //declares pointers to the nodes
    Link *node1 = big.myList.GET_LAST();
    Link *node2 = small.myList.GET_LAST();
    Link *nodesum;
    //if both nodes are empty then return 0
    if(node1==NULL && node2==NULL)
    {
        sum.INITIALIZE("0");
    }
    else if(node2 == NULL)
    {
        // if the smaller node is empty then return the top node
        sum.myList.INSERT_LEFT(node1->vals);
        while(!big.myList.IS_FIRST(node1))
        {
            node1 = big.myList.NEXT_LEFT(node1);
            sum.myList.INSERT_LEFT(node1->vals);
        }
    }
    else
    {
        // if neither node is empty, add them and return the sum
        
        //adds the first nodes
        sum.myList.INSERT_LEFT(node1->vals + node2->vals);
        nodesum=sum.myList.GET_LAST();
        //if more nodes of the smaller number (and therefore more of the larger also) exist, then perform a loop which occurs over the length of the smaller number
        while(!small.myList.IS_FIRST(node2))
        {
            overflow = OVER_FLOW(&nodesum->vals);
            node1 = big.myList.NEXT_LEFT(node1);
            node2 = small.myList.NEXT_LEFT(node2);
            sum.myList.INSERT_LEFT(node1->vals + node2->vals + overflow);
            nodesum=sum.myList.NEXT_LEFT(nodesum);
        }
        // this variable is a real piece of bit...
        int pieceOfBit = 0;
        overflow = OVER_FLOW(&nodesum->vals);
        if(overflow > 0)
        {
            pieceOfBit = 1;
        }
        // if the larger number has more nodes, then this will continue over the remaining nodes after the small number has been depleted, as well as one final pass if there is an overflow on the last node.
        while(overflow > 0 || !big.myList.IS_FIRST(node1))
        {
            if(pieceOfBit == 0)
            {
                overflow = OVER_FLOW(&nodesum->vals);
            }
            else
            {
                pieceOfBit = 0;
            }
            if(!big.myList.IS_FIRST(node1))
            {
                node1 = big.myList.NEXT_LEFT(node1);
                sum.myList.INSERT_LEFT(node1->vals + overflow);
            }
            else
            {
                if(overflow != 0)
                {
                    sum.myList.INSERT_LEFT(overflow);
                }
            }
            nodesum=sum.myList.NEXT_LEFT(nodesum);
        }
    }
    //returns the final sum
    return sum;
}
LongInteger LongInteger::ADD(int myInt)
{
    LongInteger myAdder;
    char sign = '+';
    
    if(myInt < 0)
    {
        sign = '-';
        myInt *= -1 ;
    }
    if(myInt>9999)
    {
        myAdder.myList.INSERT_RIGHT(myAdder.OVER_FLOW(&myInt));
    }
    myAdder.myList.INSERT_RIGHT(myInt);
    myAdder = ADD(myAdder);
    return myAdder;
}
LongInteger LongInteger::SUBTRACT(LongInteger myLong)
{
    //declares variables
    LongInteger big;
    LongInteger small;
    LongInteger difference;
    LongInteger myZero("0");
    //gets signs of the two ints
    char tmpsign1 = GETSIGN();
    char tmpsign2 = myLong.GETSIGN();
    int overflow = 0;
    // duplicates the integers into "big" and "small" as to not alter the original values
    big = *this;
    small = myLong.ADD(myZero);
    // allows for absolute value comparison
    big.SETSIGN('+');
    small.SETSIGN('+');
    // finds the absolute bigger or smaller value
    if(big.GREATERTHAN(small))
    {
        
        //corrects the sign back to its original form
        big.SETSIGN(tmpsign1);
        //inverts the sign of the number being subtracted from
        small.SETSIGN((tmpsign2=='+')?'-':'+');
    }
    else
    {
        //corrects the sign back to its original form and swaps positions of the variables
        big = myLong;
        small = *this;
        //inverts the sign of the number being subtracted from
        big.SETSIGN((tmpsign2=='+')?'-':'+');
        small.SETSIGN(tmpsign1);
    }
    //makes sure the original signs remained unaltered, although they shouldnt have been affected anyway
    SETSIGN(tmpsign1);
    myLong.SETSIGN(tmpsign2);
    
    //compares signs of the two numbers, if they are equal, then this is the equivilent of addition and therefore it is sent there, otherwise it sets the sign of the sum to be that of the bigger value
    if(big.GETSIGN() == small.GETSIGN())
    {
        return big.ADD(small);
    }
    else
    {
        //makes the signs equal to compare for equality of the numbers
        big.SETSIGN(small.GETSIGN());
        if(big.EQUALTO(small))
        {
            // if theyre the same number with opposite signs, then it returns 0
            difference.myList.INSERT_LEFT(0);
            difference.SETSIGN('+');
            big.SETSIGN((small.GETSIGN()=='+')?'-':'+');
            return difference;
        }
        //otherwise it returns big it its prior sign
        big.SETSIGN((small.GETSIGN()=='+')?'-':'+');
        difference.SETSIGN(big.GETSIGN());
    }
    //declares pointers to the nodes
    Link *node1 = big.myList.GET_LAST();
    Link *node2 = small.myList.GET_LAST();
    Link *nodedifference;
    //if nodes are empty return 0
    if(node1==NULL && node2==NULL)
    {
        difference.INITIALIZE("0");
    }
    else if(node2 == NULL)
    {
        // if the smaller node is empty return the larger one
        difference.myList.INSERT_LEFT(node1->vals);
        while(!big.myList.IS_FIRST(node1))
        {
            node1 = big.myList.NEXT_LEFT(node1);
            difference.myList.INSERT_LEFT(node1->vals);
        }
    }
    else
    {
        //perform initial subtraction of the first nodes
        //if(node1->vals > node2->vals)
        {
            difference.myList.INSERT_LEFT(node1->vals - node2->vals);
        }
        /*
        else
        {
            difference.myList.INSERT_LEFT(node2->vals - node1->vals);
        }
        //*/
        nodedifference=difference.myList.GET_LAST();
        //while there are still nodes in the smaller number continues to subtract using the same process as above but repeated
        while(!small.myList.IS_FIRST(node2))
        {
            
            overflow = OVER_FLOW(&nodedifference->vals);
            node1 = big.myList.NEXT_LEFT(node1);
            node2 = small.myList.NEXT_LEFT(node2);
            //if((node1->vals - overflow) > node2->vals)
            {
                difference.myList.INSERT_LEFT((node1->vals - overflow) - node2->vals);
            }
            /*
            else
            {
                difference.myList.INSERT_LEFT(node2->vals - (node1->vals - overflow));
            }
            //*/
            nodedifference=difference.myList.NEXT_LEFT(nodedifference);
        }
        //while there are still numbers in the larger number, will subtract the overflow from the number and then drag it into the difference.
        while(overflow > 0 || !big.myList.IS_FIRST(node1))
        {
            overflow = OVER_FLOW(&nodedifference->vals);
            if(!big.myList.IS_FIRST(node1))
            {
                node1 = big.myList.NEXT_LEFT(node1);
                difference.myList.INSERT_LEFT(node1->vals - overflow);
            }
            else
            {
                //this should never happen as the arbitrary bigger number is never going to leave overflow in subtraction from a smaller one but whatever
                if(overflow != 0)
                {
                    difference.myList.INSERT_LEFT(overflow);
                }
            }
            nodedifference=difference.myList.NEXT_LEFT(nodedifference);
        }
    }
    //if there are leading 0's as a result of the subtraction, this makes a new instance of the number and fails to include the leading zeros into it.
    LongInteger final;
    int flag = 0;
    final.SETSIGN(difference.GETSIGN());
    node1 = difference.myList.GET_FIRST();
    if(node1->vals != 0)
    {
        flag++;
        final.myList.INSERT_RIGHT(node1->vals);
    }
    while(!difference.myList.IS_LAST(node1))
    {
        node1 = difference.myList.NEXT_RIGHT(node1);
        if(flag == 0)
        {
            if(node1->vals == 0)
            {
                continue;
            }
            else
            {
                flag++;
            }
        }
        final.myList.INSERT_RIGHT(node1->vals);
    }
    return final;
}
LongInteger LongInteger::MULTIPLY(int myInt)
{
    LongInteger myLong;
    char sign = '+';
    
    if(myInt < 0)
    {
        sign = '-';
        myInt *= -1 ;
    }
    if(myInt>9999)
    {
        myLong.myList.INSERT_RIGHT(myLong.OVER_FLOW(&myInt));
    }
    myLong.myList.INSERT_RIGHT(myInt);
    myLong.SETSIGN(sign);
    myLong = MULTIPLY(myLong);
    return myLong;
}
LongInteger LongInteger::MULTIPLY(LongInteger myLong)
{
    //same as adding and subtracting other than the comments which will designate otherwise
    LongInteger big;
    LongInteger small;
    LongInteger product;
    LongInteger total;
    total.INITIALIZE("0");
    char tmpsign1 = GETSIGN();
    char tmpsign2 = myLong.GETSIGN();
    int overflow = 0;
    int count=1;
    big = *this;
    small = myLong;
    big.SETSIGN('+');
    small.SETSIGN('+');
    if(big.GREATERTHAN(small))
    {
        //numbers keep their original signs in this one
        big.SETSIGN(tmpsign1);
        small.SETSIGN(tmpsign2);
    }
    else
    {
        big = myLong;
        small = *this;
        big.SETSIGN(tmpsign2);
        small.SETSIGN(tmpsign1);
    }
    Link *node1 = big.myList.GET_LAST();
    Link *node2 = small.myList.GET_LAST();
    Link *nodeproduct;
    //if either of them are null or equal to total (which is 0 right now) it returns 0.
    if(node1==NULL || node2==NULL || big.EQUALTO(total) || small.EQUALTO(total))
    {
        total.SETSIGN('+');
        return total;
    }
    else
    {
        //performs initial multiplication
        product.myList.INSERT_LEFT(node1->vals * node2->vals);
        nodeproduct=product.myList.GET_LAST();
        //performs all the multiplications against node1 for the first node2
        while(!big.myList.IS_FIRST(node1))
        {
            overflow = OVER_FLOW(&nodeproduct->vals);
            node1 = big.myList.NEXT_LEFT(node1);
            product.myList.INSERT_LEFT((node1->vals * node2->vals)+overflow);
            nodeproduct=product.myList.NEXT_LEFT(nodeproduct);
        }
        overflow = OVER_FLOW(&nodeproduct->vals);
        //accounts for the inital overflow of the first function
        if(overflow > 0)
        {
            product.myList.INSERT_LEFT(overflow);
        }
        //adds this first product to the total
        total = total.ADD(product);
        //*
        // while there are still nodes in small perform essentially the same operation on for that node, except this time remember to increment the nodes and reinitalize overflow and product.
        while(!small.myList.IS_FIRST(node2))
        {
            node2 = small.myList.NEXT_LEFT(node2);
            node1 = big.myList.GET_LAST();
            if(node2->vals == 0)
            {
                count++;
                continue;
            }
            overflow = 0;
            product.~LongInteger();
            new (&product) LongInteger();
            product.myList.INSERT_LEFT(node1->vals * node2->vals);
            nodeproduct=product.myList.GET_LAST();
            while(!big.myList.IS_FIRST(node1))
            {
                overflow = OVER_FLOW(&nodeproduct->vals);
                node1 = big.myList.NEXT_LEFT(node1);
                product.myList.INSERT_LEFT((node1->vals * node2->vals)+overflow);
                nodeproduct=product.myList.NEXT_LEFT(nodeproduct);
            }
            overflow = OVER_FLOW(&nodeproduct->vals);
            if(overflow > 0)
            {
                product.myList.INSERT_LEFT(overflow);
            }
            //this line accounts for shifting left 10000 for every new iteration of small nodes
            for(int i=0; i<count; i++)
            {
                product.myList.INSERT_RIGHT(0);
            }
            count++;
            //adds the new product to the total
            total = total.ADD(product);
        }
        //*/
    }
    //sets the sign of the total to positive if theyre both the same or negative if theyre different
    if(big.GETSIGN() == small.GETSIGN())
    {
        total.SETSIGN('+');
    }
    else
    {
        total.SETSIGN('-');
    }
    //returns the total
    return total;
}

//squares the longint every iteration and finds the bit at each spot of the power being raised to. after using that bit at that position (whether 1 or 0) it shifts right and looks at the next bit. finally, this also adds the current squared value to the total if the bit is 1 in that position. once there are no more bits left in the power we are done
LongInteger LongInteger::POWER(int myPower)
{
    LongInteger copy = *this, total("1");
    while(myPower>0)
    {
        if(myPower&1) total = total.MULTIPLY(copy);
        copy=copy.MULTIPLY(copy);
        myPower=myPower>>1;
    }
    return total;
}
//*
LongInteger LongInteger::DIVIDE(LongInteger myLongOriginal)
{
    //declare initialize needed variables;
    int tmp;
    int multiplier;
    LongInteger copy = *this;
    LongInteger myLong = myLongOriginal;
    LongInteger test;
    LongInteger myZero("0");
    LongInteger myTen("10");
    LongInteger result("0");
    char signbit1 = copy.GETSIGN();
    char signbit2 = myLong.GETSIGN();
    copy.SETSIGN('+');
    myLong.SETSIGN('+');
    int top5Copy = 0;
    int top4MyLong = 0;
    Link *current;
    
    //ensure no division by 0
    if(myLong.EQUALTO(myZero))
    {
        cout << "ERROR CANNOT DIVIDE BY 0 -- UNDEFINED";
        return myZero;
    }
    //finds the first 4 digits in the bottom number (will never change)
    if(myLong.GETDIGITCOUNT()<5)
    {
        top4MyLong = myLong.myList.GET_LAST()->vals;
    }
    else
    {
        multiplier = 1;
        current = myLong.myList.GET_FIRST();
        tmp = myLong.GETDIGITCOUNT()%4;
        if(tmp == 0) tmp = 4;
        top4MyLong = current->vals;
        for(int i=tmp; i<4;i++)
        {
            top4MyLong *= 10;
        }
        for(int i=0; i<tmp; i++)
        {
            multiplier *= 10;
        }
        current = myLong.myList.NEXT_RIGHT(current);
        top4MyLong += ((current->vals)-(current->vals%multiplier))/multiplier;
    }
    //do this until the bottom number cant divide into the top anymore
    while(!copy.LESSTHAN(myLong))
    {
        // Finds the first 5 digits in the top number 
        if(copy.GETDIGITCOUNT()<5)
        {
            top5Copy = copy.myList.GET_LAST()->vals;
        }
        else
        {
            multiplier = 1;
            current = copy.myList.GET_FIRST();
            tmp = copy.GETDIGITCOUNT()%4;
            if(tmp == 0) tmp = 4;
            top5Copy = current->vals;
            for(int i=tmp; i<5;i++)
            {
                top5Copy *= 10;
            }
            for(int i=0; i<tmp-1; i++)
            {
                multiplier *= 10;
            }
            current = myLong.myList.NEXT_RIGHT(current);
            top5Copy += ((current->vals)-(current->vals%multiplier))/multiplier;
        }
        
        //finds the approx number of times the bottom number goes into the top
        tmp = top5Copy/top4MyLong;
        //calculate the value if bot is multiplied by tmp and then shifted all the way right.
        test = copy.SUBTRACT(myLong.MULTIPLY(tmp).MULTIPLY(myTen.POWER(copy.GETDIGITCOUNT()-myLong.GETDIGITCOUNT())));
        //if calculated value above is less than 0 then its because of 1 of two reasons.
        if(test.LESSTHAN(myZero))
        {
            //first if they have the same digit length, then divide final the approx number by 10, because this problem is caused by using 5digits/4digits for a number of the same length
            if(copy.GETDIGITCOUNT()-myLong.GETDIGITCOUNT()-1<0)
            {
                tmp/=10;
                test = copy.SUBTRACT(myLong.MULTIPLY(tmp).MULTIPLY(myTen.POWER(copy.GETDIGITCOUNT()-myLong.GETDIGITCOUNT())));
            }
            else
            {
                //alternatively, if its more digits than the other one, then you can simply use this to shift the projected amount on the bottom over by one more place so that it will be less than the top.
                test = copy.SUBTRACT(myLong.MULTIPLY(tmp).MULTIPLY(myTen.POWER(copy.GETDIGITCOUNT()-myLong.GETDIGITCOUNT()-1)));
            }
        }
        //finally, multiply the result or quotent by 10 and add the new number of times dividing into it.
        result = result.MULTIPLY(myTen);//.POWER(DIGIT(tmp)));
        result = result.ADD(tmp);
        //furthermore shifting the result over additional places based on change in length caused by the subtraction used to create our new top number.
        if(copy.GETDIGITCOUNT()>test.GETDIGITCOUNT()+1 && !test.LESSTHAN(myLong))
        {
            for(int i = copy.GETDIGITCOUNT(); i>test.GETDIGITCOUNT()+1;i--)
            {
                result = result.MULTIPLY(myTen);
            }
        }
        //and copy the confirmed new top value over to be repeated upon.
        copy = test;
    }
    //set the sign
    if(signbit1 == signbit2)
    {
        result.SETSIGN('+');
    }
    else
    {
        result.SETSIGN('-');
    }
    //return
    return result;
}
//*/
/*
//Original divide
LongInteger LongInteger::DIVIDE(LongInteger myLong)
{
    LongInteger copy = *this;
    LongInteger temp, temp2, temp2prev;
    LongInteger quotent("0"),myZero("0"),myNegative("-1"), myTen("10"), myMultiplier;
    Link *current, *firstcopy, *firstmylink;
    int overflow = 0, divisor=0, count=0;
    int dcCopy, dcmyLong, dcMultiplier, multiplier, newmultiplier, lastmultiplier = 0, difference, initialdifference;
    char signbit1, signbit2;
    LongInteger myLongCopy = myLong.ADD(myZero);
    signbit1 = copy.GETSIGN();
    signbit2 = myLongCopy.GETSIGN();
    copy.SETSIGN('+');
    myLongCopy.SETSIGN('+');
    if(myLongCopy.EQUALTO(quotent))
    {
        cout << "ERROR CANNOT DIVIDE BY 0 -- UNDEFINED";
        return quotent;
    }
    copy.SETSIGN(signbit1);
    myLongCopy.SETSIGN(signbit2);
    if(copy.EQUALTO(myLongCopy))
    {
        myMultiplier.INITIALIZE("+1");
        return myMultiplier;
    }
    if(copy.EQUALTO(myLongCopy.MULTIPLY(myNegative)))
    {
        myMultiplier.INITIALIZE("-1");
        return myMultiplier;
    }
    copy.SETSIGN('+');
    myLongCopy.SETSIGN('+');
    if(copy.LESSTHAN(myLongCopy))
    {
        return quotent;
    }
    initialdifference = dcCopy-dcmyLong;
    while(!copy.LESSTHAN(myLongCopy))
    {
        overflow = 0;
        if(copy.EQUALTO(myLongCopy))
        {
            current = quotent.myList.GET_LAST();
            current->vals = current->vals*10+1;
            overflow = OVER_FLOW(&current->vals);
            
            while(overflow)
            {
                if(quotent.myList.IS_FIRST(current))
                {
                    quotent.myList.INSERT_LEFT(overflow);
                }
                else
                {
                    current = quotent.myList.NEXT_LEFT(current);
                    current->vals = current->vals*10+overflow;
                    overflow = OVER_FLOW(&current->vals);
                }
            }
            copy = copy.SUBTRACT(myLongCopy);
            initialdifference--;
        }
        else
        {
            count++;
            //firstcopy = copy.myList.GET_FIRST();
            //firstmylink = myLink.myList.GET_LAST();
            dcCopy = copy.GETDIGITCOUNT();
            dcmyLong = myLongCopy.GETDIGITCOUNT();
            dcMultiplier = 0;
            difference = dcCopy-dcmyLong;
            multiplier = 1;
            myMultiplier.~LongInteger();
            new (&myMultiplier) LongInteger;
            //tmp = myLong.ADD(myZero);
            if(difference != 0)
            {
                difference--;
            }
            while(difference>3)
            {
                myMultiplier.myList.INSERT_RIGHT(0);
                dcMultiplier+=4;
                difference-=4;
            }
            while(difference-- != 0)
            {
                multiplier*=10;
                dcMultiplier++;
            }
            myMultiplier.myList.INSERT_LEFT(multiplier);
            if(lastmultiplier == 0)
            {
                lastmultiplier = dcMultiplier;
            }
            else
            {
                lastmultiplier--;
                while(lastmultiplier != dcMultiplier)
                {
                    current = quotent.myList.GET_LAST();
                    current->vals = (current->vals + 1000000)*10+0;
                    overflow = OVER_FLOW(&current->vals);
                    while(overflow)
                    {
                        if(quotent.myList.IS_FIRST(current))
                        {
                            overflow%=1000;
                            if(overflow!=0)
                                quotent.myList.INSERT_LEFT(overflow);
                            overflow = 0;
                        }
                        else
                        {
                            overflow%=1000;
                            current = quotent.myList.NEXT_LEFT(current);
                            current->vals = (current->vals + 1000000)*10+overflow;
                            overflow = OVER_FLOW(&current->vals);
                        }
                    }
                    lastmultiplier--;
                }
            }
            
            // now using multiplier as a counter for times that the smaller number divides the greater number
            multiplier = 0;
            
            temp = myLongCopy.MULTIPLY(myMultiplier);
           
            temp2 = temp.ADD(myZero);
            temp2prev = temp.ADD(myZero);
            while(!copy.LESSTHAN(temp2))
            {
                multiplier++;
                temp2prev = temp2.ADD(myZero);
                temp2 = temp2.ADD(temp);
                //cout << "\n"; copy.PRINT(); cout << " > "; temp2.PRINT(); cout << " = " << !copy.LESSTHAN(temp2);
                
            }
            temp2prev = temp2prev.ADD(myZero);
            //cout << "\ntemp2prev: ";temp2prev.PRINT();
            //cout << "\n";copy.PRINT(); cout << " - ";temp2prev.PRINT();
            copy = copy.SUBTRACT(temp2prev);
            //cout << "\ncopynew: ";copy.PRINT();
            //cout << "\nnumber of times fit: " << multiplier;
            //cout << "\nquotent before: ";quotent.PRINT();
            current = quotent.myList.GET_LAST();
            current->vals = (current->vals + 1000000)*10+multiplier;
            overflow = OVER_FLOW(&current->vals);            
            while(overflow)
            {
                if(quotent.myList.IS_FIRST(current))
                {
                    overflow%=1000;
                    if(overflow!=0)
                        quotent.myList.INSERT_LEFT(overflow);
                    overflow = 0;
                    //current->vals = current->vals*10+overflow;
                    //overflow = OVER_FLOW(&current->vals);
                }
                else
                {
                    overflow%=1000;
                    current = quotent.myList.NEXT_LEFT(current);
                    current->vals = (current->vals + 1000000)*10+overflow;
                    overflow = OVER_FLOW(&current->vals);
                }
            }
            //cout << "\nquotent as of now: ";quotent.PRINT();
            //if(count > 2)
              //  break;
        }
    }
    quotent.SETSIGN((signbit1==signbit2)?'+':'-');
    return quotent;
}
//*/

int LongInteger::DIGIT(int t)
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
int LongInteger::OVER_FLOW(int *t)
{
    if(*t<0)
    {
        *t+=10000;
        return 1;
    }
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
    
    //*
    // Part 1:
    Test1(A, "A");
    Test1(B, "B");
    Test1(C, "C");
    Test1(D, "D");
    Test1(AX, "AX");
    Test1(AZ, "AZ");
    int myB = 99999999;
    cout << "Pre B:" << myB << " - ";
    int myOverflow = B.OVER_FLOW(&myB);
    cout << "Post B:" << myB << " - Overflow:" << myOverflow << endl;
    //*/
    //*
    // Part 2:
    cout << "\nE = A+D = ";
    LongInteger E = A.ADD(D);
    E.PRINT();
    cout << "\nF = B+C = ";
    LongInteger F = B.ADD(C);
    F.PRINT();
    cout << "\nG = C+D = ";
    LongInteger G = C.ADD(D);
    G.PRINT();
    cout << "\nH = E+E = ";
    LongInteger H = E.ADD(E);
    H.PRINT();
    cout << "\nI = A+E = ";
    LongInteger I = A.ADD(E);
    I.PRINT();
    cout << "\nJ = B+G = ";
    LongInteger J = B.ADD(G);
    J.PRINT();
    cout << "\nK = A-D = ";
    LongInteger K = A.SUBTRACT(D);
    K.PRINT();
    cout << "\nL = C-D = ";
    LongInteger L = C.SUBTRACT(D);
    L.PRINT();
    cout << "\nM = D-C = ";
    LongInteger M = D.SUBTRACT(C);
    M.PRINT();
    cout << "\nN = H-H = ";
    LongInteger N = H.SUBTRACT(H);
    N.PRINT();
    cout << "\nO = L-K = ";
    LongInteger O = L.SUBTRACT(K);
    O.PRINT();
    cout << "\nP = J-M = ";
    LongInteger P = J.SUBTRACT(M);
    P.PRINT();
    cout << "\nQ = A*D = ";
    LongInteger Q = A.MULTIPLY(D);
    Q.PRINT();
    cout << "\nR = B*C = ";
    LongInteger R = B.MULTIPLY(C);
    R.PRINT();
    cout << "\nS = D*D = ";
    LongInteger S = D.MULTIPLY(D);
    S.PRINT();
    cout << "\nT = K*E = ";
    LongInteger T = K.MULTIPLY(E);
    T.PRINT();
    cout << "\nU = F*L = ";
    LongInteger U = F.MULTIPLY(L);
    U.PRINT();
    cout << "\nV = I*J = ";
    LongInteger V = I.MULTIPLY(J);
    V.PRINT();
    // part 3
    cout << "\nW = D^2 = ";
    LongInteger W = D.POWER(2);
    W.PRINT();
    cout << "\nX = A^5 = ";
    LongInteger X = A.POWER(5);
    X.PRINT();
    cout << "\nY = B^10 = ";
    LongInteger Y = B.POWER(10);
    Y.PRINT();
    cout << "\nZ = W^4 = ";
    LongInteger Z = W.POWER(4);
    Z.PRINT();
    cout << "\nAA = E^2 = ";
    LongInteger AA = E.POWER(2);
    AA.PRINT();
    cout << "\nAB = K^2 = ";
    LongInteger AB = K.POWER(2);
    AB.PRINT();
    cout << "\nAC = D/B = ";
    LongInteger AC = D.DIVIDE(B);
    AC.PRINT();
    //*
    cout << "\nAD = D/A = ";
    LongInteger AD = D.DIVIDE(A);
    AD.PRINT();
    //*
    cout << "\nAE = Q/D = ";
    LongInteger AE = Q.DIVIDE(D);
    AE.PRINT();
    cout << "\nAF = T/K = ";
    LongInteger AF = T.DIVIDE(K);
    AF.PRINT();
    cout << "\nAG = H/E = ";
    LongInteger AG = H.DIVIDE(E);
    AG.PRINT();
    cout << "\nAH = U/U = ";
    LongInteger AH = U.DIVIDE(U);
    AH.PRINT();
    //*
     //additional test cases
    cout << "\nE1 = AX*AZ = ";
    LongInteger E1 = AX.MULTIPLY(AZ);
    E1.PRINT();
    cout << "\nE2 = AX*AX = ";
    LongInteger E2 = AX.MULTIPLY(AX);
    E2.PRINT();
    cout << "\nE3 = AZ*AZ = ";
    LongInteger E3 = AZ.MULTIPLY(AZ);
    E3.PRINT();
    cout << "\nE4 = E2*E3 = ";
    LongInteger E4 = E2.MULTIPLY(E3);
    E4.PRINT();
    cout << "\nE5 = AX^10 = ";
    LongInteger E5 = AX.POWER(10);
    E5.PRINT();
    cout << "\nE6 = AZ^14 = ";
    LongInteger E6 = AZ.POWER(14);
    E6.PRINT();
    cout << "\nE7 = E2^4 = ";
    LongInteger E7 = E2.POWER(4);
    E7.PRINT();
    cout << "\nE8 = E3^7 = ";
    LongInteger E8 = E3.POWER(7);
    E8.PRINT();
    //*/
    cout << endl;
    return 0;
}
