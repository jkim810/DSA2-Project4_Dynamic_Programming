#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define LEN 1001

int global_matrix[LEN][LEN] = {0};
const string notMerge = "*** NOT A MERGE ***";

string isMerge(string &a, string &b, string &c){
    int i, j;
    // initialize matrix
    for (i=0; i<LEN; i++) {
        for (j=0; j<LEN; j++) {
            global_matrix[i][j] = 0;
        }
    }
    global_matrix[0][0] = 1;

    if (c.size() != a.size() + b.size()) return notMerge;
    for (i=0; i<=a.size(); i++) {
        for (j=0; j<=b.size(); j++) {
             if (global_matrix[i][j] == 1) {
                if (c[i+j] == a[i]) global_matrix[i+1][j] = 1;
                if (c[i+j] == b[j]) global_matrix[i][j+1] = 1;
            }
        }
    }

    if (global_matrix[a.size()][b.size()] == 1) {
        i=a.size();
        j=b.size();
        while (i>=0 && j>=0) {
            if (global_matrix[i][j] == 1 && (j == 0 || global_matrix[i][j-1] == 0)) {
                c[i+j-1] = toupper(c[i+j-1]);
                i--;
            }
            else j--;
        }
        return c;
    } else {
        return notMerge;
    }
}

int main() {
    string inFilename, outFilename;
    cout << "Enter name of input file: ";
    cin >> inFilename;
    cout << "Enter name of output file: ";
    cin >> outFilename;
    ifstream in(inFilename.c_str());
    ofstream out(outFilename.c_str());

    string a, b, c;
    while (getline(in,a) && getline(in,b) && getline(in,c)) {
        out << isMerge(a, b, c) << endl;
    }

    in.close();
    out.close();
    return 0;
}