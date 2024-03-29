#include <iostream>
#include <math.h>

using namespace std;

int LEFT_SHIFT_COUNT[16] =
{
	1,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	1
};

int PERMUTATION_AFTER_SBOX[32] = {
	16,   7,  20,  21,
	29,  12,  28,  17,
	1,  15,  23,  26,
	5,  18,  31,  10,
	2,   8,  24,  14,
	32,  27,   3,   9,
	19,  13,  30,   6,
	22,  11,   4,  25
};

int REDUCTION_TO_56_TABLE[56] =
{
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

int REDUCTION_TO_48_TABLE[48] =
{
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

int INITIAL_PERMUTATION[64] =
{
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

int  INVERSE_INITIAL_PERMUTATION[64] =
{
	40,     8,   48,    16,    56,   24,    64,   32,
	39,     7,   47,    15,    55,   23,    63,   31,
	38,     6,   46,    14,    54,   22,    62,   30,
	37,     5,   45,    13,    53,   21,    61,   29,
	36,     4,   44,    12,    52,   20,    60,   28,
	35,     3,   43,    11,    51,   19,    59,   27,
	34,     2,   42,    10,    50,   18,    58,   26,
	33,     1,   41,     9,    49,   17,    57,   25
};

int EXPANSION_TO_48_TABLE[48] =
{
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

int S[8][4][16] =
{
	{
		{ 14,  4,   13,   1,    2,  15,   11,   8,    3,  10,    6,  12,    5,   9,    0,   7 },
{ 0,  15,    7,   4,   14,   2,   13,   1,   10,   6,   12,  11,    9,   5,    3,   8 },
{ 4,  1,    14,   8,   13,   6,    2,  11,   15,  12,    9,   7,    3,  10,    5,   0 },
{ 15, 12,     8,   2,    4,   9,    1,   7,    5,  11,    3,  14,   10,   0,    6,  13 }
	},

  {
	  { 15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10 },
{ 3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5 },
{ 0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9, 3,   2, 15 },
{ 13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9 }
  },

  {
	  { 10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8 },
{ 13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1 },
{ 13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7 },
{ 1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12 }
  },

  {
	  { 7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15 },
{ 13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9 },
{ 10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4 },
{ 3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14 }
  },

  {
	  { 2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9 },
{ 14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6 },
{ 4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14 },
{ 11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3 }
  },

  {
	  { 12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11 },
{ 10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8 },
{ 9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6 },
{ 4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13 }
  },

  {
	  { 4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1 },
{ 13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6 },
{ 1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2 },
{ 6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12 }
  },

  {
	  { 13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7 },
{ 1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2 },
{ 7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8 },
{ 2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11 }
  }

};

char** kn = new char*[16];

struct Bit {
	unsigned int bit : 1;
};

class BitSet {
public:
	Bit *ray;
	int size;

	BitSet(int num) {
		size = num;
		ray = new Bit[num];

		for (int i = 0; i < num; i++) {
			ray[i].bit = 0;
		}
	}

	BitSet(BitSet* base) {
		size = base->size;
		ray = new Bit[size];

		for (int i = 0; i < size; i++) {
			ray[i].bit = base->ray[i].bit;
		}
	}

	unsigned int get(int index) {
		return ray[index].bit;
	}

	void set(int index, unsigned int val) {
		if (val == 0) {
			ray[index].bit = 0;
		}
		else ray[index].bit = 1;
	}

	BitSet* getChunk(int start, int end) {
		BitSet* chunk = new BitSet(end - start + 1);

		for (int i = start; i <= end; i++) {
			chunk->set(i - start, this->ray[i].bit);
		}

		return chunk;
	}

	char* toString() {
		char* string = new char[size + 1];

		int i;
		for (i = 0; i < size; i++) {
			string[i] = (ray[i].bit == 0) ? '0' : '1';
		}

		string[i] = '\0';

		return string;
	}

	void leftShift() {
		unsigned int buff = this->get(size - 1);

		for (int i = size - 1; i > 0; i--) {
			unsigned int temp = this->get(i - 1);
			this->set(i - 1, buff);
			buff = temp;
		}

		this->set(size - 1, buff);
	}
};

BitSet* toBitSet(char* msg, int len) {
	BitSet* bitset = new BitSet(len);

	for (int i = 0; i < len; i++) {
		bitset->set(i, (msg[i] == '0') ? 0 : 1);
	}

	return bitset;
}

BitSet* applyTable(BitSet* string, int* table, int table_len) {
	BitSet* ans = new BitSet(table_len);

	for (int i = 0; i < table_len; i++) {
		ans->set(i, string->get(table[i] - 1));
	}

	return ans;
}

BitSet* getKey56(char* basis_key) {
	BitSet* key64 = toBitSet(basis_key, 64);
	BitSet* key56 = applyTable(key64, REDUCTION_TO_56_TABLE, 56);

	return key56;
}

BitSet* xor_(BitSet* op1, BitSet* op2) {
	BitSet* res = new BitSet(op1->size);

	for (int i = 0; i < op1->size; i++) {
		res->set(i, (op1->get(i) != op2->get(i)));
	}

	return res;
}

int toDecimal(BitSet* op) {
	int val = 0;
	int index = 0;
	for (int i = op->size - 1; i >= 0; i--) {
		if (op->get(i)) {
			val += pow(2, index);
		}
		index++;
	}

	return val;
}

BitSet* toBinary4(int val) {
	BitSet* val4 = new BitSet(4);
	int index = 3;

	while (val) {
		int ans = val % 2;
		val /= 2;

		val4->set(index, ans);
		index--;
	}

	return val4;
}

BitSet* get32From48SBox(BitSet* op) {
	BitSet* key32 = new BitSet(32);

	for (int i = 0; i < 8; i++) {
		int start = i * 6;
		int end = start + 5;

		BitSet* section6 = op->getChunk(start, end);
		BitSet* section4 = new BitSet(4);

		BitSet* row = new BitSet(2);
		BitSet* col = section6->getChunk(1, 4);

		row->set(0, section6->get(0));
		row->set(1, section6->get(5));

		int row_index = toDecimal(row);
		int col_index = toDecimal(col);

		int val = S[i][row_index][col_index];

		BitSet* temp = toBinary4(val);

		for (int j = 0; j < 4; j++) {
			section4->set(j, temp->get(j));
		}

		for (int k = i * 4; k <= (i * 4) + 3; k++) {
			key32->set(k, temp->get(k - i * 4));
		}
	}

	key32 = applyTable(key32, PERMUTATION_AFTER_SBOX, 32);

	return key32;
}

char* encrypt(char* key_string, char* plain_text_string) {
	BitSet* key56 = getKey56(key_string);

	BitSet* text64 = applyTable(toBitSet(plain_text_string, 65), INITIAL_PERMUTATION, 64);

	BitSet* c0 = key56->getChunk(0, 27);
	BitSet* d0 = key56->getChunk(28, 55);

	for (int i = 0; i < 16; i++) {

		BitSet* lb = text64->getChunk(0, 31);
		BitSet* rb = text64->getChunk(32, 63);

		for (int j = 0; j < LEFT_SHIFT_COUNT[i]; j++) {
			c0->leftShift();
			d0->leftShift();
		}

		BitSet* key56_merged = new BitSet(56);

		int index;
		for (index = 0; index < 28; index++) {
			key56_merged->set(index, c0->get(index));
		}

		for (index = 28; index < 56; index++) {
			key56_merged->set(index, d0->get(index - 28));
		}

		BitSet* key48 = applyTable(key56_merged, REDUCTION_TO_48_TABLE, 48);
		BitSet* rb_expanded = applyTable(rb, EXPANSION_TO_48_TABLE, 48);
		BitSet* xor_result = xor_(rb_expanded, key48);
		BitSet* interim_result = get32From48SBox(xor_result);
		BitSet* rn = xor_(lb, interim_result);
		BitSet* ln = new BitSet(rb);

		kn[i] = key48->toString();

		for (index = 0; index < 32; index++) {
			text64->set(index, ln->get(index));
		}

		for (index = 32; index < 64; index++) {
			text64->set(index, rn->get(index - 32));
		}
	}

	BitSet temp(text64);

	for (int i = 0; i < 64; i++) {
		temp.set(i, text64->get((i + 32) % 64));
	}

	text64 = applyTable(&temp, INVERSE_INITIAL_PERMUTATION, 64);

	return text64->toString();
}

char* decrypt(char* cipher_text_string) {

	BitSet* text64 = applyTable(toBitSet(cipher_text_string, 65), INITIAL_PERMUTATION, 64);

	for (int i = 0; i < 16; i++) {

		BitSet* lb = text64->getChunk(0, 31);
		BitSet* rb = text64->getChunk(32, 63);

		BitSet* key48 = toBitSet(kn[15 - i], 48);
		BitSet* rb_expanded = applyTable(rb, EXPANSION_TO_48_TABLE, 48);
		BitSet* xor_result = xor_(rb_expanded, key48);
		BitSet* interim_result = get32From48SBox(xor_result);
		BitSet* rn = xor_(lb, interim_result);
		BitSet* ln = new BitSet(rb);

		int index;
		for (index = 0; index < 32; index++) {
			text64->set(index, ln->get(index));
		}

		for (index = 32; index < 64; index++) {
			text64->set(index, rn->get(index - 32));
		}
	}

	BitSet temp(text64);

	for (int i = 0; i < 64; i++) {
		temp.set(i, text64->get((i + 32) % 64));
	}

	text64 = applyTable(&temp, INVERSE_INITIAL_PERMUTATION, 64);

	return text64->toString();
}

int main() {
	char key_string[65] = "1111001100110100010101110111100110011011101111001101111111110001";
	char plain_text_string[65] = "0110000100100011010001010110011110001001101010111100110111101111";
	//cout << "\n Enter the key's bitstring : ";
	//cin >> key_string;

	cout << "Data : " << plain_text_string << "\n";

	char* c = encrypt(key_string, plain_text_string);

	cout << "Cipher text : " << c << "\n";

	char* p = decrypt(c);

	cout << "Plain text : " << p << "\n";

	cin.get();
	return 0;
}