import struct

class Sample:

    def __init__(self, input_size, output_size):
        self.data_input = [0.0] * input_size
        self.data_output = [0.0] * output_size

    def save(self, path):
        output_file = open(path, "wb")
        output_file.write('NNTS')
        output_file.write(struct.pack('I', len(self.data_input)))
        output_file.write(struct.pack('I', len(self.data_output)))
        output_file.write(struct.pack('d' * len(self.data_input), *self.data_input))
        output_file.write(struct.pack('d' * len(self.data_output), *self.data_output))
        output_file.close()

    @staticmethod
    def load(path):
        input_file = open(path, "rb")
        code = input_file.read(4);
        if(code != 'NNTS'):
            print 'Invalid file'
            return None
        input_size = struct.unpack('I', input_file.read(4))[0];
        output_size = struct.unpack('I', input_file.read(4))[0];
        sample = Sample(input_size, output_size)
        sample.data_input = list(struct.unpack('d' * input_size, input_file.read(8 * input_size)))
        sample.data_output = list(struct.unpack('d' * output_size, input_file.read(8 * output_size)))
        return sample
