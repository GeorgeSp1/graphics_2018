import time

x = 100
z = -200
x_f = True
z_f = True

while True:
	if ((x >= -100) and x_f):
		x = x-1
	else:
		x_f = False
		x = x+1
		if x==100:
			x_f = True
	print ("x= ",x)

	if ((z>=200) and z_f):
		z =z-2
	else:
		z_f = False
		z = z+2
		if z==-200:
			z_f = True

	print ("z= ",z)
	time.sleep(0.3)


Θέλουμε να πηγαίνουν απο το 200 εως το -200 οι τιμές του z
και απο το 100 εως το -100 οι τιμές του x. Αλλά να μηδενίζονται ταυτόχρονα