#include <iostream>
#include <cstdlib>
#include<math.h>
using namespace std;

int verificare_prim(int n);

class Polinom;
class Monom
{
private:
    int grad;
    float coef;
public:
    Monom(int gr=0,float cf=0)
    {

        try
        {
            grad=gr;
            coef=cf;

            if(grad<0)

                throw 10;
        }

        catch(int i)
        {
            cout<<"!!!!!!!!!!!!!!GRAD NEGATIV!!!!!!!!!!!!!!!!"<<endl;
        }

    }

    Monom(const Monom &ob)
    {
        try
        {
            grad=ob.grad;
            coef=ob.coef;
            if(grad<0)

                throw 10;
        }
        catch(int i)
        {
            cout<<"!!!!!!!!!!!!!!GRAD NEGATIV!!!!!!!!!!!!!!!!"<<endl;
        }

    }
    ~Monom()
    {
        cout<<"destructor"<<endl;
    }
    void set_grad(int gr)
    {
        grad=gr;
    }
    void set_coef(float cf)
    {
        coef=cf;
    }
    int get_grad()
    {
        return grad;
    }
    float get_coef()
    {
        return coef;
    }

    void citire_monom();
    void afisare_monom();
    friend class Polinom;
    friend class Polinom_ireductibil;
    friend class Polinom_reductibil;

};
void Monom::citire_monom()
{
    cout<<"introdu gradul"<<endl;
    cin>>grad;
    cout<<"introdu coeficientul"<<endl;
    cin>>coef;
}
void Monom::afisare_monom()
{
    if(coef>0)
    {
        if(grad==0)
            cout<<"+"<<coef;
        else if(grad==1)
            cout<<"+"<<coef<<"x";
        else if(grad>1)
            cout<<"+"<<coef<<"x^"<<grad;
    }
    else if(coef<0)
    {
        if(grad==0)
            cout<<coef;
        else if(grad==1)
            cout<<coef<<"x";
        else if(grad>1)
            cout<<coef<<"x^"<<grad;
    }

}
class Polinom
{
protected:
    int nr_monoame;
    Monom *m;

public:

    Polinom(int nr=0)
    {
        try
        {
            //if(nr!=0)
            // {
            m=new Monom[nr];

        }
        catch(bad_alloc x)
        {
            cout<<"!!!!!!!!!!NUMAR NEGATIV!!!!!!!!!!!!";
            exit(EXIT_FAILURE);
        }
        nr_monoame=nr;
        // }
        // else
        //    m=NULL;
    }

    Polinom(const Polinom& p)
    {
        try
        {

            m=new Monom[p.nr_monoame];
            for(int i=0; i<p.nr_monoame; i++)
                m[i]=p.m[i];
        }
        catch(bad_alloc x)
        {
            cout<<"!!!!!!!!!!NUMAR NEGATIV!!!!!!!!!!!!";
            exit(EXIT_FAILURE);
        }
        nr_monoame=p.nr_monoame;
    }
    ~Polinom()
    {
        delete[]m;
    }

    friend istream& operator>>(istream&,Polinom&);
    friend ostream& operator<<(ostream&,Polinom&); // virtuala
    Monom operator[](int i);
    void citire_polinom();
    virtual void afisare_polinom();
    void ordonare_coeficienti();
    Polinom& operator=(const Polinom& ob);

};

void Polinom::ordonare_coeficienti()
{
    int i,j;
    for(i=0; i<nr_monoame-1; i++)
        for(j=i+1; j<nr_monoame; j++)
            if(m[i].grad<m[j].grad)
                swap(m[i],m[j]);
}
void Polinom::citire_polinom()
{
    int i;
    //if(nr_monoame==0)
    //{
    cout<<"introdu nr de monoame"<<endl;
    cin>>nr_monoame;
    m=new Monom[nr_monoame];
    //}

    cout<<"dati elemente polnomului"<<endl;
    for(i=0; i<nr_monoame; i++)
    {
        m[i].citire_monom();
    }
    ordonare_coeficienti();
}

void Polinom::afisare_polinom()
{

    int i;
    for(i=0; i<nr_monoame; i++)
        m[i].afisare_monom();
    cout<<endl;

}

ostream& operator<<(ostream &out,Polinom &p)
{
    p.afisare_polinom();
    return out;
}
istream& operator>>(istream& in,Polinom &p)
{
    p.citire_polinom();
    return in;
}
Monom Polinom::operator[](int i)
{
    return m[i];
}

Polinom& Polinom::operator=(const Polinom& ob)
{
    if(this!= &ob)
    {
        nr_monoame=ob.nr_monoame;
        m=new Monom[ob.nr_monoame];
        for(int i=0; i<nr_monoame; i++)
            m[i]=ob.m[i];

    }
    return *this;
}

class Polinom_ireductibil : public Polinom
{
protected:
    int nr;
public:
    Polinom_ireductibil(int nr_monoame = 0, int b = 0) :Polinom(nr_monoame)
    {
        try
        {
            nr = b;
            if(nr<0)
                throw 10;
        }
        catch(int x)
        {
            cout<<"!!!!!!!!!!NUMAR NEGATIV!!!!!!!!!!!!";
        }


    }
    Polinom_ireductibil(const Polinom_ireductibil& ob) :Polinom(ob)
    {
        try
        {
            nr = ob.nr;

            if(nr<0)
                throw 10;
        }
        catch(int x)
        {
            cout<<"!!!!!!!!!!NUMAR NEGATIV!!!!!!!!!!!!";
        }

    }
    ~Polinom_ireductibil()
    {
        cout<<"destructor"<<endl;
    }

