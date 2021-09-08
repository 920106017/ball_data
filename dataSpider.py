import requests        #导入requests包
from bs4 import BeautifulSoup

file = open('./spiderData.txt', 'w')

for x in range(21001, 21105):
	print('get ' + str(x) + ' 期...')
	url = 'https://kaijiang.500.com/shtml/ssq/' + str(x) + '.shtml'
	strhtml = requests.get(url)        #Get方式获取网页数据
	#print(strhtml.text)
	soup = BeautifulSoup(strhtml.text, 'html.parser')
	balls = soup.find_all('li', class_='ball_red')
	blue = soup.find_all('li', class_='ball_blue')
	file.write('第'+str(x)+'期: '+balls[0].string+' '+balls[1].string+' '+balls[2].string+' '+balls[3].string+' '+balls[4].string+' '+balls[5].string+'\t'+blue[0].string+'\r\n')
file.close()
