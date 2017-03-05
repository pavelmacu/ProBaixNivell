#include "codif.h"
#include "itu.h"


const morse_table_t itu_table;
morse_char_t  seq_morse;

int  main()
{	


	itu_init();
	printf("%c\n",to_ascii(itu_table, ".----"));
	to_morse(itu_table, 'R', seq_morse);
	printf("%s\n", seq_morse);

	return 0;
}
