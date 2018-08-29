import time
import math

start = time.time()
z = 0.868*1000
#z = 1.5915*1000
pflag = False
y_old = 0
y = 0
track_old = 0
track = round(1000*(time.time()-start), 0)-track_old
total_program_duration = 420000
x = 0
test1 = 0

while True:
	x = round(1000*(time.time()-start), 0) #
	y_old = y
	y = (math.exp(math.sin(((x-test1)-z*(math.pi/2))/z))-(1/math.e))*(255/(math.e-(1/math.e))) #
	if y<y_old and pflag == False:
		pflag = True
		y_old = 255
	if y_old<y and pflag == True:
		pflag = False
		y = 0
		test1 = round(1000*(time.time()-start), 0)
		track = round(1000*(time.time()-start), 0)-track_old
		track_old = round(1000*(time.time()-start), 0)
		print "Period: ", track
		print "Time: ", x
		z = 1.5915*1000-((total_program_duration-x)/total_program_duration)*(1.5915*1000-0.868*1000)
		if total_program_duration <= x:
			break


		