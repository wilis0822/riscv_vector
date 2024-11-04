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
const int N = 64;

int vlen = 1024;
// 聲明外部向量運算函數
extern "C" void vec_len_rvv(float *r, struct pt *v, int n);
extern "C" void vec_len_rvv1(float *r, struct pt *v, int n);


struct pt v[N] = {{4, 5, 6}, {4, 5, 6}, {10, 11, 12}, {16, 17, 18}, {16, 17, 18}, {16, 17, 18}};

int main()
{
  int a[1000], b[1000];
  float lens[N], lens_rvv[N], lens_rvv1[N], lens2[N];
  for (int i = 0; i < N; i++)
  {
    a[i] = 0;
    b[i] = 0;
    v[i].x = 10000;
    v[i].y = 1000;
    v[i].z = 100;
  }

  // 計時 vec_len_rvv 函數
  auto rvv_start = std::chrono::high_resolution_clock::now(); // 開始計時
  vec_len_rvv(lens_rvv, v, N);
  auto rvv_end = std::chrono::high_resolution_clock::now();        // 結束計時
  std::chrono::duration<double> elapsed_rvv = rvv_end - rvv_start; // 計算所用時間
  
  // 計時 vec_len_rvv1 函數
  auto rvv1_start = std::chrono::high_resolution_clock::now(); // 開始計時
  vec_len_rvv1(lens_rvv1, v, N);
  auto rvv1_end = std::chrono::high_resolution_clock::now();          // 結束計時
  std::chrono::duration<double> elapsed_rvv1 = rvv1_end - rvv1_start; // 計算所用時間

  std::cout << "Execution time (vec_len_rvv): " << elapsed_rvv.count() << "(s) " << (lens_rvv[0]) << endl;
  std::cout << "Execution time (vec_len_rvv1): " << elapsed_rvv1.count() << "(s) " << (lens_rvv1[0]) << endl;
  std::string filename = "../datanum_" + std::to_string(N) + "/vlen" + std::to_string(vlen) + ".csv";

  // 寫入 vlen128.csv 檔案
  std::ofstream file2(filename, std::ios::app);
  std::vector<double> data1 = {elapsed_rvv.count(), elapsed_rvv1.count()};
  /*
  for(int i = 0;i < N;i++){
    std::cout<<a[i]<<" "<<lens_rvv[i]<<" "<<b[i]<<" "<<lens_rvv1[i]<<endl;
  }*/
  for (double i : data1)
  {
    file2 << i << ",";
  }
  file2 << "\n";
  file2.close();
  return 0;
}