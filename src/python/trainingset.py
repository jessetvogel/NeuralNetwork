import struct

class TrainingSet:

    def __init__(self, bytes_per_input_value, bytes_per_output_value, input_lower_bound, input_upper_bound, output_lower_bound
    , output_upper_bound, sample_input_size, sample_output_size):
        self.bytes_per_input_value = bytes_per_input_value
        self.bytes_per_output_value = bytes_per_output_value
        self.input_lower_bound = input_lower_bound
        self.input_upper_bound = input_upper_bound
        self.output_lower_bound = output_lower_bound
        self.output_upper_bound = output_upper_bound
        self.sample_input_size = sample_input_size
        self.sample_output_size = sample_output_size
        self.samples_data = ''
        self.amount_of_samples = 0

    def save(self, path):
        output_file = open(path, "wb")

        output_file.write('NNTS')
        output_file.write(struct.pack('I', self.amount_of_samples))
        output_file.write(struct.pack('B', self.bytes_per_input_value))
        output_file.write(struct.pack('B', self.bytes_per_output_value))
        output_file.write(struct.pack('d', self.input_lower_bound))
        output_file.write(struct.pack('d', self.input_upper_bound))
        output_file.write(struct.pack('d', self.output_lower_bound))
        output_file.write(struct.pack('d', self.output_upper_bound))
        output_file.write(struct.pack('I', self.sample_input_size))
        output_file.write(struct.pack('I', self.sample_output_size))
        output_file.write(self.samples_data)
        output_file.close()

    def add_sample(self, input_values, output_values):
        toInputValue = {
            1: lambda x: round(255.0 * (x - self.input_lower_bound) / (self.input_upper_bound - self.input_lower_bound)),
            2: lambda x: round(65535.0 * (x - self.input_lower_bound) / (self.input_upper_bound - self.input_lower_bound)),
            4: lambda x: round(4294967295.0 * (x - self.input_lower_bound) / (self.input_upper_bound - self.input_lower_bound))
        }[self.bytes_per_input_value]

        toOutputValue = {
            1: lambda x: round(255.0 * (x - self.output_lower_bound) / (self.output_upper_bound - self.output_lower_bound)),
            2: lambda x: round(65535.0 * (x - self.output_lower_bound) / (self.output_upper_bound - self.output_lower_bound)),
            4: lambda x: round(4294967295.0 * (x - self.output_lower_bound) / (self.output_upper_bound - self.output_lower_bound))
        }[self.bytes_per_output_value]

        inputs = [toInputValue(x) for x in input_values]
        outputs = [toOutputValue(x) for x in output_values]

        ic = { 1 : 'B', 2 : 'H', 4 : 'L' }[self.bytes_per_input_value]
        oc = { 1 : 'B', 2 : 'H', 4 : 'L' }[self.bytes_per_output_value]

        self.samples_data += struct.pack(ic * self.sample_input_size, *inputs)
        self.samples_data += struct.pack(oc * self.sample_output_size, *outputs)
        self.amount_of_samples += 1
