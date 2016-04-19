#Sample Python 2 sequential code

import random

def process(num):
	random_numbers = []
	for i in range(num):
		random_numbers.append(random.randint(0, num))
	sum = 0
	for number in random_numbers:
		sum+=number
	print sum


if __name__ == '__main__':
	for i in range(5000):
		process(i)