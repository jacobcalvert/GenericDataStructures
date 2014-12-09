#ifdef _DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

class huff_node
{
public:
	char c;
	long long freq;
	bool is_leaf;
	huff_node *left, *right;
	bool operator <(const huff_node &rhs)
	{
		return freq < rhs.freq;
	}
	friend bool operator ==(const huff_node &lhs, const huff_node &rhs)
	{
		return lhs.freq == rhs.freq && lhs.c == rhs.c;
	}
};


bool test_queue();
bool test_stack();
bool test_list();
bool test_minheap();
bool test_maxheap();
bool test_redblack();
bool test_bst();
bool test_hashtable();
bool test_tuple();
bool test_all();

void reverse_a_list();
void bin_sort();
void really_long_list(long long * arr, long long len);
void character_histogram();
void functional_tests();

