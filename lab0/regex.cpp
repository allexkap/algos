#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;



struct Vertex {
    char label;
    set<Vertex*> jumps;
    Vertex(char ch) : label(ch) {}
    virtual bool cnd(char) const {
        abort();
    }
};


struct Letter : Vertex {
    Letter(char ch) : Vertex(ch) {}
    bool cnd(char ch) const override {
        return ch == label;
    }
};


struct Dot : Vertex {
    Dot() : Vertex('.') {}
    bool cnd(char ch) const override {
        return true;
    }
};


struct Origin : Vertex {
    Origin() : Vertex('[') {}
    bool cnd(char ch) const override {
        return false;
    }
};


struct Finish : Vertex {
    Finish() : Vertex(']') {}
    bool cnd(char ch) const override {
        return false;
    }
};



struct Group {

    set<Vertex*> inputs, outputs;
    bool transparent = false;

    Group () {};
    Group (Vertex *vertex) : inputs{vertex}, outputs{vertex} {};

    Group& operator=(Vertex *vertex) {
        *this = Group(vertex);
        return *this;
    }

    bool connect(const Group &other) {
        if (outputs.empty()) return false;
        for (auto &v: outputs) {
            v->jumps.insert(other.inputs.begin(), other.inputs.end());
        }
        return true;
    }

    void join(const Group &other, char side) {
        if (side == 'i') {
            inputs.insert(other.inputs.begin(), other.inputs.end());
        }
        else {
            outputs.insert(other.outputs.begin(), other.outputs.end());
        }
    }
};



Group handle_group(vector<Vertex*> &graph, string::iterator &pattern) {
    Group current, previous, result;

    while (*pattern && *pattern != ')') {
        if (*pattern == '(') {
            previous = current;
            current = handle_group(graph, ++pattern);
            if (!previous.connect(current))
                result.join(current, 'i');
        }
        else if (*pattern == '|') {
            result.join(current, 'o');
            current.outputs.clear();
        }
        else if (*pattern == '+') {
            current.connect(current);
        }
        else if (*pattern == '?') {
            if (!previous.outputs.empty())
                current.join(previous, 'o');
            else
                current.transparent = true;
        }
        else if (*pattern == '*') {
            if (!previous.outputs.empty())
                current.join(previous, 'o');
            else
                current.transparent = true;
            current.connect(current);
        }
        else if (*pattern == '.') {
            graph.push_back(new Dot);
            previous = current;
            current = graph.back();
            if (!previous.connect(current))
                result.join(current, 'i');
        }
        else {
            graph.push_back(new Letter(*pattern));
            previous = current;
            current = graph.back();
            if (!previous.connect(current))
                result.join(current, 'i');
        }
        if (previous.transparent)
            result.join(current, 'i');
        ++pattern;
    }

    result.join(current, 'o');
    return result;
}



int main() {

    string pattern = "A?B((C|D*E)F)+G";
    string text = "BCFDDEFG";


    vector<Vertex*> graph;
    auto it = pattern.begin();

    graph.push_back(new Origin);
    auto group = handle_group(graph, it);
    graph.push_back(new Finish);
    Group(graph.front()).connect(group);
    group.connect(graph.back());


    for (auto &v: graph)
        for (auto &j: v->jumps)
            cout << v->label << ' ' << j->label << endl;

    cout << endl <<"Graph" << endl;
    for (auto &v: graph) {
        cout << v->label << " : ";
        for (auto &j: v->jumps) cout << j->label << ' ';
        cout << endl;
    }
    cout << endl;


    set<Vertex*> active, dead;
    active.insert(graph.front()->jumps.begin(), graph.front()->jumps.end());

    cout << "Stages" << endl << "[ : ";
    for (auto &v: active) cout << v->label << ' ';
    cout << endl;

    for (auto &ch: text) {
        dead = active;
        active.clear();
        for (auto &v: dead) {
            if (v->cnd(ch)) {
                active.insert(v->jumps.begin(), v->jumps.end());
            }
        }

        cout << ch << " : ";
        for (auto &v: active) cout << v->label << ' ';
        cout << endl;

        if (!active.size()) break;
    }


    cout << endl;
    if (active.find(graph.back()) != active.end()) cout << "Yes\n";
    else cout << "No\n";

    for (auto &v: graph) delete v;
    return 0;
}
