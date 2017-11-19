from trainingset import TrainingSet

path = "tmp_file.nnts"

# Create training set
tset = TrainingSet(1, 1, 0.0, 1.0, 0.0, 1.0, 2, 1)
tset.add_sample([0.0, 0.0], [0.0])
tset.add_sample([0.0, 1.0], [1.0])
tset.add_sample([1.0, 0.0], [1.0])
tset.add_sample([1.0, 1.0], [0.0])

# Write training set
tset.save(path)

# # Clean up
# import os
# os.remove(path)