    int verificare_prime_intre_ele();
    int criteriul_Eisenstein();
    int maxim();
    Polinom_ireductibil& operator=(const Polinom_ireductibil& ob);
};
Polinom_ireductibil& Polinom_ireductibil::operator=(const Polinom_ireductibil& ob)
{
    if(this!= &ob)
    {
        this->Polinom::operator=(ob);

    }
    return *this;
}
int Polinom_ireductibil::criteriul_Eisenstein()
{

    int p = 2, i, cnt = 0;

    int maxx;
    maxx=maxim();  ///aflam val maxima pt ca sa stim pana unde mergem cu p


    if (verificare_prime_intre_ele() == 1)

    {

repeta:
        for (i = 1; i < nr_monoame ; i++)
        {

            if ((int)(m[i].coef) % p == 0 && (int)(m[0].coef) % p != 0 && (int)(m[nr_monoame - 1].coef) % (p * p) != 0 && p <= maxx)
            {
                cnt++;                         ///trebuie cnt sa fie egal cu nr de elemente -1(in afara de ultimul)
            }

            else if (p <= maxx)
            {

                cnt = 0;
repeta2:
                p = p + 1;
                if (verificare_prim(p) == 0)
                    goto repeta2;

                goto repeta;

            }
            else if (p > maxx)
                break;
        }
    }
    else
        return 0;

    if (cnt == nr_monoame - 1)  ///ptc for ul merge pana la n-1 elemente si numaram doar atatea
        return 1;
    else
        return 0;

    return 1;
}

int verificare_prim(int n)
{
    if (n < 2)
        return 0;
    int d;
    for (d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int Polinom_ireductibil::maxim()
{
    Monom maxx;
    maxx.coef=fabs(m[0].coef);
    for(int i=1; i<nr_monoame; i++)
        if(fabs(m[i].coef)>maxx.coef)
            maxx.coef=fabs(m[i].coef);
    return maxx.coef;

}

int Polinom_ireductibil::verificare_prime_intre_ele()
{
    int cmmdc;
    int i;
    for (i = 0; i < nr_monoame; i++)
        cmmdc =fabs( m[0].coef);
    for (i = 1; i < nr_monoame; i++)
    {
        int copieEL = fabs(m[i].coef);
        while (copieEL != cmmdc)
        {
            if (copieEL > cmmdc)
                copieEL = copieEL - cmmdc;
            else if (copieEL < cmmdc)
                cmmdc = cmmdc - copieEL;
        }

    }

    return cmmdc;
}


class Polinom_reductibil :public Polinom
{
protected:
    int nr;
public:
    Polinom_reductibil(int nr_monoame = 0, int b = 0) :Polinom(nr_monoame)
    {
        nr = b;
    }
    Polinom_reductibil(const Polinom_reductibil& ob) :Polinom(ob)
    {
        nr = ob.nr;
    }
    ~Polinom_reductibil()
    {
        cout<<"destructor"<<endl;
    }
    Polinom_reductibil& operator=(const Polinom_reductibil& ob);
    void afisare_polinom();


};
void Polinom_reductibil::afisare_polinom()
{
    Polinom::afisare_polinom();
    cout<<"AFISARE POLINOM DE GRADUL 2 CA PRODUS DE 2 POLINOAME"<<endl;
    float delta,alfa,beta;
    delta=m[1].coef*m[1].coef-4*m[0].coef*m[2].coef;
    alfa=((-1*m[1].coef)+sqrt(delta))/(2*m[0].coef);
    beta=((-1*m[1].coef)-sqrt(delta))/(2*m[0].coef);
    if (alfa<0)
        cout<<m[0].coef<<"*(X+"<<-1*alfa<<")";
    else if(alfa>0)
        cout<<m[0].coef<<"*(X-"<<alfa<<")";
    cout<<"*";
    if(beta<0)
        cout<<"(X+"<<-1*beta<<")"<<endl;
    else if(beta>0)
        cout<<"(X-"<<beta<<")"<<endl;
}
Polinom_reductibil& Polinom_reductibil::operator=(const Polinom_reductibil& ob)
{
    if(this!= &ob)
    {
        this->Polinom::operator=(ob);

    }
    return *this;
}
int main()
{
    ///Testam exceptia pentru un numar negativ din constructor-ul din clasa de baza Polinom
    /*
    Polinom p(-4);
    p.citire_polinom();
    p.afisare_polinom();
    */

    ///Testam exceptia pentru un numar negativ din constructor-ul din clasa derivata Polinom_ireductibil
    /*
    Polinom_ireductibil pi(-3);
    pi.citire_polinom();
    pi.afisare_polinom();
    */

    ///Testam daca polinomul este ireductibil sau nu
    /*
    Polinom_ireductibil pi;
    pi.citire_polinom();
    pi.afisare_polinom();
    if(pi.criteriul_Eisenstein()==1)
        cout<<"polinomul este ireductibil"<<endl;
    else
       cout<<"polinomul este reductibil"<<endl;
    */

    ///O afisare diferita pentru polinomul de gradul 2 pe care il verificam la punctul anterior daca e reductibil sau nu

    Polinom_reductibil pr;
    pr.citire_polinom();
    pr.afisare_polinom();



    return 0;
}
