#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int tmp = 0;
struct Stack {
    double number;
    char znak;
    Stack* next;
};
Stack* top1;
Stack* top2;

void replace_ALL(string& s, string ss, string ch) {
    int pos = s.find(ss);
    while (pos != string::npos) {
        s.replace(pos, ss.length(), ch);
        pos = s.find(ss);
    }
}

int error(string s) {
    int balance = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            balance++;
        }
        if (s[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            return -1;
        }
    }

    if (balance != 0) {
       return -1;
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '/' && s[i + 1] == '0') {
            return -1;
        }
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' && s[i + 1] == ')') {
            return -1;
        }
    }


    for (int i = 0; i < s.length(); i++) {
        if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && s[i + 1] == ')') {
            return -1;
        }
        if ((s[i] >= '0' &&  s[i] <= '9') || s[i] == '+' || s[i] == '-' || s[i] == '*'
            || s[i] == '/' || s[i] == '^' || s[i] == 's' || s[i] == 'c' || s[i] == 't'
             || s[i] == 'l' || s[i] == 'k' || s[i] == ')' || s[i] == '('|| s[i] == '.') {
        } else {
        return -1;
        }
    }

    for (int i = 0; i < s.length(); i++) {
        if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') &&
            (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/')) {
            return -1;
        }
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '/' && s[i + 1] == '^') {
            return -1;
        }
    }

    if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-' || s[s.length() - 1] == '*' ||
        s[s.length() - 1] == '/' || s[0] == '*' || s[0] == '/') {
        return -1;
    }
}

void push(Stack*& t, double num, char znak) {
    Stack* p = (Stack*)malloc(sizeof(Stack));
    (*p).number = num;
    (*p).znak = znak;
    (*p).next = t;
    t = p;
}

Stack pop(Stack*& t) {
    Stack ch = *t;
    t = (*t).next;
    return ch;
}

void apply(char znak) {
    double elem2 = pop(top1).number;
    if (znak == '+') {
        push(top1, pop(top1).number + elem2, '@');
    }
    if (znak == '-') {
        push(top1, pop(top1).number - elem2, '@');
    }
    if (znak == '/') {
        if (elem2 == 0) {
            tmp = -1;
            return;
        }
        push(top1, pop(top1).number / elem2, '@');
    }
    if (znak == '*') {
        push(top1, pop(top1).number * elem2, '@');
    }
    if (znak == 's') {
        push(top1, sin(elem2), '@');
    }
    if (znak == 'c') {
        push(top1, cos(elem2), '@');
    }
    if (znak == 't') {
        push(top1, tan(elem2), '@');
    }
    if (znak == 'l') {
        if (elem2 <= 0) {
            tmp = -1;
            return;
        }
        push(top1, log(elem2), '@');
    }
    if (znak == '^') {
        push(top1, pow(pop(top1).number, elem2), '@');
    }
    if (znak == 'k') {
        if (elem2 <= 0) {
            tmp = -1;
            return;
        }
        push(top1, sqrt(elem2), '@');
    }
}

int prior(char a) {
    if (a == '(') {
        return 0;
    }
    if (a == '+' || a == '-') {
        return 1;
    }
    if (a == '*' || a == '/') {
        return 2;
    }
    if (a == '^'|| a == 'k') {
        return 3;
    }
    if (a == 's' || a == 'c' || a == 't' || a == 'l') {
        return 5;
    }
}

int calc(string s, double &ans) {
    string ss;
    tmp = 0;
    replace_ALL(s, "sin", "s");
    replace_ALL(s, "cos", "c");
    replace_ALL(s, "tg", "t");
    replace_ALL(s, "ln", "l");
    replace_ALL(s, "sqrt", "k");
    if (s[0] == '-') {
        s = '0' + s;
    }
    if (s[0] == '+') {
        s = '0' + s;
    }
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '(' && s[i + 1] == '-') {
            ss = ss + "(0";
        } else {
            ss = ss + s[i];
        }
    }
    ss = ss + s[s.length() - 1];
    s = ss;

    if (error(s) == -1) return -1;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            double temp = 0;
            while (s[i] >= '0' && s[i] <= '9' && i < s.length()) {
                temp = temp * 10 + (s[i] - '0');
                i++;
            }
            if(s[i] == '.') {
                i++;
                int z = 10;
                while (s[i] >= '0' && s[i] <= '9' && i < s.length()) {
                    temp = temp * z + (s[i] - '0');
                    temp = temp / z;
                    z = z*10;
                    i++;
                }
            }

            i--;


            push(top1, temp, '@');
        }

        if (s[i] == '(') push(top2, 0, s[i]);

        if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
                if (tmp == -1) return -1;
            }
            pop(top2);
        }

        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'
            || s[i] == 's' || s[i] == 'c' || s[i] == 't' || s[i] == 'l' || s[i] == 'k') {
            while (top2 != nullptr && prior(s[i]) <= prior((*top2).znak)) {
                apply(pop(top2).znak);
                if (tmp == -1) return -1;
            }
            push(top2, 0, s[i]);
        }
    }
    while (top2 != nullptr) {
           apply(pop(top2).znak);
           if (tmp == -1) return -1;
       }
       ans = pop(top1).number;
return tmp;
}
