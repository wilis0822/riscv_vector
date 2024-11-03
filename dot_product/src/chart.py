import pandas as pd
import matplotlib.pyplot as plt
datanum = "1048576"
# 定義檔案列表
files = ['datanum_' + datanum + '/vlen128.csv', 'datanum_' + datanum +'/vlen256.csv', 'datanum_' + datanum +'/vlen512.csv', 'datanum_' + datanum +'/vlen1024.csv']
mean_values = []

# 迭代每個檔案以計算平均值
for file in files:
    data = pd.read_csv(file, index_col=False, names=["lmul is 2", "lmul is 1", "rvi"], dtype=str)
    data = data.astype(float)  # 將資料轉換為浮點數型態
    mean_values.append(data.mean())

# 將每個檔案的平均值轉換為 DataFrame
mean_df = pd.DataFrame(mean_values, index=files, columns=["lmul is 2", "lmul is 1", "rvi"])

# 繪製柱狀圖
mean_df.plot(kind='bar', figsize=(10, 6), color=['blue', 'orange', 'green'])
plt.title("Performance Analysis of RVI and RVV")
plt.xlabel("File")
plt.ylabel("Average Execution Time (s)")
plt.xticks(rotation=45)

# 儲存圖表為圖檔
plt.tight_layout()  # 自動調整子圖參數
plt.savefig("datanum_" + datanum + "/datanum_" + datanum + ".png")
plt.show()  # 顯示圖表
