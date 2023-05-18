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
    // debug
    char id;
    Vertex(char ch='#') : id(ch) {}
};

struct Letter : Vertex {
    char label;
    Letter(char ch) : Vertex(ch), label(ch) {}
    bool cnd(char ch) const override {
        cout << '!' << label << ':' << ch << '\n';
        return ch == label;
    }
};

struct Dot : Vertex {
    bool cnd(char ch) const override {
        cout << '!' << '.' << ':' << ch << '\n';
        return true;
    }
};

struct Final : Vertex {
    bool cnd(char ch) const override {
        return false;
    }
};


int main() {

    string text = "ABCFDDEFG";

    vector<Vertex*> graph;
    Final *end = new Final();

    // AB((C|D*E)F)*G
    int test[15][2] = {{0, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 6}, {2, 5}, {3, 3}, {3, 4}, {4, 5}, {5, 2}, {5, 3}, {5, 4}, {5, 6}, {6, 7}, {7, 8}};
    for (auto &ch: "ABCDEFG") if (ch) graph.push_back(new Letter(ch));
    graph.push_back(end);
    for (int i = 0; i < 14; ++i) graph[test[i][0]]->jumps.insert(graph[test[i][1]]);

    set<Vertex*> active, dead;
    active.insert(graph[0]);

    for (auto &ch: text) {
        dead = active;
        active.clear();
        for (auto &v: dead)
            if (v->cnd(ch)) active.insert(v->jumps.begin(), v->jumps.end());

        cout << "Active: ";
        for (auto &v: active) cout << v->id << ' ';
        cout << endl << endl;

        if (!active.size()) break;
    }


    if (active.find(end) != active.end()) cout << "Yes\n";
    else cout << "No\n";

    for (auto &v: graph) delete v;
    return 0;
}
