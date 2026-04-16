#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 50 

int n = 1;			 
char prod[max][max]; 

int ntCount = 0; 
char nt[max];	 

int tCount = 0;
char t[max];

typedef struct
{
	char prod[max][max];
	int count;
	int already;
	char sym;
	int transation;
}Item;

Item items[max];
int item_count = 0;

/* ---------- helper functions (kept / minimally changed) ---------- */

int isNt(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int indexOf(char c)
{
    if(isNt(c))
    {
        for (int i = 0; i < ntCount; i++)
        {
            if (nt[i] == c)
            {
                return i;
            }
        }
    }
	else
    {
        for (int i = 0; i < tCount; i++)
        {
            if (t[i] == c)
            {
                return i;
            }
        }
    }

	return -1;
}

int isPresent(char arr[], char c)
{
	int i = 0;
	while (arr[i] != '\0')
	{
		if (arr[i] == c)
			return 1; 
		i++;
	}
	return 0; 
}

void add(char arr[], char c)
{
	if (!isPresent(arr, c)) 
	{
		int i = 0;
		while (arr[i] != '\0') 
		{
			i++;
		}

		arr[i] = c;	   
		arr[i + 1] = '\0'; 
	}
}

/* ---------- Updated / Fixed utility routines ---------- */

/* addNewProd:
   For every production in global 'prod' whose LHS == c,
   construct a production with a dot placed right after "->" (i.e., at the start of the RHS).
   The parameter 'pos' from original code is ignored (keeps calling style),
   because for LR(0) closure we initially place dot at beginning of RHS. 
   Marked as UPDATED.
*/
void addNewProd(Item* temp, char c, int pos) // UPDATED
{
    // initialize temp->count if not already set
    if (temp->count == 0)
    {
        temp->count = 0; // ensure it's zero (if it had garbage)
    }

	for(int i=0;i<n;i++)
	{
		if(prod[i][0] == c)
		{
			char buffer[max];
			int k = 0;
			int len = strlen(prod[i]);
			// copy lhs and "->"
			for (int j = 0; j < len; j++)
			{
				buffer[k++] = prod[i][j];
			}
			buffer[k] = '\0';
			// insert dot after "->", i.e. after index 2 (positions 0:'A',1:'-',2:'>')
			// find "->" position
			int arrowPos = -1;
			for (int j = 0; j < len - 1; j++)
			{
				if (prod[i][j] == '-' && prod[i][j+1] == '>')
				{
					arrowPos = j+1; // position of '>'
					break;
				}
			}
			// build new string with dot after '>'
			char news[max];
			int ni = 0;
			for (int j = 0; j <= arrowPos; j++) // copy upto '>'
			{
				news[ni++] = prod[i][j];
			}
			news[ni++] = '.'; // dot inserted
			for (int j = arrowPos+1; prod[i][j] != '\0'; j++)
			{
				news[ni++] = prod[i][j];
			}
			news[ni] = '\0';

			// add to temp if not already present
			int already = 0;
			for (int r = 0; r < temp->count; r++)
			{
				if (strcmp(temp->prod[r], news) == 0)
				{
					already = 1;
					break;
				}
			}
			if (!already)
			{
				strcpy(temp->prod[temp->count++], news);
			}
		}
	}
}

/* addOldProd:
   Given itemset 'a', find productions in 'a' that have a dot before symbol c
   and for each such production create from that LHS the productions with dot at start
   in b (these are the productions to be added to closure). b should be initialized
   by caller. Marked as UPDATED.
*/
void addOldProd(Item *a, Item *b, char c) // UPDATED
{
    // ensure b initialized
    // b->count should be managed by caller. Just call addNewProd for symbol c.
    addNewProd(b, c, 3); // dot at start of RHS
}

/* copyItem: copy from src to dest */
void copyItem(Item *dest, Item *src) // UPDATED
{
    dest->count = src->count;
    dest->already = src->already;
    dest->sym = src->sym;
    dest->transation = src->transation;
    for (int i = 0; i < src->count; i++)
    {
        strcpy(dest->prod[i], src->prod[i]);
    }
}

/* equalItems: compare two item sets (all productions) */
int equalItems(Item *a, Item *b) // UPDATED
{
    if (a->count != b->count) return 0;
    // For equality, every production in a must be in b
    for (int i = 0; i < a->count; i++)
    {
        int found = 0;
        for (int j = 0; j < b->count; j++)
        {
            if (strcmp(a->prod[i], b->prod[j]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

/* closure: standard LR(0) closure for a single item set.
   It modifies the given Item *I by adding productions B->.gamma whenever some
   production in I has .B (dot before nonterminal B). Marked as UPDATED.
*/
void closure(Item *I) // UPDATED
{
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < I->count; i++)
        {
            char *p = I->prod[i];
            // find dot
            for (int j = 0; p[j] != '\0'; j++)
            {
                if (p[j] == '.')
                {
                    if (p[j+1] != '\0')
                    {
                        char B = p[j+1];
                        if (isNt(B))
                        {
                            // create temp with productions of B with dot at start
                            Item temp;
                            temp.count = 0; temp.already = 0; temp.sym = 0; temp.transation = -1;
                            addNewProd(&temp, B, 3);
                            // add productions from temp to I if they are not present
                            for (int t = 0; t < temp.count; t++)
                            {
                                int found = 0;
                                for (int q = 0; q < I->count; q++)
                                {
                                    if (strcmp(I->prod[q], temp.prod[t]) == 0)
                                    {
                                        found = 1; break;
                                    }
                                }
                                if (!found)
                                {
                                    strcpy(I->prod[I->count++], temp.prod[t]);
                                    changed = 1;
                                }
                            }
                        }
                    }
                    break; // only consider symbol immediately after dot
                }
            }
        }
    }
}

/* GOTO: move dot over symbol X for every production in I where dot precedes X,
   collect those moved productions into J, then perform closure(J). Marked as UPDATED.
*/
void gotoFunc(Item *I, char X, Item *J) // UPDATED
{
    // initialize J
    J->count = 0;
    J->already = 0;
    J->sym = X;
    J->transation = -1;

    for (int i = 0; i < I->count; i++)
    {
        char buffer[max];
        strcpy(buffer, I->prod[i]);
        for (int j = 0; buffer[j] != '\0'; j++)
        {
            if (buffer[j] == '.')
            {
                if (buffer[j+1] != '\0' && buffer[j+1] == X)
                {
                    // move dot one position right
                    buffer[j] = buffer[j+1];
                    buffer[j+1] = '.';
                    // add this production to J if not present
                    int found = 0;
                    for (int q = 0; q < J->count; q++)
                    {
                        if (strcmp(J->prod[q], buffer) == 0)
                        {
                            found = 1; break;
                        }
                    }
                    if (!found)
                    {
                        strcpy(J->prod[J->count++], buffer);
                    }
                }
                break;
            }
        }
    }
    // closure on J
    if (J->count > 0) closure(J);
}

/* findItemIndex: check if itemset X already in items[], return index or -1. Marked as UPDATED. */
int findItemIndex(Item *X) // UPDATED
{
    for (int i = 0; i < item_count; i++)
    {
        if (equalItems(&items[i], X))
            return i;
    }
    return -1;
}

/* Build the canonical LR(0) collection: I0, I1, ...
   This replaces previous broken closure() function and centralizes item construction.
   Marked as UPDATED.
*/
void buildCanonicalCollection() // UPDATED
{
    // items[] and item_count are global; ensure they start clean
    item_count = 0;

    // items[0] already created outside by caller with initial productions (dot at start)
    // but to be safe, if items[0] is empty, we won't proceed.
    if (items[0].count == 0) return;

    closure(&items[0]); // closure I0
    item_count = 1;

    // collect all grammar symbols (terminals + nonterminals) for transitions
    char symbols[max*2];
    symbols[0] = '\0';
    for (int i = 0; i < ntCount; i++) add(symbols, nt[i]);
    for (int i = 0; i < tCount; i++) add(symbols, t[i]);

    // BFS over the item sets
    for (int idx = 0; idx < item_count; idx++)
    {
        Item cur;
        copyItem(&cur, &items[idx]);

        for (int s = 0; symbols[s] != '\0'; s++)
        {
            char X = symbols[s];
            Item J;
            gotoFunc(&cur, X, &J); // compute GOTO(cur, X)
            if (J.count == 0) continue;

            int foundIndex = findItemIndex(&J);
            if (foundIndex == -1)
            {
                // new item set
                items[item_count] = J;
                items[item_count].sym = X;
                items[item_count].transation = idx;
                item_count++;
            }
            else
            {
                // existing item set, we might want to record transitions; keep sym/transation for printing
                // set when first discovered; nothing more required for correctness
            }
        }
    }
}

/* ---------- kept / lightly adapted printing logic ---------- */

int main(int argc, char *argv[])
{
	if (argc != 2) 
	{
		perror("error: file name is not given\n");
		return 1;
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL) 
	{
		perror("Error: cannot open file\n");
		return 1;
	}

	int c;

	// initialize terminal/nonterminal arrays as empty strings
	nt[0] = '\0';
	t[0] = '\0';

	while ((c = fgetc(file)) != EOF)
	{
		fseek(file, -1, SEEK_CUR); 

		fgets(prod[n], max, file); 

		int len = strlen(prod[n]);
		if (len > 0 && prod[n][len - 1] == '\n')
		{
			prod[n][len - 1] = '\0'; 
			len--;
		}

        for(int i=3;i<len;i++) // UPDATED: check from rhs start till end
        {
            if(prod[n][i] == '~')   continue;
            if(!isNt(prod[n][i]) && indexOf(prod[n][i]) == -1)
            {
                add(t, prod[n][i]); // UPDATED: use add to maintain string termination
            }
            if(isNt(prod[n][i]) && indexOf(prod[n][i]) == -1)
            {
                add(nt, prod[n][i]); // UPDATED: collect nonterminals found on RHS too
            }
        }

		if (indexOf(prod[n][0]) == -1)
		{
            add(nt, prod[n][0]); // UPDATED: use add helper
		}
		n++; 
	}

    // ---------- VERY IMPORTANT FIX: set the ntCount and tCount from the filled strings ----------
    ntCount = strlen(nt); // UPDATED: set counts after filling nt[]
    tCount  = strlen(t);  // UPDATED: set counts after filling t[]
    // -----------------------------------------------------------------------

	// new start symbol Z
	prod[0][0] = 'Z';
	prod[0][1] = '-';
	prod[0][2] = '>';
	prod[0][3] = prod[1][0];
	prod[0][4] = '\0';

	// initialize items[0]
	for (int i = 0; i < max; i++) items[0].prod[i][0] = '\0';
	items[0].count = 0;
	items[0].already = 0;
	items[0].sym = 0;
	items[0].transation = -1;

	// create initial item(s) for Z -> .S  (dot at start)
	addNewProd(&items[0], 'Z', 3); // UPDATED: will put dot at start for all Z productions

	// compute canonical collection
	buildCanonicalCollection(); // UPDATED

	// print item sets
	for(int i=0;i<item_count;i++)
	{
		printf("I%d", i);
		if(i != 0)
		{
			printf(" : (I%d, %c)\n",  items[i].transation, items[i].sym);
		}
		else
		{
			printf("\n");
		}

		if(items[i].already != 0)
		{
			printf("same as I%d\n\n", items[i].already);
		}
		else
		{
			for(int j=0;j<items[i].count;j++)
			{
				printf("%s\n", items[i].prod[j]);
			}
			printf("\n");
		}
	}

	fclose(file); 

	return 0;
}
