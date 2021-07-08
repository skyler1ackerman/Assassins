import numpy as np
import math
from math import factorial as fact
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap, BoundaryNorm
from tqdm import trange
from functools import lru_cache

NUM_PLAYERS = 100
LOOPS = 1_000

class Player:
	def __init__(self, target):
		self.target = target
		self.visited = False

def assignPlayers():
	while True:
		# Put all the numbers into a hat
		players = np.arange(0,NUM_PLAYERS)
		# Give everyone a number
		np.random.shuffle(players)
		# If anyone has themselves, redeal
		players = np.where(players!=players[players], players, -1)
		if -1 not in players:
			break
	# Return a number of players
	return [Player(x) for x in players]

def getCircles(players):
	# Init number of circles
	num_circles = 0
	# Set current player to be the first player in the game
	cur = 0
	while True:
		# Get the next unvisted player
		while players[cur].visited:
			cur+=1
			# If we've visted everyone, just exit
			if cur==NUM_PLAYERS:
				return num_circles

		# Keep track of the starting point
		start = cur
		while True:
			# Mark as visited
			players[cur].visited=True
			# Go to next player
			cur = players[cur].target
			# If we've looped around, break
			if cur==start:
				break
			
		num_circles+=1

def plotTotals(total):

	x = np.arange(0,len(total))

	rescale = lambda y: (y - np.min(y)) / (np.max(y) - np.min(y))
	my_cmap = plt.get_cmap('plasma').reversed()
	curax = ax[num//5,num%5]

	curax.bar(x, total, color=my_cmap(rescale(x)), tick_label=x)
	curax.set_title(f'{NUM_PLAYERS} players')
	curax.set_xlabel('Number of loops')
	curax.set_ylabel('% of total loops')

@lru_cache
def expectedProb(n):
	total = 0
	for i in range(n+1):
		total+=((-1)**i)/fact(i)
	return fact(n-1)/(fact(n)*total)



fig, ax = plt.subplots(2,5)
fig.set_size_inches(16, 10, forward=True)

for num in trange(10):
	total = np.zeros(1000)
	for _ in range(LOOPS):
		total[getCircles(assignPlayers())]+=1
		# Get the average
	total=total/np.sum(total)
	# Remove unnessary zeros from back and the one from the front
	total = np.trim_zeros(total, trim='b')[1:]
	total = np.insert(total, 0, expectedProb(NUM_PLAYERS))
	plotTotals(total)
	NUM_PLAYERS+=0

plt.show()
