
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int GRID_SCALE = 10;
const float PI = 3.14159;
const size_t LATTICE_POINTS_PER_SIDE = 11; // number of points to divide each cubic subvolume's side

void PrintWave(const vector<double>& wave) {
  for (auto x: wave)
    cout << x << " ";
  cout << endl;
  return;
}
  
bool KeyCompare(pair<double,double> p1, pair<double,double> p2) { 
  return p1.first < p2.first;
}

/// Converts map to vector of map values, in order of the keys
vector<double> MapToVec(const map<double,double>& wave) {
  vector<double> values;
  vector<pair<double,double>> key_values;
  for (auto x: wave) {
    key_values.push_back(pair<double,double>(x.first, x.second));
  }

  sort(key_values.begin(), key_values.end(), KeyCompare);
  for (auto k: key_values) {
    values.push_back(k.second);
  }
  
  return values;
}


double gridSize(int depth) {
  if (depth == 0) {
    return 0.5;
  }
  return 1.0 * gridSize(depth - 1)/2;
}

/// Computes integral /int |f'' df| for given wave
/// Uses discrete symmetric definitions:
/// f'(x) = [f(x+a) - f(x-a)]/2a
/// f''(x) = [f(x+2a) - 2f(x) + f(x-2a)]/4a^2
float Energy(const vector<double>& f_array) {
  float total_energy = 0;
  for (size_t i = 2; i < f_array.size()-2; i++) {
    total_energy += abs((f_array.at(i+2) - 2*f_array.at(i) + f_array.at(i-2))*(f_array.at(i+1) - f_array.at(i)))/4;
  }
  return total_energy;
}

/// Given a collection of 3d points, size of lattice spacing, and number of lattice points on each side of a cube centered at each point of the collection, this function computes union of the cube volumes in units of lattice points.
size_t volumeUnion(const vector<vector<double>>& f_profile, double lattice_spacing, size_t side_points) {
  set<string> occupied_points;  // each point is represented as a string "x_y_z" for ease of storage
  int cube_radius = (side_points - 1)/2;
  for (auto p: f_profile) {
    int x = p[0]/lattice_spacing;
    int y = p[1]/lattice_spacing;
    int z = p[2]/lattice_spacing;
    for (int i = x-cube_radius; i <= x+cube_radius; i++) {
      for (int j = y-cube_radius; j <= y+cube_radius; j++) {
	    for (int k = z-cube_radius; k <= z+cube_radius; k++) {
	      stringstream point_hash;
	      point_hash << i << "_" << j << "_" << k;
	      occupied_points.insert(point_hash.str());
	    }
      }
    }
  }
  return occupied_points.size();
}

double computeMeanRadius(const vector<vector<double>>& f_profile) {
  /// Given a collection of 3d points, this function computes the mean distance to centroid.
  vector<double> centroid(3,0);
  for (auto x: f_profile) {
    for (int i = 0; i <= 2; i++) 
      centroid[i] += x.at(i);
  }
  for (int i = 0; i <= 2; i++)
    centroid[i] /= f_profile.size();

  double  sum_dist = 0;
  for (auto x: f_profile)
    sum_dist += sqrt(pow(x[0] - centroid[0],2) + pow(x[1] - centroid[1], 2) + pow(x[2] - centroid[2], 2));
  
  return  sum_dist/f_profile.size();
}

vector<vector<double>> computeProfile(const vector<double>& f_array) {
  vector<double> f1_array;
  for (size_t i = 1; i < f_array.size()-1; i++) {
    f1_array.push_back((f_array.at(i+1) - f_array.at(i-1))/2);
  }

  vector<double> f2_array;
  for (size_t i = 1; i < f1_array.size()-1; i++) {
    f2_array.push_back((f1_array.at(i+1) - f1_array.at(i-1))/2);
  }

  vector<vector<double>> f_profile;
  for (size_t i = 0; i < f2_array.size(); i++) {
    vector<double> curr_point;
    curr_point.push_back(f2_array.at(i));
    curr_point.push_back(f1_array.at(i+1));
    curr_point.push_back(f_array.at(i+2));
    f_profile.push_back(curr_point);
  }
  return f_profile;
}

void WriteProfile(const vector<double>& f_array, string outfile_name) {
  vector<vector<double>> f_profile = computeProfile(f_array);
  ofstream outfile(outfile_name.c_str());
  outfile << "f2,f1,f\n";
  for (auto x: f_profile) {
    outfile << x[0] << "," << x[1] << "," << x[2] << "\n";
  }
}

