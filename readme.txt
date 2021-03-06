#Log File System Simulation
Contributors: Caleb Donovick, Carly Schneider, David Skoda

##Main program: ./program3
Usage: ./program3 num_segments segment_size min_life min_clean input_file

the recommended settings for min_life = .4
			     										min_clean = .2

##Input generator: ./inputgen/input_gen (in it's own directory)
Usage: ./input_gen -u [-u <use>] [-i <instructions>]  [-r <reads>] [-w <writes>] [-t <touch>] [-g <grow>] [-d <delete>] [-l <locality>] [-s <size>] [-a <rAnge]
must be piped to a file, prints to stdout otherwise.

recommended settings for <num_segments> & <segment_size> below

Instructions for execution:
We have provided 3 differentfile sizes for testing:  small, medium and large.
small files contains 100 instructions:
	these files need to be ran with AT LEAST <num_segments> = 30
						 <segment_size> = 52
	or else they will return an assert error

medium files contain 500 instructinos:
	these files need to be ran with AT LEAST <num_segments> = 100
						 <segment_size> = 377
	or else they will return an assert error

Large files contain 5000 instructions:
	these files need to be ran with AT LEAST <num_segments> = 100
						 <segment_size> = 1680
	or else they will return an assert error

Following this guideline for cmd line args using new files of the corresponding sizes will reduce
the number of assert aborts. This simulation does not magically create another disk when out of space,
which we believe is the underlying cause for errors when the parameters are too small.


