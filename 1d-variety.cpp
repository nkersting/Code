
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_TRIALS = 1000;
const int MAX_DEPTH = 5;
const int GRID_SCALE = 10;
const float PI = 3.14159;
const size_t LATTICE_POINTS_PER_SIDE = 11; // number of points to divide each cubic subvolume's side
const size_t WAVE_SIZE = 20; // number of 'notes' in the wave


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


/// Computes the 'space-filling' definition of Variety:
/// First the profile of the function in (f,f',f'')-space is computed.
/// Next a centroid and average radius is computed, which defines a volume _V
/// Now a little box (volume = _V/N) is drawn around each of the N points in the profile,
/// and finally the ratio of the union of these boxes' volumes to _V is Variety.
  float Variety(const vector<double>& f_array) {
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

// generate a new wave from given wave by choosing random perturbations.
vector<double> Generate(const vector<double>& wave, int depth) {
  vector<double> new_wave;
  double grid_size = gridSize(depth);
  for (auto x: wave) {
    new_wave.push_back(x + (rand() % 3 - 1) * grid_size);  
  }
 
  return new_wave;
}

void RecurseWave(vector<double>& wave, int depth) {
  if (depth > MAX_DEPTH)
    return;
  float max_efficiency = Efficiency(wave);
  vector<double> max_wave = wave;
  vector<double> curr_wave = wave; 
  for (int i = 0; i < MAX_TRIALS; i++) {  // generate new wave from current with each trial    
    curr_wave = Generate(wave, depth);
    float curr_efficiency = Efficiency(curr_wave);
    //    cout << i << endl;
    if (curr_efficiency > max_efficiency) {
      max_efficiency = curr_efficiency;
      max_wave = curr_wave;
      cout << curr_efficiency << endl;
      PrintWave(curr_wave);
    }
  }
  wave = max_wave;
  depth += 1;
  RecurseWave(wave, depth);
}

int main() {

  // First start out making deviations from a flat line.
  // Work on the unit interval [0,1] with a grid size 0.1, initially
  // Recurse from the most economically-varied results, dividing grid size by 10 with each iteration

  /*
  wave.push_back(1);
  wave.push_back(0);
  wave.push_back(1);
  wave.push_back(1);
  wave.push_back(1);
  wave.push_back(0);
  wave.push_back(1);
  wave.push_back(0);
  wave.push_back(0);
  wave.push_back(1);
  wave.push_back(1);
  wave.push_back(1);
  wave.push_back(1);
  */

  /*
  // UNIT TEST
  vector<double> wave;
  wave.push_back(1);
  wave.push_back(0);
  wave.push_back(0);
  wave.push_back(1);
  wave.push_back(1);
  float e = Energy(wave);
  float v = Variety(wave);
  cout << "Final Energy, Variety, V/E = " << e << ", " << v << ", " << v/e << endl;
  // Final Energy, Variety, V/E = 0.5, 0, 0
  */

  

  srand (time(NULL));  
  vector<double> wave(WAVE_SIZE, 0);  // this is the pattern we're trying to optimize

  RecurseWave(wave, 0);

  float e = Energy(wave);
  float v = Variety(wave);
  cout << "Final Energy, Variety, V/E = " << e << ", " << v << ", " << v/e << endl;

  PrintWave(wave);
  
  
  return 0;
}

