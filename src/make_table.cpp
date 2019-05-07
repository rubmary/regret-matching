#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

string proc(string x) {
    return "procedimiento-" + x + ".txt";
}

int total_procs = 3;
string separator = "$ & $";

int main(int argc, char **argv) {
    string game_name = argv[1];
    string path = "../tiempos/" + game_name + "/";
    vector <string> procs({"A", "B", "C"});
    int rep = 10;
    vector <fstream> files(total_procs);
    for (int i = 0; i < total_procs; i++){
        string name_file = path + proc(procs[i]);
        files[i].open(name_file.c_str());
        files[i] >> rep;
    }
    double time;
    double iterations;
    
    double ratio;
    string format_ratio;
    for (int i = 0; i < rep + 1; i++) {
        for (int j = 0; j < total_procs; j++) {
            files[j] >> time >> iterations;
            ratio = time/iterations;
            cout << fixed << setprecision(3) << '$' << time << separator;
            int precision = (i == rep) ? 1 : 0;
            cout << fixed << setprecision(precision) << iterations << separator;
            ostringstream stream;
            stream << scientific << setprecision(2) << ratio;
            format_ratio = stream.str();
            int len = format_ratio.size();
            string format_ratio2 = format_ratio.substr(0, 4) + " {\\times} 10^{" + format_ratio.substr(5, len-5) + '}';
            cout << scientific << setprecision(2) << format_ratio2 << "$ " << (j == total_procs - 1 ? "\\\\" : "& ");
        }
        cout << ((i >= rep-1) ? " \\hline" : "") << endl;
    }

}