import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from tabulate import tabulate


plt.rc("font", family='NanumGothic')
fire =  pd.read_csv("fire_information.csv", engine='python')
lst_avg = [0,0,0,0,0,0,0,0,0,0,0,0]
lst_month=["1월","2월","3월","4월","5월","6월","7월","8월","9월","10월","11월","12월"]
colors = ['bisque','darkorange','burlywood','antiquewhite','tan','orange',
'darkgoldenrod','goldenrod', 'cornsilk']
explodes = [0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05]


#화재 발생 날짜 정리
fire['날짜_datetime'] = pd.to_datetime(fire["화재발생년월일"])
fire['날짜_월'] = pd.to_datetime(fire["화재발생년월일"]).dt.month
fire['날짜_일'] = pd.to_datetime(fire["화재발생년월일"]).dt.day

#화재 발생 월별 건수 추출
fire_month = pd.value_counts(fire["날짜_월"].values,sort=False)

#월 재산피해 추출 후 표
fire_2 = fire.loc[:,['날짜_월', '재산피해소계']]

#리스트에 월별 재산피해 평균 입력
for i in range(12):
    month = (fire_2['날짜_월'] == i+1)
    avg = fire_2.loc[month, '재산피해소계'].mean()
    lst_avg[i] = avg 

#월별 화재 건수(첫번째 그래프)
fig = plt.figure(figsize=(16, 16))
ax1 = fig.add_subplot()
ax2 = ax1.twinx()
#fire_month.plot.bar(color = "violet", rot=0)
ax1.bar(list(range(len(lst_month))),fire_month, color='rebeccapurple')
ax1.set_xticks(list(range(len(lst_month))))
ax1.set_xticklabels(lst_month)
ax2.plot(list(range(len(lst_avg))), lst_avg, color='lightgreen', linestyle='--', marker='o')
plt.title("월별 화재 건수 및 재산피해소계", fontsize=20)
#화재 재산피해
fire_m_max = fire.loc[fire['재산피해소계'].idxmax()]


#지역 별 건수 추출
fire_country = pd.value_counts(fire["시도"].values,sort=False)

#시도별 화재 건(두번째 그래프)
fig = plt.figure(figsize=(16, 16))
fire_country.plot.bar(color = "darkblue", rot=0)
plt.title("시도별 화재 건수", fontsize=20)

fig = plt.figure(figsize=(18,18))
plt.subplot(1,2,1)
plt.plot(0,0)
fire_5 = fire.loc[:,['시도','발화요인대분류','발화요인소분류']]
fire_6 = fire_5[fire_5["시도"]=='경기도']
fire_geong_m = pd.value_counts(fire_6["발화요인대분류"].values)
fire_geong_m.plot.bar(color = "skyblue", rot=0)
plt.title("경기도-발화요인대분류", fontsize=20)
fire_7 = fire_6[fire_6["발화요인대분류"]=='부주의']
fire_smallcause2 = pd.value_counts(fire_7["발화요인소분류"].values)
plt.subplot(1,2,2)
plt.plot(16,0)
fire_smallcause2.plot.pie(autopct='%.1f%%', startangle=0, counterclock=False
,colors=colors, explode=explodes, shadow=True)
plt.title("경기도-부주의-발화요인소분류", fontsize=20)



#발화요인대분류 추출
fire_bigcause = pd.value_counts(fire["발화요인대분류"].values,sort=False)

#발화요인대분류 (세번째 그래프)
fig = plt.figure(figsize=(18,18))
plt.subplot(1,2,1)
plt.plot(0,0)
fire_bigcause.plot.bar(color = "gold")
plt.title("발화요인대분류", fontsize=20)


#발화요인소분류-부주의 (네번째 그래프)
fire_3 = fire.loc[:,['발화요인대분류', '발화요인소분류']]
fire_4 = fire_3[fire_3["발화요인대분류"]=='부주의']
fire_smallcause = pd.value_counts(fire_4["발화요인소분류"].values)
plt.subplot(1,2,2)
plt.plot(16,0)
fire_smallcause.plot.pie(autopct='%.1f%%', startangle=0, counterclock=False
,colors=colors, explode=explodes, shadow=True)
plt.title("부주의-발화요인소분류", fontsize=20)

#인명피해 표(인명피해 = 부상 + 사망), 최대 인명 피해, 평균 인명 피해
number = len(fire)
fire_casualties = fire[['인명피해(명)','사망','부상']].sum()
fire_casualties['인명피해 평균'] = fire['인명피해(명)'].mean()
fire_casualties['인명피해 최대값'] = fire['인명피해(명)'].max()
fire_c_max = fire.loc[fire['인명피해(명)'].idxmax()]
print("====================================================")
print(fire_m_max)
print("====================================================")
print(fire_casualties)
print("====================================================")
print(fire_c_max)
print("====================================================")

plt.show()