/// Computes the 'space-filling' definition of Variety:
/// First the profile of the function in (f,f',f'')-space is computed.
/// Next a centroid and average radius is computed, which defines a volume _V
/// Now a little box (volume = _V/N) is drawn around each of the N points in the profile,
/// and finally the ratio of the union of these boxes' volumes to _V is Variety.
  float Variety(const vector<double>& f_array) {

    vector<vector<double>> f_profile = computeProfile(f_array);
    
  // compute centroid and average radius -> full volume V = 4/3 pi r^3; and unit volume = V/N
  // Now assign each cube a volume = V/N. We want to express this in grid units, so choose (e.g. F^3) of them (say F=11) per cube volume. Thus each cube volume is broken up into pieces of size V/(NF^3), which defines a grid spacing = (V/N)^(1/3)/F. Now express the center of each cube in units of F by dividing each center coordinate by this grid spacing (to nearest integer), and start filling a set of coordinates by walking all the points around each cube center (thus it helps if F is odd: three loops from x-(F-1)/2 to x+(F-1)/2). The final cardinality of this set C will be less than or equal to NF^3,  and the ratio C/(NF^3) is Variety.
  double mean_radius = computeMeanRadius(f_profile);
  double totalV = 4 * PI / 3 * pow(mean_radius,3);
  size_t num_points = f_profile.size();
  //  cout << mean_radius << " " << totalV << " " << num_points << endl;
  
  double lattice_spacing = pow(totalV/num_points, 1/3.)/LATTICE_POINTS_PER_SIDE;
  size_t occupied_points = volumeUnion(f_profile, lattice_spacing, LATTICE_POINTS_PER_SIDE);
  size_t total_points = num_points * pow(LATTICE_POINTS_PER_SIDE,3);
  //  cout << lattice_spacing << " " << occupied_points << " " << total_points << endl;
    
  return 1.0 * occupied_points / total_points;
}


/// Computes ratio of Variety/Energy (=Efficiency) for given wave
 float Efficiency(const vector<double>& wave) {
   float energy = Energy(wave);
   float variety = Variety(wave);
   return energy == 0 ? 0 : variety/energy;
}

int main(int argc, char *argv[]) {

  vector<double> wave;
  if ( argc != 2 ) {
    cout<<"usage: "<< argv[0] <<" <file of notes>\n";
    return 1;
  }
  else {
    ifstream the_file ( argv[1] );
    if ( !the_file.is_open() ) {
      cout<<"Could not open file\n";
      return 2;
    }
    else {
      string line;
      while ( getline(the_file, line) )
        wave.push_back(stod(line));
    }
  }
  
  
  float e = Energy(wave);
  float v = Variety(wave);
  cout << "Final Energy, Variety, V/E = " << e << ", " << v << ", " << v/e << endl;

  //  PrintWave(wave);
  string newname(argv[1]);
  WriteProfile(wave, newname + ".profile.csv");
  
  
  return 0;
}


/*
nskerstis-MBP:code nskersti$ ./a.out ../Downloads/midicsv-1.1/GnR.processed.notes.txt
Final Energy, Variety, V/E = 7777.75, 0.329774, 4.23997e-05
nskerstis-MBP:code nskersti$ ./a.out ../Downloads/midicsv-1.1/Beethoven.processed.notes.txt
Final Energy, Variety, V/E = 23091.2, 0.240334, 1.0408e-05
nskerstis-MBP:code nskersti$ tail -n +437 ../Downloads/midicsv-1.1/GnR.processed.notes.txt > ../Downloads/midicsv-1.1/GnR.riff.processed.notes.txt
nskerstis-MBP:code nskersti$ ./a.out ../Downloads/midicsv-1.1/GnR.riff.processed.notes.txt
Final Energy, Variety, V/E = 1963.25, 0.437255, 0.00022272
nskerstis-MBP:code nskersti$ tail -n +2500 ../Downloads/midicsv-1.1/Beethoven.processed.notes.txt > ../Downloads/midicsv-1.1/Beethoven.finale.processed.notes.txt 
nskerstis-MBP:code nskersti$ ./a.out ../Downloads/midicsv-1.1/Beethoven.finale.processed.notes.txt
Final Energy, Variety, V/E = 2104, 0.294725, 0.000140078
$ ./a.out ../Downloads/midicsv-1.1/Beethoven.processed.notes2.txt
Final Energy, Variety, V/E = 29152.2, 0.253748, 8.70422e-06
$ ./a.out ../Downloads/midicsv-1.1/Beethoven.processed.csardas.notes.txt
Final Energy, Variety, V/E = 1202.75, 0.374734, 0.000311564
nskerstis-MBP:midicsv-1.1 nskersti$ ../../code/compute_1d_variety.x Bohemian_Rhapsody_-_Queen.notes2.txt
Final Energy, Variety, V/E = 4270.25, 0.478119, 0.000111965
nskerstis-MBP:midicsv-1.1 nskersti$ ../../code/compute_1d_variety.x Blue_Rondo_A_La_Turk.notes1.txt
Final Energy, Variety, V/E = 2689.75, 0.278805, 0.000103655
./compute_1d_variety.x 1000.opt.txt
Final Energy, Variety, V/E = 104.994, 0.774868, 0.00738015
*/
