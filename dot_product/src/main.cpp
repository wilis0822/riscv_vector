#include <iostream>
#include <math.h> // 使用 <cmath> 替代 <math.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct pt
{
  float x;
  float y;
  float z;
};
const int N = 32768;
const int vlen = 1024;
// 聲明外部向量運算函數
extern "C" void vec_len_rvv(float *r, struct pt *v, int n, struct pt *v1,int *vl,int *runT);
extern "C" void vec_len_rvv1(float *r, struct pt *v, int n, struct pt *v1,int *vl,int *runT);
struct pt v[N] = {{4, 5, 6}, {4, 5, 6}, {10, 11, 12}, {16, 17, 18}, {16, 17, 18}, {16, 17, 18}};
struct pt v1[N] = {{4, 5, 6}, {4, 5, 6}, {10, 11, 12}, {16, 17, 18}, {16, 17, 18}, {16, 17, 18}};
int main()
{
  float  lens_rvv[N], lens_rvv1[N];
  int vl[N],vl2[N],runT1[N],runT2[N];
  for (int i = 0; i < N; i++)
  {
    vl[i] = 0;
    v[i].x = 10000;
    v[i].y = 1000;
    v[i].z = 100;
    v1[i].x = 50;
    v1[i].y = 500;
    v1[i].z = 30;
  }
  // 計時 vec_len_rvv 函數
  auto rvv_start = std::chrono::high_resolution_clock::now(); // 開始計時
  vec_len_rvv(lens_rvv, v, N, v1,vl,runT1);
  auto rvv_end = std::chrono::high_resolution_clock::now();        // 結束計時
  std::chrono::duration<double> elapsed_rvv = rvv_end - rvv_start; // 計算所用時間
  std::cout << "Execution time (vec_len_rvv): " << elapsed_rvv.count() << "(s) " << (lens_rvv[N-1]) <<"  vlmax : "<<vl[0]<< " run times : "<<runT1[0]<< endl;

  // 計時 vec_len_rvv1 函數
  auto rvv1_start = std::chrono::high_resolution_clock::now(); // 開始計時
  vec_len_rvv1(lens_rvv1, v, N, v1,vl2,runT2);
  auto rvv1_end = std::chrono::high_resolution_clock::now();          // 結束計時
  std::chrono::duration<double> elapsed_rvv1 = rvv1_end - rvv1_start; // 計算所用時間

  std::cout << "Execution time (vec_len_rvv1): " << elapsed_rvv1.count() << "(s) " << (lens_rvv1[N-1]) <<"  vlmax : "<<vl2[0]<< " run times : "<<runT2[0]<<endl;
  std::string filename = "../datanum_" + std::to_string(N) + "/vlen" + std::to_string(vlen) + ".csv";
   std::cout << "data_num : "<<N<<endl;
  // 寫入 vlen128.csv 檔案
  std::ofstream file2(filename, std::ios::app);
  std::vector<double> data1 = {elapsed_rvv.count(), elapsed_rvv1.count()};
  for (double i : data1)
  {
    file2 << i << ",";
  }
  file2 << "\n";
  file2.close();
  return 0;
}