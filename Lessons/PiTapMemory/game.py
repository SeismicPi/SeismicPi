from collections import deque
import random
import time


def play(buttons=3, speed=5, itr=10):
	gen_Order = deque(maxlen = itr)
	for i in xrange(itr):
		nextIn = random.randint(1,buttons)
		gen_Order.append(nextIn)
		print nextIn
		time.sleep(0.75/speed)

	while True:
		userIn = int(raw_input())
		if(not userIn == gen_Order.popleft()):
			lose()
			return 
		elif(not gen_Order):
			win()
			return 

def lose():
	print "You Lose"

def win():
	print "You Win"

play(5, 5, 5)


	