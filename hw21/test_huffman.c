#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "log_macros.h"
#include "huffman.h"

static int _test_frequencies_invalid() {									//Tests a test file that does not exist
	mu_start();
	//
	const char* error;
	Frequencies freqs = {0};
	bool is_success = calc_frequencies(freqs, "null.txt", &error);
	mu_check(!is_success);
	//
	mu_end();
}

static int _test_frequencies_valid() {										//Tests a valid file with differing characters within the file
	mu_start();
	//
	const char* error;
	Frequencies freq = {0};
	bool is_success = calc_frequencies(freq, "test.txt", &error);
	mu_check(is_success);
	mu_check(freq[10] == 5);
	mu_check(freq['\t'] == 4);
	for(int i = 113; i <= 115; i++) {
		mu_check(freq[i] == 2);
	}
	char* string = "~_^`,coding";
	for(int i = 0; i < strlen(string); i++) {
		mu_check(freq[string[i + 0] + 0] == 1);
	}
	Node* test = make_huffman_pq(freq);
	mu_check(test != NULL);
	destroy_list(&test, free);
	mu_end();
}

static int _test_frequencies_recurring() {									//Tests a valid file with many recurring character wihtin the file
	mu_start();
	//
	const char* error;
	Frequencies freq = {0};
	bool is_success = calc_frequencies(freq, "recurring.txt", &error);
	mu_check(is_success);
	mu_check(freq[120] == 15);
	mu_check(freq[121] == 15);
	Node* test = make_huffman_pq(freq);
	mu_check(test != NULL);
	destroy_list(&test, free);
	mu_end();
}

static int _test_make_huffman() {											//Tests making a huffman tree
	mu_start();
	//
	const char* error;
	Frequencies freq = {0};
	bool is_success = calc_frequencies(freq, "huffman.txt", &error);
	mu_check(is_success);
	Node* tree = make_huffman_pq(freq);
	mu_check(tree != NULL);
	TreeNode* huffman = make_huffman_tree(tree);
	mu_check(huffman != NULL);
	mu_check(huffman -> frequency == 7);								
	mu_check(huffman -> character == '\0');								
	mu_check((huffman -> left) -> frequency == 3);						
	mu_check((huffman -> right) -> frequency == 4);
	mu_check((huffman -> left) -> character == 'x');
	mu_check((huffman -> right) -> character == 'y');
	destroy_huffman_tree(&huffman);
	//
	mu_end();
}

static int _test_coding_table_easy() {										//Tests coding a single character into a tree
	mu_start();
	//
	const char* error;
	Frequencies freq = {0};
	bool is_success = calc_frequencies(freq, "table_easy.txt", &error);
	mu_check(is_success);
	Node* tree = make_huffman_pq(freq);
	TreeNode* huffman = make_huffman_tree(tree);
	BitWriter writer = open_bit_writer("coding_table_easy.txt");
	write_coding_table(huffman, &writer);
	close_bit_writer(&writer);
	FILE *fp = fopen("coding_table_easy.txt", "r");
	mu_check(fgetc(fp) == 0xB0);
	mu_check(fgetc(fp) == 0x80);
	fclose(fp);
	destroy_huffman_tree(&huffman);
	//
	mu_end();
}

static int _test_coding_table_simple() {									//Tests coding two characters into two leaves in a tree
	mu_start();
	//
	const char* error;
	Frequencies freq = {0};
	bool is_success = calc_frequencies(freq, "huffman.txt", &error);
	mu_check(is_success);
	Node* tree = make_huffman_pq(freq);
	TreeNode* huffman = make_huffman_tree(tree);
	
	BitWriter writer = open_bit_writer("coding_table_simple.txt");
	write_coding_table(huffman, &writer);
	close_bit_writer(&writer);
	FILE *fp = fopen("coding_table_simple.txt", "r");
	mu_check(fgetc(fp) == 0xBC);
	mu_check(fgetc(fp) == 0x5E);
	mu_check(fgetc(fp) == 0x40);
	fclose(fp);
	destroy_huffman_tree(&huffman);
	//
	mu_end();
}

