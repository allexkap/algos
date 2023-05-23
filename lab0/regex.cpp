#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;



struct Vertex {
    set<Vertex*> jumps;
    virtual bool cnd(char) const {
        abort();
    }
    char id; Vertex(char ch) : id(ch) {} // debug
};


struct Letter : Vertex {
    char label;
    Letter(char ch) : Vertex(ch), label(ch) {}
    bool cnd(char ch) const override {
        cout << '!' << label << ':' << ch << '\n';
        return ch == label;
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
        inputs.clear();
        outputs.clear();
        inputs.insert(vertex);
        outputs.insert(vertex);
        transparent = false;
        return *this;
    }

    bool connect(const Group &other) {
        if (outputs.empty()) return false;
        for (auto &v: outputs) {
            v->jumps.insert(other.inputs.begin(), other.inputs.end());
        }
        return true;
    }
};



Group handle_group(vector<Vertex*> &graph, string::iterator &pattern) {
    Group current, previous, result;

    while (*pattern && *pattern != ')') {
        if (*pattern == '(') {
            previous = current;
            current = handle_group(graph, ++pattern);
            if (!previous.connect(current)) {
                result.inputs.insert(current.inputs.begin(), current.inputs.end());
            }
        }
        else if (*pattern == '|') {
            result.outputs.insert(current.outputs.begin(), current.outputs.end());
            current.outputs.clear();
        }
        else if (*pattern == '+') {
            current.connect(current);
        }
        else if (*pattern == '?') {
            if (previous.outputs.empty()) {
                current.transparent = true;
            }
            else {
                current.outputs.insert(previous.outputs.begin(), previous.outputs.end());
            }
        }
        else if (*pattern == '*') {
            if (previous.outputs.empty()) {
                current.transparent = true;
            }
            else {
                current.outputs.insert(previous.outputs.begin(), previous.outputs.end());
            }
            current.connect(current);
        }
        else {
            graph.push_back(new Letter(*pattern));
            previous = current;
            current = graph.back();
            if (!previous.connect(current)) {
                result.inputs.insert(current.inputs.begin(), current.inputs.end());
            }
        }
        if (previous.transparent) {
            result.inputs.insert(current.inputs.begin(), current.inputs.end());
        }
        ++pattern;
    }

    result.outputs.insert(current.outputs.begin(), current.outputs.end());
    return result;
}



int main() {

    string pattern = "A?B((C|D*E)F)+G";
    string text = "BCFDDEFG";


    vector<Vertex*> graph;
    auto it = pattern.begin();

    graph.push_back(new Origin());
    auto group = handle_group(graph, it);
    graph.push_back(new Finish());
    Group(graph[0]).connect(group);
    group.connect(graph.back());

    cout << "Graph:" << endl;
    for (auto &v: graph) {
        cout << v->id << " : ";
        for (auto &j: v->jumps) cout << j->id << ' ';
        cout << endl;
    }
    cout << endl << endl;


    set<Vertex*> active, dead;
    active.insert(graph[0]->jumps.begin(), graph[0]->jumps.end());

    for (auto &ch: text) {
        dead = active;
        active.clear();
        for (auto &v: dead) {
            if (v->cnd(ch)) {
                active.insert(v->jumps.begin(), v->jumps.end());
            }
        }

        cout << "Active: ";
        for (auto &v: active) cout << v->id << ' ';
        cout << endl << endl;

        if (!active.size()) break;
    }


    if (active.find(graph.back()) != active.end()) cout << "Yes\n";
    else cout << "No\n";

    for (auto &v: graph) delete v;
    return 0;
}
