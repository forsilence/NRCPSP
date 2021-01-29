# include"../include/_M_processing_line.h"
void print_line(size_t len,int total_len)
{
	double mod_size_tmp = total_len/100.0;
	int mod_size = (int)mod_size_tmp + ((mod_size_tmp-(double)(int)mod_size_tmp) >0.0 ? 1:0);
	int in_len = len/mod_size;
	int in_total_len = total_len/mod_size;
	printf("\r");
	printf("[%d|%d]:[",len,total_len);
	for(int i=0;i<in_len;i++){
		printf("#");
	}
	for(int i=in_len;i<in_total_len;++i){
		printf(" ");
	}
	printf("]");
	printf("%f",(double)len/(double)total_len);
}