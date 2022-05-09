#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

// Parameters
// V_R = 0, V_T = 1, n = 10^4, m = 10^3, S = 1, f = 1

int main(){
  int num = 1000; //number of neurons
  int matrix[num][num];
  int i, j, k, t, sum;
  int index = 0;
  double bp_sum;
  int a_sum;
  float prob;
  double current[num]; //array of current voltage
  double start[num]; //array of starting voltage
  double end[num]; // the ending voltage of each neuron after each time step
  vector<int> neighbors;

  int v_r = 0;
  int v_t = 1;
  int n = 10^4;
  int m = 10^3;
  int s = 1;
  int f = 1;

  // initialize fire state to zero
  int fire[1000];
  for (i = 0; i < num; i++){
    fire[i] = 0;
  }

  // initialize matrix
  // randomly assign
  for (i = 0; i < num; i++){
    for (j = 0; j < num; j++){
      matrix[i][j] = bool rand75();
    }
  }

  /*
  test code:
  for (i = 0; i < num; i++){
    for (j = 0; j < num; j++){
      sum = sum + matrix[i][j];
    }
  }
  prob = sum/num000;
  printf("%0.4f", prob);
  */

  // create an array to store starting voltage
  for (i = 0; i < num, i++){
    // randonly assign values with four decimals between between 0 and 1
    start[i] = (rand() % (10000 - 0)) / 10000.0;
  }

  for (i = 0; i < num, i++){
    // randonly assign values between .8 and 1.2
    current[i] = (rand() % (120000 - 80000)) / 10000.0;;
  }

  /* for loop that goes through 1000 time steps
   * check whether each neuron spikes
   * check the fired neuron's neighbors and whether they spike, then check the fired neighbors' neighbors
   */
  float time_step = 0.01;
  for (t = 0; t < 1000; t++){
    // for each neuron, we run the following steps
    for (i = 0; i < num; i++){

      // calculate BP
      for (k = 0; k < num; k++){
        bp_sum += current[k];
      }
      // calculate A
      for (j = 0; j < num; j++){
        if (matrix[k][j] == 1 && j != k){
          a_sum ++; // unsure whether plus 1 or plus voltage
        }
      }

      // calculate current voltage
      current[i] = v_r - current[i] + f * bp_sum + s/num * a_sum;
      // what is num? 1000? the number of sensory-neuron connections?

      if (current[i] >= v_t && fire[i] == 0) {
        current[i] = v_r;
        fire[i] = 1;
        for (j = 0; j < num; j++){
          if (matrix[j][i] == 1 && fire[j] != 0){
            neighbors.push_back(j);
          }
        }
        handle_neighbor(neighbors, index);
      }
    }
    // end of each iteration

    // after each iteration, fire state resets to zero for all neurons
    for (i = 0; i < num; i++){
      fire[i] = 0;
    }

  }

}

int handle_neighbor(vector<int> neighbors, int index){
  // add the interaction to neighbors, check if they spike, check their neighbors
  for (i = index; i < neighbors.size(); i++){
    current[neighbors[i]] = current[neighbors[i]] + 1 * s/num;
    if (current[neighbors[i]] >= v_t && fire[i] == 0){
      current[i] = v_r;
      fire[i] = 1;
    }

    for (j = 0; j < num; j++){
      if (matrix[j][i] == 1){
        neighbors.push_back(j);
      }
    }
    index ++;
    if (neighbors.size() != 0){
      handle_neighbor(neighbors, index);
    }
  }
}
