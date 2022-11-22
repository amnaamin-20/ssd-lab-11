#include<iostream>

using namespace std;


class Packing{
 
public:
 

virtual string pack()
{
        string p = "name";

        return p;
}
    virtual int price()
    {
        int p=0;

        return p;
    }
};

class CD : public Packing {

public:
string pack()
{
        string p= "CD name";

        return p;
}
};

class CDType : public CD{
protected:
    Packing array[5];

public:
string pack()
{
        string p = "CD Company name";
        return  p;
}
int price()
{
        int p= 0;

        return p;
}
};

class Company : public CD{
public:
int price()
{
        int p= 0;

        return p;
}
};

class Sony : public Company{
public:
    string pack()
    {
        string a = "Sony";
        return a;
    }
    int price()
    {
        int  b = 120;
        return b;
    }
};

class Samsung : public Company{
public:
    string pack()
    {
        string a = "Samsung";
        return a;
    }
    int price()
    {
        int b = 130;
        return b;
    }
};

class CDBuilder : public CDType{
protected:
    Sony a;
    Samsung b;
public:
    void buildSonyCD()
    {
        cout<<"Product pack : "<<a.pack()<<", price :"<<a.price()<<endl;
       
    }
    void buildsamsung()
    {
        cout << "Product pack : " << b.pack() << ", price :" << b.price()<<endl;
    }
};

int main()
{
    CDBuilder obj;
    obj.buildsamsung();
    obj.buildSonyCD();



return 0;
}