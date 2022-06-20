/*Copyright (C) 2015 Olivier Delaneau, Halit Ongen, Emmanouil T. Dermitzakis
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.*/


#include "mode_merge/merge_data.h"

void printModes(){
    cout << "Usage:" << endl;
    cout << " fenrich [mode] [options]" << endl;
    cout << " eg: mergeCounts merge --help" << endl;
    cout << "\x1B[36;1m" << "Available modes:" << "\033[0m" <<  endl;
    cout << "\x1B[37;1m" <<   " merge" << "\033[0m" << " Merge featureCounts .txt files into multi sample bed file" << endl;
}

int main(int argc, char ** argv) {

    cout << "\n" << "\x1B[32;1m" << "Merge featureCounts results into single multi sample bed file" << "\033[0m" << endl;
    cout << " * Authors : Nikolaos M.R. LYKOSKOUFIS" << endl;
    cout << " * Contact : nikolaos.lykoskoufis@unige.ch" << endl;
    cout << " * Version : version 1.0" << endl;

    // MODES
    vector < string > args;
    if(argc < 2){
        printModes();
        exit(0);
    }
    for(int a= 2; a < argc ; a++) args.push_back(string(argv[a]));

    // NULL MODE
    if (strcmp(argv[1], "merge") == 0) merge_main(args);

    else if (strcmp(argv[1], "--help") == 0){
        printModes();
        exit(0);
    } else {
        printModes();
        cout << "Unrecognized mergeCounts mode!" << endl;
    }
}
