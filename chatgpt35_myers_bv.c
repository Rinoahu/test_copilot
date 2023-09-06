#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000
#define BITS_PER_WORD 32

// Divide text length by bits per word
#define TEXT_WORDS(n) ((n)+BITS_PER_WORD-1)/BITS_PER_WORD 

// Mask to extract appropriate bit
#define BIT_MASK(i) (1UL<<(i)&(unsigned long)0xffffffff) 

// Compute approximate matches within distance d
int myers_bit_vector(char* text, int text_len, char* pattern, int pattern_len, int d) {

  unsigned long *text_bits = calloc(TEXT_WORDS(text_len), sizeof(unsigned long));

  // Set bits corresponding to characters in text
  for(int i=0; i<text_len; i++) {
    text_bits[i/BITS_PER_WORD] |= BIT_MASK(i%BITS_PER_WORD); 
  }

  int matches = 0;

  for(int i=d; i<=text_len-pattern_len+d; i++) {

    unsigned long pattern_bits = 0;

    // Set bits corresponding to characters in pattern
    for(int j=0; j<pattern_len; j++) {
      if(text[i+j] == pattern[j])
         pattern_bits |= BIT_MASK(j);
    }

    // Check for approximate match    
    if((text_bits[i/BITS_PER_WORD] & pattern_bits) == pattern_bits)
      matches++;

  }

  free(text_bits);
  return matches;

}

int main() {

  //char text[] = "HEIWORLDHELLO";
  //char pattern[] = "HE";
  char text[] = "HEELLOX";
  char pattern[] = "HELOB";

  int matches = myers_bit_vector(text, strlen(text), pattern, strlen(pattern), 1);

  printf("%d matches found\n", matches);

  return 0;
}
