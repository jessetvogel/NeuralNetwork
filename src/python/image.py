import glob, os
from PIL import Image
from trainingset import TrainingSet

# Declare directories
png_directory = "/Users/jessetvogel/Downloads/mnist_png"
nnts_directory = "/Users/jessetvogel/Desktop/data"

# Scan directories
for subdirectory in ["training", "testing"]:
    print "Scanning " + subdirectory + " directory ..."
    training_set = TrainingSet(1, 1, 0.0, 1.0, 0.0, 1.0, 28 * 28, 10)
    for i in range(10):
        print "Scanning for digit " + str(i)
        n = 0
        directory = png_directory + "/" + subdirectory + "/" + str(i)
        for file in os.listdir(directory):
            if file.endswith(".png"):
                img = Image.open(directory + "/" + file)
                output = [0.0] * 10
                output[i] = 1.0
                training_set.add_sample([x / 255.0 for x in list(img.getdata())], output)
                img.close()
                n += 1
                if n == 200:
                    break
        print "Read " + str(n) + " images"

    print "Saving " + subdirectory + " ..."
    training_set.save(nnts_directory + "/" + subdirectory + ".nnts")
    print ""

print "Done!"
