#include "eden.h"

#include <stack>


/* Question 2 : 0-credit */

/*  getting an approximation using the new Fraction class */
Fraction<cf_int> ContinuedFraction::getApproximation(unsigned int k) const {
    //TODO
//        if (k==0) {
//            throw Fraction<int>(0,0);
//        }
    
    int counter = 0;
    Fraction<cf_int> toRet = Fraction<cf_int>(1,0);
    stack<cf_int> list = *new stack<cf_int>;
    auto it = (this->getIterator());
    
    while (!it->isDone() && counter<k) {
        list.push(it->next());
        counter++;
    }
    
    while (list.size()!=0) {
//        auto a = list.top();
//        auto temp_n = toRet.getNumerator();
//        auto temp_d = toRet.getDenominator();
//        toRet =  Fraction<cf_int>((a*temp_n)+temp_d,a);
//        list.pop();
        auto x = list.top();
        auto n = toRet.getNumerator();
        auto d = toRet.getDenominator();
        toRet =  Fraction<cf_int>((x*n)+d,toRet.getNumerator());
        list.pop();

        
    }

    return toRet;
    
    
    
}

/* Building a rational cf using the new Fraction class*/
RationalCF::RationalCF(Fraction<cf_int> f) {
//    //TODO
    auto a = f.getNumerator();
    auto b = f.getDenominator();
    
//    while (a!=0) {
//        this->fixedPart.push_back(b/a);
//        auto temp=a;
//        a = b%a;
//        b= temp;
//    }
  
    // same as getCFlargerThanOne from hw1
    while (b != 0) {
        if (a != 0) {
            
            fixedPart.push_back(a / b);
        }
        auto tmp = a % b;
        a= b;
        b = tmp;
    }
    
    
}

/* Question 3 : Euler squared */

Iterator *EulerSquared::getIterator() const {
    //TODO
    return new EulerSquaredIterator;
}


cf_int EulerSquaredIterator::next() {
    // [7 ; 2, 1, 1, 3, 18, 5, 1, 1, 6, 30, 8, 1, 1, 9, 42, 11, 1, 1 ...];
    //TODO
    cf_int temp = index;
    index++;
    if (temp==0) { return 7;}
    if (temp%5 == 2|| temp%5 == 3) {
       
        return 1;
    }
    else if (temp%5 == 1) {
        return 2 + ((temp/5)*3);
    }
    else if (temp%5 == 4) {
        return 3 + ((temp/5)*3);
    }
    return 18 + (((temp/5)-1)*12);
}

bool EulerSquaredIterator::isDone() const {
    return false;
}


/* Question 4 : PeriodicCF iterator*/

Iterator *PeriodicCF::getIterator() const {
        PeriodicCF *cf = new PeriodicCF(fixedPart, periodicPart);
        auto toRet =new PeriodicCFIterator(*cf);
    
        return toRet;
    
}


cf_int PeriodicCFIterator::next() {
    
    
    if (it < cf.fixedPart.size()) {
        (it)++;
        return cf.fixedPart[(it)-1];
    }
    if (cf.periodicPart.size() != 0) {
        cf_int n = cf.fixedPart.size();
        cf_int m = cf.periodicPart.size();
        
        return cf.periodicPart[(it - n) % m];
        
        
    }
    
    
    return 0;
}

bool PeriodicCFIterator::isDone() const {
    //TODO
    if ( it >= cf.fixedPart.size() && cf.periodicPart.size() ==0) {
        return true;
    }
    
    return false;
}


/* Question 5 : MagicBoxCF iterator */

Iterator *MagicBoxCF::getIterator() const {
    return new MagicBoxCFIterator(boxedFraction.getIterator(),a,b);
    
}

cf_int MagicBoxCFIterator::next() {
    //TODO
    if(isDone()) throw -1.0;
    updateIndeces();
    if(k==0 & l==0) return -1;
    cf_int qq = i/k;
    cf_int ii =k,
    jj = l,
    kk = i-k *qq,
    ll= j-l *qq;
    i=ii;
    j=jj;
    k=kk;
    k=kk;
    l=ll;
    
    
    return  qq;
    
}

bool MagicBoxCFIterator::isDone() const {
    return k==0&&l==0;
}



