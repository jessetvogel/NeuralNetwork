import sample

path = "tmp_file.nnts"

# Write sample
s1 = sample.Sample(3, 4)
s1.data_input = [1.23, 4.56, 7.89]
s1.data_output = [0.12, 3.45, 6.78, 9.01]
s1.save(path)

# Load sample
s2 = sample.Sample.load(path)

# Evaluate test
if s2.data_input == [1.23, 4.56, 7.89] and s2.data_output == [0.12, 3.45, 6.78, 9.01]:
    print 'Test save/load sample: success'
else:
    print 'Test save/load sample: failure'

# Clean up
import os
os.remove(path)
