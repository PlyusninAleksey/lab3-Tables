#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Monom.h"
#include "List.h"


class Polynomial
{
public:

    List<Monom> monoms;
    std::string infix;

    Polynomial() {}
    Polynomial(std::string infix_) :infix(infix_) {}
    Polynomial(const Polynomial& obj) :monoms(obj.monoms) {}

    bool ValidCheck() {
        for (char symbol : infix) {
            if (!std::isdigit(symbol) && !std::isalpha(symbol) && symbol != '-' && symbol != '+' && symbol != '*' && symbol != '^' && symbol != '.' && symbol != ' ') { return false; }
        }
        return true;
    }

    void push(Monom& obj)
    {
        bool flag = false;

        for (auto it = monoms.Begin(); it != monoms.End(); it++)
        {
            if (*it == obj)
            {
                it->coef += obj.coef;
                if (it->coef == 0)
                {
                    monoms.Erase(it);
                }
                flag = true;
                break;
            }

        }
        if (flag != true && obj.coef != 0)
        {
            monoms.PushBack(obj);
        }
    }

    void toPolynom()
    {
        if (ValidCheck() == true)
        {
            std::stringstream ss(infix);
            std::string term;
            while (ss >> term)
            {
                if (term == "+")
                {
                    continue;
                }
                double coef;
                int degreeX, degreeY, degreeZ;
                sscanf_s(term.c_str(), "%lf*x^%d*y^%d*z^%d", &coef, &degreeX, &degreeY, &degreeZ);
                monoms.PushBack(Monom(coef, degreeX, degreeY, degreeZ));
            }
        }
        else
        {
            throw std::exception("Valid infix");
        }
    }
    friend std::ostream& operator<<(std::ostream& stream, const Polynomial& obj)
    {
        stream << obj.monoms.Begin().target->value;
        if (obj.monoms.Begin() != obj.monoms.End())
        {
            auto it = obj.monoms.Begin();
            ++it;
            for (; it != obj.monoms.End(); ++it)
            {
                stream << " + " << *it;
            }
        }
        return stream;
    }
    Polynomial operator*(const Polynomial& obj) {
        Polynomial res;
        for (auto it1 = monoms.Begin(); it1 != monoms.End(); it1++) {
            for (auto it2 = obj.monoms.Begin(); it2 != obj.monoms.End(); it2++) {
                Monom comp = (*it1) * (*it2);
                res.push(comp);
            }
        }
        return res;
    }

    Polynomial operator+(const Polynomial& obj)
    {
        Polynomial res(*this);
        for (auto it = obj.monoms.Begin(); it != obj.monoms.End(); ++it)
        {
            res.push(*it);
        }
        return res;
    }
    
    bool operator==(const Polynomial& obj) {
        size_t counterSrc = 0;
        size_t counterTrg = 0;
        for (auto i = this->monoms.Begin(); i != this->monoms.End(); i++) counterSrc++;
        for (auto i = obj.monoms.Begin(); i != obj.monoms.End(); i++) counterTrg++;
        if (counterSrc != counterTrg) return false;

        for (auto i = this->monoms.Begin(); i != this->monoms.End(); i++) {
            for (auto k = obj.monoms.Begin(); k != obj.monoms.End(); k++) {
                if (*i == *k) {
                    counterSrc--;
                    break;
                }
            }
        }

        return !counterSrc;
    }

    bool operator!=(const Polynomial& obj) {
        return !(*this == obj);
    }
};