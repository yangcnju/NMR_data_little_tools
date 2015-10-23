#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<string> get_peaks(const string &fname);
void process(const string &fname);

int main()
{
  cout << "Extract peak heights from nmrPipe generated peak list. " << endl;
  cout << "Enter filename ('q' to quit): " << endl;

  string filename;	
  while(cin >> filename && filename != "q"){
    process(filename);
  }	

  return 0;
}

vector<string> get_peaks(const string &fname)
{
  ifstream filein(fname);
  string line;
  vector<string> lines;

  // skip the first 19 lines that do not contain peaks.
  for(int i=0; i!=19; ++i)
    getline(filein,line);

  while(getline(filein,line)){
    lines.push_back(line);
  }
  filein.close();
  return lines;
}

void process(const string &fname)
{
  vector<string> peaks;
  peaks = get_peaks(fname);
  string outfile = fname + ".out";
  ofstream ofile(outfile);
  for(auto peak : peaks) {
    vector<string> peak_elems;
    istringstream peak_stream(peak);
    copy(istream_iterator<string>(peak_stream),
         istream_iterator<string>(),
         back_inserter(peak_elems));
		vector<string> peak_concised;
		peak_concised.push_back(peak_elems[5]);	// 6th ppm
		peak_concised.push_back(peak_elems[6]); // 7th ppm
		peak_concised.push_back(peak_elems[17]);// 18th height
		peak_concised.push_back(peak_elems[18]);
		peak_concised.push_back(peak_elems[19]);
		for(auto elem : peak_concised)
			ofile << elem << "\t";
    ofile << endl;
	}
  cout << "output complete." << endl;
  ofile.close();	
}

