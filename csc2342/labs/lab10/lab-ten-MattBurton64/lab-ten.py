"""
Matt Burton
csc 2342
04/19/21
"""

pairs = {};
pair = input("Enter an ordered pair of verticies. example (a,b): ");

while(pair):
	
	#unintended but potentially common error
	if pair == 'nothing':
		print("Press the enter key instead of typing 'nothing'.");
	
	pair = pair.strip('()');
	a,b = pair.split(',');

	if a in pairs.keys():
		pairs[a].append(b);
	else:
		pairs[a] = [b];

	if b in pairs.keys():
		pairs[b].append(a);
	else:
		pairs[b] = [a];

	pair = input("Enter another pair or nothing to stop: ");

key = input("Find the neighborhood of which vertex: ");
while(key):
	if pair == 'nothing':
		print("Press the enter key instead of typing 'nothing'.");
	
	print(pairs[key]);
	key = input("Enter another vertex or enter nothing to stop: ");