static int _test_coding_table_hard() {										//Tests coding many characters into branches and leaves in a tree
	mu_start();
	//
	const char* error;
	Frequencies freq = {0};
	bool is_success = calc_frequencies(freq, "table_hard.txt", &error);
	mu_check(is_success);
	Node* tree = make_huffman_pq(freq);
	TreeNode* huffman = make_huffman_tree(tree);
	BitWriter writer = open_bit_writer("coding_table_hard.txt");
	write_coding_table(huffman, &writer);
	close_bit_writer(&writer);
	FILE *fp = fopen("coding_table_hard.txt", "r");
	mu_check(fgetc(fp) == 0xB3);
	mu_check(fgetc(fp) == 0x5A);
	mu_check(fgetc(fp) == 0x2D);
	mu_check(fgetc(fp) == 0x89);
	mu_check(fgetc(fp) == 0x01);
	mu_check(fgetc(fp) == 0x75);
	mu_check(fgetc(fp) == 0xBC);
	mu_check(fgetc(fp) == 0xD8);
	mu_check(fgetc(fp) == 0x4B);
	mu_check(fgetc(fp) == 0x6D);
	mu_check(fgetc(fp) == 0xBA);
	mu_check(fgetc(fp) == 0xE6);
	mu_check(fgetc(fp) == 0x00);
	fclose(fp);
	destroy_huffman_tree(&huffman);
	//
	mu_end();
}

static int _test_write_compressed_simple() {								//Writing a simple compressed file
	mu_start();
	//
	const char* uncompressed = "coding_table_simple.txt";
	const char* compressed = "compressed_simple.bits";
	Frequencies freq = {0};
	const char* error = NULL;
	if(calc_frequencies(freq, uncompressed, &error)) {
		Node* tree = make_huffman_pq(freq);
		TreeNode* huffman = make_huffman_tree(tree);
		BitWriter writer = open_bit_writer(compressed);
		unsigned char file_contents_simple[] = {'x', 'x', 'x', 'y', 'y', 'y', 'y', '\0'};
		write_compressed(huffman, &writer, file_contents_simple);
		close_bit_writer(&writer);
		FILE *file = fopen("compressed_simple.bits", "r");
		mu_check(fgetc(file) == 0x1E);
		destroy_huffman_tree(&huffman);
		fclose(file);
	}
	//
	mu_end();
}

static int _test_write_compressed_hard() {									//Writing a complex compressed file
	mu_start();
	//
	const char* uncompressed = "coding_table_hard.txt";
	const char* compressed = "compressed_hard.bits";
	Frequencies freq = {0};
	const char* error = NULL;
	if(calc_frequencies(freq, uncompressed, &error)) {
		Node* tree = make_huffman_pq(freq);
		TreeNode* huffman = make_huffman_tree(tree);
		BitWriter writer = open_bit_writer(compressed);
		unsigned char file_contents_hard[] = {'h', 'u', 'f', 'f', 'm', 'a', 'n', ' ', 'f', 'l', 'u', 'f', 'f', 's', ' ', 'm', 'a', 'n', 'y', ' ', 'm', 'u', 'm', 's', '\0'};
		write_compressed(huffman, &writer, file_contents_hard);
		close_bit_writer(&writer);
		FILE *file = fopen("compressed_hard.bits", "r");
		mu_check(fgetc(file) == 0x48);
		mu_check(fgetc(file) == 0x1a);
		mu_check(fgetc(file) == 0xf9);
		mu_check(fgetc(file) == 0x8b);
		mu_check(fgetc(file) == 0x03);
		mu_check(fgetc(file) == 0xde);
		mu_check(fgetc(file) == 0xbe);
		mu_check(fgetc(file) == 0xa7);
		mu_check(fgetc(file)== 0xa6);
		mu_check(fgetc(file) == 0xf0);
		destroy_huffman_tree(&huffman);
		fclose(file);
	}
	//
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_frequencies_invalid);
	mu_run(_test_frequencies_valid);
	mu_run(_test_frequencies_recurring);
	mu_run(_test_make_huffman);
	mu_run(_test_coding_table_easy);
	mu_run(_test_coding_table_simple);
	mu_run(_test_coding_table_hard);
	mu_run(_test_write_compressed_simple);
	mu_run(_test_write_compressed_hard);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
