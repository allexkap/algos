#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <functional>
#include <cmath>
#include "token.cpp"
using namespace std;


unordered_map<char, long> operators {
    {'+',   0x000},
    {'-',   0x001},
    {'*',   0x102},
    {'/',   0x103},
    {'^', 0x10204},
    {'(',  0xfe05},
    {')',  0xff06},
};
vector<function<double(double, double)>> actions {
    [](double a, double b) { return a + b; },
    [](double a, double b) { return a - b; },
    [](double a, double b) { return a * b; },
    [](double a, double b) { return a / b; },
    [](double a, double b) { return pow(a, b); },
};


vector<Token> tokenize(const string &expr) {
    vector<Token> tokens;
    for (size_t i = 0, j; i < expr.size(); ++i) {
        if ('0' <= expr[i] && expr[i] <= '9') {
            tokens.emplace_back(stod(&expr[i], &j));
            i += j-1;
        }
        else if (auto search = operators.find(expr[i]); search != operators.end()) {
            tokens.emplace_back(search->second);
        }
    }
    return tokens;
}


vector<Token> toPostfix(const vector<Token> &infix) {

    stack<Token> opstack;
    vector<Token> postfix;
    postfix.reserve(infix.size());

    for (const Token &token: infix) {
        if (token.isNum()) {
            postfix.push_back(token);
        }
        else if (token.getPriority() == -2) {
            opstack.push(token);
        }
        else if (token.getPriority() == -1){
            while (opstack.top().getPriority() != -2) {
                postfix.push_back(opstack.top());
                opstack.pop();
            }
            opstack.pop();
        }
        else {
            while (opstack.size() && (opstack.top().getPriority() > token.getPriority()
                                  || opstack.top().getPriority() == token.getPriority() && token.isLeftAss())) {
                postfix.push_back(opstack.top());
                opstack.pop();
            }
            opstack.push(token);
        }
    }

    while (opstack.size()) {
        postfix.push_back(opstack.top());
        opstack.pop();
    }

    return postfix;
}


double popr(stack<Token> &s) {
    double t = s.top().num;
    s.pop();
    return t;
}


double evalPostfix(const vector<Token> &postfix) {
    stack<Token> argstack;
    for (const Token &token: postfix) {
        if (!token.isNum())
            argstack.emplace(actions[token.getIndex()](popr(argstack), popr(argstack)));
        else
            argstack.push(token);
    }
    return argstack.top().num;
}


void coutTokens(const vector<Token> &tokens) {
    static const string chars = "+-*/^()";
    for (const Token &t: tokens) {
        if (t.isNum()) cout << t.num;
        else cout << chars[t.getIndex()];
        cout << ' ';
    }
    cout << endl;
}


int main() {
    fstream file("shunting_yard.in");

    string expr;
    getline(file, expr);

    auto tokens = tokenize(expr);
    auto postfix = toPostfix(tokens);
    double result = evalPostfix(postfix);

    coutTokens(tokens);
    coutTokens(postfix);
    cout << result << endl;

    return 0;
}
