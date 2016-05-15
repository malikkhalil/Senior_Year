#Sample Python 2 multiprocessed code

import multiprocessing
import random

def process(start, end):
	for i in range(start, end):
		calculate(i)

def calculate(num):
	random_numbers = []
	for i in range(num):
		random_numbers.append(random.randint(0, num))
	sum = 0
	for number in random_numbers:
		sum+=number
	print sum


if __name__ == '__main__':
	processes = []
	arguments = [(0, 999), (1000, 1999), (2000, 2999), (3000, 3999)]
	for i in range(4):
		one_process = multiprocessing.Process(target=process, args=(arguments[i]))
		processes.append(one_process)
		one_process.start()
	for proc in processes:
		proc.join()