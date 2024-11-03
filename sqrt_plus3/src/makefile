# 定義執行次數
RUN_COUNT = 50

# 主目標
go: main repeat

# 編譯目標
main: main.cpp vec.S vec_1.S makefile
	riscv64-unknown-linux-gnu-g++ -g -O main.cpp vec.S vec_1.S -o main -march=rv64gcv_zba -lm -static -pg 

# repeat 目標：重複執行 100 次
repeat:
	@for i in $(shell seq 1 $(RUN_COUNT)); do \
		echo "Run $$i:"; \
		qemu-riscv64 -cpu rv64,v=true,zba=true,vlen=128,rvv_ta_all_1s=on,rvv_ma_all_1s=on ./main -s -S; \
	done
