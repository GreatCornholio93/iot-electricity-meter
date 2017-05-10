
def convert_12byte_to_ints(str_bytes):

	byte = [int(str_bytes[i:i+2], 16) for i in range(0, len(str_bytes), 2)]

	eints = []
	for i in range(0, len(byte), 4):
		e = 0
		e |= byte[i + 3]
		e <<= 8
		e |= byte[i + 2]
		e <<= 8
		e |= byte[i + 1]
		e <<= 8
		e |= byte[i]
		eints.append(e)

	return eints


if __name__ == '__main__':
	sbytes = '080200001e00000028000000'
	print(convert_12byte_to_ints(sbytes))